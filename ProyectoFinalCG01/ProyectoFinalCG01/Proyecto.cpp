//******************************************************************//
//*****************************************************************//
//*************			Visual Studio 2017					   ****//
//*************			Proyecto Final					 		***//
//*************   		Computación Gráfica   Gpo:1            ***//
//*************			Alumno: Ochoa Nava Jose Leonardo        **//


// flecha derecha -> girar a la derecha
// flecha izquierda	-> girar izquierda
// flecha arriba	-> girar arriba
// flecha abajo	->	girar abajo
// Barra espacio -> recorrido automatico
// W	->	avanzar al frente
// A	->	moverse a la izquierda
// S	->	moverse hacia abajo
// D	->	moverse hacia la derecha


#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

static GLuint ciudad_display_list;	//Display List for the Monito

//Variables de dibujo y manipulacion
//Agrego variables
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0, rotRodDer = 0, rotRodPiernaIzq = 0.0;
float rotRodPiernaDer = 0.0f, rotCabeza = 0.0, rotCuello = 0.0;
float rotCin = 0.0;
float rotBI = 0.0, rotBD = 0.0;
float giroMonito = 0;
float giropuerta = 0;
#define MAX_FRAMES 400
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX 
	float posY;		//Variable para PosicionY 
	float posZ;		//Variable para PosicionZ 
	float incX;		//Variable para IncrementoX DESPLAZA EN X
	float incY;		//Variable para IncrementoY DESPLAZA EN Y
	float incZ;		//Variable para IncrementoZ DESPLAZA EN Z
	float rotRodIzq; //ROTAR la rodilla izquierda
	float rotRodDer; //rota rodilla derecha
	float rotRodPiernaIzq; //Rota pierna izquierda
	float rotRodPiernaDer; //Rota piera derecha
	float rotCabeza = 0.0; //rota cabeza
	float rotCuello = 0.0; //rota cuello
	float rotBI = 0.0; //rota brazo izquierdo
	float rotBD = 0.0; //rota brazo derecho
	float rotCin = 0.0;
	float rotInc; //rotacion inicial rodilla izquierda
	float rotIncDer; //rotacion inicial rodilla derecha
	float rotIncPI; //rotacion inicial pierna izquierda
	float rotIncPD; //rotacion inicial pierna derecha
	float rotIncC; //rotacion inicial de la cabeza
	float rotIncBI; //rotacion inicial del brazo izquierdo
	float rotIncBD; //rotacion inicial del brazo derecho
	float rotIncCin; //rotacion inicial de la cintura
	float rotIncCu;
	float giroMonito;
	float giroMonitoInc;
}
FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;
bool play = false;
int playIndex = 0;

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera
CCamera objCamera2; //Recorrido automatico
CCamera objCamera3;
CCamera objCamera4;
CCamera objCamera5;
CCamera *objCameraptr;

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = { 22 };

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01
CTexture pasto; //textura de pasto
CTexture block;
CTexture puerta; //textura de puerta
CTexture block2;  //textura de los minibloques
CTexture grava; //para los cono
CTexture metal; //para el cilindro guia
CTexture yellow; //para los rieles
CTexture blue; //para la textura de los barrotes
CTexture rie; //textura para las llantas
CTexture madera;
CTexture MetalSoportes;
CTexture Morado;
CTexture ColoresSoporte;
CTexture Kila;

CFiguras cubo;
CFiguras sky;

float abrirPuerta = 0;
CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;
CFiguras fig5;
CFiguras fig6;
CFiguras fig7;
CFiguras pisoObj;
CFiguras pilar;
CFiguras fachada;
CFiguras rieles;
CFiguras car;
CFiguras llanta;;
CFiguras soporte;

CModel flag;
CModel ArbolParque;
CModel maceta;
CModel parque;
CModel Maceta2;
CModel Pajaro;
CModel Arbol1;
CModel arbol;
CModel SofaPremium;
CModel Tienda;
CModel Rakc;
CModel Dove;	//ave
CModel Bird;
CModel Drone;
CModel Banca;
CModel Mesita;
CModel Sofa;

//Animacion por maquina de estados
float movKitX = 0.0;
float movKitY = 0.0;
float movKitZ = 0.0;
float rotKitA = 0.0;
float rotKitB = 0.0;
float rotKitC = 0.0;
float rotLlanta = 0.0;
float rotpendulo = 0.0;			//Pendulo
float trasKila = 0.0;			//Kilahuea
float movXAve = 0.0;			//Aves
float movZAve = 0.0;			 //Aves
float rotAve1 = 0.0;			 //Aves
//Otras aves
float movXAve1 = 0.0;
float movZAv2 = 0.0;
float rotAve2 = 0.0;
bool inicio = true;
bool estadoA = true;
bool estadoB = false;
bool estadoC = false;
bool estadoD = false;
bool estadoDA = false; //estado auxiliar
bool estadoE = false;
bool estadoEA = false; //estado auxiliar
bool estadoF = false;
bool estadoFA = false; //estado auxiliar
bool estadoG = false;
bool estadoH = false;
bool estadoHA = false; //estado auxiliar;
bool estadoI = false;
bool estadoIA = false;
bool estadoJ = false;
bool estadoK = false;
bool estadoL = false;
bool estadoM = false;
bool estadoN = false;
bool estadoO = false;
bool estadoMA = false; //estado para rotar
bool estadoOA = false; //estado auxiliar para rotar
bool estadoP = false;
bool estadoQ = false;
bool estadoQA = false; //estado auxiliar
bool estadoR = false;
bool estadoS = false;
bool estado1 = true;
bool estado2 = false;
bool estado1A = true; //estados para el kilahuea
bool estado2A = false;
bool estado3A = true; //estados para las aves
bool estado3B = false;
//para las otras aves
bool estado3C = true;
bool estado3D = false;
bool estado3E = false;
bool estado3F = false;
bool estado3G = false;
//para el recorrido preestablecido
bool inicio2 = false;
bool estadoA1 = true;
bool estadoA2 = false;
bool estadoA3 = false;
bool estadoA4 = false;
bool estadoA5 = false;
bool estadoA6 = false;

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito; //Guarda frame de la rodilla izquierda
	KeyFrame[FrameIndex].rotRodDer = rotRodDer; //guarda frame de la rodilla derecha
	KeyFrame[FrameIndex].rotRodPiernaIzq = rotRodPiernaIzq; //guarda frame de la pierna izquierda
	KeyFrame[FrameIndex].rotRodPiernaDer = rotRodPiernaDer;//guarda frame de la pierna derecha
	KeyFrame[FrameIndex].rotCabeza = rotCabeza;//guarda frame de la cabeza
	KeyFrame[FrameIndex].rotCuello = rotCuello;//guarda frame de la pierna derecha
	KeyFrame[FrameIndex].rotBI = rotBI;//guarda frame del brazo izquierdo
	KeyFrame[FrameIndex].rotBD = rotBD;//guarda frame del brazo derecho
	KeyFrame[FrameIndex].rotCin = rotCin;//guarda frame de la cintura

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq; //resetea rodilla izquierda
	giroMonito = KeyFrame[0].giroMonito;
	rotRodDer = KeyFrame[0].rotRodDer; //resetea rodilla derecha
	rotRodPiernaIzq = KeyFrame[0].rotRodPiernaIzq; //reseta pierna izquierda
	rotRodPiernaDer = KeyFrame[0].rotRodPiernaDer; //resetea pierna derecha
	rotCabeza = KeyFrame[0].rotCabeza; //resetea cabeza
	rotCuello = KeyFrame[0].rotCuello; //resetea cuello
	rotBI = KeyFrame[0].rotBI; //resetea brazo izquierdo
	rotBD = KeyFrame[0].rotBD; //resetea brazo derecho
	rotCin = KeyFrame[0].rotCin; //resetea cintura

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;	 //interpola rodilla izquierda inical
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps; //interpola mono
	KeyFrame[playIndex].rotIncDer = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps; //interpola movimiento de rodilla derecha
	KeyFrame[playIndex].rotIncPI = (KeyFrame[playIndex + 1].rotRodPiernaIzq - KeyFrame[playIndex].rotRodPiernaIzq) / i_max_steps; //interpola movimiento de pierna izquierda
	KeyFrame[playIndex].rotIncPD = (KeyFrame[playIndex + 1].rotRodPiernaDer - KeyFrame[playIndex].rotRodPiernaDer) / i_max_steps; //interpola movimiento de pierna derecha
	KeyFrame[playIndex].rotIncC = (KeyFrame[playIndex + 1].rotCabeza - KeyFrame[playIndex].rotCabeza) / i_max_steps; //interpola movimiento de la cabeza
	KeyFrame[playIndex].rotIncCu = (KeyFrame[playIndex + 1].rotCuello - KeyFrame[playIndex].rotCuello) / i_max_steps; //interpola movimiento del cuello
	KeyFrame[playIndex].rotIncBI = (KeyFrame[playIndex + 1].rotBI - KeyFrame[playIndex].rotBI) / i_max_steps; //interpola movimiento del brazo izquierdo
	KeyFrame[playIndex].rotIncBD = (KeyFrame[playIndex + 1].rotBD - KeyFrame[playIndex].rotBD) / i_max_steps; //interpola movimiento del brazo derecho
	KeyFrame[playIndex].rotIncCin = (KeyFrame[playIndex + 1].rotCin - KeyFrame[playIndex].rotCin) / i_max_steps; //interpola movimiento de la cintura

}

