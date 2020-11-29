// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"

typedef enum {PUNTOS, ALAMBRE, SOLIDO, AJEDREZ, LUZ} visualizacion;
typedef enum {INMEDIATO, DIFERIDO} dibujado;

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(visualizacion modo_visualizacion);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(visualizacion modo_visualizacion);

   //función para crear los VBOs para el modo diferido
   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado) ;

   //Funciones para dibujar en modo ajedrez
   void draw_Ajedrez_Inmediato();
   void draw_Ajedrez_Diferido();

   //Función para crear las tablas de colores de los objetos
   void establecer_colores(float R = 1.0, float G = 0.5490, float B = 0.0);

   //Función para establecer el material de la malla
   void setMaterial(Material mat);

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f, f_pares, f_impares; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c_puntos, c_lineas, c_solido, c_pares, c_impares; //Tabla de colores, con 3 floats por color RGB
   std::vector<Tupla3f> nc, nv; // tablas de normales de caras y vértices

   GLuint VBO_v = 0, VBO_f = 0, VBO_f_pares = 0, VBO_f_impares = 0, VBO_c_puntos = 0, VBO_c_lineas = 0, VBO_c_solido = 0, VBO_c_pares = 0, VBO_c_impares = 0, VBO_nv = 0; //VBOs para el modo diferido
   
   Material m; // material para la visualización con iluminación
} ;


#endif
