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


class stat {
    public:
        stat() {};
        ~stat() {};
        
        u_int max = 0;
        u_int sum = 0;
        u_int count = 0;

        void set_max(u_int new_max) {
            if(new_max > max) {
                max = new_max;
            }
        }

        void update(u_int q) {
            set_max(q);
            sum += q;
            count++;
        }

        double get_avg() {
            double avg = sum / (double)count;
            return avg;
        }

        int get_max() {
            return (int)max;
        }
};

class Stats {
    public:
        Stats() {};
        ~Stats() {};

        stat mlyn;
        stat kotol;
        stat s_kad;
        stat o_kad;
        stat panev;
        stat kv_tank;
        stat lz_tank;
};