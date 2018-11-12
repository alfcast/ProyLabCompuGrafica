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

int font = (int)GLUT_BITMAP_HELVETICA_18;

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
CTexture hair;
CTexture eye;
CTexture discoBall;
CTexture pillow;
CTexture wooden;
CTexture orangeWall;
CTexture stoneWall;
CTexture whiteStone;

CFiguras pris;
CFiguras figCielo;
CFiguras cubo;
CFiguras sky;

//Figuras de 3D Studio
//CModel tv;

#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames puerta
	float degree;
	float incDegree;

}FRAMEP;

typedef struct _framep
{
	//Variables para GUARDAR Key Frames perro
	float rotPaso1;
	float rotPaso2;
	float posZ;
	float incDesplaza;
	float incDegree1;
	float incDegree2;

}FRAMEPerro;

FRAMEP KeyFrameP[MAX_FRAMES];
int playPuerta = 1;
int playIndexP = 0;
float rotPuerta = 0;


FRAMEPerro KeyFramePerro[MAX_FRAMES];
int playIndexPerro = 0;
float rotPaso1 = 0, posZ = 0, rotPaso2 = 0;

float esfera = 0, rotVentana = 0, transAlm = 0, rotAlm = 0;
int abre = 1;

int w = 500, h = 500;
int frame = 0;


void interpolationPuerta(void)
{
	KeyFrameP[playIndexP].incDegree = (KeyFrameP[playIndexP + 1].degree - KeyFrameP[playIndexP].degree) / i_max_steps;
}

