// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: suelo.h

//
// #############################################################################

#ifndef SUELO_H_INCLUDED
#define SUELO_H_INCLUDED

#include "aux.h"
#include "malla.h"

class Suelo : public Malla3D{
    public:
        Suelo(float lado = 1);
};

#endif