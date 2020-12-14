#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices

   //Vértices Delanteros
   Tupla3f A(-lado/2,lado/2,lado/2), B(-lado/2,-lado/2,lado/2), C(lado/2,lado/2,lado/2), D(lado/2,-lado/2,lado/2);

   v.push_back(A); //0
   v.push_back(B); //1
   v.push_back(C); //2
   v.push_back(D); //3

   //Vértices Traseros
   Tupla3f E(-lado/2,lado/2,-lado/2), F(-lado/2,-lado/2,-lado/2), G(lado/2,lado/2,-lado/2), H(lado/2,-lado/2,-lado/2);

   v.push_back(E); //4
   v.push_back(F); //5
   v.push_back(G); //6
   v.push_back(H); //7

   //Duplicación de los vertices para aplicar las texturas correctamente en las caras laterales
   //Vertices Delanteros
   v.push_back(A); //8
   v.push_back(B); //9
   v.push_back(C); //10
   v.push_back(D); //11

   //Vertices Traseros
   v.push_back(E); //12
   v.push_back(F); //13
   v.push_back(G); //14
   v.push_back(H); //15

   //Duplicación de los vertices para aplicar las texturas correctamente en las caras superior e inferior
   //Vertices Delanteros
   v.push_back(A); //16
   v.push_back(B); //17
   v.push_back(C); //18
   v.push_back(D); //19

   //Vertices Traseros
   v.push_back(E); //20
   v.push_back(F); //21
   v.push_back(G); //22
   v.push_back(H); //23

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   //Cara Frontal
   Tupla3i f1(1,3,0), f2(3,2,0);

   f.push_back(f1);
   f.push_back(f2);

   //Cara Derecha
   Tupla3i f3(11,15,10), f4(15,14,10);

   f.push_back(f3);
   f.push_back(f4);

   //Cara Izquierda
   Tupla3i f5(9,8,13), f6(13,8,12);

   f.push_back(f5);
   f.push_back(f6);

   //Cara Trasera
   Tupla3i f7(5,4,7), f8(7,4,6);

   f.push_back(f7);
   f.push_back(f8);

   //Cara Superior
   Tupla3i f9(16,18,20), f10(18,22,20);

   f.push_back(f9);
   f.push_back(f10);

   //Cara Inferior
   Tupla3i f11(17,21,19), f12(19,21,23);

   f.push_back(f11);
   f.push_back(f12);
}

void Cubo::calcularCoordTex(){
   Tupla2f t0(0,0), t1(0,1), t2(1,0), t3(1,1), t4(0,0), t5(0,1), t6(1,0), t7(1,1);
   Tupla2f t8(1,1), t9(1,0), t10(1,1), t11(1,0), t12(0,1), t13(0,0), t14(0,1), t15(0,0);
   Tupla2f t16(1,1), t17(1,1), t18(0,1), t19(0,1), t20(1,0), t21(1,0), t22(0,0), t23(0,0);
   ct.push_back(t0);
   ct.push_back(t1);
   ct.push_back(t2);
   ct.push_back(t3);
   ct.push_back(t4);
   ct.push_back(t5);
   ct.push_back(t6);
   ct.push_back(t7);
   ct.push_back(t8);
   ct.push_back(t9);
   ct.push_back(t10);
   ct.push_back(t11);
   ct.push_back(t12);
   ct.push_back(t13);
   ct.push_back(t14);
   ct.push_back(t15);
   ct.push_back(t16);
   ct.push_back(t17);
   ct.push_back(t18);
   ct.push_back(t19);
   ct.push_back(t20);
   ct.push_back(t21);
   ct.push_back(t22);
   ct.push_back(t23);
}