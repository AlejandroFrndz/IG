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
    private:
        unsigned int paso = 1;
        float angulo = 0;
        bool from5 = false;
        void mover(Tupla3f inc);
        void posicionar(Tupla3f pos);
    public:
        LuzPosicional(const Tupla3f & pos, GLenum lid, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular);
        void animar();
        void printPos();
};

#endif