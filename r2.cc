#include "r2.h"

R2::R2(){
    cuerpo = new Cuerpo();
    piernaD = new Pierna(1);
    piernaI = new Pierna(-1);
}

void R2::draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado, bool tapas){
    glPushMatrix();
        cuerpo->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado, tapas);

        glPushMatrix();
            glTranslatef(60,-40,0);
            piernaD->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-60,-40,0);
            piernaI->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();
    glPopMatrix();
}

void R2::drawSeleccion(){
    glPushMatrix();
        cuerpo->drawSeleccion();

        glPushMatrix();
            glTranslatef(60,-40,0);
            piernaD->drawSeleccion();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-60,-40,0);
            piernaI->drawSeleccion();
        glPopMatrix();
    glPopMatrix();
}

void R2::setColorSeleccion(float R, float G, float B){
    cuerpo->setColorSeleccion(R,G,B);
    piernaD->setColorSeleccion(R,G,B);
    piernaI->setColorSeleccion(R,G,B);
}

void R2::setColorDetalle(float R, float G, float B){
    cuerpo->setColorDetalle(R,G,B);
    piernaD->setColorDetalle(R,G,B);
    piernaI->setColorDetalle(R,G,B);
}

void R2::setColorLentes(float R, float G, float B){
    cuerpo->setColorLentes(R,G,B);
}

void R2::setColorMetal(float R, float G, float B){
    cuerpo->setColorMetal(R,G,B);
    piernaD->setColorMetal(R,G,B);
    piernaI->setColorMetal(R,G,B);
}

void R2::setMaterialDetalle(Material mat){
    cuerpo->setMaterialDetalle(mat);
    piernaD->setMaterialDetalle(mat);
    piernaI->setMaterialDetalle(mat);
}

void R2::setMaterialLentes(Material mat){
    cuerpo->setMaterialLentes(mat);
}

void R2::setMaterialMetal(Material mat){
    cuerpo->setMaterialMetal(mat);
    piernaD->setMaterialMetal(mat);
    piernaI->setMaterialMetal(mat);
}

bool R2::animarCuerpo(float v){
    return cuerpo->animar(v);
}

bool R2::animarCabeza(float v){
    return cuerpo->animarCabeza(v);
}

bool R2::animarPeriscopio(float v_a, float v_h){
    return cuerpo->animarPeriscopio(v_a,v_h);
}