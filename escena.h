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
#include "camara.h"
#include "suelo.h"
#include "skybox.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,SELILUMINACION,ANIMACION,SELCAMARA} menu;
typedef enum {MOVIENDO_CAMARA,NOACTIVO} raton;
typedef enum {NO,MODELO,CUBO,LATA,MUNDO,TETRAEDRO,PEON,HORMIGA} objetos;

#define MOUSE_WHEEL_UP 3
#define MOUSE_WHEEL_DOWN 4

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
	void change_projection();
	void change_observer();
    
    //creación de objetos de la escena
    void crear_objetos();

    //creación de los materiales para la escena
    void crear_materiales();

    //carga de las imágenes de textura para la escena
    void cargar_texturas();

    void clear_window();

    void seleccionarObjeto();
    void deseleccionarObjeto();

    menu modoMenu=NADA;

    raton estadoRaton = NOACTIVO;
    int xant = 0;
    int yant = 0;

    //Variables para opciones de menú
    bool solido = true;
    bool puntos = false;
    bool lineas = false;
    bool ajedrez = false;
    bool tapas = true;
    bool smooth = false;
    bool flat = false;
    dibujado modo_dibujado = DIFERIDO;
    bool luz0B = false;
    bool luz1B = false;
    bool varA = false;
    bool varB = false;
    int gradoLibertad = -1;
    bool animacionAutomatica = false;
    bool animacionLuz = false;

    //Booleanos para la selección de objeto
    bool cuboB = true;
    bool r2B = true;
    bool lataB = true;
    bool mundoB = true;
    bool peonB = true;
    bool tetraedroB = true;
    bool hormigaB = true;

    // Objetos de la escena
    Ejes ejes;
    Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
    R2 * r2 = nullptr;
    ObjRevolucion * lata = nullptr;
    Esfera * esfera = nullptr;
    Suelo * suelo = nullptr;
    Skybox * skybox = nullptr;
    ObjRevolucion * peon = nullptr;
    Tetraedro * tetraedro = nullptr;
    ObjPLY * hormiga = nullptr;

    //Camaras
    Camara * camaras[3] = {nullptr};
    unsigned int camara_activa = 1;
    objetos objSeleccionado[3] = {NO};

    //Luces
    LuzPosicional * luz0 = nullptr;
    LuzDireccional * luz1 = nullptr;

    //Materiales
    Material plata, bronce, cobre, obsidiana, plastico_verde, goma_amarilla, esmeralda, turquesa;

    //Texturas
    Textura tex_cuadro, tex_madera, tex_lata, tex_mundo, tex_suelo, tex_cielo;
    
    //Variables para a velocidad de la animación
    float v_Cabeza = 0.004;
    float v_Cuerpo = 0.004;
    float v_h_Periscopio = 0.004;
    float v_a_Periscopio = 0.004;

    const float max_speed = 0.064;
    const float min_speed = 0.001;

    public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
    void dibujaSeleccion();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
    void seleccion(int x, int y);


    //Animaciones
    void animarModeloJerarquico();
    void animarLuzPosicional();

};
#endif
