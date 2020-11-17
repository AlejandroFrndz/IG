#include "aux.h"
#include "objrevolucion.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, short eje) {
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo, perfil_original);

   crearMalla(perfil_original,num_instancias,tapa_sup,tapa_inf,eje);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil, int num_instancias, bool tapa_sup, bool tapa_inf, short eje) {
   crearMalla(perfil, num_instancias, tapa_sup, tapa_inf,eje);
}

void ObjRevolucion::crearMalla(const std::vector<Tupla3f> &perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf, short eje){
   std::vector<Tupla3f> perfil;
   perfil = perfil_original;

   switch (eje)
   {
      case 1:
         //Rotar en y
         if(perfil_original[0](1) > perfil_original[perfil_original.size()-1](1)){
            std::reverse(perfil.begin(), perfil.end());
         }
      break;

      case 0:
         //Rotar en x
         if(perfil_original[0](0) > perfil_original[perfil_original.size()-1](0)){
            std::reverse(perfil.begin(), perfil.end());
         }
      break;

      case 2: 
         //Rotar en z
         if(perfil_original[0](2) > perfil_original[perfil_original.size()-1](2)){
            std::reverse(perfil.begin(), perfil.end());
         }
      break;
   }

   extraerTapas(perfil,eje);

   crearVertices(perfil,num_instancias,eje);
   crearCaras(perfil,num_instancias,eje);
   v_ntapas = v;
   f_ntapas = f;
   crearTapas(perfil,num_instancias,tapa_sup,tapa_inf,eje);

}

void ObjRevolucion::extraerTapas(std::vector<Tupla3f> &perfil, short eje){
   switch(eje)
   {
      case 1:
         //Rotar en y
         if(perfil[0](0) == 0){
            poloSur = perfil[0];
            perfil.erase(perfil.begin());
         }
         else{
            poloSur(0) = 0;
            poloSur(1) = perfil[0](1);
            poloSur(2) = 0;
         }

         if(perfil[perfil.size()-1](0) == 0){
            poloNorte = perfil[perfil.size()];
            perfil.pop_back();
         }
         else{
            poloNorte(0) = 0;
            poloNorte(1) = perfil[perfil.size()-1](1);
            poloNorte(2) = 0;
         }
      break;

      case 0:
         //Rotar en x
         if(perfil[0](1) == 0){
            poloSur = perfil[0];
            perfil.erase(perfil.begin());
         }
         else{
            poloSur(0) = perfil[0](0);
            poloSur(1) = 0;
            poloSur(2) = 0;
         }

         if(perfil[perfil.size()-1](1) == 0){
            poloNorte = perfil[perfil.size()];
            perfil.pop_back();
         }
         else{
            poloNorte(0) = perfil[perfil.size()-1](0);
            poloNorte(1) = 0;
            poloNorte(2) = 0;
         }
      break;

      case 2:
         //Rotar en z
         if(perfil[0](0) == 0){
            poloSur = perfil[0];
            perfil.erase(perfil.begin());
         }
         else{
            poloSur(0) = 0;
            poloSur(1) = 0;
            poloSur(2) = perfil[0](2);
         }

         if(perfil[perfil.size()-1](0) == 0){
            poloNorte = perfil[perfil.size()];
            perfil.pop_back();
         }
         else{
            poloNorte(0) = 0;
            poloNorte(1) = 0;
            poloNorte(2) = perfil[perfil.size()-1](2);
         }
      break;
   }
}

