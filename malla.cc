#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

//Función para crear las tablas de colores de los elementos
void Malla3D::establecer_colores(){
   Tupla3f azul(0.0,0.0,1.0), rojo(1.0,0.0,0.0), verde(0,1.0,0.0), naranja(1.0,0.5490,0.0);

   for(int i = 0; i < v.size(); i++){
      c_puntos.push_back(azul);
      c_lineas.push_back(verde);
      c_solido.push_back(naranja);
      c_pares.push_back(rojo);
      c_impares.push_back(verde);
   }
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(visualizacion modo_visualizacion)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0 , v.data());
   glEnableClientState(GL_COLOR_ARRAY);
   switch (modo_visualizacion)
   {
   case PUNTOS:
      glColorPointer(3, GL_FLOAT, 0, c_puntos.data());
   break;
   
   case ALAMBRE:
      glColorPointer(3, GL_FLOAT, 0, c_lineas.data());
   break;

   case SOLIDO:
      glColorPointer(3, GL_FLOAT, 0, c_solido.data());
   break;
   }
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, f.data());
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(visualizacion modo_visualizacion)
{
   if(VBO_v == 0){
      VBO_v = CrearVBO(GL_ARRAY_BUFFER, 3*v.size()*sizeof(float), v.data());
   }

   if(VBO_f == 0){
      VBO_f = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f.size()*sizeof(int), f.data());
   }

   glBindBuffer(GL_ARRAY_BUFFER, VBO_v);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_VERTEX_ARRAY);

   switch (modo_visualizacion)
   {
   case PUNTOS:
      if(VBO_c_puntos == 0)
         VBO_c_puntos = CrearVBO(GL_ARRAY_BUFFER, 3*c_puntos.size()*sizeof(float), c_puntos.data());
      glBindBuffer(GL_ARRAY_BUFFER, VBO_c_puntos);
   break;

   case ALAMBRE:
      if(VBO_c_lineas == 0)
         VBO_c_lineas = CrearVBO(GL_ARRAY_BUFFER, 3*c_lineas.size()*sizeof(float), c_lineas.data());
      glBindBuffer(GL_ARRAY_BUFFER, VBO_c_lineas);
   break;

   case SOLIDO:
      if(VBO_c_solido == 0)
         VBO_c_solido = CrearVBO(GL_ARRAY_BUFFER, 3*c_solido.size()*sizeof(float), c_solido.data());
      glBindBuffer(GL_ARRAY_BUFFER, VBO_c_solido);
   break;
   }

   glColorPointer(3, GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_COLOR_ARRAY);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_f);
   glDrawElements(GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   
}

//Creación de VBOs
GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram){
   GLuint id_vbo;
   glGenBuffers(1, &id_vbo);
   glBindBuffer(tipo_vbo, id_vbo);

   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

   glBindBuffer(tipo_vbo, 0);
   return id_vbo;
}

void Malla3D::draw_Ajedrez_Inmediato(){
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glShadeModel(GL_FLAT);
   glVertexPointer(3, GL_FLOAT, 0, v.data());

   for(int i = 0; i < f.size(); i+=2){
      f_pares.push_back(f[i]);
      f_impares.push_back(f[i+1]);
   }

   if((f.size() % 2) != 0){
      f_pares.push_back(f[f.size()-1]);
   }

   glColorPointer(3,GL_FLOAT,0,c_pares.data());
   glDrawElements(GL_TRIANGLES, 3*f_pares.size(), GL_UNSIGNED_INT, f_pares.data());

   glColorPointer(3,GL_FLOAT,0,c_impares.data());
   glDrawElements(GL_TRIANGLES, 3*f_impares.size(), GL_UNSIGNED_INT, f_impares.data());

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

void Malla3D::draw_Ajedrez_Diferido(){
   for(int i = 0; i < f.size(); i+=2){
      f_pares.push_back(f[i]);
      f_impares.push_back(f[i+1]);
   }

   if((f.size() % 2) != 0){
      f_pares.push_back(f[f.size()-1]);
   }

   if(VBO_v == 0){
      VBO_v = CrearVBO(GL_ARRAY_BUFFER, 3*v.size()*sizeof(float), v.data());
   }

   glBindBuffer(GL_ARRAY_BUFFER, VBO_v);
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glEnableClientState(GL_VERTEX_ARRAY);

   glEnableClientState(GL_COLOR_ARRAY);

   //Caras Pares
   if(VBO_c_pares == 0){
      VBO_c_pares = CrearVBO(GL_ARRAY_BUFFER, 3*c_pares.size()*sizeof(float), c_pares.data());
   }

   glBindBuffer(GL_ARRAY_BUFFER, VBO_c_pares);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   if(VBO_f_pares == 0){
      VBO_f_pares = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f_pares.size()*sizeof(int), f_pares.data());
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_f_pares);
   glDrawElements(GL_TRIANGLES, 3*f_pares.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   //Caras impares
   if(VBO_c_impares == 0){
      VBO_c_impares = CrearVBO(GL_ARRAY_BUFFER, 3*c_impares.size()*sizeof(float), c_impares.data());
   }

   glBindBuffer(GL_ARRAY_BUFFER, VBO_c_impares);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   if(VBO_f_impares == 0){
      VBO_f_impares = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f_impares.size()*sizeof(int), f_impares.data());
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_f_impares);
   glDrawElements(GL_TRIANGLES, 3*f_impares.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}


// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw(bool puntos, bool alambre, bool solido, bool ajedrez, dibujado modo_dibujado)
{
   if(puntos){
      glPointSize(3);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

      if(modo_dibujado == INMEDIATO)
         this->draw_ModoInmediato(PUNTOS);
      else{
         this->draw_ModoDiferido(PUNTOS);
      }
      
   }

   if(alambre){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      
      if(modo_dibujado == INMEDIATO)
         this->draw_ModoInmediato(ALAMBRE);
      else{
         this->draw_ModoDiferido(ALAMBRE);
      };
   }

   if(solido){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      if(modo_dibujado == INMEDIATO)
         this->draw_ModoInmediato(SOLIDO);
      else{
         this->draw_ModoDiferido(SOLIDO);
      }
   }

   if(ajedrez){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      
      if(modo_dibujado == INMEDIATO)
         this->draw_Ajedrez_Inmediato();
      else
         this->draw_Ajedrez_Diferido();
   }

}

