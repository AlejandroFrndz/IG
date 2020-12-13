// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: textura.h

//
// #############################################################################

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"

class Textura{
    private:
        GLuint idTex;
        unsigned char * data;
        int width, height;
    public:
        Textura(){}
        Textura(std::string archivo);
        void activar();
};

#endif