#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f & pos, GLenum lid, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular){
    posicion(0) = pos(0);
    posicion(1) = pos(1);
    posicion(2) = pos(2);
    posicion(3) = 1.0;

    id = lid;
    colorAmbiente = ambiente;
    colorDifuso = difuso;
    colorEspecular = especular;
}