void ObjRevolucion::crearVertices(const std::vector<Tupla3f> &perfil, int num_instancias, short eje){
   Tupla3f vertice;
   v.clear();
   
   switch(eje){
      case 1:
         //Rotar en y
         for(int i = 0; i < num_instancias; i++){
            for(int j = 0; j < perfil.size(); j++){
               vertice(0) = cos((2 * M_PI *i) /num_instancias) * perfil[j](0);
               vertice(1) = perfil[j](1);
               vertice(2) = sin((2 * M_PI * i) /num_instancias) * perfil[j](0);
               v.push_back(vertice);
            }
         }
      break;

      case 0:
         //Rotar en x
         for(int i = 0; i < num_instancias; i++){
            for(int j = 0; j < perfil.size(); j++){
               vertice(0) = perfil[j][0];
               vertice(1) = cos((2 * M_PI *i) /num_instancias) * perfil[j](1);
               vertice(2) = sin((2 * M_PI * i) /num_instancias) * perfil[j](1);
               v.push_back(vertice);
            }
         }
      break;

      case 2:
         //Rotar en z 
         for(int i = 0; i < num_instancias; i++){
            for(int j = 0; j < perfil.size(); j++){
               vertice(0) = cos((2 * M_PI *i) /num_instancias) * perfil[j](0);
               vertice(1) = sin((2 * M_PI * i) /num_instancias) * perfil[j](0);
               vertice(2) = perfil[j](2);
               v.push_back(vertice);
            }
         }
      break;
   }

}

void ObjRevolucion::crearCaras(const std::vector<Tupla3f> &perfil, int num_instancias, short eje){
   Tupla3i cara;
   unsigned int a, b;
   f.clear();

   switch(eje){
      case 1:
         //Rotar en y
         for(int i = 0; i < num_instancias; i++){
            for(int j = 0; j < perfil.size()-1; j++){
               a = perfil.size() * i + j;
               b = perfil.size() * ((i + 1) % num_instancias) + j;
               cara(0) = b + 1;
               cara(1) = b;
               cara(2) = a;
               f.push_back(cara);

               cara(0) = a + 1;
               cara(1) = b + 1;
               cara(2) = a;
               f.push_back(cara);
            }
         }
      break;

      case 0:
         //Rotar en x
         for(int i = 0; i < num_instancias; i++){
            for(int j = 0; j < perfil.size()-1; j++){
               a = perfil.size() * i + j;
               b = perfil.size() * ((i + 1) % num_instancias) + j;
               cara(0) = b;
               cara(1) = b + 1;
               cara(2) = a;
               f.push_back(cara);

               cara(0) = b + 1;
               cara(1) = a + 1;
               cara(2) = a;
               f.push_back(cara);
            }
         }
      break;

      case 2:
         //Rotar en z
         for(int i = 0; i < num_instancias; i++){
            for(int j = 0; j < perfil.size()-1; j++){
               a = perfil.size() * i + j;
               b = perfil.size() * ((i + 1) % num_instancias) + j;
               cara(0) = b + 1;
               cara(1) = a;
               cara(2) = b;
               f.push_back(cara);

               cara(0) = a + 1;
               cara(1) = a;
               cara(2) = b + 1;
               f.push_back(cara);
            }
         }
      break;
   }
}

