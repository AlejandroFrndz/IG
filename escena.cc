

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
   cargar_texturas();
   crear_objetos();


}

void Escena::crear_objetos(){
   //Modelo Jerarquico
   r2 = new R2();
   r2->setColorDetalle();
   r2->setColorLentes();
   r2->setColorMetal();
   r2->setColorSeleccion(0,0,0);
   r2->setMaterialDetalle(turquesa);
   r2->setMaterialLentes(obsidiana);
   r2->setMaterialMetal(plata);

   //Cubo-Textura
   cubo = new Cubo(1);
   cubo->establecer_colores(1,1,1);
   cubo->setColorSeleccion(0,1,0);
   cubo->setMaterial(plata);
   cubo->calcularCoordTex();
   cubo->setTextura(tex_madera);

   //Lata
   lata = new ObjRevolucion("./plys/lata-pcue.ply",50,true,true);
   lata->establecer_colores(1,1,1);
   lata->setColorSeleccion(0,0,1);
   lata->setMaterial(plata);
   lata->setTextura(tex_lata);
   lata->calcularCoordTex();

   //Esfera-Textura
   esfera = new Esfera(100,100,50);
   esfera->establecer_colores(1,1,1);
   esfera->setColorSeleccion(1,1,0);
   esfera->setMaterial(plata);
   esfera->setTextura(tex_mundo);
   esfera->calcularCoordTex();

   //Peon
   peon = new ObjRevolucion("./plys/reverse_peon-x.ply",50,true,true,0);
   peon->establecer_colores();
   peon->setColorSeleccion(0,1,1);
   peon->setMaterial(plastico_verde);

   //Hormiga
   hormiga = new ObjPLY("./plys/ant.ply");
   hormiga->establecer_colores(1,0,0);
   hormiga->setColorSeleccion(1,0,1);
   hormiga->setMaterial(esmeralda);

   //Tetraedro
   tetraedro = new Tetraedro();
   tetraedro->establecer_colores(0,0.5,0);
   tetraedro->setColorSeleccion(1,0,0);
   tetraedro->setMaterial(obsidiana);

   //Skybox
   skybox = new Skybox(1500);
   skybox->establecer_colores(1,1,1);
   skybox->setMaterial(plata);
   skybox->setTextura(tex_cielo);
   skybox->calcularCoordTex();

   //Suelo
   suelo = new Suelo(2048);
   suelo->establecer_colores(1,1,1);
   suelo->setMaterial(plata);
   suelo->setTextura(tex_suelo);

   //LuzPosicional
   luz0 = new LuzPosicional({0.0,0.0,0.0},GL_LIGHT0,{0.5,0.5,0.5,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});
   //LuzDireccional
   luz1 = new LuzDireccional({0.0,0.0},GL_LIGHT1,{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0});

   //Camaras
   camaras[0] = new Camara({0,70,400},{0,0,0},{0,1,0},0,50,2000);
   camaras[1] = new Camara({0,70,200},{0,0,0},{0,1,0},1,50,2000);
   camaras[2] = new Camara({30,10,150},{0,0,0},{0,1,0},1,50,2000);
}

void Escena::crear_materiales(){
   plata = Material({0.19225,0.19225,0.19225,1.0},{0.50754,0.50754,0.50754,1.0},{0.508273,0.508273,0.508273,1.0},0.4*128);
   bronce = Material({0.2125,0.1275,0.054,1.0},{0.714,0.4284,0.18144,1.0},{0.393548,0.271906,0.166721,1.0},0.2*128);
   obsidiana = Material({0.05375,0.05,0.06625,1.0},{0.18275,0.17,0.22525,1.0},{0.332741,0.328634,0.346435,1.0},0.3*128);
   plastico_verde = Material({0.0,0.0,0.0,1.0},{0.1,0.35,0.1,1.0},{0.45,0.55,0.45,1.0},0.25*128);
   goma_amarilla = Material({0.05,0.05,0.0,1.0},{0.5,0.5,0.4,1.0},{0.7,0.7,0.04,1.0},0.078125*128);
   esmeralda = Material({0.0215,0.1745,0.0215,1.0},{0.07568,0.61424,0.07568,1.0},{0.633,0.727811,0.633,1.0},0.6*128);
   turquesa = Material({0.1f, 0.18725f, 0.1745f, 0.8f},{0.396f, 0.74151f, 0.69102f, 0.8f},{0.297254f, 0.30829f, 0.306678f, 0.8f},12.8);
}

