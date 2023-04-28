#pragma once

#include "noise.h"
#include <vector3d.h>

struct stronghold_ring{
    int amount;
    int min;
    int max;
};


class mineclone_stronghold{
    private:
        PseudoRandom pr;

        float distance(v3s16 pos1,v3s16 pos2);
    public:
        static stronghold_ring* stronghold_rings;
        static int ringAmount;
        static int strongholdsTotal;
        static int bedrock_max;
        static int overworld_min;

        mineclone_stronghold(uint64_t seed); //not too sure if this should be unsigned

        v3s16* all(void);
        v3s16* nearestStrongholds(v3s16 position, int amount);
};