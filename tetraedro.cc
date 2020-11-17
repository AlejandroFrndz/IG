#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices
   Tupla3f v0(1,0,-1), v1(-1,0,-1), v2(0,0,1), v3(0,1,0); 
    
   v.push_back(v0);
   v.push_back(v1);
   v.push_back(v2);
   v.push_back(v3);
   // inicializar la tabla de caras o triángulos:
   Tupla3i f1(1,3,0), f2(1,2,3), f3(0,3,2), f4(0,2,1);

   f.push_back(f1);
   f.push_back(f2);
   f.push_back(f3);
   f.push_back(f4);
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

}