void Escena::cargar_texturas(){
   tex_cuadro = Textura("./texturas/tlou2.jpg");
   tex_madera = Textura("./texturas/text-madera.jpg");
   tex_lata = Textura("./texturas/text-lata-1.jpg");
   tex_mundo = Textura("./texturas/mundo.jpg");
   tex_suelo = Textura("./texturas/suelo.jpg");
   tex_cielo = Textura("./texturas/cielo.jpg");
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

   for(int i = 0; i < 3; i++){
      camaras[i]->setVolumen(-Width,Width,-Height,Height);
   }

   change_projection();
	glViewport( 0, 0, UI_window_width, UI_window_height );

   //Mostrar opciones del menú
   std::cout << "-------OPCIONES DEL MENÚ------------\n";
   std::cout << "Selección de Objeto: O\n";
   std::cout << "Modo de Visualización: V\n";
   std::cout << "Modo de Dibujado: D\n";
   std::cout << "Opciones de Iluminación: I\n";
   std::cout << "Animación: M\n";
   std::cout << "Selección de Cámara: C\n";
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
   
   
   if(r2B){
      glPushMatrix();
         glTranslatef(0,9,-40);
         glScalef(0.6,0.6,0.6);
         r2->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado,tapas);
      glPopMatrix();
   }
   
   if(cuboB){
      glPushMatrix();
         glTranslatef(80,-25,0);
         glScalef(50,50,50);
         cubo->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado);
      glPopMatrix();
   }
   
   if(lataB){
      glPushMatrix();
         glTranslatef(80,-50,80);
         glScalef(50,50,50);
         lata->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado,tapas);
      glPopMatrix();
   }

   if(mundoB){
      glPushMatrix();
         glTranslatef(-70,150,0);
         esfera->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado,tapas);
      glPopMatrix();
   }

   if(tetraedroB){
      glPushMatrix();
         glTranslatef(-50,-50,100);
         glScalef(50,50,50);
         glRotatef(30,0,1,0);
         tetraedro->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado);
      glPopMatrix();
   }

   if(peonB){
      glPushMatrix();
         glTranslatef(-70,0,0);
         glScalef(20,20,20);
         peon->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado,tapas);
      glPopMatrix();
   }

   if(hormigaB){
      glPushMatrix();
         glTranslatef(30,-30,80);
         glScalef(2,2,2);
         hormiga->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado);
      glPopMatrix();
   }

   glPushMatrix();
      glTranslatef(-1024,-50,1024);
      glRotatef(-90,1,0,0);
      suelo->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado);
   glPopMatrix();

   skybox->draw(puntos,lineas,solido,ajedrez,smooth,flat,modo_dibujado);


   if(smooth || flat){
      glDisable(GL_LIGHTING);
      glDisable(GL_NORMALIZE);
      luz0->desactivar();
      luz1->desactivar();
   }
    
}

void Escena::dibujaSeleccion(){
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);

   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   if(r2B){
      glPushMatrix();
         glTranslatef(0,9,-40);
         glScalef(0.6,0.6,0.6);
         r2->drawSeleccion();
      glPopMatrix();
   }
   
   if(cuboB){
      glPushMatrix();
         glTranslatef(80,-25,0);
         glScalef(50,50,50);
         cubo->drawSeleccion();
      glPopMatrix();
   }
   
   if(lataB){
      glPushMatrix();
         glTranslatef(80,-50,80);
         glScalef(50,50,50);
         lata->drawSeleccion();
      glPopMatrix();
   }

   if(mundoB){
      glPushMatrix();
         glTranslatef(-70,150,0);
         esfera->drawSeleccion();
      glPopMatrix();
   }

   if(tetraedroB){
      glPushMatrix();
         glTranslatef(-50,-50,100);
         glScalef(50,50,50);
         glRotatef(30,0,1,0);
         tetraedro->drawSeleccion();
      glPopMatrix();
   }

   if(peonB){
      glPushMatrix();
         glTranslatef(-70,0,0);
         glScalef(20,20,20);
         peon->drawSeleccion();
      glPopMatrix();
   }

   if(hormigaB){
      glPushMatrix();
         glTranslatef(30,-30,80);
         glScalef(2,2,2);
         hormiga->drawSeleccion();
      glPopMatrix();
   }

   glEnable(GL_DITHER);
}

