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
#include "r2.h"
#include "cuadro.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELILUMINACION,ANIMACION} menu;

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

    //carga de las imágenes de textura para la escena
    void cargar_texturas();

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
    int gradoLibertad = -1;
    bool animacionAutomatica = false;

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
    Cuadro * cuadro = nullptr;

    //Materiales
    Material oro, plata, bronce, cobre, obsidiana, plastico_verde, goma_amarilla, esmeralda, turquesa;

    //Texturas
    Textura tex_cuadro;
   
    //R2
    R2 * r2 = nullptr;

    //Variables para a velocidad de la animación
    float v_Cabeza = 0.00004;
    float v_Cuerpo = 0.00004;
    float v_h_Periscopio = 0.00004;
    float v_a_Periscopio = 0.00004;

    const float max_speed = 0.00016;
    const float min_speed = 0.00001;

    public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    void animarModeloJerarquico();

};
#endif
