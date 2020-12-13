#include "textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(std::string archivo){
    jpg::Imagen * pimg = NULL;

    pimg = new jpg::Imagen(archivo);

    width = pimg->tamX();
    height = pimg->tamY();
    data = pimg->leerPixels();

    glGenTextures(1,&idTex);
}

void Textura::activar(){
    glBindTexture(GL_TEXTURE_2D,idTex);

    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,width,height,GL_RGB,GL_UNSIGNED_BYTE,data);

    //La textura no reemplazará la componente especular del material (con la luz activa)
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SINGLE_COLOR);

    //Establecer interpolación para seleccionar los texels a partir de la coordenada de textura
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    //La imagen de textura se repetirá si las coordenadas de textura no están en el rango [0,1]
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
}