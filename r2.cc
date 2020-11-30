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