#include "luzdireccional.h"

LuzDireccional::LuzDireccional(const Tupla2f & orientacion, GLenum lid, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular){
    alpha = orientacion(0);
    beta = orientacion(1);
    posicion(3) = 0.0;
    reorientar();

    id = lid;
    colorAmbiente = ambiente;
    colorDifuso = difuso;
    colorEspecular = especular;
}

float LuzDireccional::variarAnguloAlpha(float incremento){
    if((incremento > 0 && alpha < 360) || (incremento < 0 && alpha > 0)){
        alpha += incremento;
        reorientar();
    }
    return alpha;
}

float LuzDireccional::variarAnguloBeta(float incremento){
    if((incremento > 0 && beta < 360) || (incremento < 0 && beta > 0)){
        beta += incremento;
        reorientar();
    }
    return beta;
}

void LuzDireccional::reorientar(){
    posicion(0) = sin(beta*(M_PI/180)) * cos(alpha*(M_PI/180));
    posicion(1) = sin(beta*(M_PI/180)) * sin(alpha*(M_PI/180));
    posicion(2) = cos(beta*(M_PI/180));
}