void interpolationPerro(void)
{
	KeyFramePerro[playIndexPerro].incDegree1 = (KeyFramePerro[playIndexPerro + 1].rotPaso1 - KeyFramePerro[playIndexPerro].rotPaso1) / i_max_steps;
	KeyFramePerro[playIndexPerro].incDegree2 = (KeyFramePerro[playIndexPerro + 1].rotPaso2 - KeyFramePerro[playIndexPerro].rotPaso2) / i_max_steps;
	KeyFramePerro[playIndexPerro].incDesplaza = (KeyFramePerro[playIndexPerro + 1].posZ - KeyFramePerro[playIndexPerro].posZ) / i_max_steps;
}

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
		pris.prismaT(2.0, 440.0, 340.0, wall.GLindex, NULL, NULL, NULL,NULL ,orangeWall.GLindex, NULL);
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
		pris.prismaT(440.0, 2.0, 340.0, wall.GLindex, NULL, NULL,NULL , orangeWall.GLindex, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha arriba
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(220.0, 140.0, -30.0);
		pris.prismaT(160.0, 2.0, 340.0, wall.GLindex, NULL, NULL, orangeWall.GLindex, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha derecha
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(220.0, 0.0, 85.0);
		pris.prismaT(120.0, 2.0, 110.0, wall.GLindex, NULL, NULL, orangeWall.GLindex, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha ventana
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(220.0, 60.0, -30.0);
		glRotatef(rotVentana, 0, 0, 1);
		glTranslatef(0.0, -60.0, 0.0);
		pris.prisma(120.0, 2.0, 120.0, window.GLindex);
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha izquierda
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(220.0, 0.0, -145.0);
		pris.prismaT(120.0, 2.0, 110.0, wall.GLindex, NULL, NULL, orangeWall.GLindex, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared derecha abajo
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(220.0, -140.0, -30.0);
		pris.prismaT(160.0, 2.0, 340.0, wall.GLindex, NULL, NULL, orangeWall.GLindex, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared trasera
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0.0, 0.0, -200.0);
		pris.prismaT(440.0, 440.0, 2.0, wall.GLindex, NULL, orangeWall.GLindex, NULL, NULL, NULL , NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared delantera lateral
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(90.0, 0.0, 140.0);
		pris.prismaT(440.0, 260.0, 2.0, wall.GLindex, orangeWall.GLindex, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared puerta derecha
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-40.0, 0.0, 140.0);
		glRotatef(rotPuerta, 0, 1, 0);
		glTranslatef(-45.0, 0.0, 0.0);
		pris.prisma(440.0, 90.0, 2.0, wooden.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Pared puerta izquierda
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-220.0, 0.0, 140.0);
		glRotatef(-rotPuerta, 0, 1, 0);
		glTranslatef(45.0, 0.0, 0.0);
		pris.prisma(440.0, 90.0, 2.0, wooden.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void fachada() {

	//pilar izquierdo
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-200.0, 0.0, 250.0);
		pris.prismaT(440.0, 30.0, 30.0, stoneWall.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//pilar central
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0.0, 0.0, 250.0);
		pris.prismaT(440.0, 30.0, 30.0, stoneWall.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//pilar central
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(200.0, 0.0, 250.0);
		pris.prismaT(440.0, 30.0, 30.0, stoneWall.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	//Techo
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(0.0, 220.0, 220.0);
		pris.prisma(10.0, 440.0, 150.0, stoneWall.GLindex);
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

void esferaRota() {
	//Esfera giratoria
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1);
		glTranslatef(-60.0, 140.0, -90.0);
		glRotatef(esfera, 0, 1, 0);
		pris.esfera(20.0, 100.0, 100.0, discoBall.GLindex);
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_LIGHTING);

		//Hilo del que pende
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(0.0, 20.0, 0.0);
			pris.cilindro(0.5, 60.0, 150.0, hair.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

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

	//Almohada
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(-30.0, -95.0+transAlm, -110.0);
		glRotatef(60-rotAlm, 1,0, 0);
		pris.prismaT(10.0, 70.0, 40.0, pillow.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);
	glPopMatrix();
}

void perro() {
	//Cuerpo
	glPushMatrix();

		glDisable(GL_LIGHTING);
		glTranslatef(280.0, -170.0, -80.0+posZ);
		glRotatef(180, 0, 1, 0);
		pris.prismaT(30.0, 30.0, 80.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
		glEnable(GL_LIGHTING);

		//---------------------Patas---------------------------

		//Pierna izquierda  frontal
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(-15.0, -25.0, -40.0);
			glRotatef(rotPaso1,1,0,0);
			pris.prismaT(60.0, 8.0, 8.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
			glEnable(GL_LIGHTING);

			//Pata
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(0.0, -33.0, -4.0);
				pris.prismaT(6.0, 8.0, 16.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
				glEnable(GL_LIGHTING);
			glPopMatrix();

		glPopMatrix();

		//pierna izquierda  trasera
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(-15.0, -25.0, 40.0);
			glRotatef(-rotPaso2, 1, 0, 0);
			pris.prismaT(60.0, 8.0, 8.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
			glEnable(GL_LIGHTING);

			//Pata
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(0.0, -33.0, -4.0);
				pris.prismaT(6.0, 8.0, 16.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
				glEnable(GL_LIGHTING);
			glPopMatrix();

		glPopMatrix();
	
		//pierna derecha  frontal
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(15.0, -25.0, -40.0);
			glRotatef(rotPaso2, 1, 0, 0);
			pris.prismaT(60.0, 8.0, 8.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
			glEnable(GL_LIGHTING);

			//Pata
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(0.0, -33.0, -4.0);
				pris.prismaT(6.0, 8.0, 16.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
				glEnable(GL_LIGHTING);
			glPopMatrix();

		glPopMatrix();

		//pierna derecha  trasera
		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(15.0, -25.0, 40.0);
			glRotatef(-rotPaso1, 1, 0, 0);
			pris.prismaT(60.0, 8.0, 8.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
			glEnable(GL_LIGHTING);

			//Pata
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(0.0, -33.0, -4.0);
				pris.prismaT(6.0, 8.0, 16.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
				glEnable(GL_LIGHTING);
			glPopMatrix();

		glPopMatrix();


		//--------------Cuello------------------------

		
		glPushMatrix();

			glDisable(GL_LIGHTING);
			glTranslatef(0.0, 30.0, -40.0);
			glRotatef(-20,1,0,0);
			pris.prismaT(60.0, 10.0, 10.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
			glEnable(GL_LIGHTING);

			//----------------Cabeza--------------
			glPushMatrix();
				glDisable(GL_LIGHTING);
				glTranslatef(0.0, 35.0, -10.0);
				pris.prismaT(10.0, 10.0, 30.0, hair.GLindex, NULL, NULL, NULL, NULL, NULL, NULL);
				glEnable(GL_LIGHTING);

				//---------------Ojos--------------------
				glPushMatrix();
					glDisable(GL_LIGHTING);
					glRotatef(20, 1, 0, 0);
					glTranslatef(3.0, 12.0, 8.0);
					glRotatef(-90, 0, 1, 0);
					pris.esfera(4.0, 100.0, 100.0, eye.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

				glPushMatrix();
					glDisable(GL_LIGHTING);
					glRotatef(20, 1, 0, 0);
					glTranslatef(-3.0, 12.0, 8.0);
					glRotatef(-90, 0, 1, 0);
					pris.esfera(4.0, 100.0, 100.0, eye.GLindex);
					glEnable(GL_LIGHTING);
				glPopMatrix();

			glPopMatrix();

		glPopMatrix();

		//----------------Cola----------------------------------

		glPushMatrix();
			glDisable(GL_LIGHTING);
			glTranslatef(0.0, 10.0, 40.0);
			glRotatef(45,1,0,0);
			pris.cilindro(3.0, 30.0, 150.0, hair.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		
	glPopMatrix();
	

}

void perroDefault() {
	rotPaso1 = 0;
	posZ = 0;
	rotPaso2 = 0;

	KeyFramePerro[0].rotPaso1 = 0;
	KeyFramePerro[0].rotPaso2 = 0;
	KeyFramePerro[0].posZ = 0;
	KeyFramePerro[0].incDesplaza = 0;
	KeyFramePerro[0].incDegree1 = 0;
	KeyFramePerro[0].incDegree2 = 0;

	KeyFramePerro[1].rotPaso1 = 25;
	KeyFramePerro[1].rotPaso2 = 0;
	KeyFramePerro[1].posZ = 40;
	KeyFramePerro[1].incDesplaza = 0;
	KeyFramePerro[1].incDegree1 = 0;
	KeyFramePerro[1].incDegree2= 0;

	KeyFramePerro[2].rotPaso1 = 0;
	KeyFramePerro[2].rotPaso2 = 25;
	KeyFramePerro[2].posZ = 80;
	KeyFramePerro[2].incDesplaza = 0;
	KeyFramePerro[2].incDegree1 = 0;
	KeyFramePerro[2].incDegree2 = 0;

	KeyFramePerro[3].rotPaso1 = 25;
	KeyFramePerro[3].rotPaso2 = 0;
	KeyFramePerro[3].posZ = 40;
	KeyFramePerro[3].incDesplaza = 0;
	KeyFramePerro[3].incDegree1 = 0;
	KeyFramePerro[3].incDegree2 = 0;

	KeyFramePerro[4].rotPaso1 = 0;
	KeyFramePerro[4].rotPaso2 = 25;
	KeyFramePerro[4].posZ = 0;
	KeyFramePerro[4].incDesplaza = 0;
	KeyFramePerro[4].incDegree1 = 0;
	KeyFramePerro[4].incDegree2 = 0;

	/*KeyFramePerro[5].rotPaso1 = 0;
	KeyFramePerro[5].rotPaso2 = 0;
	KeyFramePerro[5].posZ = 0;
	KeyFramePerro[5].incDesplaza = 0;
	KeyFramePerro[5].incDegree1 = 0;
	KeyFramePerro[5].incDegree2 = 0;*/
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

	wall.LoadTGA("Textures/blueWall.tga");
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

	hair.LoadTGA("Textures/hair.tga");
	hair.BuildGLTexture();
	hair.ReleaseImage();

	eye.LoadTGA("Textures/eye.tga");
	eye.BuildGLTexture();
	eye.ReleaseImage();

	discoBall.LoadTGA("Textures/discoBall.tga");
	discoBall.BuildGLTexture();
	discoBall.ReleaseImage();

	pillow.LoadTGA("Textures/pillow.tga");
	pillow.BuildGLTexture();
	pillow.ReleaseImage();

	wooden.LoadTGA("Textures/wooden.tga");
	wooden.BuildGLTexture();
	wooden.ReleaseImage();

	orangeWall.LoadTGA("Textures/orangeWall.tga");
	orangeWall.BuildGLTexture();
	orangeWall.ReleaseImage();

	stoneWall.LoadTGA("Textures/stoneWall2.tga");
	stoneWall.BuildGLTexture();
	stoneWall.ReleaseImage();

	whiteStone.LoadTGA("Textures/whiteStone.tga");
	whiteStone.BuildGLTexture();
	whiteStone.ReleaseImage();

	//tv._3dsLoad("Models/kitt.3ds");

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, SunDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SunSpecular);

	//glEnable(GL_COLOR_MATERIAL);


	objCamera.Position_Camera(-140,2.5f,360, 140,2.5f,300, 0, 1, 0);

	//NEW Iniciar variables de KeyFramePs
	for (int i = 0; i<MAX_FRAMES; i++)
	{
		KeyFrameP[i].incDegree = 0;
		KeyFrameP[i].degree = 26 * i;
	}

	perroDefault();
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

					fachada();

					roperoBuroCaja();

					mesaSilla();

					cama();

					esferaRota();

					perro();

					/*glPushMatrix();
						glDisable(GL_COLOR_MATERIAL);
						tv.GLrender(NULL, _SHADED, 1.0);
						glEnable(GL_COLOR_MATERIAL);
					glPopMatrix();*/

			glPopMatrix(); //pop del segundo push matriz

	glPopMatrix(); //pop del push matriz principal

	glutSwapBuffers ( );

}

void animacion()
{

	//Movimiento de la puerta
	if (playPuerta)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndexP++;
			if (playIndexP > 4)	//end of total animation?
			{
				printf("termina anim\n");
				playIndexP = 0;
				playPuerta = 0;
				rotPuerta = 0;
			}
			else //Next frame interpolationPuertas
			{
				i_curr_steps = 0; //Reset counter
				interpolationPuerta(); //interpolationPuerta
			}
		}
		else
		{
			if (playIndexP == 0)
			{
				interpolationPuerta();
			}
			//Draw animation
			rotPuerta += KeyFrameP[playIndexP].incDegree;

			i_curr_steps++;
		}
	}

	//Movimiento perro
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndexPerro++;
			if (playIndexPerro > 4)	//end of total animation?
			{
				printf("termina anim\n");
				playIndexPerro = 0;
				perroDefault();
			}
			else //Next frame interpolationPuertas
			{
				i_curr_steps = 0; //Reset counter
				interpolationPerro(); //interpolationPuerta
			}
		}
		else
		{
			if (playIndexPerro == 0)
			{
				interpolationPerro();
			}
			//Draw animation
			rotPaso1 += KeyFramePerro[playIndexPerro].incDegree1;
			posZ += KeyFramePerro[playIndexPerro].incDesplaza;
			rotPaso2 += KeyFramePerro[playIndexPerro].incDegree2;

			i_curr_steps++;
		}
		
	//Movimiento esfera
		if (esfera >= 360)
		{
			esfera = 0;
		}
		else {
			esfera++;
		}

	//Movimiento esfera
		if (rotVentana >= 90)
		{
			rotVentana--;
			abre = 0;
		}
		else if(rotVentana <= 0){
			rotVentana++;
			abre = 1;
		}
		else if (abre) {
			rotVentana++;
		}
		else {
			rotVentana--;
		}
		
	//Movimiento almohada
		if (rotAlm >= 60)
		{
			rotAlm = 0;
			transAlm = 0;
		}
		else {
			rotAlm++;
			transAlm -= 0.1;
		}

	glutPostRedisplay();
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

		case 'o':
		case 'O':
			objCamera.UpDown_Camera(CAMERASPEED);
			break;

		case 'p':
		case 'P':
			objCamera.UpDown_Camera(-CAMERASPEED);
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
