#include "semiesfera.h"

Semiesfera::Semiesfera(const int num_vert_perfil, const int num_instancias_perf, const float radio, short eje){
    Tupla3f vertice;
    float angulo = 0;
    float dangulo = M_PI/(num_vert_perfil*2);
    std::vector<Tupla3f> perfil_original;

    for(int i = 0; i < num_vert_perfil; i++){
        vertice(0) = cos(angulo) * radio;
        vertice(1) = sin(angulo) * radio;
        angulo += dangulo;
        perfil_original.push_back(vertice);
    }

    crearMalla(perfil_original,num_instancias_perf,true,true,eje);
}