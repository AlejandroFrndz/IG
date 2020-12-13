// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cuadro.h

//
// #############################################################################

#ifndef CUADRO_H_INLCUDED
#define CUADRO_H_INCLUDED

#include "aux.h"
#include "malla.h"

class Cuadro : public Malla3D{
    public:
        Cuadro(float lado = 1);
};

#endif