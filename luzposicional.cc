#include "luzposicional.h"

LuzPosicional::LuzPosicional(const Tupla3f & pos, GLenum lid, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular){
    posicion(0) = pos(0);
    posicion(1) = pos(1);
    posicion(2) = pos(2);
    posicion(3) = 1.0;

    id = lid;
    colorAmbiente = ambiente;
    colorDifuso = difuso;
    colorEspecular = especular;
}

void LuzPosicional::mover(Tupla3f inc){
    posicion(0) += inc(0);
    posicion(1) += inc(1);
    posicion(2) += inc(2);
}

void LuzPosicional::posicionar(Tupla3f pos){
    posicion(0) = pos(0);
    posicion(1) = pos(1);
    posicion(2) = pos(2);
}

void LuzPosicional::printPos(){
    std::cout << "Posición Actual-->\n X: " << posicion(0) << " Y: " << posicion(1) << " Z: " << posicion(2) << std::endl << "Paso: " << paso << std::endl;
}

void LuzPosicional::animar(){
    switch(paso){
        case 1:
            if(posicion(1) < 100){
                mover({0,0.1,0});
            }
            else{
                paso = 2;
            }
        break;

        case 2:
            if(posicion(0) < 100){
                mover({0.1,0,0});
            }
            else{
                paso = 3;
            }
        break;

        case 3:
            if(angulo < 360){
                angulo += 0.36;
                float x, z;
                x = cos(angulo*(M_PI/180)) * 100;
                z = sin(angulo*(M_PI/180)) * 100;
                posicionar({x,posicion(1),z});
            }
            else if (!from5){
                angulo = 0;
                paso = 4;
            }
            else{
                angulo = 0;
                paso = 4;
            }
        break;
        
        case 4:
            if(posicion(0) > 0){
                mover({-0.1,0,0});
            }
            else if (!from5){
                paso = 5;
            }
            else{
                from5 = false;
                paso = 1;
            }
        break;

        case 5:
            if(posicion(1) > -100){
                mover({0,-0.1,0});
            }
            else{
                from5 = true;
                paso = 3;
            }
        break;

    }
}