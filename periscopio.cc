#include "periscopio.h"

Periscopio::Periscopio(){
    cilindro = new Cilindro(50,50,100,50);
    cubo1 = new Cubo(100);
    cubo2 = new Cubo(100);
    cubo3 = new Cubo(100);
}

void Periscopio::draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado, bool tapas){
    glPushMatrix();
        glTranslatef(0,h,0);
        glRotatef(alpha,0,1,0);
        glScalef(1,0.6,1);

        glPushMatrix();
            glScalef(0.1,1,0.1);
            cilindro->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado, tapas);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,107.5,0);
            glScalef(0.1,0.15,0.1);
            cubo1->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,107.5,5);
            glScalef(0.05,0.05,0.05);
            cubo2->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,116,0);
            glScalef(0.14,0.02,0.14);
            cubo3->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
        glPopMatrix();
    glPopMatrix();
}

void Periscopio::setColorLentes(float R, float G, float B){
    cubo2->establecer_colores(R,G,B);
}

void Periscopio::setColorMetal(float R, float G, float B){
    cilindro->establecer_colores(R,G,B);
    cubo1->establecer_colores(R,G,B);
}

void Periscopio::setColorDetalle(float R, float G, float B){
    cubo3->establecer_colores(R,G,B);
}

void Periscopio::setMaterialLentes(Material mat){
    cubo2->setMaterial(mat);
}

void Periscopio::setMaterialMetal(Material mat){
    cilindro->setMaterial(mat);
    cubo1->setMaterial(mat);
}

void Periscopio::setMaterialDetalle(Material mat){
    cubo3->setMaterial(mat);
}

void Periscopio::animar(float incremento_alpha, float incremento_h){
    if( (incremento_alpha < 0 && alpha > 0) || (incremento_alpha > 0 && alpha < 360) ){
        alpha += incremento_alpha;
    }

    if( (incremento_h < 0 && h > min_h) || (incremento_h > 0 && h < 0) ){
        h += incremento_h;
    }
}