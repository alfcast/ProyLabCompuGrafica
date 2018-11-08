//Semestre 2019 - 1
//************************************************************//
//************************************************************//
//************** Alumno: Castillo Reyes Alfonso Ignacio*******//
//************************************************************//
//************************************************************//
//************************************************************//
//************************************************************//

#include "Headers/texture.h"
#include "Headers/figuras.h"
#include "Headers/Camera.h"



CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

CTexture cielo;
CTexture madera;
CTexture wall;

CFiguras pris;
CFiguras figCielo;
CFiguras cubo;
CFiguras sky;

int font=(int)GLUT_BITMAP_HELVETICA_18;

void construirCasa() {
	//Techo de la casa
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0.0, 220.0, -10.0);
	pris.prisma(2.0, 440.0, 340.0, wall.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared izquierda
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-220.0, 120.0, -10.0);
	glRotatef(90, 0, 0, 1);
	pris.prisma(2.0, 440.0, 340.0, wall.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(220.0, 120.0, -10.0);
	glRotatef(90, 0, 0, 1);
	pris.prisma(2.0, 440.0, 340.0, wall.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared trasera
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(0.0, 50.0, -180.0);
	glRotatef(90, 1, 0, 0);
	pris.prisma(2.0, 440.0, 340.0, wall.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared delantera lateral
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(90.0, 50.0, 160.0);
	glRotatef(90, 1, 0, 0);
	pris.prisma(2.0, 260.0, 340.0, wall.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared puerta izquierda
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-85.0, 50.0, 160.0);
	glRotatef(90, 1, 0, 0);
	pris.prisma(2.0, 90.0, 340.0, wall.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared puerta derecha
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-175.0, 50.0, 160.0);
	glRotatef(90, 1, 0, 0);
	pris.prisma(2.0, 90.0, 340.0, wall.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
			
void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	cielo.LoadTGA("Textures/CieloAtardecer.tga");
	cielo.BuildGLTexture();
	cielo.ReleaseImage();

	madera.LoadTGA("Textures/wood.tga");
	madera.BuildGLTexture();
	madera.ReleaseImage();

	wall.LoadTGA("Textures/wall.tga");
	wall.BuildGLTexture();
	wall.ReleaseImage();

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);


}

void pintaTexto(float x, float y, float z, void *font,char *string)
{
  
  char *c;     //Almacena los caracteres a escribir
  glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
  //glWindowPos2i(150,100);
  for (c=string; *c != '\0'; c++) //Condicion de fin de cadena
  {
    glutBitmapCharacter(font, *c); //imprime
  }
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity(); //Cargamos matriz identidad

	glPushMatrix(); //Primer Push matriz

			glRotatef(g_lookupdown, 1.0f, 0, 0); //Rotamos camara

			gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
				objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
				objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z); //Configuramos lookat

		
			glPushMatrix(); //Segundo push matriz

					glPushMatrix(); //Creamos cielo
						glDisable(GL_LIGHTING);
						glTranslatef(0, 60, 0);
						figCielo.skybox(580.0, 320.0, 580.0, cielo.GLindex);
						glEnable(GL_LIGHTING);
					glPopMatrix();

					construirCasa();

			glPopMatrix(); //pop del segundo push matriz

	glPopMatrix(); //pop del primer push matriz

	glutSwapBuffers ( );

}

void animacion()
{
	
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 700.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.2 );
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.2));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.4));
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.4 );
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

int main ( int argc, char** argv )   // Main Function
{

  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (500, 500);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Final"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );


  glutMainLoop        ( );          // 

  return 0;
}
