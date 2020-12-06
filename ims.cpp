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

#define KAPACITA_KV_TANKU 200
#define KAPACITA_LZ_TANKU 600

#define SANCA_NA_KONTAMINACIU 0.001

/* zariadenia */
Store Mlyn("Mlyn", 100);
Store Kotol("Varny kotol",800);
Store S_kad("Scedovacia Kad",800);
Store O_kad("Odstrediva Kad",800);
Store Panev("Mladinova panev",800);
Store KV_tank("Kvasny tank",5 * KAPACITA_KV_TANKU);
Store LZ_tank("Leziacky tank",6 * KAPACITA_LZ_TANKU);

/* pocty zariadeni */
int kotol_p;
int s_kad_p;
int o_kad_p;
int panev_p;
int kv_tank_p;
int lz_tank_p;

/* hlavne suroviny */
int slad = 0;           // vstupna
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

class ZelenePivo : public Process {
    /* m = 600 kg */
    void Behavior() {
        Enter(LZ_tank, 600);
        if(typ10) {
            Wait(10 TYZ);
        } else {
            Wait(12 TYZ);
        }

        if(Random() <= SANCA_NA_KONTAMINACIU) {
            /* varka je kontaminovaná */
            Terminate();
        }
        if(typ10){
            leziak10 += 600;
            
        } else {
            leziak12 += 600;
            
        }
        Leave(KV_tank, 600);
        
    }
    
};

class KvasnaMladina : public Process {
    /* m = 200 kg */
    void Behavior() {
        kvasnice -= 1;
        Enter(KV_tank, 200);

        Wait(10 DEN);
        
        if(Random() <= SANCA_NA_KONTAMINACIU) {
            /* varka je kontaminovana */
            Terminate();
        }
        z_pivo += 200;

        /* ak je dostatocne mnozstvo napln LZ_tank */
        while(z_pivo >= 600) {
            z_pivo -= 600;
            (new ZelenePivo)->Activate();
        }
        
        Leave(KV_tank, 200);
    }
};

class Mladina : public Process {
    /* m = 680 kg */
    void Behavior() {
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
    /* m = 680 kg */
    void Behavior() {
        chmel -= 1.36;
        Enter(Panev, 680);

        Wait(2.5 HOD);
        (new Mladina)->Activate();

        Leave(Panev, 680);
    }
};

class Rmut : public Process {
    /* m = 800 kg */
    void Behavior() {
        /* ochladenie */
        Wait(30 MIN);

        /* scedenie */
        Enter(S_kad, 800);

        Wait(3.5 HOD);
        mlato += 120;
        (new Sladina)->Activate();  // 680 kg

        Leave(S_kad, 800);
    }
};

class Vystierka : public Process {
    /* m = 800 kg */
    void Behavior() {
        Enter(Kotol, 800);

        Wait(5 HOD);
        (new Rmut)->Activate();

        Leave(Kotol);
    }
};

class Slad : public Process {
    /* m = 100 kg */
    void Behavior() {

        /* pomletie */
        Enter(Mlyn, 100);

        Wait(5 MIN);

        Leave(Mlyn, 100);

        /* vstup do kotla */
        voda -= 700;
        Enter(Kotol, 800);

        Wait(15 MIN);
        (new Vystierka)->Activate();

        Leave(Kotol, 800);
    }
};

class Start : public Event {
    void Behavior(){
        (new Slad)->Activate();
        Activate(Time);
    }
};


int main(int argc, char *argv[])//int argc, char const *argv[])
{
    string vystup = "output.out";
    int doba_behu = 1 TYZ;
    int c;
    //parse args
    while ((c = getopt (argc, argv, "M:K:S:O:P:k:l")) != -1) 
	{
		switch (c)
		{
			case 'M':
				Mlyn.SetCapacity(atoi(optarg));
				break;
            case 'K':
                kotol_p = atoi(optarg);
                break;
            case 'S':
                s_kad_p = atoi(optarg);
                break;
            case 'O':
                o_kad_p = atoi(optarg);
                break;
            case 'P':
                panev_p = atoi(optarg);
                break;
            case 'k':
                kv_tank_p = atoi(optarg);
                break;
            case 'l':
                lz_tank_p = atoi(optarg);
                break;
			default:
				break;
		}
	}

    
    
    SetOutput(vystup.c_str());

    RandomSeed(time(NULL));

    Init(0, doba_behu);
    
    (new Start)->Activate();

    Run();

    // nejake vypisy jeble
    Print("Vysledky:\n");
    Print("Leziak 10: %dl\n",leziak10);
    Print("Leziak 12: %dl",leziak12);
    //free(vystup.c_str());

    return 0;
}
