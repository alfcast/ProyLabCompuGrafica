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
#include "cmodel/CModel.h"



CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

GLfloat SunDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };			// Diffuse Light Values
GLfloat SunSpecular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat SunShininess[] = { 50.0 };


GLfloat lightPosition[] = { 200.0f, 20.0f, -20.0f, 1.0f };			// Light Position

GLfloat mat_ambienta[] = { 1.0,0.0,1.0, 1.0 };					// Color background
GLfloat mat_diffusea[] = { 0.8,0.1,0.1, 1.0 };					// Object Color main
GLfloat mat_speculara[] = { 0.8,0.2,0.4, 1.0 };
GLfloat mat_shininessa[] = { 50.0f };

CTexture cielo;
CTexture wood;
CTexture wall;
CTexture window;
CTexture blind;
CTexture whiteWood;
CTexture nightstand;
CTexture darkWood;
CTexture ecualizador;
CTexture blackPlastic;
CTexture woodFloor;
CTexture fornitureWood;
CTexture respaldo;
CTexture empty;
CTexture openBox;
CTexture cabecera;

CFiguras pris;
CFiguras figCielo;
CFiguras cubo;
CFiguras sky;

//Figuras de 3D Studio
//CModel tv;

int font=(int)GLUT_BITMAP_HELVETICA_18;

void setMat(GLfloat *amb, GLfloat *diff, GLfloat *spec, GLfloat* shine)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

