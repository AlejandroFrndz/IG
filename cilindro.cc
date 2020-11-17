#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, short eje){
    Tupla3f vertice;
    float dy = altura/num_vert_perfil;
    vertice(0) = radio;
    vertice(1) = -altura/2;
    vertice(2) = 0;
    std::vector<Tupla3f> perfil_original;
    for(int i = 0; i < num_vert_perfil; i++){
        vertice(1) += dy;
        perfil_original.push_back(vertice);
    }
    crearMalla(perfil_original,num_instancias_perf,true,true,eje);
}