void ciudad()
{

	glPushMatrix(); //Camino1
	glTranslatef(23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0); //objeto
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Camino2
	glTranslatef(-23.5, 0.0, 0.0);
	glScalef(40, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text4.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, -4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0); //primer argumento
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glTranslatef(0.0, 0.0, 4.0);
	glScalef(87, 0.1, 1);
	glDisable(GL_LIGHTING);
	fig4.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, 7.0);
	glRotatef(90, 1, 0, 0);
	glRotatef(180, 0, 0, 1);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Casa01
	glTranslatef(0.0, 3.0, -7.0);
	glRotatef(90, 1, 0, 0);
	//glRotatef(180,0,0,1);
	glScalef(6, 5.0, 6);
	glDisable(GL_LIGHTING);
	fig5.prisma2(text6.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void monito()
{
	//glNewList(1, GL_COMPILE);
	glPushMatrix();//Pecho
	glScalef(0.5, 0.5, 0.5);
	fig7.prisma(2.0, 2.0, 1, text2.GLindex);
	glPushMatrix();//Cuello
	glTranslatef(0, 1.0, 0.0);
	//girar cuello hacia la izquierda o derecha
	glRotatef(rotCabeza, 0, 0, 1); //rota cabeza
	glRotatef(rotCuello, 1, 0, 0); //rota cuello
	fig7.cilindro(0.25, 0.25, 15, 0);
	glPushMatrix();//Cabeza
	glTranslatef(0, 1.0, 0);
	fig7.esfera(0.75, 15, 15, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //Brazo derecho-->
	glTranslatef(1.25, 0.65, 0);
	glRotatef(rotBD, 0, 0, 1); //rota brazo derecho
	glRotatef(rotCin, 0, 1, 0); //rota brazo hacia la derecha o izquierda 
	fig7.esfera(0.5, 12, 12, 0);
	glPushMatrix(); //Antebrazo derecho
	glTranslatef(0.25, 0, 0);
	glRotatef(-45, 0, 1, 0);
	glTranslatef(0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();


	//Br
	glPushMatrix(); //Brazo izquierdo <--
	glTranslatef(-1.25, 0.65, 0);
	glRotatef(-rotBI, 0, 0, 1); //rota brazo izquierdo
	glRotatef(-rotCin, 0, 1, 0);
	fig7.esfera(0.5, 12, 12, 0);
	glPushMatrix();
	glTranslatef(-0.25, 0, 0);
	//glRotatef(45, 0, 1, 0); 
	//glRotatef(25, 0, 0, 1);
	//glRotatef(25, 1, 0, 0); 
	glTranslatef(-0.75, 0, 0);
	fig7.prisma(0.7, 1.5, 0.7, 0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();//Cintura
	glColor3f(0, 0, 1);
	glTranslatef(0, -1.5, 0);
	//glRotatef(rotCin,0,1,0);
	fig7.prisma(1, 2, 1, 0);

	glPushMatrix(); //Pie Derecho --> pierna derecha
	glTranslatef(0.75, -0.5, 0);
	glRotatef(rotRodPiernaDer, 1, 0, 0);
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, 0);

	glPushMatrix(); //rodilla derecha
	glTranslatef(0, -0.5, 0);
	glRotatef(rotRodDer, 1, 0, 0); //rota rodilla derecha
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, 0);

	glPushMatrix(); //pie izquierdo
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Pie Izquierdo --> toda la pierna
	glTranslatef(-0.75, -0.5, 0);
	glRotatef(rotRodPiernaIzq, 1, 0, 0); //variable para la rotacion pierna izquierda
	glTranslatef(0, -0.5, 0);
	fig7.prisma(1.0, 0.5, 1, 0);

	glPushMatrix(); //rodilla izquierda
	glTranslatef(0, -0.5, 0);
	glRotatef(rotRodIzq, 1, 0, 0); //rota rodilla izquierda
	glTranslatef(0, -0.75, 0);
	fig7.prisma(1.5, 0.5, 1, 0);

	glPushMatrix(); //pie izquierdo
	glTranslatef(0, -0.75, 0.3);
	fig7.prisma(0.2, 1.2, 1.5, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();


	glColor3f(1, 1, 1);
	glPopMatrix();
	//glEndList();
}

void castillo() {

	glPushMatrix(); //pared de atras
	glTranslatef(7.0, -30, -80);
	glRotatef(90.0, 0, 0, 1);
	fachada.prisma(110.0, 20, 5.0, block.GLindex);
	glPopMatrix();

	glPushMatrix(); //cilindro trasero izquierdo
	glTranslatef(77.0, -40.0, -80.0);
	glScalef(15.0, 50.0, 5.0);
	pilar.cilindro(1.0, 1.0, 100, block.GLindex);
	glPopMatrix();

	glPushMatrix();//cilindro trasero derecho
	glTranslatef(-63.0, -40.0, -80.0);
	glScalef(15.0, 50.0, 5.0);
	pilar.cilindro(1.0, 1.0, 100, block.GLindex);
	glPopMatrix();

	glPushMatrix();//pared de la izquierda
	glTranslatef(-65.0, -30, -20.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	fachada.prisma(110.0, 20, 5.0, block.GLindex);
	glPopMatrix();

	glPushMatrix(); //cilindro delantero izquierdo
	glTranslatef(-63.0, -40.0, 40.0);
	glScalef(15.0, 50.0, 5.0);
	pilar.cilindro(1.0, 1.0, 100, block.GLindex);
	glPopMatrix();

	glPushMatrix(); //pared de enfrente
	glTranslatef(-24.0, -30.0, 40.0);
	glRotatef(90, 0, 0, 1);
	fachada.prisma(50.0, 20, 5.0, block.GLindex);
	glPopMatrix();

	glPushMatrix();//pared media de enfrente
	glTranslatef(13.0, -21.3, 40.0);
	glRotatef(90, 0, 0, 1);
	fachada.prisma(25.0, 2.65, 5.0, block.GLindex);
	glPopMatrix();


	glPushMatrix(); //pared de enfrente 2
	glTranslatef(50.0, -30.0, 40.0);
	glRotatef(90, 0, 0, 1);
	fachada.prisma(50.0, 20, 5.0, block.GLindex);
	glPopMatrix();

	//cilindro delantero derecho

	glPushMatrix(); //cilindro delantero izquierdo
	glTranslatef(80.0, -40.0, 40.0);
	glScalef(15.0, 50.0, 5.0);
	pilar.cilindro(1.0, 1.0, 100, block.GLindex);
	glPopMatrix();


	//pared derecha

	glPushMatrix();//pared de la izquierda
	glTranslatef(80.0, -30, -20.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	fachada.prisma(110.0, 20, 5.0, block.GLindex);
	glPopMatrix();

	//puerta

	glPushMatrix();
	glTranslatef(2.0, -31.0, 46.5);
	glRotatef(90.0, 0, 1, 0);
	fachada.prisma(17.5, 8.0, 2.0, puerta.GLindex);
	glPopMatrix();

	//puerta 2
	glPushMatrix();
	glTranslatef(24.0, -31.0, 46.5);
	glRotatef(90.0, 0, 1, 0);
	//glRotatef(giropuerta, 0, 1, 0);
	fachada.prisma(17.5, 8.0, 2.0, puerta.GLindex);
	glPopMatrix();

	//Cuadros de la pared de enfrente

	glPushMatrix();
	glTranslatef(-45, -18.5, 40.0);
	fachada.prisma(3.0, 5.0, 5.0, block2.GLindex);
	for (int i = 0; i <= 12; i++) {
		glTranslatef(8, 0, 0);
		fachada.prisma(3.0, 5.0, 5.0, block2.GLindex);
	}
	glPopMatrix();

	//cuadros de la pared de la izquierda

	glPushMatrix();
	glTranslatef(80, -18.5, 30);
	glRotatef(180, 0, 1, 0);
	fachada.prisma(3.0, 5.0, 5.0, block2.GLindex);
	for (int i = 0; i <= 12; i++) {
		glTranslatef(0, 0, 8);
		fachada.prisma(3.0, 5.0, 5.0, block2.GLindex);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-45, -18.5, -80.0);
	fachada.prisma(3.0, 5.0, 5.0, block2.GLindex);
	for (int i = 0; i <= 12; i++) {
		glTranslatef(8, 0, 0);
		fachada.prisma(3.0, 5.0, 5.0, block2.GLindex);
	}
	glPopMatrix();

	glPushMatrix();

	glTranslatef(-65, -18.5, 30);
	glRotatef(180, 0, 1, 0);
	fachada.prisma(3.0, 5.0, 5.0, block2.GLindex);
	for (int i = 0; i <= 12; i++) {
		glTranslatef(0, 0, 8);
		fachada.prisma(3.0, 5.0, 5.0, block2.GLindex);
	}
	glPopMatrix();

	//conos
	glPushMatrix();
	glTranslatef(77.0, 10.0, -80.0);
	glScalef(15.0, 20.0, 5.0);
	fachada.cono(1, 1.0, 30, grava.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80.0, 10.0, 40.0);
	glScalef(15.0, 20.0, 5.0);
	fachada.cono(1, 1.0, 30, grava.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-63.0, 10.0, 40.0);
	glScalef(15.0, 20.0, 5.0);
	fachada.cono(1, 1.0, 30, grava.GLindex);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(-63.0, 10.0, -80.0);
	glScalef(15.0, 20.0, 5.0);
	fachada.cono(1, 1.0, 30, grava.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//banderas
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-66.5, 35.0, -82.0);
	glRotatef(45.0, 0, 1, 0);
	glScalef(0.05, 0.05, 0.05);
	flag.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(73.5, 35.0, -82.0);
	glRotatef(45.0, 0, 1, 0);
	glScalef(0.05, 0.05, 0.05);
	flag.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(76.5, 35.0, 38.0);
	glRotatef(45.0, 0, 1, 0);
	glScalef(0.05, 0.05, 0.05);
	flag.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-66.5, 35.0, 38.0);
	glRotatef(45.0, 0, 1, 0);
	glScalef(0.05, 0.05, 0.05);
	flag.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	/**/

	glPushMatrix();		// sofa abajo de los arboles
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-38, -37, -5);
	glScalef(.17, .17, .17);
	Sofa.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		// sofa abajo de los arboles
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-20, -37, 10);
	glScalef(.17, .17, .17);
	glRotatef(90, 0, 1, 0);
	Sofa.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		// Mesita para comer tipo bronce
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(40, -41, -68);
	glScalef(5, 5, 5);
	Mesita.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		// Mesita para comer tipo bronce
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(0, -41, -68);
	glScalef(5, 5, 5);
	Mesita.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		// Mesita para comer tipo bronce
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-20, -41, -68);
	glScalef(5, 5, 5);
	Mesita.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//Banca
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(45, -36, -10);
	glScalef(5, 5, 5);
	glRotatef(90, 0, 1, 0);
	Banca.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//Banca
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(20, -36, 0);
	glScalef(5, 5, 5);
	Banca.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//Banca
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(10, -36, 0);
	glScalef(5, 5, 5);
	Banca.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//Banca
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(0, -36, 0);
	glScalef(5, 5, 5);
	Banca.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //juego de niños
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-20, -40, -10);
	glScalef(4.5, 4.5, 4.5);
	parque.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//tienda de regalos
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(35, -39, 27);
	glScalef(.001, .0015, .001);
	glRotatef(130.0, 0, 1, 0);
	Tienda.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();


	glPushMatrix();		//sofa premium
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(64, -38, -72);
	glScalef(.15, .15, .15);
	SofaPremium.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//arboles (verde)
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-55, -28, -55);
	glScalef(.003, .003, .003);
	ArbolParque.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//arboles (blanco)
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-55, -32, -40);
	glScalef(.5, .5, .5);
	Arbol1.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//arboles (verde)
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-55, -28, -25);
	glScalef(.003, .003, .003);
	ArbolParque.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//arbol blanco
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-55, -32, -10);
	glScalef(.5, .5, .5);
	Arbol1.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//arboles (verde)
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-55, -28, 5);
	glScalef(.003, .003, .003);
	ArbolParque.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();



	//decorado enfrente 
	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-46.2, -17, 40);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-38, -17, 40);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-29.8, -17, 40);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-21.6, -17, 40);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-13.4, -17, 40);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-5.2, -17, 40);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(3, -17, 40);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(11.2, -17, 40);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(19.4, -17, 40);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(27.6, -17, 40);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(35.8, -17, 40);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(44, -17, 40);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(52.2, -17, 40);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(60.4, -17, 40);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//decorado barda izquierda

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-65, -17, 23);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-65, -17, 14.8);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-65, -17, 6.6);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-65, -17, -1.6);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-65, -17, -9.8);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-65, -17, -18);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-65, -17, -26.2);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-65, -17, -37.4);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-65, -17, -45.6);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//decorado barda derecha							

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, 22);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, 13.8);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, 5.6);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, -2.6);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, -10.8);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, -19);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, -26.8);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, -35);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, -42.5);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, -50);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, -58.4);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(79.2, -17, -66.5);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	//decorado barda de atras

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-45.7, -17, -80);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-37.5, -17, -80);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-29.3, -17, -80);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-21.1, -17, -80);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-12.9, -17, -80);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(-4.7, -17, -80);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(3.5, -17, -80);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(11.7, -17, -80);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(19.2, -17, -80);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(27.4, -17, -80);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(35.3, -17, -80);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(43.2, -17, -80);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //maceta
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(51.6, -17, -80);
	glScalef(5, 5, 5);
	maceta.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix(); //arbusto
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(59.7, -17, -80);
	glScalef(.7, .5, .7);
	arbol.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();


	/**/
}
void Pendulo() {

	glPushMatrix(); //soporte trasero derecho
	glTranslatef(35.0, -43.0, -35.0);
	glScalef(5.0, 20, 5.0);
	glRotatef(45, 1, 0, 0);
	glRotatef(35, 0, 0, 1);
	soporte.cilindro(0.2, 3, 80, MetalSoportes.GLindex);
	glPopMatrix();


	glPushMatrix(); //soporte trasero izquierdo
	glTranslatef(15.0, -43.0, -35.0);
	glScalef(5.0, 20, 5.0);
	glRotatef(45, 1, 0, 0);
	glRotatef(-35, 0, 0, 1);
	soporte.cilindro(0.2, 3, 80, MetalSoportes.GLindex);
	glPopMatrix();

	glPushMatrix(); //soporte delantero derecho
	glTranslatef(35.0, -43.0, -5.0);
	glScalef(5.0, 20, 5.0);
	glRotatef(-45, 1, 0, 0);
	glRotatef(35, 0, 0, 1);
	soporte.cilindro(0.2, 3, 80, MetalSoportes.GLindex);
	glPopMatrix();

	glPushMatrix(); //soporte delantero izquierdo
	glTranslatef(15.0, -43.0, -5.0);
	glScalef(5.0, 20, 5.0);
	glRotatef(-45, 1, 0, 0);
	glRotatef(-35, 0, 0, 1);
	soporte.cilindro(0.2, 3, 80, MetalSoportes.GLindex);
	glPopMatrix();

	glPushMatrix(); //cuadro de union
	glTranslatef(25.0, -7, -20.0);
	glRotatef(90, 1, 0, 0);
	soporte.prisma(18, 5, 3.0, Morado.GLindex);
	glPopMatrix();



	//ponerlo jerarquico
	glPushMatrix(); //cono rotado de soporte union con soporte toroide
	//glRotatef(rotpendulo, 0, 0, 1);
	glTranslatef(25, -10, -26);	//(25,-10,-26)
	glScalef(3.0, 8, 5.0);
	glRotatef(90, 1, 0, 0);
	soporte.cilindro(0.2, 2.5, 80, Morado.GLindex);
	glPopMatrix();


	//MODELO JERARQUICO
	glPushMatrix(); //soporte de toroide
	//pivote
	glTranslatef(25, -10, -26);
	glRotatef(rotpendulo, 0, 0, 1);

	//figuras
	//SOPORTE
	glTranslatef(0, -18.5, 6);
	glScalef(5.0, 6, 5.0);
	soporte.cilindro(0.1, 3, 80, yellow.GLindex);
	//lo volvemos a la normalidad
	glScalef(0.2, 0.16, 0.2);

	glPushMatrix(); //cono de toroide
	glTranslatef(0, -2.5, 0);

	glScalef(5.0, 1.5, 5.0);
	soporte.cilindro(0.4, 3, 80, yellow.GLindex);
	glPopMatrix();

	glPushMatrix(); //uniones de toroide con cono
	glTranslatef(0, -1.7, -7.5);
	glScalef(1, .6, 10.0);
	glRotatef(90, 1, 0, 0);
	soporte.cilindro(.5, 1.3, 80, ColoresSoporte.GLindex);
	glPopMatrix();

	glPushMatrix(); //toroide
	glTranslatef(0, -1.5, 0);	//(25,-30,-20)
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(1, 7, 10, 10);
	glPopMatrix();

	glPopMatrix(); //fin modelador jerarquico

}

