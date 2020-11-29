// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cabeza.h
//
// #############################################################################

#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INLCUDED

#include "aux.h"
#include "periscopio.h"
#include "malla.h"
#include "semiesfera.h"
#include "cubo.h"

class Cabeza : public Malla3D{
    private:
        Periscopio * periscopio = nullptr;
        Semiesfera * semiesfera = nullptr;
        Semiesfera * semiesfera_ojo = nullptr;
        Cubo * cubo_ojo = nullptr;
        float alpha = 0;

    public:
        Cabeza();
        void draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado, bool tapas);
        void setColorDetalle(float R = 0.0, float G = 0.0, float B = 1.0);
        void setColorLentes(float R = 0.0, float G = 0.0, float B = 0.0);
        void setColorMetal(float R = 0.75, float G = 0.75, float B = 0.75);
        void setMaterialDetalle(Material mat);
        void setMaterialLentes(Material mat);
        void setMaterialMetal(Material mat);
        void animar(float incremento);
        void animarPeriscopio(float incremento_alpha, float incremento_h);
};

#endif