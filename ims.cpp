/*
 * IMS projekt - simulácia výroby piva
 * Adam Ševšík - xsevci64
 * Martin Hiner - xhiner00
 */

#include <stdlib.h>
#include <iostream>
#include "simlib.h"
#include <unistd.h>
#include <string>


/* konstanty */
#define MIN *1
#define HOD MIN*60
#define DEN HOD*24
#define TYZ DEN*7
#define MES TYZ*4

#define KAPACITA_MLYNU      100
#define KAPACITA_KOTLU      800
#define KAPACITA_S_KADE     800
#define KAPACITA_O_KADE     800
#define KAPACITA_PANVE      800
#define KAPACITA_KV_TANKU   200
#define KAPACITA_LZ_TANKU   600

#define SANCA_NA_KONTAMINACIU 0.001

bool verbose = false;   // for debug purposes
double init_chmel;

/* zariadenia */
Store Mlyn("Mlyn", KAPACITA_MLYNU);
Store Kotol("Varny kotol", KAPACITA_KOTLU);
Store S_kad("Scedovacia Kad", KAPACITA_S_KADE);
Store O_kad("Odstrediva Kad", KAPACITA_O_KADE);
Store Panev("Mladinova panev", KAPACITA_PANVE);
Store KV_tank("Kvasny tank", 5 * KAPACITA_KV_TANKU);
Store LZ_tank("Leziacky tank", 6 * KAPACITA_LZ_TANKU);

/* pocty zariadeni */
int mlyn_p = 1;
int kotol_p = 1;
int s_kad_p = 1;
int o_kad_p = 1;
int panev_p = 1;
int kv_tank_p = 5;
int lz_tank_p = 6;

/* hlavne suroviny */
int slad = 100;           // vstupna
int pomlety_slad = 0;
int vystierka = 0;
int rmut = 0;
int sladina = 0;
int mladina = 0;        // in use
int z_pivo = 0;         // in use
int leziak10 = 0;
int leziak12 = 0;

bool typ10 = true;

/* vedlajsie suroviny */
int voda = 0;           // vstupna
double chmel = 2;       // vstupna
int kvasnice = 0;       // vstupna

/* odpad */
int mlato = 0;
int kal = 0;
int zly_slad = 0;
int kontam_pivo = 0;

using namespace std;

void log(const char* msg) {
    if(verbose) {
        printf("%s\n", msg);
    }
}


class Lezanie : public Process {
    public : Lezanie() : Process(7) {}
    bool robim;

    /* m = 600 kg */
    void Behavior() {
        printf("Som v Pive\n");
        Enter(LZ_tank, 600);
        robim = typ10;
        typ10 = !typ10;     // zmena vyroby
        if(robim) {
            Wait(Uniform(30 DEN, 40 DEN));
        } else {
            Wait(Uniform(10 TYZ, 12 TYZ));
        }

        if(Random() <= SANCA_NA_KONTAMINACIU) {
            /* varka je kontaminovaná */
            kontam_pivo += 600;
            Terminate();
        }
        if(robim){
            leziak10 += 600;
            
        } else {
            leziak12 += 600;
            
        }

        Leave(LZ_tank, 600);
        printf("Zrobil som 600l piva\n");
    }
    
};

class Kvasenie : public Process {
    public : Kvasenie() : Process(6) {}
    
    /* m = 200 kg */
    void Behavior() {
        printf("Som v KVMLAD\n");
        kvasnice += 1;
        Enter(KV_tank, 200);

        Wait(10 DEN);
        
        if(Random() <= SANCA_NA_KONTAMINACIU) {
            /* varka je kontaminovana */
            kontam_pivo += 200;
            Terminate();
        }
        z_pivo += 200;

        /* ak je dostatocne mnozstvo napln LZ_tank */
        printf("Z_PIVO: %d\n", z_pivo);
        while(z_pivo >= 600) {
            z_pivo -= 600;
            (new Lezanie)->Activate();
        }
        
        Leave(KV_tank, 200);
    }
};

class Chladenie : public Process {
    public : Chladenie() : Process(5) {}
    
    /* m = 680 kg */
    void Behavior() {
        printf("Som v Mladine\n");
        /* cistenie */
        Enter(O_kad, 680);
        
        Wait(1 HOD);
        kal += 3;

        /* ochladenie */
        Wait(30 MIN);
        mladina += 680;

        /* rozdel vytvorenu mladinu na diely do tankov*/
        while(mladina >= 200) {
            mladina -= 200;
            (new Kvasenie)->Activate();
        }

        Leave(O_kad, 680);
    }
};

class Chmelovar : public Process {
    public : Chmelovar() : Process(4) {}
    
    /* m = 680 kg */
    void Behavior() {
        log("Chmelovar");
        chmel -= 1.36;
        Enter(Panev, 680);

        Wait(2.5 HOD);
        (new Chladenie)->Activate();
        log("   vytvoril Mladinu");
        Leave(Panev, 680);
    }
};

class Scedzovanie : public Process {
    public : Scedzovanie() : Process(3) {}
    
    /* m = 800 kg */
    void Behavior() {
        log("Scedzovanie");
        /* ochladenie */
        Wait(30 MIN);

        /* scedenie */
        Enter(S_kad, 800);

        Wait(3.5 HOD);
        mlato += 120;
        (new Chmelovar)->Activate();  // 680 kg
        log("   vytvoril Sladinu");
        Leave(S_kad, 800);
    }
};

class Rmutovanie : public Process {
    public : Rmutovanie() : Process(2) {}
    
    /* m = 800 kg */
    void Behavior() {
        log("Rmutovanie");
        Enter(Kotol, 800);

        Wait(Uniform(5 HOD,5.5 HOD));
        (new Scedzovanie)->Activate();
        log("   vytvoril Scedzovanie");
        Leave(Kotol, 800);
    }
};

