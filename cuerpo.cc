#include "cuerpo.h"

Cuerpo::Cuerpo(){
    cubo1 = new Cubo(100);
    cubo2 = new Cubo(100);
    cubo3 = new Cubo(100);

    cilindro1 = new Cilindro(50,50,100,50);
    cilindro2 = new Cilindro(50,50,100,50);
    cilindro3 = new Cilindro(50,50,100,50);

    cabeza = new Cabeza();
}

void Cuerpo::draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado, bool tapas){
    glPushMatrix();
        glRotatef(alpha,1,0,0);
        glTranslatef(0,-85,0);

        glPushMatrix();
            glTranslatef(0,100,0);
            cabeza->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado, tapas);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,60,45);
            glScalef(0.4,0.1,0.1);
            cubo1->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,75,45);
            glScalef(0.4,0.1,0.1);
            cubo2->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,90,45);
            glScalef(0.4,0.1,0.1);
            cubo3->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();

        cilindro1->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado, tapas);

        glPushMatrix();
            glTranslatef(-55,85,0);
            glRotatef(-90,0,0,1);
            glScalef(0.3,0.1,0.3);
            cilindro2->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado, tapas);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(55,85,0);
            glRotatef(90,0,0,1);
            glScalef(0.3,0.1,0.3);
            cilindro3->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado, tapas);
        glPopMatrix();
    glPopMatrix();
}

void Cuerpo::drawSeleccion(){
    glPushMatrix();
        glRotatef(alpha,1,0,0);
        glTranslatef(0,-85,0);

        glPushMatrix();
            glTranslatef(0,100,0);
            cabeza->drawSeleccion();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,60,45);
            glScalef(0.4,0.1,0.1);
            cubo1->drawSeleccion();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,75,45);
            glScalef(0.4,0.1,0.1);
            cubo2->drawSeleccion();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,90,45);
            glScalef(0.4,0.1,0.1);
            cubo3->drawSeleccion();
        glPopMatrix();

        cilindro1->drawSeleccion();

        glPushMatrix();
            glTranslatef(-55,85,0);
            glRotatef(-90,0,0,1);
            glScalef(0.3,0.1,0.3);
            cilindro2->drawSeleccion();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(55,85,0);
            glRotatef(90,0,0,1);
            glScalef(0.3,0.1,0.3);
            cilindro3->drawSeleccion();
        glPopMatrix();
    glPopMatrix();
}

void Cuerpo::setColorSeleccion(float R, float G, float B){
    cubo1->setColorSeleccion(R,G,B);
    cubo2->setColorSeleccion(R,G,B);
    cubo3->setColorSeleccion(R,G,B);
    cabeza->setColorSeleccion(R,G,B);
    cilindro1->setColorSeleccion(R,G,B);
    cilindro2->setColorSeleccion(R,G,B);
    cilindro3->setColorSeleccion(R,G,B);
}

void Cuerpo::setColorDetalle(float R, float G, float B){
    cubo1->establecer_colores(R,G,B);
    cubo2->establecer_colores(R,G,B);
    cubo3->establecer_colores(R,G,B);
    cabeza->setColorDetalle(R,G,B);
}

void Cuerpo::setColorLentes(float R, float G, float B){
    cabeza->setColorLentes(R,G,B);
}

void Cuerpo::setColorMetal(float R, float G, float B){
    cilindro1->establecer_colores(R,G,B);
    cilindro2->establecer_colores(R,G,B);
    cilindro3->establecer_colores(R,G,B);
    cabeza->setColorMetal(R,G,B);
}

void Cuerpo::setMaterialDetalle(Material mat){
    cubo1->setMaterial(mat);
    cubo2->setMaterial(mat);
    cubo3->setMaterial(mat);
    cabeza->setMaterialDetalle(mat);
}

void Cuerpo::setMaterialLentes(Material mat){
    cabeza->setMaterialLentes(mat);
}

void Cuerpo::setMaterialMetal(Material mat){
    cilindro1->setMaterial(mat);
    cilindro2->setMaterial(mat);
    cilindro3->setMaterial(mat);
    cabeza->setMaterialMetal(mat);
}

bool Cuerpo::animarCabeza(float v){
    return cabeza->animar(v);
}

bool Cuerpo::animarPeriscopio(float v_a, float v_h){
    return cabeza->animarPeriscopio(v_a,v_h);
}

bool Cuerpo::animar(float v){
    float incremento = v * max_alpha;

    if( (incremento < 0 && alpha > -max_alpha) || (incremento > 0 && alpha < max_alpha) ){
        alpha += incremento;
        return true;
    }

    return false;
}

void Cuerpo::seleccionar(){
    cubo1->seleccionar();
    cubo2->seleccionar();
    cubo3->seleccionar();
    cilindro1->seleccionar();
    cilindro2->seleccionar();
    cilindro3->seleccionar();
    cabeza->seleccionar();
}

void Cuerpo::deseleccionar(){
    cubo1->deseleccionar();
    cubo2->deseleccionar();
    cubo3->deseleccionar();
    cilindro1->deseleccionar();
    cilindro2->deseleccionar();
    cilindro3->deseleccionar();
    cabeza->deseleccionar();
}