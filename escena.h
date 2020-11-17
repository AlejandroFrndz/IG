#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "semiesfera.h"
#include "luzposicional.h"
#include "luzdireccional.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELILUMINACION} menu;

class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    
    //creación de objetos de la escena
    void crear_objetos();

    //creación de los materiales para la escena
    void crear_materiales();

    void clear_window();

    menu modoMenu=NADA;

    //Variables para opciones de menú
    bool solido = true;
    bool puntos = false;
    bool lineas = false;
    bool ajedrez = false;
    bool tapas = true;
    bool smooth = false;
    bool flat = false;
    dibujado modo_dibujado = DIFERIDO;
    bool cuboB = true;
    bool tetraedroB = true;
    bool objetoPLYB = true;
    bool peonB = true;
    bool cilindroB = true;
    bool conoB = true;
    bool esferaB = true;
    bool semiesferaB = true;
    bool luz0B = false;
    bool luz1B = true;
    bool varA = false;
    bool varB = false;

    // Objetos de la escena
    Ejes ejes;
    Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
    Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
    ObjPLY * objeto_ply = nullptr;
    ObjRevolucion * lata_superior = nullptr;
    ObjRevolucion * lata_cuerpo = nullptr;
    ObjRevolucion * lata_inferior = nullptr;
    ObjRevolucion * peon = nullptr;
    Cilindro * cilindro = nullptr;
    Cono * cono = nullptr;
    Esfera * esfera = nullptr;
    Semiesfera * semiesfera = nullptr;
    LuzPosicional * luz0 = nullptr;
    LuzDireccional * luz1 = nullptr;

    //Materiales
    Material oro, plata, bronce, cobre, obsidiana, plastico_verde, goma_amarilla, esmeralda; 
   
    public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
