// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cuerpo.h
//
// #############################################################################

#ifndef CUERPO_H_INCLUDED
#define CUERPO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cilindro.h"
#include "cubo.h"
#include "cabeza.h"

class Cuerpo{
    private:
        const float max_alpha = 15;
        Cubo * cubo1 = nullptr;
        Cubo * cubo2 = nullptr;
        Cubo * cubo3 = nullptr;
        Cilindro * cilindro1 = nullptr;
        Cilindro * cilindro2 = nullptr;
        Cilindro * cilindro3 = nullptr;
        Cabeza * cabeza = nullptr;
        float alpha = 0;

    public:
        Cuerpo();
        void draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado, bool tapas);
        void drawSeleccion();
        void setColorSeleccion(float R, float G, float B);
        void setColorDetalle(float R = 0.0, float G = 0.0, float B = 1.0);
        void setColorLentes(float R = 0.0, float G = 0.0, float B = 0.0);
        void setColorMetal(float R = 0.75, float G = 0.75, float B = 0.75);
        void setMaterialDetalle(Material mat);
        void setMaterialLentes(Material mat);
        void setMaterialMetal(Material mat);
        bool animar(float v);
        bool animarCabeza(float v);
        bool animarPeriscopio(float v_a, float v_h);
        void seleccionar();
        void deseleccionar();
};

#endif