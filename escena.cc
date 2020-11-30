

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

   crear_materiales();
   crear_objetos();


}

void Escena::crear_objetos(){

   r2 = new R2();
   r2->setColorDetalle();
   r2->setColorLentes();
   r2->setColorMetal();
   r2->setMaterialDetalle(turquesa);
   r2->setMaterialLentes(obsidiana);
   r2->setMaterialMetal(plata);

   //LuzPosicional
   luz0 = new LuzPosicional({0.0,0.0,0.0},GL_LIGHT0,{0.5,0.5,0.5,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
   //LuzDireccional
   luz1 = new LuzDireccional({0.0,0.0},GL_LIGHT1,{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
}

void Escena::crear_materiales(){
   oro = Material({0.24725,0.1995,0.0745,1.0},{0.75164,0.60648,0.22648,1.0},{0.628281,0.555802,0.366065,1.0},0.4*128);
   plata = Material({0.19225,0.19225,0.19225,1.0},{0.50754,0.50754,0.50754,1.0},{0.508273,0.508273,0.508273,1.0},0.4*128);
   bronce = Material({0.2125,0.1275,0.054,1.0},{0.714,0.4284,0.18144,1.0},{0.393548,0.271906,0.166721,1.0},0.2*128);
   obsidiana = Material({0.05375,0.05,0.06625,1.0},{0.18275,0.17,0.22525,1.0},{0.332741,0.328634,0.346435,1.0},0.3*128);
   plastico_verde = Material({0.0,0.0,0.0,1.0},{0.1,0.35,0.1,1.0},{0.45,0.55,0.45,1.0},0.25*128);
   goma_amarilla = Material({0.05,0.05,0.0,1.0},{0.5,0.5,0.4,1.0},{0.7,0.7,0.04,1.0},0.078125*128);
   esmeralda = Material({0.0215,0.1745,0.0215,1.0},{0.07568,0.61424,0.07568,1.0},{0.633,0.727811,0.633,1.0},0.6*128);
   turquesa = Material({0.1f, 0.18725f, 0.1745f, 0.8f},{0.396f, 0.74151f, 0.69102f, 0.8f},{0.297254f, 0.30829f, 0.306678f, 0.8f},12.8);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

   //Mostrar opciones del menú
   std::cout << "-------OPCIONES DEL MENÚ------------\n";
   std::cout << "Selección de Objeto: O\n";
   std::cout << "Modo de Visualización: V\n";
   std::cout << "Modo de Dibujado: D\n";
   std::cout << "Opciones de Iluminación: I\n";
   std::cout << "Salir: Q\n";
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   glEnable(GL_CULL_FACE);
   ejes.draw();

   if(smooth || flat){
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);
      
      if(luz0B)
         luz0->activar();

      if(luz1B){
         glPushMatrix();
            glLoadIdentity();
            luz1->activar();
         glPopMatrix();
      }
   }
   
   r2->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado,tapas);

   if(smooth || flat){
      glDisable(GL_LIGHTING);
      glDisable(GL_NORMALIZE);
      luz0->desactivar();
      luz1->desactivar();
   }
    
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl << endl;
   bool salir=false;
   if(modoMenu == NADA){
      
   }
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA){
            varA = false;
            varB = false;
            modoMenu=NADA;  
            cout << "\n-------OPCIONES DEL MENÚ-------\n";
            cout << "Selección de Objeto: O\n";
            cout << "Modo de Visualización: V\n";
            cout << "Modo de Dibujado: D\n";
            cout << "Opciones de Iluminación: I\n";
            cout << "Salir: Q\n";
         }          
         else {
            salir=true ;
         }
      break ;

      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO; 
         cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
         cout << "Activar/Desactivar Cubo: C\n";
         cout << "Activar/Desactivar Tetraedro: T\n";
         cout << "Activar/Desactivar Hormiga: H\n";
         cout << "Activar/Desactivar Esfera: E\n";
         cout << "Activar/Desactivar Cilindro: G\n";
         cout << "Activar/Desactivar Cono: K\n";
         cout << "Activar/Desactivar Peon: P\n";
         cout << "Volver al menú principal: Q\n";
      break ;

      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         cout << "\n-------OPCIONES DE VISUALIZACIÓN-------\n";
         cout << "Activar/Desactivar Puntos: P\n";
         cout << "Activar/Desactivar Líneas: L\n";
         cout << "Activar/Desactivar Sólido: S (Por defecto)\n";
         cout << "Activar/Desactivar Ajedrez: A\n";
         cout << "Activar/Desactivar Tapas (Objetos de Revolución): T\n";
         cout << "Volver al menú principal: Q\n";
      break ;
       
      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         modoMenu=SELDIBUJADO;
         cout << "\n-------OPCIONES DE DIBUJADO-------\n";
         cout << "Activar el dibujado en modo inmediato con glDrawElements: 1\n";
         cout << "Activar el dibujado en modo diferido con VBOs (por defecto): 2\n";
         cout << "Volver al menú principal: Q\n";
      break ;

      case 'C' :
         if(modoMenu==SELOBJETO){
            if(!cuboB){
               cout << "Se ha activado el cubo\n";
               cuboB = true;
            }
            else{
               cout << "Se ha desactivado el cubo\n";
               cuboB = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Activar/Desactivar Esfera: E\n";
            cout << "Activar/Desactivar Cilindro: G\n";
            cout << "Activar/Desactivar Cono: K\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'T' :
         if(modoMenu==SELOBJETO){
            if(!tetraedroB){
               cout << "Se ha activado el tetraedro\n";
               tetraedroB = true;
            }
            else{
               cout << "Se ha desactivado el tetraedro\n";
               tetraedroB = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Activar/Desactivar Esfera: E\n";
            cout << "Activar/Desactivar Cilindro: G\n";
            cout << "Activar/Desactivar Cono: K\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Volver al menú principal: Q\n";
         }

         else if(modoMenu==SELVISUALIZACION){
            if(!tapas){
               cout << "Se ha activado la visualización de tapas\n";
               tapas = true;
            }
            else{
               cout << "Se ha desactivado la visualización de tapas\n";
               tapas = false;
            }

            cout << "\n-------OPCIONES DE VISUALIZACIÓN-------\n";
            cout << "Activar/Desactivar Puntos: P\n";
            cout << "Activar/Desactivar Líneas: L\n";
            cout << "Activar/Desactivar Sólido: S (Por defecto)\n";
            cout << "Activar/Desactivar Ajedrez: A\n";
            cout << "Activar/Desactivar Tapas (Objetos de Revolución): T\n";
            cout << "Volver al menú principal: Q\n";
         }

         else if(modoMenu==SELILUMINACION){
            if(!smooth){
               cout << "Se ha activado la iluminación suavizada\n";
               smooth = true;
               flat = false;
            }
            else{
               cout << "Se ha activado la iluminación plana\n";
               smooth = false;
               flat = true;
            }

            cout << "\n-------OPCIONES DE ILUMINACIÓN-------\n";
            cout << "Activar/Desactivar Iluminación: P\n";
            cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
            cout << "Encender/Apagar luz: 0-1\n";
            cout << "Variación de Alpha: A\n";
            cout << "Variación de Beta: B\n";
            cout << "Incrementar Ángulo: >\n";
            cout << "Decrementar Ángulo: <\n";
         }

         else{
               cout << "Opción inválida\n";
         }
      break;

      case 'P' :
         if(modoMenu==SELVISUALIZACION){
            if(!puntos){
               cout << "Se ha activado la visualización de puntos\n";
               puntos = true;
               ajedrez = false;
               smooth = false;
               flat = false;
            }
            else{
               cout << "Se ha desactivado la visualización de puntos\n";
               puntos = false;
            }

            cout << "\n-------OPCIONES DE VISUALIZACIÓN-------\n";
            cout << "Activar/Desactivar Puntos: P\n";
            cout << "Activar/Desactivar Líneas: L\n";
            cout << "Activar/Desactivar Sólido: S (Por defecto)\n";
            cout << "Activar/Desactivar Ajedrez: A\n";
            cout << "Activar/Desactivar Tapas (Objetos de Revolución): T\n";
            cout << "Volver al menú principal: Q\n";
         }

         else if(modoMenu==SELOBJETO){
               if(!peonB){
                  cout << "Se ha activado el Peon\n";
                  peonB = true;
               }
               else{
                  cout << "Se ha desactivado el Peon\n";
                  peonB = false;
               }

               cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
               cout << "Activar/Desactivar Cubo: C\n";
               cout << "Activar/Desactivar Tetraedro: T\n";
               cout << "Activar/Desactivar Hormiga: H\n";
               cout << "Activar/Desactivar Esfera: E\n";
               cout << "Activar/Desactivar Cilindro: G\n";
               cout << "Activar/Desactivar Cono: K\n";
               cout << "Activar/Desactivar Peon: P\n";
               cout << "Volver al menú principal: Q\n";
            }

            else if(modoMenu==SELILUMINACION){
               if(!flat && !smooth){
                  cout << "Se ha activado la Iluminación y encendido ambas luces\n";
                  smooth = true;
                  flat = false;
                  ajedrez = false;
                  puntos = false;
                  lineas = false;
                  solido = false;
                  luz0B = true;
                  luz1B = true;
               }

               else{
                  cout << "Se ha desactivado la Iluminación y apagado ambas luces\n";
                  smooth = false;
                  flat = false;
                  solido = true;
                  luz0B = false;
                  luz1B = false;
                  varA = false;
                  varB = false;
               }

               cout << "\n-------OPCIONES DE ILUMINACIÓN-------\n";
               cout << "Activar/Desactivar Iluminación: P\n";
               cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
               cout << "Encender/Apagar luz: 0-1\n";
               cout << "Variación de Alpha: A\n";
               cout << "Variación de Beta: B\n";
               cout << "Incrementar Ángulo: >\n";
               cout << "Decrementar Ángulo: <\n";
            }

            else{
               cout << "Opción inválida\n";
            }
      break;

      case 'L' :
         if(modoMenu==SELVISUALIZACION){
            if(!lineas){
               cout << "Se ha activado la visualización de líneas\n";
               lineas = true;
               ajedrez = false;
               smooth = false;
               flat = false;
            }
            else{
               cout << "Se ha desactivado la visualización de líneas\n";
               lineas = false;
            }
            
            cout << "\n-------OPCIONES DE VISUALIZACIÓN-------\n";
            cout << "Activar/Desactivar Puntos: P\n";
            cout << "Activar/Desactivar Líneas: L\n";
            cout << "Activar/Desactivar Sólido: S (Por defecto)\n";
            cout << "Activar/Desactivar Ajedrez: A\n";
            cout << "Activar/Desactivar Tapas (Objetos de Revolución): T\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'S' :
         if(modoMenu==SELVISUALIZACION){
            if(!solido){
               cout << "Se ha activado la visualización de sólidos\n";
               solido = true;
               ajedrez = false;
               smooth = false;
               flat = false;
            }
            else{
               cout << "Se ha desactivado la visualización de sólidos\n";
               solido = false;
            }
            
            cout << "\n-------OPCIONES DE VISUALIZACIÓN-------\n";
            cout << "Activar/Desactivar Puntos: P\n";
            cout << "Activar/Desactivar Líneas: L\n";
            cout << "Activar/Desactivar Sólido: S (Por defecto)\n";
            cout << "Activar/Desactivar Ajedrez: A\n";
            cout << "Activar/Desactivar Tapas (Objetos de Revolución): T\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'A' :
         if(modoMenu==SELVISUALIZACION){
            if(!ajedrez){
               cout << "Se ha activado la visualización en modo ajedrez y desactivado las demás\n";
               ajedrez = true;
               puntos = false;
               lineas = false;
               solido = false;
               smooth = false;
               flat = false;
            }
            else{
               cout << "Se ha desactivado la visualización en modo ajedrez y vuelto a la visualización de sólidos\n";
               ajedrez = false;
               solido = true;
            }
            
            cout << "\n-------OPCIONES DE VISUALIZACIÓN-------\n";
            cout << "Activar/Desactivar Puntos: P\n";
            cout << "Activar/Desactivar Líneas: L\n";
            cout << "Activar/Desactivar Sólido: S (Por defecto)\n";
            cout << "Activar/Desactivar Ajedrez: A\n";
            cout << "Activar/Desactivar Tapas (Objetos de Revolución): T\n";
            cout << "Volver al menú principal: Q\n";
         }

         else if(modoMenu==SELILUMINACION){
            if(!varA){
               cout << "Se ha seleccionado la variación del ángulo alpha\n";
               varA = true;
               varB = false;
            }
            else{
               cout << "Se ha deseleccionado la variación del ángulo alpha\n";
               varA = false;
            }
            cout << "\n-------OPCIONES DE ILUMINACIÓN-------\n";
            cout << "Activar/Desactivar Iluminación: P\n";
            cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
            cout << "Encender/Apagar luz: 0-1\n";
            cout << "Variación de Alpha: A\n";
            cout << "Variación de Beta: B\n";
            cout << "Incrementar Ángulo: >\n";
            cout << "Decrementar Ángulo: <\n";
         }

         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'B':
         if(modoMenu==SELILUMINACION){
            if(!varB){
               cout << "Se ha seleccionado la variación del ángulo beta\n";
               varB = true;
               varA = false;
            }
            else{
               cout << "Se ha deseleccionado la variación del ángulo beta\n";
               varB = false;
            }

            cout << "\n-------OPCIONES DE ILUMINACIÓN-------\n";
            cout << "Activar/Desactivar Iluminación: P\n";
            cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
            cout << "Encender/Apagar luz: 0-1\n";
            cout << "Variación de Alpha: A\n";
            cout << "Variación de Beta: B\n";
            cout << "Incrementar Ángulo: >\n";
            cout << "Decrementar Ángulo: <\n";
         }

         else{
            cout << "Opción inválida\n";
         }
      break;

      case '0':
         if(modoMenu==SELILUMINACION){
            if(!luz0B){
               cout << "Se ha activado la luz 0 (posicional)\n";
               luz0B = true;
            }
            else{
               cout << "Se ha desactivado la luz 0 (posicional)\n";
               luz0B = false;
            }
         }

         else{
            cout << "Opción inválida\n";
         }
      break;

      case '1' :
         if(modoMenu==SELDIBUJADO){
            cout << "Se ha seleccionado el modo de dibujado inmediato\n";
            modo_dibujado = INMEDIATO;

            cout << "\n-------OPCIONES DE DIBUJADO-------\n";
            cout << "Activar el dibujado en modo inmediato con glDrawElements: 1\n";
            cout << "Activar el dibujado en modo diferido con VBOs (por defecto): 2\n";
            cout << "Volver al menú principal: Q\n";
         }

         else if(modoMenu==SELILUMINACION){
            if(!luz1B){
               cout << "Se ha activado la luz 1 (direccional)\n";
               luz1B = true;
            }
            else{
               cout << "Se ha desactivado la luz 1 (direccional)\n";
               luz1B = false; 
               varA = false;
               varB = false;
            }
         }
         else{
            cout << "Opción inválida\n";
         } 
      break;

      case '2' :
         if(modoMenu==SELDIBUJADO){
            cout << "Se ha seleccionado el modo de dibujado diferido\n";
            modo_dibujado = DIFERIDO;

            cout << "\n-------OPCIONES DE DIBUJADO-------\n";
            cout << "Activar el dibujado en modo inmediato con glDrawElements: 1\n";
            cout << "Activar el dibujado en modo diferido con VBOs (por defecto): 2\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         } 
      break;

      case 'H' :
         if(modoMenu==SELOBJETO){
            if(!objetoPLYB){
               cout << "Se ha activado la hormiga\n";
               objetoPLYB = true;
            }
            else{
               cout << "Se ha desactivado la hormiga\n";
               objetoPLYB = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Activar/Desactivar Esfera: E\n";
            cout << "Activar/Desactivar Cilindro: G\n";
            cout << "Activar/Desactivar Cono: K\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'E' :
         if(modoMenu==SELOBJETO){
            if(!esferaB){
               cout << "Se ha activado la esfera\n";
               esferaB = true;
            }
            else{
               cout << "Se ha desactivado la esfera\n";
               esferaB = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Activar/Desactivar Esfera: E\n";
            cout << "Activar/Desactivar Cilindro: G\n";
            cout << "Activar/Desactivar Cono: K\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'G' :
         if(modoMenu==SELOBJETO){
            if(!cilindroB){
               cout << "Se ha activado el cilindro\n";
               cilindroB = true;
            }
            else{
               cout << "Se ha desactivado el cilindro\n";
               cilindroB = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Activar/Desactivar Esfera: E\n";
            cout << "Activar/Desactivar Cilindro: G\n";
            cout << "Activar/Desactivar Cono: K\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'K' :
         if(modoMenu==SELOBJETO){
            if(!conoB){
               cout << "Se ha activado el cono\n";
               conoB = true;
            }
            else{
               cout << "Se ha desactivado el cono\n";
               conoB = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Activar/Desactivar Esfera: E\n";
            cout << "Activar/Desactivar Cilindro: G\n";
            cout << "Activar/Desactivar Cono: K\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'I':
         modoMenu = SELILUMINACION;
         cout << "\n-------OPCIONES DE ILUMINACIÓN-------\n";
         cout << "Activar/Desactivar Iluminación: P\n";
         cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
         cout << "Encender/Apagar luz: 0-1\n";
         cout << "Variación de Alpha: A\n";
         cout << "Variación de Beta: B\n";
         cout << "Incrementar Ángulo: >\n";
         cout << "Decrementar Ángulo: <\n";
      break;

      case '>':
         if(varA){
            cout << "Ángulo alpha actual: " << luz1->variarAnguloAlpha(20) << endl;
         }
         else if(varB){
            cout << "Ángulo beta actual: " << luz1->variarAnguloBeta(20) << endl;
         }

         else{
            cout << "No se ha seleccionado ningún ángulo o la luz1 está desactivada\n";
         }
      break;

      case '<':
         if(varA){
            cout << "Ángulo alpha actual: " << luz1->variarAnguloAlpha(-20) << endl;
         }
         else if(varB){
            cout << "Ángulo beta actual: " << luz1->variarAnguloBeta(-20) << endl;
         }

         else{
            cout << "No se ha seleccionado ningún ángulo o la luz1 está desactivada\n";
         }
      break;

      default :
         cout << "Opción inválida\n";
      break;
            
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
