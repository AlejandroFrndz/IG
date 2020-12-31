#include "pierna.h"

Pierna::Pierna(short int sentido){
    cubo1 = new Cubo(100);
    cubo2 = new Cubo(100);
    cubo3 = new Cubo(100);
    cubo4 = new Cubo(100);
    orientacion = sentido;
}

void Pierna::draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado){
    glPushMatrix();
        glPushMatrix();
            glScalef(0.15,1.1,0.3);
            cubo1->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5*orientacion,-55,0);
            glScalef(0.3,0.07,0.6);
            cubo2->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(8*orientacion,0,0);
            glScalef(0.01,0.9,0.2);
            cubo3->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-9.5*orientacion,-42,0);
            glScalef(0.05,0.2,0.3);
            cubo4->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();
    glPopMatrix();
}

void Pierna::drawSeleccion(){
    glPushMatrix();
        glPushMatrix();
            glScalef(0.15,1.1,0.3);
            cubo1->drawSeleccion();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5*orientacion,-55,0);
            glScalef(0.3,0.07,0.6);
            cubo2->drawSeleccion();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(8*orientacion,0,0);
            glScalef(0.01,0.9,0.2);
            cubo3->drawSeleccion();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-9.5*orientacion,-42,0);
            glScalef(0.05,0.2,0.3);
            cubo4->drawSeleccion();
        glPopMatrix();
    glPopMatrix();
}

void Pierna::setColorSeleccion(float R, float G, float B){
    cubo1->setColorSeleccion(R,G,B);
    cubo2->setColorSeleccion(R,G,B);
    cubo3->setColorSeleccion(R,G,B);
    cubo4->setColorSeleccion(R,G,B);
}

void Pierna::setColorDetalle(float R, float G, float B){
    cubo3->establecer_colores(R,G,B);
}

void Pierna::setColorMetal(float R, float G, float B){
    cubo1->establecer_colores(R,G,B);
    cubo2->establecer_colores(R,G,B);
    cubo4->establecer_colores(R,G,B);
}

void Pierna::setMaterialDetalle(Material mat){
    cubo3->setMaterial(mat);
}

void Pierna::setMaterialMetal(Material mat){
    cubo1->setMaterial(mat);
    cubo2->setMaterial(mat);
    cubo4->setMaterial(mat);
}