void kilauea() {

	glPushMatrix(); //soporte
	glTranslatef(-25.0, -40.0, -35.0);
	glScalef(5.0, 20, 5.0);
	soporte.cilindro(0.2, 3, 80, ColoresSoporte.GLindex);
	glScalef(.2, .1, .1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -trasKila);
	glutSolidTorus(1, 2.7, 10, 10);
	glPopMatrix();

	glPushMatrix(); //soporte
	glTranslatef(-10.0, -40.0, -35.0);
	glScalef(5.0, 20, 5.0);
	soporte.cilindro(0.2, 3, 80, ColoresSoporte.GLindex);
	glScalef(.2, .1, .1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -trasKila);
	glutSolidTorus(1, 2.7, 10, 10);
	glPopMatrix();

	glPushMatrix(); //soporte
	glTranslatef(-17.5, -40.0, -25.0);
	glScalef(5.0, 20, 5.0);
	soporte.cilindro(0.2, 3, 80, ColoresSoporte.GLindex);
	glScalef(.2, .1, .1);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 0, -trasKila);
	glutSolidTorus(1, 2.7, 10, 10);
	glPopMatrix();

	glPushMatrix(); //sopote superiores
	glTranslatef(-10, 20, -35.0);
	glRotatef(90, 0, 0, 1);
	glScalef(5.0, 5, 5.0);
	soporte.cilindro(0.2, 2.5, 80, ColoresSoporte.GLindex);
	glPopMatrix();

	glPushMatrix(); //sopote superiores
	glTranslatef(-10, 20, -35.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(52, 1, 0, 0);
	glScalef(5.0, 5, 5.0);
	soporte.cilindro(0.2, 2.5, 80, ColoresSoporte.GLindex);
	glPopMatrix();

	glPushMatrix(); //sopote superiores
	glTranslatef(-17.5, 20, -25.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(-52, 1, 0, 0);
	glScalef(5.0, 5, 5.0);
	soporte.cilindro(0.2, 2.5, 80, ColoresSoporte.GLindex);
	glPopMatrix();

	glPushMatrix(); //sopote superiores
	glTranslatef(-17.5, 20, -25.0);
	glRotatef(-45, 1, 0, 0);
	glScalef(5.0, 5, 5.0);
	soporte.cilindro(0.2, 2, 80, ColoresSoporte.GLindex);
	glPopMatrix();

	glPushMatrix(); //sopote superiores
	glTranslatef(-10, 20, -35.0);
	glRotatef(28, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(5.0, 5, 5.0);
	soporte.cilindro(0.2, 2, 80, ColoresSoporte.GLindex);
	glPopMatrix();

	glPushMatrix(); //soporte superior
	glTranslatef(-25.0, 20.0, -35.0);
	glRotatef(28, 1, 0, 0);
	glRotatef(-45, 0, 0, 1);
	glScalef(5.0, 5, 5.0);
	soporte.cilindro(0.2, 2, 80, ColoresSoporte.GLindex);
	glPopMatrix();
}


void Superman() {

	glPushMatrix();
	glTranslatef(-20, -35.5, -50);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 16.0, 100, yellow.GLindex);

	glTranslatef(-3.0, 0.0, -3.0);
	rieles.cilindro(0.5, 16.0, 100, metal.GLindex);

	glTranslatef(3.0, 0.0, -3.0);
	rieles.cilindro(0.5, 16.0, 100, yellow.GLindex);

	glTranslatef(0.1, 15.0, 0.1);
	glRotatef(90.0, 0, 0, 1);
	glRotatef(45.0, 1, 0, 0);
	rieles.cilindro(0.3, 4.0, 100, yellow.GLindex);

	for (int i = 0; i <= 6; i++) {
		glTranslatef(-2.0, 0.0, 0.0);
		rieles.cilindro(0.3, 4.0, 100, yellow.GLindex);
	}

	glTranslatef(14.1, 3.9, 0.2);
	glRotatef(87.0, 1, 0, 0);
	rieles.cilindro(0.3, 4.3, 100, yellow.GLindex);

	for (int i = 0; i <= 6; i++) {
		glTranslatef(-2.0, 0, 0);
		rieles.cilindro(0.3, 4.0, 100, yellow.GLindex);
	}
	glPopMatrix();


	glPushMatrix();

	glTranslatef(-20.5, -35.5, -50);
	glRotatef(-48, 0, 0, 1);
	rieles.cilindro(0.5, 43.0, 100, yellow.GLindex);

	glTranslatef(2.5, -2.0, -3.0);
	rieles.cilindro(0.5, 43.0, 100, metal.GLindex);

	glTranslatef(-2.5, 2.0, -3.0);
	rieles.cilindro(0.5, 43.0, 100, yellow.GLindex);
	glPopMatrix();
	//rieles de la segunda columna
	glPushMatrix();
	glTranslatef(-20.0, -35.0, -56.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-18.0, -33.0, -56.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-14.5, -30.0, -56.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.5, -26.5, -56.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-1.5, -18.5, -56.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-6.5, -22.5, -56.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.5, -14.0, -56.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(8.5, -9.5, -56.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	//Segundo riel

	glPushMatrix();
	glTranslatef(21, -6.9, -50);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 10.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(22.3, -10.0, -53);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 11.0, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(21.0, -6.9, -56);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 10.0, 100, yellow.GLindex);
	glPopMatrix();

	//tablas
	glPushMatrix();
	glTranslatef(13, -6.7, -56);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(17, -6.7, -56);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.5, -6.8, -50);
	glRotatef(-135, 0, 0, 1);
	rieles.cilindro(0.5, 45.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(22.0, -10.0, -53);
	glRotatef(-135, 0, 0, 1);
	rieles.cilindro(0.5, 42.0, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.5, -6.8, -56);
	glRotatef(-135, 0, 0, 1);
	rieles.cilindro(0.5, 45.0, 100, yellow.GLindex);
	glPopMatrix();

	//base de los rieles

	glPushMatrix();
	glTranslatef(20.5, -6.8, -56);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(23.5, -9.8, -56);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(27.5, -13.8, -56);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(32.5, -18.8, -56);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(37.5, -23.8, -56);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(42.5, -28.8, -56);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(47.5, -33.8, -56);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	//Tercer riel
	glPushMatrix();
	glTranslatef(67.0, -38.5, -56.0);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 15.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(64.0, -39.5, -53.0);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 13.0, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.5, -38.5, -50.0);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 10.0, 100, yellow.GLindex);
	glPopMatrix();


	//base de lo rieles

	glPushMatrix();
	glTranslatef(53.0, -38.5, -50.0);
	glRotatef(-90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(53.0, -38.5, -50.0);
	glRotatef(-90, 1, 0, 0);
	rieles.cilindro(0.3, 4.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(59.0, -38.5, -50.0);
	glRotatef(-90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	//Cuarto riel

	glPushMatrix();
	glTranslatef(67.0, -38.5, -56.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.5, 43.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(64.0, -39.5, -53.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.5, 40.0, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -38.5, -50.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.5, 37.0, 100, yellow.GLindex);
	glPopMatrix();

	//base de los rieles

	glPushMatrix();
	glTranslatef(61.0, -38.5, -49.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -38.5, -44.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -38.5, -40.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -38.5, -36.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -38.5, -32.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -38.5, -28.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -38.5, -24.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -38.5, -20.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -38.5, -16.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	//Riel 5

	glPushMatrix();
	glTranslatef(61.0, -38.5, -13.3);
	glRotatef(45, 1, 0, 0);
	rieles.cilindro(0.5, 40.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -38.5, -13.3);
	glRotatef(45, 1, 0, 0);
	rieles.cilindro(0.5, 40.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(64.0, -39.5, -13.3);
	glRotatef(45, 1, 0, 0);
	rieles.cilindro(0.5, 40.0, 100, metal.GLindex);
	glPopMatrix();

	//Base de los rieles

	glPushMatrix();
	glTranslatef(67.0, -38.5, -13.3);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -34.5, -9.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -30.5, -5.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -26.5, -1.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -21.5, 3.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -17.5, 7.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -13.5, 11.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	//Riel 

	glPushMatrix();
	glTranslatef(67.0, -10.5, 14.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.5, 16.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(64.0, -11.5, 14.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.5, 13.5, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -10.5, 14.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.5, 10.0, 100, yellow.GLindex);
	glPopMatrix();

	//Base de rieles

	glPushMatrix();
	glTranslatef(61.0, -10.5, 14.5);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -10.5, 18.5);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -10.5, 22.5);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	//Riel

	glPushMatrix();
	glTranslatef(61.3, -10.5, 24.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 75.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(64.0, -11.5, 27.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 78.0, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.3, -10.5, 30.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 81.0, 100, yellow.GLindex);
	glPopMatrix();

	//Base rieles

	glPushMatrix();
	glTranslatef(61.3, -10.5, 30.5);
	glRotatef(-90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);

	for (int i = 0; i <= 17; i++) {
		glTranslatef(-4.0, 0, 0);
		rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	}

	glPopMatrix();

	//Riel
	glPushMatrix();
	glTranslatef(-13.5, -10.8, 30.5);
	glRotatef(45, 0, 0, 1);
	rieles.cilindro(0.5, 53.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13.5, -11.8, 27.5);
	glRotatef(45, 0, 0, 1);
	rieles.cilindro(0.5, 53.0, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-13.5, -10.8, 24.5);
	glRotatef(45, 0, 0, 1);
	rieles.cilindro(0.5, 53.0, 100, yellow.GLindex);
	glPopMatrix();

	//Base rieles

	glPushMatrix();
	glTranslatef(-13.5, -10.8, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-16.5, -7.8, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19.5, -4.8, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-22.5, -1.8, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-25.5, 1.5, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28.5, 4.5, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-31.5, 7.5, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-34.5, 10.5, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-37.5, 13.5, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40.5, 16.5, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-43.5, 19.5, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-46.5, 22.5, 24.5);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	//Riel
	glPushMatrix();
	glTranslatef(-50.5, 26.5, 24.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 15.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50.5, 25.5, 27.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 18.0, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50.5, 26.5, 30.5);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 21.0, 100, yellow.GLindex);
	glPopMatrix();

	//Base de Rieles
	glPushMatrix();
	glTranslatef(-50.5, 26.5, 30.5);
	glRotatef(-90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);

	for (int i = 0; i <= 3; i++) {
		glTranslatef(-3.0, 0, 0);
		rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	}

	glPopMatrix();

	//Riel

	glPushMatrix();
	glTranslatef(-71.5, 26.5, 30.5);
	glRotatef(-90, 1, 0, 0);
	rieles.cilindro(0.5, 87.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-68.5, 25.5, 28.0);
	glRotatef(-90, 1, 0, 0);
	rieles.cilindro(0.5, 81.0, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65.5, 26.5, 25.0);
	glRotatef(-90, 1, 0, 0);
	rieles.cilindro(0.5, 75.0, 100, yellow.GLindex);
	glPopMatrix();

	//Base rieles
	glPushMatrix();
	glTranslatef(-65.5, 26.5, 23.0);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);

	for (int i = 0; i <= 23; i++) {
		glTranslatef(0, 0, -3.0);
		rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	}

	glPopMatrix();

	//Rieles Principales
	glPushMatrix();
	glTranslatef(-65.5, 26.5, -50.0);
	glRotatef(-154, 0, 0, 1);
	rieles.cilindro(0.5, 69.5, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65.5, 25.5, -53.0);
	glRotatef(-154.5, 0, 0, 1);
	rieles.cilindro(0.5, 70.5, 100, metal.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65.5, 26.5, -56.0);
	glRotatef(-154.5, 0, 0, 1);
	rieles.cilindro(0.5, 69.5, 100, yellow.GLindex);
	glPopMatrix();

	//Rieles de apoyo

	glPushMatrix();
	glTranslatef(-71.5, 26.5, -56.0);
	glRotatef(-90, 0, 0, 1);
	rieles.cilindro(0.5, 6.3, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65.5, 25.5, -53.0);
	glRotatef(90, 0, 0, 1);
	rieles.cilindro(0.5, 2.5, 100, metal.GLindex);
	glPopMatrix();

	//Base rieles

	glPushMatrix();
	glTranslatef(-65.5, 26.5, -56.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60.5, 16.5, -56.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-55.5, 6.5, -56.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-51.0, -3.5, -56.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-46.0, -13.5, -56.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-41.4, -23.5, -56.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-36.5, -33.5, -56.0);
	glRotatef(90, 1, 0, 0);
	rieles.cilindro(0.3, 6.0, 100, yellow.GLindex);
	glPopMatrix();

	//Estructuras exteriores 

	glPushMatrix();
	glTranslatef(-65.5, -40.5, -50.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65.5, -41.0, -53.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65.5, -40.5, -56.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-68.5, -41.0, -53.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-71.5, -40.5, -56.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-71.5, -40.5, -50.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-71.5, -40.5, 30.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-68.5, -41.0, 27.5);
	rieles.cilindro(1.0, 67.0, 99, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65.5, -40.5, 25.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-71.5, -40.5, 25.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65.5, -40.5, 31.0);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-51.0, -40.5, 30.5);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-51.0, -41.5, 27.5);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-51.0, -40.5, 24.5);
	rieles.cilindro(1.0, 67.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-14.2, -40.0, 30.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-14.2, -41.0, 27.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-14.2, -40.0, 24.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.2, -40.5, 24.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.2, -40.5, 30.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.2, -40.5, 30.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.2, -40.5, 23.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(64.0, -41.5, 27.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(64.0, -41.5, 14.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -41.0, 14.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -41.0, 14.5);
	rieles.cilindro(1.0, 30.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -41.0, -12.5);
	rieles.cilindro(1.0, 3.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -41.0, -12.5);
	rieles.cilindro(1.0, 3.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(61.0, -41.5, -50.0);
	rieles.cilindro(1.0, 3.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(67.0, -41.5, -56.5);
	rieles.cilindro(1.0, 3.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52.0, -41.5, -50.0);
	rieles.cilindro(1.0, 3.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52.0, -41.5, -56.0);
	rieles.cilindro(1.0, 3.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.5, -40.3, -56.0);
	rieles.cilindro(1.0, 33.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(22.5, -43.0, -53.0);
	rieles.cilindro(1.0, 33.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20.5, -40.3, -50.0);
	rieles.cilindro(1.0, 33.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(11.5, -40.3, -56.0);
	rieles.cilindro(1.0, 33.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12.0, -43.0, -53.0);
	rieles.cilindro(1.0, 33.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(11.5, -40.3, -50.0);
	rieles.cilindro(1.0, 33.0, 100, blue.GLindex);
	glPopMatrix();
	//----------------------------------------//
	glPushMatrix();
	glTranslatef(-20.5, -40.3, -50.0);
	rieles.cilindro(1.0, 5.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20.5, -40.3, -56.0);
	rieles.cilindro(1.0, 5.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35.5, -40.3, -56.0);
	rieles.cilindro(1.0, 5.0, 100, blue.GLindex);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35.5, -40.3, -50.0);
	rieles.cilindro(1.0, 5.0, 100, blue.GLindex);
	glPopMatrix();
}

void carro() {
	glPushMatrix();
	//cilindro base
	glTranslatef(movKitX, movKitY, movKitZ);
	glTranslatef(64.0, -34.5, -30.0);
	glRotatef(90, 1, 0, 0);
	glRotatef(rotKitA, 1, 0, 0);
	glRotatef(rotKitB, 0, 1, 0);
	glRotatef(rotKitC, 0, 0, 1);
	car.cilindro(3.5, 10.0, 100, madera.GLindex);
	glPushMatrix();					//cono
	glTranslatef(0, 10.0, 0);
	car.cono(5.0, 3.5, 100, madera.GLindex);
	glPopMatrix();

	glPushMatrix();					//1ra Llanta
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(3.5, 10.0, 1.5);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(90, 0, 0, 1);
	glRotatef(rotLlanta, 0, 1, 0);
	llanta.torus(5.0, 2.0, 50, 50, 0);
	glPopMatrix();

	glPushMatrix();					//2da Llante
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-3.5, 10.0, 1.5);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(90, 0, 0, 1);
	glRotatef(rotLlanta, 0, 1, 0);
	llanta.torus(5.0, 2.0, 50, 50, 0);
	glPopMatrix();

	glPushMatrix();					//3ra Llante
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-3.5, 2.0, 1.5);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(90, 0, 0, 1);
	glRotatef(rotLlanta, 0, 1, 0);
	llanta.torus(5.0, 2.0, 50, 50, 0);
	glPopMatrix();

	glPushMatrix();					//4a Llanta
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(3.5, 2.0, 1.5);
	glScalef(0.5, 0.5, 0.5);
	glRotatef(90, 0, 0, 1);
	glRotatef(rotLlanta, 0, 1, 0);
	llanta.torus(5.0, 2.0, 50, 50, 0);
	glPopMatrix();
	glPopMatrix();
}

GLuint createDL()
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands
	ciudad();
	monito();
	// endList
	glEndList();

	return(ciudadDL);
}

void InitGL(GLvoid)     // Inicializamos parametros
{
	//Fonde negro
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glEnable(GL_BLEND);

	text1.LoadBMP("texturas/orig.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("texturas/block2.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	pasto.LoadBMP("texturas/grass2.bmp");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	block.LoadBMP("texturas/block.bmp");
	block.BuildGLTexture();
	block.ReleaseImage();

	puerta.LoadTGA("texturas/puerta.TGA");
	puerta.BuildGLTexture();
	puerta.ReleaseImage();

	block2.LoadTGA("texturas/block2.TGA");
	block2.BuildGLTexture();
	block2.ReleaseImage();

	grava.LoadTGA("texturas/grava.TGA");
	grava.BuildGLTexture();
	grava.ReleaseImage();

	metal.LoadTGA("texturas/metal.TGA");
	metal.BuildGLTexture();
	metal.ReleaseImage();

	yellow.LoadTGA("texturas/yellow.TGA");
	yellow.BuildGLTexture();
	yellow.ReleaseImage();

	blue.LoadTGA("texturas/blue.TGA");
	blue.BuildGLTexture();
	blue.ReleaseImage();

	rie.LoadTGA("texturas/tire.TGA");
	rie.BuildGLTexture();
	rie.ReleaseImage();

	madera.LoadTGA("texturas/wood.TGA");
	madera.BuildGLTexture();
	madera.ReleaseImage();

	MetalSoportes.LoadTGA("texturas/MetalSoportes.TGA");
	MetalSoportes.BuildGLTexture();
	MetalSoportes.ReleaseImage();

	ColoresSoporte.LoadTGA("texturas/ColoresSoporte.TGA");
	ColoresSoporte.BuildGLTexture();
	ColoresSoporte.ReleaseImage();

	Morado.LoadTGA("texturas/Morado.TGA");
	Morado.BuildGLTexture();
	Morado.ReleaseImage();

	//Modelos .3DS
	flag._3dsLoad("glag.3ds");
	ArbolParque._3dsLoad("ArbolParque.3ds");
	maceta._3dsLoad("maceta.3ds");
	parque._3dsLoad("parque.3ds");
	Maceta2._3dsLoad("Maceta2.3ds");
	Arbol1._3dsLoad("Arbol1.3ds");
	arbol._3dsLoad("arbol.3ds");
	SofaPremium._3dsLoad("SofaPremium.3ds");
	Tienda._3dsLoad("Tienda.3ds");
	Pajaro._3dsLoad("Pajaro.3ds");
	Dove._3dsLoad("Dove.3ds");
	Bird._3dsLoad("Bird.3ds");
	Drone._3dsLoad("Drone.3ds");
	Sofa._3dsLoad("Sofa.3ds");
	Banca._3dsLoad("Banca.3ds");
	Mesita._3dsLoad("Mesita.3ds");

	objCamera.Position_Camera(9.0, -30.5f, 100.0, 20, -50.0f, 0, 0, 1.0, 0);

	ciudad_display_list = createDL();

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotRodIzq = 0; //rotacion de la rodilla izquierda
		KeyFrame[i].rotInc = 0; //rotacion inicial de rodilla izquierda
		KeyFrame[i].giroMonito = 0;
		KeyFrame[i].giroMonitoInc = 0;
		KeyFrame[i].rotRodDer = 0; //rotacion de la rodilla derecha
		KeyFrame[i].rotIncDer = 0.0; //rotacion inicial de la pierna derecha
		KeyFrame[i].rotIncPI = 0.0; //rotacion inicial de la pierna izquierda
		KeyFrame[i].rotRodPiernaIzq = 0.0; //rotacion de la pierna izquierda
		KeyFrame[i].rotRodPiernaDer = 0.0; //rotacion de la pierna derecha
		KeyFrame[i].rotCabeza = 0.0; //rotacion de la cabeza
		KeyFrame[i].rotCuello = 0.0; //rotacion de la cabeza
		KeyFrame[i].rotBD = 0.0; //rotacion del brazo derecho
		KeyFrame[i].rotBI = 0.0; //rotacion del brazo izquierdo
		KeyFrame[i].rotCin = 0.0; //rotacion del cuello
		KeyFrame[i].rotIncBD = 0.0; //rotacion incial del brazo derecho
		KeyFrame[i].rotIncBI = 0.0; //rotacion inicial del brazo izquierdo
		KeyFrame[i].rotIncC = 0.0; //rotacion inicial de la cabeza
		KeyFrame[i].rotIncCin = 0.0; //rotacion inicial de la cintura
		KeyFrame[i].rotIncCu = 0.0; //rotacion inicial del cuello
		KeyFrame[i].rotIncPD = 0.0; //rotacion inicial de la pierna derecha
	}
}

void pintaTexto(float x, float y, float z, void *font, char *string)
{
	char *c;						 //Caracteres a escribir
	glRasterPos3f(x, y, z);			 //Centro de la ventana

	for (c = string; *c != '\0'; c++) //Fin de cadena
	{
		glutBitmapCharacter(font, *c);
	}
}

void display(void)   // Funcion Dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);
	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);

	glPushMatrix();
	glPushMatrix();				//Cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(200.0, 250.0, 200.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pastito
	glDisable(GL_LIGHTING);
	glTranslatef(0, -40.0, 0);
	glRotatef(90, 1, 0, 0);
	pisoObj.prisma(200.0, 200.0, 0.1, pasto.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();							//Castillo
	glDisable(GL_LIGHTING);
	//glTranslatef(0, -5.0, 0);
	castillo();
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glDisable(GL_LIGHTING);
	Superman();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	Pendulo();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	kilauea();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glDisable(GL_LIGHTING);
	//glScalef(0.7,0.7,0.7);
	carro();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	//	PAJAROS		//
	glPushMatrix();		//Pajaro
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(movXAve, 0, movZAve);
	glTranslatef(-10, 25, 50);
	glScalef(.1, .1, .1);
	glRotatef(45.0, 1, 0, 0);
	glRotatef(rotAve1, 0, 1, 0);
	Pajaro.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//Pajaro
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(movXAve, 0, movZAve);
	glTranslatef(-10, 29, 50);
	glScalef(.1, .1, .1);
	glRotatef(45.0, 1, 0, 0);
	glRotatef(rotAve1, 0, 1, 0);
	Pajaro.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//Pajaro volando
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(movXAve1, 0, movZAv2);
	glTranslatef(-50, 38, 0);
	glScalef(15, 15, 15);
	glRotatef(rotAve2, 0, 1, 0);
	Dove.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//Pajaro volando
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(movXAve1, 0, movZAv2);
	glTranslatef(-45, 40, 0);
	glScalef(15, 15, 15);
	glRotatef(rotAve2, 0, 1, 0);
	Dove.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//Dron
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(5, -40, 20);
	glScalef(.15, .2, .15);
	Drone.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPushMatrix();		//drone
	glDisable(GL_COLOR_MATERIAL);
	glTranslatef(0, -40, 60);
	glScalef(.15, .15, .15);
	Drone.GLrender(NULL, _SHADED, 1.0);
	glPopMatrix();

	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "ProyectoFinal CG01");
	pintaTexto(-11, 8.5, -14, (void *)font, s);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	printf("objCamera.mPos.x = %.3f \n", objCamera.mPos.x);
	printf("objCamera.mPos.y = %.3f \n", objCamera.mPos.y);
	printf("objCamera.mPos.z = %.3f \n", objCamera.mPos.z);
	printf("objCamera.mView.x = %.3f \n", objCamera.mView.x);
	printf("objCamera.mView.z = %.3f \n", objCamera.mView.y);
	printf("objCamera.mView.z = %.3f \n", objCamera.mView.z);
	printf("objCamera.mUp.x = %.3f \n", objCamera.mUp.x);
	printf("objCamera.mUp.y = %.3f \n", objCamera.mUp.y);
	printf("objCamera.mUp.z = %.3f \n\n", objCamera.mUp.z);

	glutSwapBuffers();

}


void animacion()
{

	if (inicio) {
		if (estadoA) {
			movKitZ++;
			rotKitA -= 3.0;
			if (movKitZ > 3.0 && rotKitA <= -45.0) {
				//cambiamos de estado
				estadoA = false;
				estadoB = true;
			}
		}
		//estado B
		if (estadoB) {

			movKitZ += 0.85;
			movKitY += 0.78;

			if (movKitZ > 44.0) {
				rotKitA = -5.0;
				estadoB = false;
				estadoC = true;
			}

		}

		if (estadoC) {
			movKitZ++;
			if (movKitZ > 55.750) {
				estadoC = false;
				estadoDA = true;
			}
		}

		if (estadoDA) {
			rotKitC += 5.0;
			if (rotKitC >= 85.0) {
				estadoDA = false;
				estadoE = true;
			}
		}

		if (estadoE) {
			movKitX--;
			if (movKitX < -65.0) {
				estadoE = false;
				estadoEA = true;
			}
		}

		if (estadoEA) {
			movKitX -= 0.2;
			rotKitB--;
			//movKitY += 0.85;

			if (rotKitB < -45.0) {
				estadoEA = false;
				estadoF = true;
			}
		}

		if (estadoF) {
			movKitY += 0.78;
			movKitX -= 0.80;

			if (movKitX < -113.0) {
				rotKitB = 0.0;
				estadoF = false;
				estadoG = true;
			}
		}

		if (estadoG) {
			movKitX--;
			if (movKitX < -131.0) {
				estadoG = false;
				estadoFA = true;
			}
		}

		if (estadoFA) {
			rotKitC += 5.0;
			rotKitA += 0.5;
			if (rotKitC > 170.0 && rotKitA >= 3.0) {
				estadoFA = false;
				estadoH = true;
			}
		}

		if (estadoH) {
			movKitZ -= 1.5;
			if (movKitZ < -23.0) {
				estadoH = false;
				estadoI = true;
			}
		}

		if (estadoI) {
			rotKitC += 5.0;
			if (rotKitC > 277.0) {
				estadoI = false;
				estadoIA = true;
			}
		}


		if (estadoIA) {
			movKitX += 0.5;
			if (movKitX < -128.0) {
				movKitY += 1.5;
				estadoIA = false;
				estadoJ = true;
			}
		}

		if (estadoJ) {
			rotKitB -= 5.0;
			if (rotKitB < -47.0) {
				estadoJ = false;
				estadoK = true;
			}
		}

		if (estadoK) {
			movKitX += 1.3;
			movKitY -= 2.4;
			if (movKitX > -102.0) {
				estadoK = false;
				estadoL = true;
			}
		}

		if (estadoL) {
			movKitX += 0.5;
			rotKitB += 5.0;
			movKitY -= 0.75;
			movKitZ += 0.1;

			if (movKitX > -96.2) {
				rotKitC = 270.0;
				estadoL = false;
				estadoM = true;
			}

		}

		if (estadoM) {
			movKitX += 0.2;
			rotKitB += 0.8;
			if (movKitX > -87.0) {
				estadoM = false;
				estadoN = true;
			}

		}

		if (estadoN) {
			movKitY += 0.70;
			movKitX += 0.80;
			if (movKitX > -55.8) {
				rotKitB = 3.6;
				estadoN = false;
				estadoOA = true;
			}
		}

		if (estadoOA) {
			movKitX += 1.5;
			if (movKitX > -43.6) {
				estadoOA = false;
				estadoO = true;
			}
		}

		if (estadoO) {
			rotKitB -= 5.0;
			movKitY += 0.1;
			if (rotKitB < -37.4) {
				estadoO = false;
				estadoP = true;
			}
		}

		if (estadoP) {
			movKitX += 0.8;
			movKitY -= 0.75;
			if (movKitX > -18.5) {
				estadoP = false;
				estadoQ = true;
			}
		}

		if (estadoQ) {
			movKitX += 0.2;
			movKitY -= 0.18;
			rotKitB += 1.0;

			if (movKitX > -9.9) {
				estadoQ = false;
				estadoQA = true;
			}
		}

		if (estadoQA) {
			movKitX++;
			if (movKitX > -2.5) {
				estadoQA = false;
				estadoR = true;
			}
		}

		if (estadoR) {
			rotKitC++;
			if (rotKitC > 350.0) {
				movKitX = 0.0;
				movKitY = 0.0;
				estadoR = false;
				estadoS = true;
			}
		}

		if (estadoS) {
			movKitZ++;
			if (movKitZ >= 0.0) {
				estadoS = false;
				//variables reinicio
				rotKitA = 0.0;
				rotKitB = 0.0;
				rotKitC = 0.0;
				estadoA = true;
			}
		}
	}
	//Pendulo
	if (inicio) {

		if (estado1) {
			rotpendulo += 5.0;
			if (rotpendulo > 66.0) {
				estado1 = false;
				estado2 = true;
			}
		}

		if (estado2) {
			rotpendulo -= 5.0;
			if (rotpendulo < -66.0) {
				estado2 = false;
				estado1 = true;
			}
		}
	}

	//Kilahuea
	if (inicio) {

		if (estado1A) {
			trasKila += 3.0;
			if (trasKila > 28.0) {
				estado1A = false;
				estado2A = true;
			}
		}

		if (estado2A) {
			trasKila -= 1.0;
			if (trasKila <= 1.0) {
				estado1A = true;
				estado2A = false;
			}
		}

	}

	//Pajaros//
	if (inicio) {

		if (estado3A) {
			movZAve -= 1.0;

			if (movZAve < -160.0) {
				estado3A = false;
				estado3B = true;
				movXAve = 41.0;
				rotAve1 = 160.0;
			}
		}
		if (estado3B) {
			movZAve++;
			if (movZAve > 66.0) {
				estado3B = false;
				movXAve = 0.0;
				rotAve1 = 8.0;
				estado3A = true;

			}
		}

		if (inicio) {
			if (estado3C) {
				movZAv2 += 0.5;
				if (movZAv2 > 88.0) {
					estado3C = false;
					estado3D = true;
					rotAve2 = 90.0;
				}
			}

			if (estado3D) {
				movXAve1++;
				if (movXAve1 > 113.0) {
					estado3D = false;
					estado3E = true;
					rotAve2 = 180.0;
				}
			}

			if (estado3E) {
				movZAv2--;
				if (movZAv2 < -65.0) {
					estado3E = false;
					estado3F = true;
					rotAve2 = 270.0;
				}
			}

			if (estado3F) {
				movXAve1--;
				if (movXAve1 <= 0.0) {
					estado3F = false;
					estado3G = true;
					rotAve2 = 0.0;
				}
			}

			if (estado3G) {
				movZAv2 += 0.5;
				if (movZAv2 >= 0.0) {
					estado3G = false;
					estado3C = true;
				}
			}

		}

	}

	//inicio recorrido
	if (inicio2) {
		if (estadoA1) {


			objCamera.mPos.x += 0.05;
			objCamera.mPos.z -= 0.5;
			objCamera.mView.x += 0.05;
			objCamera.mView.z -= 0.5;
			if (objCamera.mView.z < -59.0) {
				estadoA1 = false;
				estadoA2 = true;
			}

		}

		if (estadoA2) {

			objCamera.mView.x -= 2.5;
			objCamera.mView.z += 1.0;

			if (objCamera.mView.z > -24.0) {
				estadoA2 = false;
				estadoA3 = true;
			}
		}

		if (estadoA3) {
			objCamera.mPos.x -= 0.5;
			objCamera.mPos.z -= 1.0;
			objCamera.mView.x -= 0.5;
			objCamera.mView.z -= 1.0;

			if (objCamera.mPos.z < 11.0) {
				estadoA3 = false;
				estadoA4 = true;
			}

		}

		if (estadoA4) {
			objCamera.mView.x += 3.5;
			objCamera.mView.z += 1.0;

			if (objCamera.mView.z > 10.0) {
				estadoA4 = false;
				estadoA5 = true;
			}

		}

		if (estadoA5) {
			objCamera.mPos.x += 1.0;
			objCamera.mView.x += 1.0;

			if (objCamera.mView.x > 185.0) {
				estadoA5 = false;
				estadoA6 = true;
			}
		}

		if (estadoA6) {
			objCamera.mView.x -= 4.0;
			objCamera.mView.z -= 2.5;

			if (objCamera.mView.z < -115.0) {
				estadoA6 = false;
			}
		}
	}

	//Movimiento del monito
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX; //SIGUIENTE CUADRO
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			//rotacion de la rodilla izquierda
			rotRodIzq += KeyFrame[playIndex].rotInc; //Le pasamos a la rotacion de la parte la rotacion inicial de dicha parte
			//rotacion de la rodilla derecha
			rotRodDer += KeyFrame[playIndex].rotIncDer; //variable de pierna derecha

			//rotacion de la pierna izquierda
			rotRodPiernaIzq += KeyFrame[playIndex].rotIncPI; //rotacion de la pierna izquierda
			rotRodPiernaDer += KeyFrame[playIndex].rotIncPD; //rotacion de la pierna izquierda
			rotCabeza += KeyFrame[playIndex].rotIncC; //rotacion de la cabeza
			rotCuello += KeyFrame[playIndex].rotIncCu; //rotacion del cuello
			rotBD += KeyFrame[playIndex].rotIncBD; //rotacion del brazo derecho
			rotBI += KeyFrame[playIndex].rotIncBI; //rotacion del brazo izquierdo
			rotCin += KeyFrame[playIndex].rotIncCin; //rotacion del brazo izquierdo
			giroMonito += KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
		}

	}
	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(0.01);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(0.01));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(0.01));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(0.01);
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

		break;

	case 'l':
	case 'L':
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	case ' ':
		inicio2 ^= true;
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
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
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex > 1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;
	}
}

void menu(int id)
{

}

int main(int argc, char** argv)   // Main Function
{
	PlaySound("diversiones.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	int submenu;
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("PFCG01"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}