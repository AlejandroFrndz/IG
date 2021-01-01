// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: r2.h
//
// #############################################################################

#ifndef R2_H_INCLUDED
#define R2_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "pierna.h"
#include "cuerpo.h"

class R2{
    private:
        Cuerpo * cuerpo = nullptr;
        Pierna * piernaD = nullptr;
        Pierna * piernaI = nullptr;
    
    public:
        R2();
        void draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado, bool tapas);
        void drawSeleccion();
        void setColorSeleccion(float R, float G, float B);
        void setColorDetalle(float R = 0.0, float G = 0.0, float B = 1.0);
        void setColorLentes(float R = 0.0, float G = 0.0, float B = 0.0);
        void setColorMetal(float R = 0.75, float G = 0.75, float B = 0.75);
        void setMaterialDetalle(Material mat);
        void setMaterialLentes(Material mat);
        void setMaterialMetal(Material mat);
        bool animarCuerpo(float v);
        bool animarCabeza(float v);
        bool animarPeriscopio(float v_a, float v_h);
        void seleccionar();
        void deseleccionar();
};

#endif