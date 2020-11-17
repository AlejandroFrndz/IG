#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices

   //Vértices Inferiores
   Tupla3f v0(lado/2,-lado/2,lado/2), v1(lado/2,-lado/2,-lado/2), v2(-lado/2,-lado/2,-lado/2), v3(-lado/2,-lado/2,lado/2);

   v.push_back(v0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);

   //Vértices Superiores
   Tupla3f v4(lado/2,lado/2,lado/2), v5(lado/2,lado/2,-lado/2), v6(-lado/2,lado/2,-lado/2), v7(-lado/2,lado/2,lado/2);

   v.push_back(v4);
   v.push_back(v5);
   v.push_back(v6);
   v.push_back(v7);

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   //Cara Frontal
   Tupla3i f1(0,4,3), f2(3,4,7);

   f.push_back(f1);
   f.push_back(f2);

   //Cara Derecha
   Tupla3i f3(0,1,5), f4(5,4,0);

   f.push_back(f3);
   f.push_back(f4);

   //Cara Izquierda
   Tupla3i f5(3,7,6), f6(6,2,3);

   f.push_back(f5);
   f.push_back(f6);

   //Cara Trasera
   Tupla3i f7(1,2,6), f8(6,5,1);

   f.push_back(f7);
   f.push_back(f8);

   //Cara Superior
   Tupla3i f9(4,5,7), f10(5,6,7);

   f.push_back(f9);
   f.push_back(f10);

   //Cara Inferior
   Tupla3i f11(0,3,1), f12(3,2,1);

   f.push_back(f11);
   f.push_back(f12);
}
