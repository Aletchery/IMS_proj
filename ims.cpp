/*
 * IMS projekt - simulácia výroby piva
 * Adam Ševšík - xsevci64
 * Martin Hiner - xhiner00
 */

#include <stdlib.h>
#include <iostream>
#include "simlib.h"

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


int main()//int argc, char const *argv[])
{
    char *vystup = "output";
    int doba_behu = 1 MES;
    
    //parse args
    
    //SetOutput(vystup);
    
    RandomSeed(time(NULL));
    //Init(0, doba_behu);

    // alebo nejaky iny spustac
    while(slad >= 100) {
        slad -= 100;
        (new Slad)->Activate();
    }

    //Run();

    // nejake vypisy jeble

    free(vystup);

    return 0;
}
