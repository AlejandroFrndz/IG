// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: pierna.h
//
// #############################################################################

#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"

class Pierna{
    private:
        Cubo * cubo1 = nullptr;
        Cubo * cubo2 = nullptr;
        Cubo * cubo3 = nullptr;
        Cubo * cubo4 = nullptr;
        short int orientacion;  // 1 = Pierna Derecha, -1 = Pierna Izquierda
    
    public:
        Pierna(short int sentido);
        void draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado);
        void setColorDetalle(float R = 0.0, float G = 0.0, float B = 1.0);
        void setColorMetal(float R = 0.75, float G = 0.75, float B = 0.75);
        void setMaterialDetalle(Material mat);
        void setMaterialMetal(Material mat);

};

#endif