// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: luzdireccional.h

//
// #############################################################################

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "luz.h"

class LuzDireccional : public Luz {
    protected:
        float alpha;
        float beta;
        void reorientar();
    public:
        LuzDireccional(const Tupla2f & orientacion, GLenum lid, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular);
        float variarAnguloAlpha(float incremento);
        float variarAnguloBeta(float incremento);
};

#endif