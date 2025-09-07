//
// Created by joaop on 9/7/2025.
//

#include "header/house.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

// Função de callback chamada sempre que a janela é redimensionada.
static void resize(int width, int height) {
    glViewport(0, 0, width, height);
}

// Função de callback responsável por desenhar os elementos na tela.
static void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(200, 0, 400, 400);
    glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(-40.0f, -40.0f);
    glVertex2f(40.0f, -40.0f);
    glVertex2f(40.0f, 40.0f);
    glVertex2f(-40.0f, 40.0f);

    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2f(-10.0f, -38.0f);
    glVertex2f(10.0f, -38.0f);
    glVertex2f(10.0f, 10.0f);
    glVertex2f(-10.0f, 10.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(23.0f, 12.0f);
    glVertex2f(35.0f, 12.0f);
    glVertex2f(35.0f, 22.0f);
    glVertex2f(23.0f, 22.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex2f(23.0f, 17.0f);
    glVertex2f(35.0f, 17.0f);

    glVertex2f(29.0f, 12.0f);
    glVertex2f(29.0f, 22.0f);
    glEnd();

    glEnd();

    glViewport(200, 400, 400, 400);
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-40.0f, -40.0f);
    glVertex2f(40.0f, -40.0f);
    glVertex2f(0.0f, 40.0f);
    glEnd();
    glFlush();
}

// Função de callback para tratamento de eventos do teclado.
static void key(unsigned char key, int x, int y) {
    // Encerra o programa quando a tecla ESC (código 27) é pressionada.
    if (key == 27)
        exit(0);
}

// Configurações iniciais de visualização (sistema de coordenadas).
void setup(void) {
    gluOrtho2D(-40.0f, 40.0f, -40.0f, 40.0f); // sistema de coordenadas 2D
}


// Programa principal
int main(int argc, char *argv[]) {
    // Inicializa a biblioteca GLUT
    glutInit(&argc, argv);

    // Define o modo de exibição (buffer simples + modelo de cores RGB)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Define o tamanho inicial da janela em pixels
    glutInitWindowSize(800, 800);

    // Define a posição inicial da janela na tela
    glutInitWindowPosition(100, 100);

    // Cria a janela e define o título
    glutCreateWindow("Prática 01 - Exemplo 01");

    // Registra as funções de callback do GLUT
    glutDisplayFunc(display); // redesenho
    glutKeyboardFunc(key); // eventos do teclado
    glutReshapeFunc(resize); // redimensionamento da janela

    // Executa as configurações iniciais de visualização
    setup();

    // Inicia o loop principal de eventos da GLUT
    glutMainLoop();

    return 0;
}
