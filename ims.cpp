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

/* zariadenia */
Store Mlyn("Mlyn", KAPACITA_MLYNU);
Store Kotol("Varny kotol", KAPACITA_KOTLU);
Store S_kad("Scedovacia Kad", KAPACITA_S_KADE);
Store O_kad("Odstrediva Kad", KAPACITA_O_KADE);
Store Panev("Mladinova panev", KAPACITA_PANVE);
Store KV_tank("Kvasny tank", 5 * KAPACITA_KV_TANKU);
Store LZ_tank("Leziacky tank", 6 * KAPACITA_LZ_TANKU);

/* pocty zariadeni */
int mlyn_p;
int kotol_p;
int s_kad_p;
int o_kad_p;
int panev_p;
int kv_tank_p;
int lz_tank_p;

/* hlavne suroviny */
int slad = 100;           // vstupna
int zly_slad = 0;
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
double chmel = 0;       // vstupna
int kvasnice = 0;       // vstupna

/* odpad */
int mlato = 0;
int kal = 0;

using namespace std;

void log(const char* msg) {
    if(verbose) {
        printf("%s\n", msg);
    }
}


class ZelenePivo : public Process {
    public : ZelenePivo() : Process(7) {}
    bool robim;

    /* m = 600 kg */
    void Behavior() {
        printf("Som v Pive\n");
        Enter(LZ_tank, 600);
        robim = typ10;
        typ10 = !typ10;     // zmena vyroby
        if(robim) {
            Wait(10 TYZ);
        } else {
            Wait(12 TYZ);
        }

        if(Random() <= SANCA_NA_KONTAMINACIU) {
            /* varka je kontaminovaná */
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

class KvasnaMladina : public Process {
    public : KvasnaMladina() : Process(6) {}
    
    /* m = 200 kg */
    void Behavior() {
        printf("Som v KVMLAD\n");
        kvasnice -= 1;
        Enter(KV_tank, 200);

        Wait(10 DEN);
        
        if(Random() <= SANCA_NA_KONTAMINACIU) {
            /* varka je kontaminovana */
            Terminate();
        }
        z_pivo += 200;

        /* ak je dostatocne mnozstvo napln LZ_tank */
        printf("Z_PIVO: %d\n", z_pivo);
        while(z_pivo >= 600) {
            z_pivo -= 600;
            (new ZelenePivo)->Activate();
        }
        
        Leave(KV_tank, 200);
    }
};

class Mladina : public Process {
    public : Mladina() : Process(5) {}
    
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
            (new KvasnaMladina)->Activate();
        }

        Leave(O_kad, 680);
    }
};

class Sladina : public Process {
    public : Sladina() : Process(4) {}
    
    /* m = 680 kg */
    void Behavior() {
        log("Sladina");
        chmel -= 1.36;
        Enter(Panev, 680);

        Wait(2.5 HOD);
        (new Mladina)->Activate();
        log("   vytvoril Mladinu");
        Leave(Panev, 680);
    }
};

class Rmut : public Process {
    public : Rmut() : Process(3) {}
    
    /* m = 800 kg */
    void Behavior() {
        log("Rmut");
        /* ochladenie */
        Wait(30 MIN);

        /* scedenie */
        Enter(S_kad, 800);

        Wait(3.5 HOD);
        mlato += 120;
        (new Sladina)->Activate();  // 680 kg
        log("   vytvoril Sladinu");
        Leave(S_kad, 800);
    }
};

class Vystierka : public Process {
    public : Vystierka() : Process(2) {}
    
    /* m = 800 kg */
    void Behavior() {
        log("Vystierka");
        Enter(Kotol, 800);

        Wait(5 HOD);
        (new Rmut)->Activate();
        log("   vytvoril Rmut");
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
        (new Vystierka)->Activate();
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
    string vystup = "output.out";
    int doba_behu = 12 MES;
    int c;
    //parse args
    while ((c = getopt (argc, argv, "s:M:K:S:O:P:k:l:v")) != -1) 
	{
		switch (c)
		{
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

    
    
    SetOutput(vystup.c_str());

    RandomSeed(time(NULL));

    Init(0, doba_behu);
    
    auto start = new Start;
    start->m = slad;
    start->Activate();

    Run();

    // nejake vypisy jeble
    Print("Vysledky:\n");
    Print("Leziak 10: %dl\n",leziak10);
    Print("Leziak 12: %dl\n",leziak12);
    Print("Mlato: %dkg\n",mlato);
    Print("Spotreba vody: %dkg\n",voda);
    Print("Pokazeny slad: %dkg\n",zly_slad);
    //free(vystup.c_str());

    return 0;
}
