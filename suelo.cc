#include "suelo.h"

Suelo::Suelo(float lado){
    Tupla3f v0(0,0,0), v1(lado,0,0), v2(0,lado,0), v3(lado,lado,0);

    v.push_back(v0);
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    Tupla3i f0(0,1,2), f1(1,3,2);

    f.push_back(f0);
    f.push_back(f1);

    Tupla2f t0(0,1), t1(1,1), t2(0,0), t3(1,0);
    
    ct.push_back(t0);
    ct.push_back(t1);
    ct.push_back(t2);
    ct.push_back(t3);
}