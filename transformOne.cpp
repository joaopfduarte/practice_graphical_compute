//
// Created by joaop on 9/22/2025.
//

#include "header/transformOne.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

void desenharCirculo(GLsizei numeroVertice){
     float angulo, incremento;
     incremento = (2 * M_PI) / numeroVertice;
     glBegin(GL_POLYGON);
         for(angulo=0; angulo<2*M_PI; angulo+=incremento){
            glVertex2f(cos(angulo), sin(angulo));
         }
     glEnd();
}

void desenharQuadrado(){
	glBegin(GL_QUADS);
        glVertex2f(-1.0f,-1.0f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f( 1.0f, 1.0f);
        glVertex2f( 1.0f,-1.0f);
    glEnd();
}

void desenharTriangulo(){
    glBegin(GL_TRIANGLES);
		glVertex2f(-1.0f, 0.0f);
		glVertex2f( 1.0f, 0.0f);
		glVertex2f( 0.0f, 1.0f);
	glEnd();
}

void desenharCasa(){
    glPushMatrix();
        glTranslatef(0, 5, 0);
        glScalef(10, 5 , 1);
        desenharQuadrado();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 10, 0);
        glScalef(15, 5 , 1);
        desenharTriangulo();
    glPopMatrix();
}


//matriz de cisalhamento
GLfloat shearMatrix[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
   -0.8f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};


// Fun  o de callback chamada sempre que a janela   redimensionada.
static void resize(int width, int height){
    glViewport(0, 0, width, height);
}

// Fun  o de callback respons vel por desenhar os elementos na tela.
static void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    //gramado
    glPushMatrix();
        glTranslatef(0, -20, 0);
        glScalef(40, 20 , 1);
        glColor3f(0.0f, 1.0f, .0f);
        desenharQuadrado();
    glPopMatrix();

    //casa
    glColor3f(0.0f, 0.0f, 1.0f);
    desenharCasa();

    //sombra
    glPushMatrix();
        glMultMatrixf(shearMatrix);
        glScalef(1, -1 , 1);
        glColor3f(0.8f, 0.8f, 0.8f);
        desenharCasa();
    glPopMatrix();

    //linha
    glLineWidth(1.5f);
    glColor3f(0.0f, 0.0f, .0f);
    glBegin(GL_LINES);
       glVertex2i(-40, 0);
       glVertex2i(40, 0);
    glEnd();

    //sol
    glPushMatrix();
        glTranslatef(-20, 33, 0);
        glScalef(5, 5 , 1);
        glColor3f(1.0f, 1.0f, 0.0f);
        desenharCirculo(30);
    glPopMatrix();

	glFlush();
}

// Fun  o de callback para tratamento de eventos do teclado.
static void key(unsigned char key, int x, int y){
    // Encerra o programa quando a tecla ESC (c digo 27)   pressionada.
    if (key == 27)
        exit(0);
}


// Configura  es iniciais de visualiza  o (sistema de coordenadas).
void setup(void){

    glViewport(0, 0, 400, 400);
    gluOrtho2D(-40.0f, 40.0f, -40.0f, 40.0f);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

}

// Programa principal
int main(int argc, char *argv[]){
    // Inicializa a biblioteca GLUT
    glutInit(&argc, argv);

    // Define o modo de exibi  o (buffer simples + modelo de cores RGB)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Define o tamanho inicial da janela em pixels
    glutInitWindowSize(400, 400);

    // Define a posi  o inicial da janela na tela
    glutInitWindowPosition(100, 100);

    // Cria a janela e define o t tulo
    glutCreateWindow("Pr tica 03 - Exemplo 01");

    // Registra as fun  es de callback do GLUT
    glutDisplayFunc(display);   // redesenho
    glutKeyboardFunc(key);      // eventos do teclado
    glutReshapeFunc(resize);    // redimensionamento da janela

    // Executa as configura  es iniciais de visualiza  o
    setup();

    // Inicia o loop principal de eventos da GLUT
    glutMainLoop();

    return 0;
}
