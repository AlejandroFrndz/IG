#include "camara.h"

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float near, float far){
    this->eye = eye;
    this->eyeFP = eye;
    this->at = at;
    this->up = up;
    this->tipo = tipo;
    this->near = near;
    this->far = far;
    Vdir = at - eye;
    modulo = sqrt(pow(Vdir(0),2) + pow(Vdir(1),2) + pow(Vdir(2),2) );

    giroX = 0;
    giroY = 0;

    enSeleccion = false;
}

void Camara::setObserver(){
    gluLookAt(eye(0),eye(1),eye(2),at(0),at(1),at(2),up(0),up(1),up(2));
}

void Camara::setProjection(){
    if(tipo == 0){
        glOrtho(left,right,bottom,top,near,far);
    }
    else{
        glFrustum(left,right,bottom,top,near,far);
    }
}

void Camara::rotar(int eje, float d){
    if(!enSeleccion){
        rotarFirstPerson(eje,d);
    }
    else{
        rotarExaminar(eje,d);
    }
}

void Camara::rotarFirstPerson(int eje, float d){
    Tupla3f at_aux = at - eye;
    float modulo = sqrt(at_aux.lengthSq());

    if(eje == 0){
        at_aux(1) = cos(d*(M_PI/180)) * at_aux(1) - sin(d*(M_PI/180)) * at_aux(2);
        at_aux(2) = sin(d*(M_PI/180)) * at_aux(1) + cos(d*(M_PI/180)) * at_aux(2);
    }
    else{
        at_aux(0) = cos(d*(M_PI/180)) * at_aux(0) + sin(d*(M_PI/180)) * at_aux(2);
        at_aux(2) = -sin(d*(M_PI/180)) * at_aux(0) + cos(d*(M_PI/180)) * at_aux(2);
    }

    at_aux = at_aux.normalized() * modulo;

    at = at_aux + eye;
}

void Camara::rotarExaminar(int eje, float d){
    Tupla3f eye_aux = eye - at;
    float modulo = sqrt(eye_aux.lengthSq());

    if(eje == 0){
        eye_aux(1) = cos(d*(M_PI/180)) * eye_aux(1) - sin(d*(M_PI/180)) * eye_aux(2);
        eye_aux(2) = sin(d*(M_PI/180)) * eye_aux(1) + cos(d*(M_PI/180)) * eye_aux(2);
    }
    else{
        eye_aux(0) = cos(d*(M_PI/180)) * eye_aux(0) + sin(d*(M_PI/180)) * eye_aux(2);
        eye_aux(2) = -sin(d*(M_PI/180)) * eye_aux(0) + cos(d*(M_PI/180)) * eye_aux(2);
    }

    eye_aux = eye_aux.normalized() * modulo;

    eye = eye_aux + at;
}

void Camara::setSeleccion(Tupla3f new_at){
    eye = eyeFP;
    at = new_at;
    enSeleccion = true;
}

void Camara::unsetSeleccion(){
    if(enSeleccion){
        eye = eyeFP;
        at = {0,0,0};
    }

    enSeleccion = false;
}

void Camara::setVolumen(float left, float right, float bottom, float top){
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
}

void Camara::redimensionar(float ratio){
    left = bottom * ratio;
    right = top * ratio;
}

void Camara::zoom(float factor){
    left *= factor;
    right *= factor;
    bottom *= factor;
    top *= factor;
}