class Slad : public Process {
    public : Slad() : Process(1) {}
    long int cas;
    
    /* m = 100 kg */
    void Behavior() {
        log("Slad");
        /* pomletie */
        Enter(Mlyn, 100);

        Wait(Uniform(5 MIN,8 MIN));

        Leave(Mlyn, 100);

        /* vstup do kotla */
        cas = Time;
        voda += 700;
        Enter(Kotol, 800);
        printf("POCET PROCESOV KOTOL V RADE KOTOL:%d\n",Kotol.QueueLen());
        if(Time - cas > (3 MES)) {
            /* pomletý slad sa pokazil */
            zly_slad += Kotol.QueueLen() * 100;
            Terminate();
        }

        Wait(15 MIN);
        (new Rmutovanie)->Activate();
        log("   vytvoril Vystierku");

        Leave(Kotol, 800);

    }
};

class Start : public Event {
    public: int m;
    
    void Behavior(){
        if(!KV_tank.Full() && m >= 100) {
            m -= 100;
            (new Slad)->Activate();
        }

        Activate(Time + 1 HOD);
    }
};


int main(int argc, char *argv[])//int argc, char const *argv[])
{
    string vystup = "result.md";
    int doba_behu = 12 MES;
    int c;
    //parse args
    while ((c = getopt (argc, argv, "o:c:s:M:K:S:O:P:k:l:v")) != -1) 
	{
		switch (c)
		{
            case 'o':
                vystup = optarg;
                break;
            case 'c':
                chmel = atoi(optarg);
                break;
            case 's':
                slad = atoi(optarg);
                break;
			case 'M':
                mlyn_p = atoi(optarg);
				Mlyn.SetCapacity(KAPACITA_MLYNU * mlyn_p);
				break;
            case 'K':
                kotol_p = atoi(optarg);
                Kotol.SetCapacity(KAPACITA_KOTLU * kotol_p);
                break;
            case 'S':
                s_kad_p = atoi(optarg);
                S_kad.SetCapacity(KAPACITA_S_KADE * s_kad_p);
                break;
            case 'O':
                o_kad_p = atoi(optarg);
                O_kad.SetCapacity(KAPACITA_O_KADE * o_kad_p);
                break;
            case 'P':
                panev_p = atoi(optarg);
                Panev.SetCapacity(KAPACITA_PANVE * panev_p);
                break;
            case 'k':
                kv_tank_p = atoi(optarg);
                KV_tank.SetCapacity(KAPACITA_KV_TANKU * kv_tank_p);
                break;
            case 'l':
                lz_tank_p = atoi(optarg);
                LZ_tank.SetCapacity(KAPACITA_LZ_TANKU * lz_tank_p);
                break;
            case 'v':
                verbose = true;
                break;
			default:
				break;
		}
	}
    
    init_chmel = chmel;

    SetOutput(vystup.c_str());

    RandomSeed(time(NULL));

    Init(0, doba_behu);
    
    auto start = new Start;
    start->m = slad;
    start->Activate();

    Run();

    Print("# Vysledky:\n");
    Print("## Informacie o zariadeniach:\n");
    Print("Zariadenie | Pocet | Kapacita | Rada\n");
    Print(":--- | :---: | :---: | ---:\n");
    Print("Mlyn:             | %d | %d kg | %d\n", mlyn_p, KAPACITA_MLYNU, Mlyn.QueueLen());
    Print("Varný kotol:      | %d | %d kg | %d\n", kotol_p, KAPACITA_KOTLU, Kotol.QueueLen());
    Print("Scedovacia kad:   | %d | %d kg | %d\n", s_kad_p, KAPACITA_S_KADE, S_kad.QueueLen());
    Print("Odstrediva kad:   | %d | %d kg | %d\n", o_kad_p, KAPACITA_O_KADE, O_kad.QueueLen());
    Print("Mladinova panev:  | %d | %d kg | %d\n", panev_p, KAPACITA_PANVE, Panev.QueueLen());
    Print("Kvasny tank:      | %d | %d kg | %d\n", kv_tank_p, KAPACITA_KV_TANKU, KV_tank.QueueLen());
    Print("Leziacky tank:    | %d | %d kg | %d\n---\n", lz_tank_p, KAPACITA_LZ_TANKU, LZ_tank.QueueLen());
    Print("## Vstupne suroviny:\n");
    Print("Surovina | Hmotnost\n");
    Print(":--- | ---:\n");
    Print("Slad:  | %d kg\n", slad);
    Print("Chmel: | %.2f kg\n---\n", init_chmel);
    Print("## Spotrebované suroviny: \n");
    Print("Surovina | Hmotnost\n");
    Print(":--- | ---:\n");
    Print("Slad:  | %d kg\n", slad - start->m);
    Print("Chmel: | %.2f kg\n", (double)init_chmel - chmel);
    Print("Voda:     | %d l\n", voda);
    Print("Kvasnice: | %d l\n---\n", kvasnice);
    Print("## Medziprodukty a odpad: \n");
    Print("Typ | Hmotnost\n");
    Print(":--- | ---:\n");
    Print("Mlato:                | %d kg\n", mlato);
    Print("Kal:                  | %d kg\n", kal);
    Print("Pokazeý slad:         | %d kg\n", zly_slad);
    Print("Kontaminovane pivo:   | %d l\n---\n", kontam_pivo);
    Print("## Vyrobené pivo:\n");
    Print("Typ | Hmotnost\n");
    Print(":--- | ---:\n");
    Print("Vycap 10:  | %d l\n",leziak10);
    Print("Leziak 12: | %d l\n",leziak12);
    
    //free(vystup.c_str());

    return 0;
}
