#include "cabeza.h"

Cabeza::Cabeza(){
    periscopio = new Periscopio();
    cubo_ojo = new Cubo(100);
    semiesfera = new Semiesfera(50,50,50);
    semiesfera_ojo = new Semiesfera(50,50,50);
}

void Cabeza::draw(bool puntos, bool alambre, bool solido, bool ajedrez, bool smooth, bool flat, dibujado modo_dibujado, bool tapas){
    glPushMatrix();
        glRotatef(alpha,0,1,0);

        //Periscopio
        glPushMatrix();
            glTranslatef(-25,0,0);
            periscopio->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado, tapas);
        glPopMatrix();

        //Ojo
        glPushMatrix();
            glTranslatef(0,25,40);
            glScalef(0.2,0.2,0.2);
            cubo_ojo->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado);
            glPushMatrix();
                glTranslatef(0,0,37.5);
                glScalef(0.7,0.7,0.7);
                glRotatef(90,1,0,0);
                semiesfera_ojo->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado, tapas);
            glPopMatrix();
        glPopMatrix();

        //Cabeza
        semiesfera->draw(puntos, alambre, solido, ajedrez, smooth, flat, modo_dibujado, tapas);
    glPopMatrix();
}

void Cabeza::setColorDetalle(float R, float G, float B){
    periscopio->setColorDetalle(R,G,B);
    cubo_ojo->establecer_colores(R,G,B);
}

void Cabeza::setColorLentes(float R, float G, float B){
    periscopio->setColorLentes(R,G,B);
    semiesfera_ojo->establecer_colores(R,G,B);
}

void Cabeza::setColorMetal(float R, float G, float B){
    periscopio->setColorMetal(R,G,B);
    semiesfera->establecer_colores(R,G,B);
}

void Cabeza::setMaterialDetalle(Material mat){
    periscopio->setMaterialDetalle(mat);
    cubo_ojo->setMaterial(mat);
}

void Cabeza::setMaterialLentes(Material mat){
    periscopio->setMaterialLentes(mat);
    semiesfera_ojo->setMaterial(mat);
}

void Cabeza::setMaterialMetal(Material mat){
    periscopio->setMaterialMetal(mat);
    semiesfera->setMaterial(mat);
}

void Cabeza::animar(float incremento){
    if( (incremento < 0 && alpha > 0) || (incremento > 0 && alpha < 360) ){
        alpha += incremento;
    }
}

void Cabeza::animarPeriscopio(float incremento_alpha, float incremento_h){
    periscopio->animar(incremento_alpha,incremento_h);
}