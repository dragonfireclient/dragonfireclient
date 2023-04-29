#include "noise.h"
#include <vector3d.h>
#include "mineclone_stronghold.h"
#include <math.h>
#include "constants.h"
#include "util/numeric.h"
#include <stdlib.h>

#include <iostream>

stronghold_ring* mineclone_stronghold::stronghold_rings = new stronghold_ring[8]{
    stronghold_ring {3,1408,2688},
    stronghold_ring {6,4480,5760},
    stronghold_ring {10,7550,8832},
    stronghold_ring {15,10624,11904},
    stronghold_ring {21,13696,14976},
    stronghold_ring {28,16768,18048},
    stronghold_ring {36,19840,21120},
    stronghold_ring {9,22912,24192},
};

int mineclone_stronghold::ringAmount = 8;

int mineclone_stronghold::strongholdsTotal = 128;
int mineclone_stronghold::overworld_min = -62;
int mineclone_stronghold::bedrock_max = -58;

mineclone_stronghold::mineclone_stronghold(uint64_t seed){
    double mclSeed = seed;
    pr = PseudoRandom((uint64_t) mclSeed); //lua 5.1 uses doubles, so you need this to get seeds above 2^52 correct!
}

v3s16* mineclone_stronghold::all(){
    v3s16* positions = new v3s16[strongholdsTotal];
    int current = 0;
    for(int s=0;s<ringAmount;s++){
        stronghold_ring ring = stronghold_rings[s];
        double angle = pr.next();
        angle = ((angle / 32767) * (M_PI*2));
        for(int a=0;a<ring.amount;a++){
            float dist = pr.range(ring.min,ring.max);
            double x =  cos(angle) * dist;
            double y =  pr.range(bedrock_max+1, overworld_min+48);
            double z =  sin(angle) * dist;
            v3d pos3d = v3d(x,y,z);
                        
            v3s16 pos = doubleToInt(pos3d,1.0);
            positions[current] = pos;
            current++;
            angle = fmod(angle + ((M_PI*2) / ring.amount),M_PI*2);
        }
    }
    return positions;
}

float mineclone_stronghold::distance(v3s16 pos1,v3s16 pos2){
    int distX = pos1.X-pos2.X;
    int distZ = pos1.Z-pos2.Z;
    return sqrt((distX*distX) + (distZ*distZ));
}

v3s16* mineclone_stronghold::nearestStrongholds(v3s16 position,int amount){
    v3s16* positions = new v3s16[amount];
    float* distances = new float[amount];
    v3s16* strongholds = all();
    for(int index = 0; index < strongholdsTotal; index++){
        v3s16 stronghold = strongholds[index];
        float dist = distance(position,stronghold);
        for(int aindex = 0;aindex<amount;aindex++){
            if(distances[aindex] == NULL || distances[aindex] > dist){
                distances[aindex] = dist;
                positions[aindex] = stronghold;
                break;
            }
        }
    }
    delete[] strongholds;
    delete[] distances;
    return positions;
}