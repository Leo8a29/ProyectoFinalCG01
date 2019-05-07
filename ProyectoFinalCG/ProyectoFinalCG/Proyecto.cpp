//******************************************************************//
//*************			Visual Studio 2017					   ****//
//*************				Proyecto Final - 1er avance			***//
//*************   		Computación Gráfica   Gpo:1            ***//
//*************		Alumno: Ochoa Nava Jose Leonardo			 **//
//****************************************************************//

//El codigo de la practica 11 fue la base para crear el proyecto y avance 1 .

#include "texture.h"
#include "figuras.h"
#include "Camera.h"


static GLuint ciudad_display_list;	//Display List for the Monito

//NEW// Keyframes
//Variables de dibujo y manipulacion
//Agrego variables

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

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

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

CFiguras cubo;
CFiguras sky;

float abrirPuerta = 0;

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito
CFiguras pisoObj; //para crear el piso
CFiguras pilar;
CFiguras fachada; //para la fachada

void castillo() {
						//Pared de atras
	glPushMatrix(); 
	glTranslatef(7.0, -30, -80);
	glRotatef(90.0, 0, 0, 1);
	fachada.prisma(110.0, 20, 5.0, block.GLindex);
	glPopMatrix();
						//Cilindro trasero izquierdo
	glPushMatrix(); 
	glTranslatef(77.0, -40.0, -80.0);
	glScalef(15.0, 50.0, 5.0);
	pilar.cilindro(1.0, 1.0, 100, block.GLindex);
	glPopMatrix();
						//Cilindro trasero derecho
	glPushMatrix();
	glTranslatef(-63.0, -40.0, -80.0);
	glScalef(15.0, 50.0, 5.0);
	pilar.cilindro(1.0, 1.0, 100, block.GLindex);
	glPopMatrix();
						//Pared de la izquierda
	glPushMatrix();
	glTranslatef(-65.0, -30, -20.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	fachada.prisma(110.0, 20, 5.0, block.GLindex);
	glPopMatrix();
						//Cilindro delantero izquierdo
	glPushMatrix(); 
	glTranslatef(-63.0, -40.0, 40.0);
	glScalef(15.0, 50.0, 5.0);
	pilar.cilindro(1.0, 1.0, 100, block.GLindex);
	glPopMatrix();
						//Pared de enfrente
	glPushMatrix(); 
	glTranslatef(-24.0, -30.0, 40.0);
	glRotatef(90, 0, 0, 1);
	fachada.prisma(50.0, 20, 5.0, block.GLindex);
	glPopMatrix();
						//Pared media de enfrente
	glPushMatrix();
	glTranslatef(13.0, -25.0, 40.0);
	glRotatef(90, 0, 0, 1);
	fachada.prisma(25.0, 10, 5.0, block.GLindex);
	glPopMatrix();
						//Pared media de enfrente
	glPushMatrix(); 
	glTranslatef(50.0, -30.0, 40.0);
	glRotatef(90, 0, 0, 1);
	fachada.prisma(50.0, 20, 5.0, block.GLindex);
	glPopMatrix();
						//cilindro delantero derecho
	glPushMatrix(); 
	glTranslatef(80.0, -40.0, 40.0);
	glScalef(15.0, 50.0, 5.0);
	pilar.cilindro(1.0, 1.0, 100, block.GLindex);
	glPopMatrix();
						//Pared derecha
	glPushMatrix();
	glTranslatef(80.0, -30, -20.0);
	glRotatef(90, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	fachada.prisma(110.0, 20, 5.0, block.GLindex);
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
	glEndList();

	return(ciudadDL);
}

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);


	text1.LoadBMP("orig.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("block2.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	//Textura de pasto
	pasto.LoadBMP("grass2.bmp");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	block.LoadBMP("block.bmp");
	block.BuildGLTexture();
	block.ReleaseImage();

	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	ciudad_display_list = createDL();
}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();

	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
	objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
	objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);

	glPushMatrix();

	glPushMatrix(); //Cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(200.0, 200.0, 200.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Pasto
	glDisable(GL_LIGHTING);
	glTranslatef(0, -40.0, 0);
	glRotatef(90, 1, 0, 0);
	pisoObj.prisma(200.0, 200.0, 0.1, pasto.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //castillo
	glDisable(GL_LIGHTING);

	castillo();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); 
	glScalef(7, 0.1, 7);
	glDisable(GL_LIGHTING);
	fig3.prisma_anun(text3.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "P.F-CG01- 1er avance");
	pintaTexto(-11, 8.5, -14, (void *)font, s);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

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
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
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

void menu(int id)
{

}

int main(int argc, char** argv)   // Main Function
{
	int submenu;
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 11"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras	
	glutCreateMenu(menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();          // 

	return 0;
}