void construirCasa() {
	//Techo de la casa
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0.0, 220.0, -30.0);
		pris.prisma(2.0, 440.0, 340.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Piso de la casa
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0.0, -220.0, -30.0);
		pris.prisma(1.0, 440.0, 340.0, woodFloor.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared izquierda
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-220.0, 0.0, -30.0);
		glRotatef(90, 0, 0, 1);
		pris.prisma(2.0, 440.0, 340.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha arriba
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(220.0, 140.0, -30.0);
		glRotatef(90, 0, 0, 1);
		pris.prisma(2.0, 160.0, 340.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha derecha
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(220.0, 0.0, 85.0);
		glRotatef(90, 0, 0, 1);
		pris.prisma(2.0, 120.0, 110.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha ventana
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(220.0, 0.0, -30.0);
		glRotatef(90, 0, 0, 1);
		pris.prisma(2.0, 120.0, 120.0, window.GLindex);
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha izquierda
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(220.0, 0.0, -145.0);
		glRotatef(90, 0, 0, 1);
		pris.prisma(2.0, 120.0, 110.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha abajo
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(220.0, -140.0, -30.0);
		glRotatef(90, 0, 0, 1);
		pris.prisma(2.0, 160.0, 340.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared trasera
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0.0, 0.0, -200.0);
		glRotatef(90, 1, 0, 0);
		pris.prisma(2.0, 440.0, 440.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared delantera lateral
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(90.0, 0.0, 140.0);
		glRotatef(90, 1, 0, 0);
		pris.prisma(2.0, 260.0, 440.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared puerta izquierda
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-85.0, 0.0, 140.0);
		glRotatef(90, 1, 0, 0);
		pris.prisma(2.0, 90.0, 440.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared puerta derecha
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-175.0, 0.0, 140.0);
		glRotatef(90, 1, 0, 0);
		pris.prisma(2.0, 90.0, 440.0, wall.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void roperoBuroCaja() {
	//Ropero
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(170.0, -40.0, -150.0);
		pris.prismaT(340.0, 100.0, 100.0, whiteWood.GLindex, blind.GLindex, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Buro
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-160.0, -130.0, -150.0);
		pris.prismaT(180.0, 100.0, 100.0, darkWood.GLindex, nightstand.GLindex, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Amplificador
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(170.0, -170.0, -50.0);
		glRotatef(-45,0,1,0);
		pris.prismaT(100.0, 60.0, 60.0, blackPlastic.GLindex, ecualizador.GLindex, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Caja
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(-30.0, -174.0, 0.0);
		glRotatef(-45, 0, 1, 0);
		pris.prismaT(35.0, 30.0, 30.0, openBox.GLindex, NULL, NULL, NULL, NULL, wood.GLindex, NULL);
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_LIGHTING);
	glPopMatrix();

}

void mesaSilla() {

	//----------------MESA-----------------------------
	//Pata izquierda mesa
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(140.0, -170.0, 30.0);
		pris.prismaT(130.0, 30.0, 30.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pata derecha mesa
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(140.0, -170.0, 110.0);
		pris.prismaT(130.0, 30.0, 30.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Parte superior mesa
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(140.0, -100.0, 70.0);
		pris.prismaT(6.0, 80.0, 140.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//----------------SILLA-----------------------------


	//Pata izquierda silla frontal
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(70.0, -170.0, 40.0);
		//glRotatef(90, 0, 1, 0);
		pris.prismaT(90.0, 8.0, 8.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pata derecha silla frontal
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(70.0, -170.0, 70.0);
		//glRotatef(90, 0, 1, 0);
		pris.prismaT(90.0, 8.0, 8.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pata izquierda silla trasera
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(50.0, -170.0, 40.0);
		//glRotatef(90, 0, 1, 0);
		pris.prismaT(90.0, 8.0, 8.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pata derecha silla trasera
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(50.0, -170.0, 70.0);
		//glRotatef(90, 0, 1, 0);
		pris.prismaT(90.0, 8.0, 8.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Parte superior silla madera
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(66.0, -120.0, 55.0);
		//glRotatef(90, 0, 1, 0);
		pris.prismaT(6.0, 40.0, 40.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Parte superior silla material
	glPushMatrix();
		glTranslatef(66.0, -114.0, 55.0);
		glDisable(GL_TEXTURE_2D);
		setMat(mat_ambienta, mat_diffusea, mat_speculara, mat_shininessa);
		pris.prismaM(6.0, 40.0, 40.0);
		glEnable(GL_TEXTURE_2D);
	glPopMatrix();


	//Respaldo silla
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(50.0, -70.0, 55.0);
		//glRotatef(90, 0, 1, 0);
		pris.prismaT(80.0, 8.0, 40.0, fornitureWood.GLindex, NULL, NULL, respaldo.GLindex, respaldo.GLindex, NULL, NULL);
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_LIGHTING);
	glPopMatrix();

}

void cama() {

	//Pata derecha cama trasera
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(20.0, -170.0, -140.0);
	//glRotatef(90, 0, 1, 0);
	pris.prismaT(90.0, 8.0, 8.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pata derecha cama frontal
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(20.0, -170.0, 0.0);
	//glRotatef(90, 0, 1, 0);
	pris.prismaT(90.0, 8.0, 8.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pata izquierda cama trasera
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-80.0, -170.0, -140.0);
	//glRotatef(90, 0, 1, 0);
	pris.prismaT(90.0, 8.0, 8.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pata izquierda cama frontal
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-80.0, -170.0, 0.0);
	//glRotatef(90, 0, 1, 0);
	pris.prismaT(90.0, 8.0, 8.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Parte superior cama madera
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-30.0, -120.0, -70.0);
	//glRotatef(90, 0, 1, 0);
	pris.prismaT(6.0, 110.0, 150.0, fornitureWood.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//Parte superior cama material
	glPushMatrix();
		glTranslatef(-30.0, -114.0, -70.0);
		glDisable(GL_TEXTURE_2D);
		setMat(mat_ambienta, mat_diffusea, mat_speculara, mat_shininessa);
		pris.prismaM(6.0, 110.0, 150.0);
		glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	//Cabecera
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(-30.0, -64.0, -140.0);
		//glRotatef(90, 0, 1, 0);
		pris.prismaT(100.0, 110.0, 8.0, fornitureWood.GLindex, cabecera.GLindex, cabecera.GLindex, NULL, NULL, NULL, NULL);
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}
			
void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On

	cielo.LoadTGA("Textures/snow.tga");
	cielo.BuildGLTexture();
	cielo.ReleaseImage();

	wood.LoadTGA("Textures/wood.tga");
	wood.BuildGLTexture();
	wood.ReleaseImage();

	wall.LoadTGA("Textures/blueCWall.tga");
	wall.BuildGLTexture();
	wall.ReleaseImage();

	window.LoadTGA("Textures/window.tga");
	window.BuildGLTexture();
	window.ReleaseImage();

	blind.LoadTGA("Textures/blind.tga");
	blind.BuildGLTexture();
	blind.ReleaseImage();

	whiteWood.LoadTGA("Textures/whiteWood.tga");
	whiteWood.BuildGLTexture();
	whiteWood.ReleaseImage();

	nightstand.LoadTGA("Textures/nightstand.tga");
	nightstand.BuildGLTexture();
	nightstand.ReleaseImage();

	darkWood.LoadTGA("Textures/darkWood.tga");
	darkWood.BuildGLTexture();
	darkWood.ReleaseImage();

	ecualizador.LoadTGA("Textures/ecualizador.tga");
	ecualizador.BuildGLTexture();
	ecualizador.ReleaseImage();

	blackPlastic.LoadTGA("Textures/blackPlastic.tga");
	blackPlastic.BuildGLTexture();
	blackPlastic.ReleaseImage();

	woodFloor.LoadTGA("Textures/woodFloor.tga");
	woodFloor.BuildGLTexture();
	woodFloor.ReleaseImage();

	fornitureWood.LoadTGA("Textures/fornitureWood.tga");
	fornitureWood.BuildGLTexture();
	fornitureWood.ReleaseImage();

	respaldo.LoadTGA("Textures/respaldo.tga");
	respaldo.BuildGLTexture();
	respaldo.ReleaseImage();

	empty.LoadTGA("Textures/empty.tga");
	empty.BuildGLTexture();
	empty.ReleaseImage();

	openBox.LoadTGA("Textures/openBox.tga");
	openBox.BuildGLTexture();
	openBox.ReleaseImage();

	cabecera.LoadTGA("Textures/cabecera.tga");
	cabecera.BuildGLTexture();
	cabecera.ReleaseImage();

	//tv._3dsLoad("Models/kitt.3ds");

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, SunDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SunSpecular);

	//glEnable(GL_COLOR_MATERIAL);


	objCamera.Position_Camera(-140,2.5f,360, 140,2.5f,300, 0, 1, 0);


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

	glPushMatrix(); //Principal Push matriz

			glRotatef(g_lookupdown, 1.0f, 0, 0); //Rotamos camara
			glRotatef(-90, 0, 1, 0); //Rotamos camara


			gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
				objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
				objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z); //Configuramos lookat

		
			glPushMatrix(); //Segundo push matriz

					glPushMatrix(); //Creamos cielo
						glDisable(GL_LIGHTING);
						glTranslatef(0, 60, 0);
						figCielo.skybox(750.0, 580.0, 790.0, cielo.GLindex);
						glEnable(GL_LIGHTING);
					glPopMatrix();

					glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

					//glPushMatrix();
					//glDisable(GL_TEXTURE_2D);
					//glTranslatef(200.0,20.0,-20.0);
					//setMat(mat_ambienta, mat_diffusea, mat_speculara, mat_shininessa);
					//glutSolidSphere(4.0, 20, 20);  //Draw Sun (radio,H,V);
					//glEnable(GL_TEXTURE_2D);
					//glPopMatrix();

					construirCasa();

					roperoBuroCaja();

					mesaSilla();

					cama();

					/*glPushMatrix();
						glDisable(GL_COLOR_MATERIAL);
						tv.GLrender(NULL, _SHADED, 1.0);
					glPopMatrix();*/

			glPopMatrix(); //pop del segundo push matriz

	glPopMatrix(); //pop del push matriz principal

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
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 800.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Strafe_Camera(-(CAMERASPEED + 0.1));
			break;

		case 's':
		case 'S':
			objCamera.Strafe_Camera(CAMERASPEED + 0.1);
			break;

		case 'a':
		case 'A':
			objCamera.Move_Camera(-(CAMERASPEED + 0.1));
			break;

		case 'd':
		case 'D':
			objCamera.Move_Camera(CAMERASPEED + 0.1);
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
