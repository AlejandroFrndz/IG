// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzposicional.h

//
// #############################################################################

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "luz.h"

class LuzPosicional : public Luz{
    public:
        LuzPosicional(const Tupla3f & pos, GLenum lid, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular);
};

#endif