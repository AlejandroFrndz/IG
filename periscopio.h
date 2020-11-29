// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: periscopio.h
//
// #############################################################################

#ifndef PERISCOPIO_H_INCLUDED
#define PERISCOPIO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cilindro.h"
#include "cubo.h"

class Periscopio : public Malla3D{
    private:
        const float min_h = -35.5;
        Cilindro * cilindro = nullptr;
        Cubo * cubo1 = nullptr;
        Cubo * cubo2 = nullptr;
        Cubo * cubo3 = nullptr;
        float alpha = 0.0;
        float h = min_h;

    public:
        Periscopio();
        void draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado, bool tapas);
        void setColorLentes(float R = 0, float G = 0, float B = 0);
        void setColorMetal(float R = 0.75, float G = 0.75, float B = 0.75);
        void setColorDetalle(float R = 0, float G = 0, float B = 1);
        void setMaterialLentes(Material mat);
        void setMaterialMetal(Material mat);
        void setMaterialDetalle(Material mat);
        void animar(float incremento_alpha, float incremento_h);
};

#endif