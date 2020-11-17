#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, short eje){
    Tupla3f vertice;
    float dx = radio/num_vert_perfil;
    float dy = altura/num_vert_perfil;
    std::vector<Tupla3f> perfil_original;
    vertice(0) = radio;
    vertice(1) = -(altura/2);
    vertice(2) = 0;
    perfil_original.push_back(vertice);

    for(int i = 0; i < num_vert_perfil; i++){
        vertice(0) -= dx;
        vertice(1) += dy;
        perfil_original.push_back(vertice);
    }

    crearMalla(perfil_original,num_instancias_perf,true,true,eje);
}