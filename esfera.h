// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Esfera.h

//
// #############################################################################

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"


class Esfera : public ObjRevolucion{
    public:
        Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio, short eje=1);
};

#endif