void ObjRevolucion::crearTapas(const std::vector<Tupla3f> &perfil, int num_instancias, bool tapa_sup, bool tapa_inf, short eje){
   Tupla3i cara;
   int a, b;
   
   switch(eje){
      case 1:
         //Rotar en y
         if(tapa_inf){
            v.push_back(poloSur);
            a = v.size()-1;
            for(int i = 0; i < num_instancias - 1; i++){
               b = perfil.size() * i;
               cara(0) = a;
               cara(1) = b;
               cara(2) = b + perfil.size();
               f.push_back(cara);
            }

            cara(0) = a;
            cara(1) = perfil.size() * (num_instancias - 1);
            cara(2) = 0;
            f.push_back(cara);
         }

         if(tapa_sup){
            v.push_back(poloNorte);
            a = v.size() - 1;
            
            for(int i = 0; i < num_instancias - 1; i++){
               b = perfil.size() * (i + 1) - 1;
               cara(0) = b + perfil.size();
               cara(1) = b;
               cara(2) = a;
               f.push_back(cara);
            }

            cara(0) = perfil.size() - 1;
            cara(1) = perfil.size() * (num_instancias) - 1;
            cara(2) = a;
            f.push_back(cara);
         }
      break;

      case 0:
         //Rotar en x
         if(tapa_inf){
            v.push_back(poloSur);
            a = v.size()-1;
            for(int i = 0; i < num_instancias - 1; i++){
               b = perfil.size() * i;
               cara(0) = a;
               cara(1) = b + perfil.size();
               cara(2) = b;
               f.push_back(cara);
            }

            cara(0) = a;
            cara(1) = 0;
            cara(2) = perfil.size() * (num_instancias - 1);
            f.push_back(cara);
         }

         if(tapa_sup){
            v.push_back(poloNorte);
            a = v.size() - 1;
            
            for(int i = 0; i < num_instancias - 1; i++){
               b = perfil.size() * (i + 1) - 1;
               cara(0) = b;
               cara(1) = b + perfil.size();
               cara(2) = a;
               f.push_back(cara);
            }

            cara(0) =  perfil.size() * (num_instancias) - 1;
            cara(1) = perfil.size() - 1;
            cara(2) = a;
            f.push_back(cara);
         }
      break;

      case 2:
         //Rotar en z
         if(tapa_inf){
            v.push_back(poloSur);
            a = v.size()-1;
            for(int i = 0; i < num_instancias - 1; i++){
               b = perfil.size() * i;
               cara(0) = a;
               cara(1) = b + perfil.size();
               cara(2) = b;
               f.push_back(cara);
            }

            cara(0) = a;
            cara(1) = 0;
            cara(2) = perfil.size() * (num_instancias - 1);
            f.push_back(cara);
         }

         if(tapa_sup){
            v.push_back(poloNorte);
            a = v.size() - 1;
            
            for(int i = 0; i < num_instancias - 1; i++){
               b = perfil.size() * (i + 1) - 1;
               cara(0) = b + perfil.size();
               cara(1) = a;
               cara(2) = b;
               f.push_back(cara);
            }

            cara(0) = perfil.size() - 1;
            cara(1) = a;
            cara(2) = perfil.size() * (num_instancias) - 1;
            f.push_back(cara);
         }
      break;
   }
}

void ObjRevolucion::draw(bool puntos, bool alambre, bool solido, bool ajedrez, dibujado modo_dibujado, bool tapas)
{
   if(puntos){
      glPointSize(3);
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

      if(modo_dibujado == INMEDIATO){
         if(!tapas){
            this->draw_Inmediato_NTapas(PUNTOS);
         }
         else{
            this->draw_ModoInmediato(PUNTOS);
         }
      }
      else{
         if(!tapas){
            this->draw_Diferido_NTapas(PUNTOS);
         }
         else{
            this->draw_ModoDiferido(PUNTOS);
         }
      }
   }

   if(alambre){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      
      if(modo_dibujado == INMEDIATO){
         if(!tapas){
            this->draw_Inmediato_NTapas(ALAMBRE);
         }
         else{
            this->draw_ModoInmediato(ALAMBRE);
         }
      }
      else{
         if(!tapas){
            this->draw_Diferido_NTapas(ALAMBRE);
         }
         else{
            this->draw_ModoDiferido(ALAMBRE);
         }
      }
   }

   if(solido){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      if(modo_dibujado == INMEDIATO){
         if(!tapas){
            this->draw_Inmediato_NTapas(SOLIDO);
         }
         else{
            this->draw_ModoInmediato(SOLIDO);
         }
      }
      else{
         if(!tapas){
            this->draw_Diferido_NTapas(SOLIDO);
         }
         else{
            this->draw_ModoDiferido(SOLIDO);
         }
      }
   }

   if(ajedrez){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      
      if(modo_dibujado == INMEDIATO){
         if(!tapas){
            this->draw_Ajedrez_Inmediato_NTapas();
         }
         else{
            this->draw_Ajedrez_Inmediato();
         }
      }
      else{
         if(!tapas){
            this->draw_Ajedrez_Diferido_NTapas();
         }
         else{
            this->draw_Ajedrez_Diferido();
         }
      }
   }

}

