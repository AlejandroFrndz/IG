#include "material.h"

Material::Material(){}

Material::Material(Tupla4f mambiente, Tupla4f mdifuso, Tupla4f mespecular, float mbrillo){
    ambiente = mambiente;
    difuso = mdifuso;
    especular = mespecular;
    brillo = mbrillo;
}

void Material::aplicar(){
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambiente);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,difuso);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,especular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);
}