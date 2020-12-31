// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: skybox.h

#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED

#include "aux.h"
#include "malla.h"

class Skybox : public Malla3D
{
   public:
   Skybox(float l=1) ;
   void calcularCoordTex();
} ;




#endif