//Función para la animación automática del modelo jerarquico
void Escena::animarModeloJerarquico(){
   if(animacionAutomatica){
      if(!r2->animarCabeza(v_Cabeza)){
         v_Cabeza *= -1;
      }

      if(!r2->animarCuerpo(v_Cuerpo)){
         v_Cuerpo *= -1;
      }

      if(!r2->animarPeriscopio(v_a_Periscopio,0)){
         v_a_Periscopio *= -1;
      }

      if(!r2->animarPeriscopio(0,v_h_Periscopio)){
         v_h_Periscopio *= -1;
      }
   }
}

//Función para la animación de la luz posicional
void Escena::animarLuzPosicional(){
   if((smooth || flat) && animacionLuz){
      luz0->animar();
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
            cout << "Animación: M\n";
            cout << "Selección de Cámara: C\n";
            cout << "Salir: Q\n";
         }          
         else {
            salir=true ;
         }
      break ;

      case 'O' :
         if(modoMenu==NADA){
            modoMenu=SELOBJETO; 
            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar R2: R\n";
            cout << "Activar/Desactivar Lata: L\n";
            cout << "Activar/Desactivar Mundo: M";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Volver al menú principal: Q\n";
         }

         else{
            cout << "Opción inválida\n";
         }
      break ;

      case 'V' :
         if(modoMenu==NADA){
            modoMenu=SELVISUALIZACION;
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
      break ;
       
      case 'D' :
         if(modoMenu==NADA){
            modoMenu=SELDIBUJADO;
            cout << "\n-------OPCIONES DE DIBUJADO-------\n";
            cout << "Activar el dibujado en modo inmediato con glDrawElements: 1\n";
            cout << "Activar el dibujado en modo diferido con VBOs (por defecto): 2\n";
            cout << "Volver al menú principal: Q\n";
         }

         else{
            cout << "Opción inválida\n";
         }
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
            cout << "Activar/Desactivar R2: R\n";
            cout << "Activar/Desactivar Lata: L\n";
            cout << "Activar/Desactivar Mundo: M";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Volver al menú principal: Q\n";
         }

         else if(modoMenu==NADA){
            modoMenu = SELCAMARA;

            cout << "\n-------OPCIONES DE SELECCIÓN DE CÁMARA-------\n";
            cout << "Se está usando la cámara " << camara_activa << endl;
            cout << "Activar Cámara Ortogonal: 0\n";
            cout << "Activar Cámara Perspectiva 1: 1\n";
            cout << "Activar Cámara Perspectiva 2: 2\n";
            cout << "Volver al menú principal: Q\n";

         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'T' :
         if(modoMenu==SELVISUALIZACION){
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
            cout << "Activar/Desactivar Iluminación: I\n";
            cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
            cout << "Encender/Apagar luz: 0-1\n";
            cout << "Variación de Alpha: A\n";
            cout << "Variación de Beta: B\n";
            cout << "Incrementar Ángulo: >\n";
            cout << "Decrementar Ángulo: <\n";
            cout << "Activar animación de la luz puntual (luz0): P\n";
         }

         else if(modoMenu==SELOBJETO){
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
            cout << "Activar/Desactivar R2: R\n";
            cout << "Activar/Desactivar Lata: L\n";
            cout << "Activar/Desactivar Mundo: M";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Activar/Desactivar Hormiga: H\n";
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
            else if(modoMenu==SELILUMINACION){
               if(!animacionLuz){
                  animacionLuz = true;
                  cout << "Se ha activado la animación de la luz puntual\n";
               }
               else{
                  animacionLuz = false;
                  cout << "Se ha desactivado la animación de la luz puntual\n";
               }

               cout << "\n-------OPCIONES DE ILUMINACIÓN-------\n";
               cout << "Activar/Desactivar Iluminación: I\n";
               cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
               cout << "Encender/Apagar luz: 0-1\n";
               cout << "Variación de Alpha: A\n";
               cout << "Variación de Beta: B\n";
               cout << "Incrementar Ángulo: >\n";
               cout << "Decrementar Ángulo: <\n";
               cout << "Activar animación de la luz puntual (luz0): P\n";
            }

            else if(modoMenu==SELOBJETO){
               if(!peonB){
                  cout << "Se ha activado el peón\n";
                  peonB = true;
               }
               else{
                  cout << "Se ha desactivado el peón\n";
                  peonB = false;
               }

               cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
               cout << "Activar/Desactivar Cubo: C\n";
               cout << "Activar/Desactivar R2: R\n";
               cout << "Activar/Desactivar Lata: L\n";
               cout << "Activar/Desactivar Mundo: M";
               cout << "Activar/Desactivar Tetraedro: T\n";
               cout << "Activar/Desactivar Peon: P\n";
               cout << "Activar/Desactivar Hormiga: H\n";
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

         else if(modoMenu==SELOBJETO){
            if(!lataB){
               cout << "Se ha activado la lata\n";
               lataB = true;
            }
            else{
               cout << "Se ha desactivado la lata\n";
               lataB = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar R2: R\n";
            cout << "Activar/Desactivar Lata: L\n";
            cout << "Activar/Desactivar Mundo: M";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'H':
         if(modoMenu==SELOBJETO){
            if(!hormigaB){
               cout << "Se ha activado la hormiga\n";
               hormigaB = true;
            }
            else{
               cout << "Se ha desactivado la hormiga\n";
               hormigaB = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar R2: R\n";
            cout << "Activar/Desactivar Lata: L\n";
            cout << "Activar/Desactivar Mundo: M";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Activar/Desactivar Hormiga: H\n";
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
            cout << "Activar/Desactivar Iluminación: I\n";
            cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
            cout << "Encender/Apagar luz: 0-1\n";
            cout << "Variación de Alpha: A\n";
            cout << "Variación de Beta: B\n";
            cout << "Incrementar Ángulo: >\n";
            cout << "Decrementar Ángulo: <\n";
            cout << "Activar animación de la luz puntual (luz0): P\n";
         }

         else if(modoMenu==ANIMACION){
            if(!animacionAutomatica){
               cout << "Se ha activado la animación automática\n";
               animacionAutomatica = true;
            }
            else{
               cout << "Se ha desactivado la animación automática\n";
               animacionAutomatica = false;
            }
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
            cout << "Activar/Desactivar Iluminación: I\n";
            cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
            cout << "Encender/Apagar luz: 0-1\n";
            cout << "Variación de Alpha: A\n";
            cout << "Variación de Beta: B\n";
            cout << "Incrementar Ángulo: >\n";
            cout << "Decrementar Ángulo: <\n";
            cout << "Activar animación de la luz puntual (luz0): P\n";
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

         else if(modoMenu==ANIMACION){
            if(gradoLibertad != 0){
               cout << "Se ha seleccionado el grado de libertad 0\n";
               gradoLibertad = 0;
            }
            else{
               cout << "Se ha deseleccionado el grado de libertad 0\n";
               gradoLibertad = -1;
            }
         }

         else if(modoMenu==SELCAMARA){
            cout << "Se ha activado la cámara ortogonal\n";
            deseleccionarObjeto();
            camara_activa = 0;
            seleccionarObjeto();
            change_projection();

            cout << "\n-------OPCIONES DE SELECCIÓN DE CÁMARA-------\n";
            cout << "Se está usando la cámara " << camara_activa << endl;
            cout << "Activar Cámara Ortogonal: 0\n";
            cout << "Activar Cámara Perspectiva 1: 1\n";
            cout << "Activar Cámara Perspectiva 2: 2\n";
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

         else if(modoMenu==ANIMACION){
            if(gradoLibertad != 1){
               cout << "Se ha seleccionado el grado de libertad 1\n";
               gradoLibertad = 1;
            }
            else{
               cout << "Se ha deseleccionado el grado de libertad 1\n";
               gradoLibertad = -1;
            }
         }

         else if(modoMenu==SELCAMARA){
            cout << "Se ha activado la cámara perspectiva 1\n";
            deseleccionarObjeto();
            camara_activa = 1;
            seleccionarObjeto();
            change_projection();

            cout << "\n-------OPCIONES DE SELECCIÓN DE CÁMARA-------\n";
            cout << "Se está usando la cámara " << camara_activa << endl;
            cout << "Activar Cámara Ortogonal: 0\n";
            cout << "Activar Cámara Perspectiva 1: 1\n";
            cout << "Activar Cámara Perspectiva 2: 2\n";
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

         else if(modoMenu==ANIMACION){
            if(gradoLibertad != 2){
               cout << "Se ha seleccionado el grado de libertad 2\n";
               gradoLibertad = 2;
            }
            else{
               cout << "Se ha deseleccionado el grado de libertad 2\n";
               gradoLibertad = -1;
            }
         }

         else if(modoMenu==SELCAMARA){
            cout << "Se ha activado la cámara perspectiva 2\n";
            deseleccionarObjeto();
            camara_activa = 2;
            seleccionarObjeto();
            change_projection();

            cout << "\n-------OPCIONES DE SELECCIÓN DE CÁMARA-------\n";
            cout << "Se está usando la cámara " << camara_activa << endl;
            cout << "Activar Cámara Ortogonal: 0\n";
            cout << "Activar Cámara Perspectiva 1: 1\n";
            cout << "Activar Cámara Perspectiva 2: 2\n";
            cout << "Volver al menú principal: Q\n";
         }

         else{
            cout << "Opción inválida\n";
         } 
      break;

      case '3':
         if(modoMenu==ANIMACION){
            if(gradoLibertad != 3){
               cout << "Se ha seleccionado el grado de libertad 3\n";
               gradoLibertad = 3;
            }
            else{
               cout << "Se ha deseleccionado el grado de libertad 3\n";
               gradoLibertad = -1;
            }
         }

         else{
            cout << "Opción inválida\n";
         }
      break;
      
      case 'R' :
         if(modoMenu==SELOBJETO){
            if(!r2B){
               cout << "Se ha activado el R2 (Modelo Jerarquico)\n";
               r2B = true;
            }
            else{
               cout << "Se ha desactivado el R2 (Modelo Jerarquico)\n";
               r2B = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar R2: R\n";
            cout << "Activar/Desactivar Lata: L\n";
            cout << "Activar/Desactivar Mundo: M";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Volver al menú principal: Q\n";
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'I':
         if(modoMenu==NADA){
            modoMenu = SELILUMINACION;
            cout << "\n-------OPCIONES DE ILUMINACIÓN-------\n";
            cout << "Activar/Desactivar Iluminación: I\n";
            cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
            cout << "Encender/Apagar luz: 0-1\n";
            cout << "Variación de Alpha: A\n";
            cout << "Variación de Beta: B\n";
            cout << "Incrementar Ángulo: >\n";
            cout << "Decrementar Ángulo: <\n";
            cout << "Activar animación de la luz puntual (luz0): P\n";
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
               animacionLuz = false;
            }

            cout << "\n-------OPCIONES DE ILUMINACIÓN-------\n";
            cout << "Activar/Desactivar Iluminación: I\n";
            cout << "Cambiar Visualización Suave/Plana (Suave por defecto): T\n";
            cout << "Encender/Apagar luz: 0-1\n";
            cout << "Variación de Alpha: A\n";
            cout << "Variación de Beta: B\n";
            cout << "Incrementar Ángulo: >\n";
            cout << "Decrementar Ángulo: <\n";
            cout << "Activar animación de la luz puntual (luz0): P\n";
         }
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

      case '+':
         if(modoMenu==ANIMACION){
            if(!animacionAutomatica){
               switch(gradoLibertad){
                  case -1:
                     cout << "No se ha seleccionado ningún grado de libertad\n";
                  break;

                  case 0:
                     r2->animarPeriscopio(0,-0.05);
                  break;

                  case 1:
                     r2->animarPeriscopio(0.05,0);
                  break;

                  case 2:
                     r2->animarCabeza(0.05);
                  break;

                  case 3:
                     r2->animarCuerpo(0.05);
                  break;
               }
            }
            else{
               switch(gradoLibertad){
                  case -1:
                     if(abs(v_Cuerpo) < max_speed){
                        v_Cuerpo *= 2;
                     }

                     if(abs(v_Cabeza) < max_speed){
                        v_Cabeza *= 2;
                     }

                     if(abs(v_a_Periscopio) < max_speed){
                        v_a_Periscopio *= 2;
                     }

                     if(abs(v_h_Periscopio) < max_speed){
                        v_h_Periscopio *= 2;
                     }
                  break;

                  case 0:
                     if(abs(v_h_Periscopio) < max_speed){
                        v_h_Periscopio *= 2;
                     }
                  break;

                  case 1:
                     if(abs(v_a_Periscopio) < max_speed){
                        v_a_Periscopio *= 2;
                     }
                  break;

                  case 2:
                     if(abs(v_Cabeza) < max_speed){
                        v_Cabeza *= 2;
                     }
                  break;

                  case 3:
                     if(abs(v_Cuerpo) < max_speed){
                        v_Cuerpo *= 2;
                     }
                  break;
               }
            }
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case '-':
         if(modoMenu==ANIMACION){
            if(!animacionAutomatica){
               switch(gradoLibertad){
                  case -1:
                     cout << "No se ha seleccionado ningún grado de libertad\n";
                  break;

                  case 0:
                     r2->animarPeriscopio(0,0.05);
                  break;

                  case 1:
                     r2->animarPeriscopio(-0.05,0);
                  break;

                  case 2:
                     r2->animarCabeza(-0.05);
                  break;

                  case 3:
                     r2->animarCuerpo(-0.05);
                  break;
               }
            }
            else{
               switch(gradoLibertad){
                  case -1:
                     if(abs(v_Cuerpo) > min_speed){
                        v_Cuerpo /= 2;
                     }

                     if(abs(v_Cabeza) > min_speed){
                        v_Cabeza /= 2;
                     }

                     if(abs(v_a_Periscopio) > min_speed){
                        v_a_Periscopio /= 2;
                     }

                     if(abs(v_h_Periscopio) > min_speed){
                        v_h_Periscopio /= 2;
                     }
                  break;

                  case 0:
                     if(abs(v_h_Periscopio) > min_speed){
                        v_h_Periscopio /= 2;
                     }
                  break;

                  case 1:
                     if(abs(v_a_Periscopio) > min_speed){
                        v_a_Periscopio /= 2;
                     }
                  break;

                  case 2:
                     if(abs(v_Cabeza) > min_speed){
                        v_Cabeza /= 2;
                     }
                  break;

                  case 3:
                     if(abs(v_Cuerpo) > min_speed){
                        v_Cuerpo /= 2;
                     }
                  break;
               }
            }
         }
         else{
            cout << "Opción inválida\n";
         }
      break;

      case 'M':
         if(modoMenu==NADA){
            modoMenu=ANIMACION;
            cout << "\n-------OPCIONES DE ANIMACIÓN------\n";
            cout << "Activar/Desactivar animación automática: A\n";
            cout << "Mover Periscopio: 0\n";
            cout << "Girar Periscopio: 1\n";
            cout << "Girar Cabeza: 2\n";
            cout << "Girar Cuerpo: 3\n";
            cout << "Aumentar valor del grado seleccionado (";
            if(gradoLibertad < 0){
               cout << "-";
            }
            else{
               cout << gradoLibertad;
            }
            cout << "): +\n";

            cout << "Decrementar valor del grado seleccionado (";
            if(gradoLibertad < 0){
               cout << "-";
            }
            else{
               cout << gradoLibertad;
            }
            cout << "): -\n";
            cout << "Volver al menú principal: Q\n";
         }

         else if(modoMenu==SELOBJETO){
            if(!mundoB){
               cout << "Se ha activado el mundo\n";
               mundoB = true;
            }
            else{
               cout << "Se ha desactivado el mundo\n";
               mundoB = false;
            }

            cout << "\n-------OPCIONES DE SELECCIÓN DE OBJETO-------\n";
            cout << "Activar/Desactivar Cubo: C\n";
            cout << "Activar/Desactivar R2: R\n";
            cout << "Activar/Desactivar Lata: L\n";
            cout << "Activar/Desactivar Mundo: M";
            cout << "Activar/Desactivar Tetraedro: T\n";
            cout << "Activar/Desactivar Peon: P\n";
            cout << "Activar/Desactivar Hormiga: H\n";
            cout << "Volver al menú principal: Q\n";
         }

         else{
            cout << "Opción Inválida\n";
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
         camaras[camara_activa]->rotar(1,1);
         //Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         camaras[camara_activa]->rotar(1,-1);
         //Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         camaras[camara_activa]->rotar(0,1);
         //Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         camaras[camara_activa]->rotar(0,-1);
         //Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camara_activa]->zoom(1.2);
         change_projection();
         //Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camara_activa]->zoom(0.8333);
         change_projection();
         //Observer_distance /= 1.2 ;
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

void Escena::change_projection()
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   //const float wx = float(Height)*ratio_xy ;
   //glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
   camaras[camara_activa]->setProjection();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   float ratio = (float)newWidth / (float)newHeight;
   for(int i = 0; i < 3; i++){
      camaras[i]->redimensionar(ratio);
   }
   change_projection();
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
   camaras[camara_activa]->setObserver();
}

void Escena::clickRaton(int boton, int estado, int x, int y){
   xant = x;
   yant = y;

   if(boton == GLUT_RIGHT_BUTTON){
      if(estado == GLUT_DOWN){
         estadoRaton=MOVIENDO_CAMARA;
      }
      else{
         estadoRaton=NOACTIVO;
      }
   }
   else if(boton == MOUSE_WHEEL_UP){
      camaras[camara_activa]->zoom(0.8333);
      change_projection();
   }
   else if(boton == MOUSE_WHEEL_DOWN){
      camaras[camara_activa]->zoom(1.2);
      change_projection();
   }

   else if(boton == GLUT_LEFT_BUTTON){
      if(estado == GLUT_DOWN)
         seleccion(x,y);
   }
}

void Escena::ratonMovido(int x, int y){
   if(estadoRaton==MOVIENDO_CAMARA){
      if(camara_activa == 0){
         camaras[camara_activa]->rotar(1,(x-xant)*0.1);
         camaras[camara_activa]->rotar(0,(y-yant)*0.1);
      }
      else{
         camaras[camara_activa]->rotar(1,(x-xant)*0.3);
         camaras[camara_activa]->rotar(0,(y-yant)*0.3);
      }

      xant = x;
      yant = y;
   }
}

bool comparaColores(Tupla3f uno, Tupla3f otro){
   return (uno[0] == otro[0] && uno[1] == otro[1] && uno[2] == otro[2]);
}

void Escena::seleccion(int x, int y){
   dibujaSeleccion();
   
   GLint viewport[4];
   GLfloat pixel[3];
   Tupla3f color;

   glGetIntegerv(GL_VIEWPORT,viewport);

   glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_FLOAT,(void *)pixel);

   color[0] = pixel[0];
   color[1] = pixel[1];
   color[2] = pixel[2];

   if(comparaColores({0,0,0},color)){
      if(objSeleccionado[camara_activa] == MODELO){
         r2->deseleccionar();
         camaras[camara_activa]->unsetSeleccion();
         objSeleccionado[camara_activa] = NO;
      }
      else{
         std::cout << "Se ha seleccionado el modelo jerarquico R2\n";
         deseleccionarObjeto();
         r2->seleccionar();
         camaras[camara_activa]->setSeleccion({0,9,-40});
         objSeleccionado[camara_activa] = MODELO;
      }
   }
   else if(comparaColores({1,0,0},color)){
      if(objSeleccionado[camara_activa] == TETRAEDRO){
         tetraedro->deseleccionar();
         camaras[camara_activa]->unsetSeleccion();
         objSeleccionado[camara_activa] = NO;
      }
      else{
         std::cout << "Se ha seleccionado el tetraedro\n";
         deseleccionarObjeto();
         tetraedro->seleccionar();
         camaras[camara_activa]->setSeleccion({-50,-50,100});
         objSeleccionado[camara_activa] = TETRAEDRO;
      }
   }
   else if(comparaColores({0,1,0},color)){
      if(objSeleccionado[camara_activa] == CUBO){
         cubo->deseleccionar();
         camaras[camara_activa]->unsetSeleccion();
         objSeleccionado[camara_activa] = NO;
      }
      else{
         std::cout << "Se ha seleccionado el cubo\n";
         deseleccionarObjeto();
         cubo->seleccionar();
         camaras[camara_activa]->setSeleccion({80,-25,0});
         objSeleccionado[camara_activa] = CUBO;
      }
   }
   else if(comparaColores({0,0,1},color)){
      if(objSeleccionado[camara_activa] == LATA){
         lata->deseleccionar();
         camaras[camara_activa]->unsetSeleccion();
         objSeleccionado[camara_activa] = NO;
      }
      else{
         std::cout << "Se ha seleccionado la lata\n";
         deseleccionarObjeto();
         lata->seleccionar();
         camaras[camara_activa]->setSeleccion({80,-50,80});
         objSeleccionado[camara_activa] = LATA;
      }
   }
   else if(comparaColores({1,1,0},color)){
      if(objSeleccionado[camara_activa] == MUNDO){
         esfera->deseleccionar();
         camaras[camara_activa]->unsetSeleccion();
         objSeleccionado[camara_activa] = NO;
      }
      else{
         std::cout << "Se ha seleccionado la esfera (mundo)\n";
         deseleccionarObjeto();
         esfera->seleccionar();
         camaras[camara_activa]->setSeleccion({-70,150,0});
         objSeleccionado[camara_activa] = MUNDO;
      }
   }
   else if(comparaColores({0,1,1},color)){
      if(objSeleccionado[camara_activa] == PEON){
         peon->deseleccionar();
         camaras[camara_activa]->unsetSeleccion();
         objSeleccionado[camara_activa] = NO;
      }
      else{
         std::cout << "Se ha seleccionado el peon\n";
         deseleccionarObjeto();
         peon->seleccionar();
         camaras[camara_activa]->setSeleccion({-70,0,0});
         objSeleccionado[camara_activa] = PEON;
      }
   }
   else if(comparaColores({1,0,1},color)){
      if(objSeleccionado[camara_activa] == HORMIGA){
         hormiga->deseleccionar();
         camaras[camara_activa]->unsetSeleccion();
         objSeleccionado[camara_activa] = NO;
      }
      else{
         std::cout << "Se ha seleccionado la hormiga\n";
         deseleccionarObjeto();
         hormiga->seleccionar();
         camaras[camara_activa]->setSeleccion({30,-30,80});
         objSeleccionado[camara_activa] = HORMIGA;
      }
   }
   else{
      camaras[camara_activa]->unsetSeleccion();
      deseleccionarObjeto();
      objSeleccionado[camara_activa] = NO;
   }
}

void Escena::deseleccionarObjeto(){
   switch (objSeleccionado[camara_activa]){
      case MODELO:
         r2->deseleccionar();
      break;

      case TETRAEDRO:
         tetraedro->deseleccionar();
      break;

      case CUBO:
         cubo->deseleccionar();
      break;

      case LATA:
         lata->deseleccionar();
      break;

      case MUNDO:
         esfera->deseleccionar();
      break;

      case PEON:
         peon->deseleccionar();
      break;

      case HORMIGA:
         hormiga->deseleccionar();
      break;
   }
}

void Escena::seleccionarObjeto(){
   switch (objSeleccionado[camara_activa]){
      case MODELO:
         r2->seleccionar();
      break;
      
      case TETRAEDRO:
         tetraedro->seleccionar();
      break;

      case CUBO:
         cubo->seleccionar();
      break;

      case LATA:
         lata->seleccionar();
      break;

      case MUNDO:
         esfera->seleccionar();
      break;

      case PEON:
         peon->seleccionar();
      break;

      case HORMIGA:
         hormiga->seleccionar();
      break;
   }
}