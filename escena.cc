

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

   crear_objetos();


}

void Escena::crear_objetos(){
   //Cubo
   cubo = new Cubo(1.0);
   cubo->establecer_colores();
   //Tetraedro
   tetraedro = new Tetraedro();
   tetraedro->establecer_colores();
   //Objeto PLY
   objeto_ply = new ObjPLY("./plys/ant.ply");
   objeto_ply->establecer_colores();
   //Lata
   lata_superior = new ObjRevolucion("./plys/lata-psup.ply",25,true,false);
   lata_cuerpo = new ObjRevolucion("./plys/lata-pcue.ply",25,false,false);
   lata_inferior = new ObjRevolucion("./plys/lata-pinf.ply",25,false,true);
   lata_superior->establecer_colores();
   lata_cuerpo->establecer_colores();
   lata_inferior->establecer_colores();
   //Peon
   peon = new ObjRevolucion("./plys/reverse_peon-z.ply",25,true,true,2);
   peon->establecer_colores();
   //Cilindro
   cilindro = new Cilindro(5,25,2,1);
   cilindro->establecer_colores();
   //Cono
   cono = new Cono(10,25,1,0.5);
   cono->establecer_colores();
   //Esfera
   esfera = new Esfera(20,35,1);
   esfera->establecer_colores();
   //Semiesfera
   semiesfera = new Semiesfera(20,35,1);
   semiesfera->establecer_colores();
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

   //Selección del objeto activo
   if(cuboB){
      glPushMatrix();
      glTranslatef(30,20,-40);
      glScalef(40,40,40);
      cubo->draw(puntos,lineas,solido,ajedrez,modo_dibujado);
      glPopMatrix();
   }

   if(tetraedroB){
      glPushMatrix();
      glTranslatef(-45,0,-45);
      glScalef(40,40,40);
      tetraedro->draw(puntos,lineas,solido,ajedrez,modo_dibujado);
      glPopMatrix();
   }

   if(objetoPLYB){
      glPushMatrix();
      glTranslatef(25,10,45);
      glScalef(1.5,1.5,1.5);
      objeto_ply->draw(puntos,lineas,solido,ajedrez,modo_dibujado);
      glPopMatrix();
   }

   if(lataB){
      glPushMatrix();
      glTranslatef(-40,0,40);
      glScalef(20,20,20);
      lata_superior->draw(puntos,lineas,solido,ajedrez,modo_dibujado,tapas);
      lata_cuerpo->draw(puntos,lineas,solido,ajedrez,modo_dibujado,tapas);
      lata_inferior->draw(puntos,lineas,solido,ajedrez,modo_dibujado,tapas);
      glPopMatrix();
   }

   if(esferaB){
      glPushMatrix();
      glTranslatef(80,20,40);
      glScalef(20,20,20);
      esfera->draw(puntos,lineas,solido,ajedrez,modo_dibujado,tapas);
      glPopMatrix();
   }

   if(conoB){
      glPushMatrix();
      glTranslatef(-80,20,40);
      glScalef(40,40,40);
      cono->draw(puntos,lineas,solido,ajedrez,modo_dibujado,tapas);
      glPopMatrix();
   }

   if(cilindroB){
      glPushMatrix();
      glTranslatef(90,20,-40);
      glScalef(20,20,20);
      cilindro->draw(puntos,lineas,solido,ajedrez,modo_dibujado,tapas);
      glPopMatrix();
   }

   if(peonB){
      glPushMatrix();
      glTranslatef(0,0,100);
      glScalef(20,20,20);
      peon->draw(puntos,lineas,solido,ajedrez,modo_dibujado,tapas);
      glPopMatrix();
   }

   if(semiesferaB){
      glPushMatrix();
         glScalef(40,40,40);
         semiesfera->draw(puntos,lineas,solido,ajedrez,modo_dibujado,tapas);
      glPopMatrix();
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
            modoMenu=NADA;  
            cout << "\n-------OPCIONES DEL MENÚ-------\n";
            cout << "Selección de Objeto: O\n";
            cout << "Modo de Visualización: V\n";
            cout << "Modo de Dibujado: D\n";
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
         cout << "Activar/Desactivar Lata: L\n";
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
            cout << "Activar/Desactivar Lata: L\n";
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
            cout << "Activar/Desactivar Lata: L\n";
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
            else{
               cout << "Opción inválida\n";
            }
      break;

      case 'P' :
         if(modoMenu==SELVISUALIZACION){
            if(!puntos){
               cout << "Se ha activado la visualización de puntos\n";
               puntos = true;
               if(ajedrez){
                  ajedrez = false;
               }
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
               cout << "Activar/Desactivar Lata: L\n";
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

      case 'L' :
         if(modoMenu==SELVISUALIZACION){
            if(!lineas){
               cout << "Se ha activado la visualización de líneas\n";
               lineas = true;
               if(ajedrez){
                  ajedrez = false;
               }
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

         else if(modoMenu==SELOBJETO){
               if(!lataB){
                  cout << "Se ha activado la Lata\n";
                  lataB = true;
               }
               else{
                  cout << "Se ha desactivado la Lata\n";
                  lataB = false;
               }

               cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
               cout << "Activar/Desactivar Cubo: C\n";
               cout << "Activar/Desactivar Tetraedro: T\n";
               cout << "Activar/Desactivar Hormiga: H\n";
               cout << "Activar/Desactivar Lata: L\n";
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

      case 'S' :
         if(modoMenu==SELVISUALIZACION){
            if(!solido){
               cout << "Se ha activado la visualización de sólidos\n";
               solido = true;
               if(ajedrez){
                  ajedrez = false;
               }
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
            cout << "Activar/Desactivar Lata: L\n";
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
            cout << "Activar/Desactivar Lata: L\n";
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
            cout << "Activar/Desactivar Lata: L\n";
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
            cout << "Activar/Desactivar Lata: L\n";
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
