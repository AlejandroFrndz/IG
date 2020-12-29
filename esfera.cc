#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio, short eje){
    Tupla3f vertice;
    float angulo = -(M_PI/2);
    float dangulo = M_PI/num_vert_perfil;
    std::vector<Tupla3f> perfil_original;
    /*
    vertice(2) = 0;
    vertice(1) = -radio;
    vertice(0) = 0;
    perfil_original.push_back(vertice);
    angulo += dangulo;*/

    vertice(2) = 0.0;

    for(int i = 0; i < num_vert_perfil; i++){
        vertice(0) = cos(angulo) * radio;
        vertice(1) = sin(angulo) * radio;
        angulo += dangulo;
        perfil_original.push_back(vertice);
    }

    crearMalla(perfil_original,num_instancias_perf,true,true,eje);
}