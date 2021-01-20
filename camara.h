// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h

//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

class Camara{
    private:
        Tupla3f eye;
        Tupla3f at;
        Tupla3f up;
        Tupla3f eyeFP;

        int tipo; //0: ortogonal || 1: perspectiva

        float left, right, top, bottom, near, far;

        Tupla3f Vdir;
        float modulo;

        bool enSeleccion;

        float giroX;
        float giroY;
    
    public:
        Camara(){};
        Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float near, float far);
        void setObserver();
        void setProjection();
        void rotar(int eje, float d);
        void rotarFirstPerson(int eje, float d);
        void rotarExaminar(int eje, float d);
        void setVolumen(float left, float right, float bottom, float top);
        void redimensionar(float ratio);
        void zoom(float factor);
        void setSeleccion(Tupla3f new_at);
        void unsetSeleccion();
        void mover(bool forward, int dir);
        bool enFP();
};

#endif