// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: objrevolucion.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "ply_reader.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
    public:
        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, short eje=1) ;
        ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, short eje=1) ;
        void draw (bool puntos, bool alambre, bool solido, bool ajedrez, dibujado modo_dibujado, bool tapas);

    protected:
        Tupla3f poloNorte, poloSur;
        int ntapas_f, ntapas_f_par = 0, ntapas_f_impar = 0;
        void crearMalla(const std::vector<Tupla3f> &perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf, short eje);
        void extraerTapas(std::vector<Tupla3f> &perfil, short eje);
        void crearVertices(const std::vector<Tupla3f> &perfil, int num_instancias, short eje);
        void crearCaras(const std::vector<Tupla3f> &perfil, int num_instancias, short eje);
        void crearTapas(const std::vector<Tupla3f> &perfil, int num_instancias, bool tapa_sup, bool tapa_inf, short eje);
        void draw_Diferido_NTapas(visualizacion modo_visualizacion);
        void draw_Inmediato_NTapas(visualizacion modo_visualizacion);
        void draw_Ajedrez_Diferido_NTapas();
        void draw_Ajedrez_Inmediato_NTapas();
} ;




#endif