void ObjRevolucion::draw_Inmediato_NTapas(visualizacion modo_visualizacion)
{
  // visualizar la malla usando glDrawElements,
   glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_FLOAT, 0 , v_ntapas.data());
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
   glDrawElements(GL_TRIANGLES, 3*f_ntapas.size(), GL_UNSIGNED_INT, f_ntapas.data());
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

void ObjRevolucion::draw_Diferido_NTapas(visualizacion modo_visualizacion){
   if(VBO_v_ntapas == 0){
      VBO_v_ntapas = CrearVBO(GL_ARRAY_BUFFER, 3*v_ntapas.size()*sizeof(float), v_ntapas.data());
   }

   if(VBO_f_ntapas == 0){
      VBO_f_ntapas = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f_ntapas.size()*sizeof(int), f_ntapas.data());
   }

   glBindBuffer(GL_ARRAY_BUFFER, VBO_v_ntapas);
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

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_f_ntapas);
   glDrawElements(GL_TRIANGLES, 3*f_ntapas.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

void ObjRevolucion::draw_Ajedrez_Diferido_NTapas(){
   for(int i = 0; i < f_ntapas.size(); i+=2){
      f_pares_ntapas.push_back(f[i]);
      f_impares_ntapas.push_back(f[i+1]);
   }

   if((f_ntapas.size() % 2) != 0){
      f_pares_ntapas.push_back(f[f.size()-1]);
   }

   if(VBO_v_ntapas == 0){
      VBO_v_ntapas = CrearVBO(GL_ARRAY_BUFFER, 3*v_ntapas.size()*sizeof(float), v_ntapas.data());
   }

   glBindBuffer(GL_ARRAY_BUFFER, VBO_v_ntapas);
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

   if(VBO_f_pares_ntapas == 0){
      VBO_f_pares_ntapas = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f_pares_ntapas.size()*sizeof(int), f_pares_ntapas.data());
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_f_pares_ntapas);
   glDrawElements(GL_TRIANGLES, 3*f_pares_ntapas.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   //Caras impares
   if(VBO_c_impares == 0){
      VBO_c_impares = CrearVBO(GL_ARRAY_BUFFER, 3*c_impares.size()*sizeof(float), c_impares.data());
   }

   glBindBuffer(GL_ARRAY_BUFFER, VBO_c_impares);
   glColorPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   if(VBO_f_impares_ntapas == 0){
      VBO_f_impares_ntapas = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f_impares_ntapas.size()*sizeof(int), f_impares_ntapas.data());
   }

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_f_impares_ntapas);
   glDrawElements(GL_TRIANGLES, 3*f_impares_ntapas.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}

void ObjRevolucion::draw_Ajedrez_Inmediato_NTapas(){
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glShadeModel(GL_FLAT);
   glVertexPointer(3, GL_FLOAT, 0, v_ntapas.data());

   for(int i = 0; i < f_ntapas.size(); i+=2){
      f_pares_ntapas.push_back(f[i]);
      f_impares_ntapas.push_back(f[i+1]);
   }

   if((f_ntapas.size() % 2) != 0){
      f_pares_ntapas.push_back(f[f.size()-1]);
   }

   glColorPointer(3,GL_FLOAT,0,c_pares.data());
   glDrawElements(GL_TRIANGLES, 3*f_pares_ntapas.size(), GL_UNSIGNED_INT, f_pares_ntapas.data());

   glColorPointer(3,GL_FLOAT,0,c_impares.data());
   glDrawElements(GL_TRIANGLES, 3*f_impares_ntapas.size(), GL_UNSIGNED_INT, f_impares_ntapas.data());

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}