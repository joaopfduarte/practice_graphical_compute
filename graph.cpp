//
// Created by joaop on 9/3/2025.
//

#include "header/graph.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>
#include <vector>

// Função de callback chamada sempre que a janela é redimensionada.
static void resize(int width, int height) {
    glViewport(0, 0, width, height);
}

static std::vector<float> createFuncOne(bool answer) {
    std::vector<float> pointsXi = {-3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<float> pointYi = {15, 8, 3, 0, -1, 0, 3, 8};

    if(answer) {
        return pointsXi;
    }
    return pointYi;
}

static std::vector<float> createFuncTwo(bool answer) {
    std::vector<float> pointsXii = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<float> pointYii = {-18, -10, -4, 0, 2, 2, 0, -4, -10, -18};

    if(answer) {
        return pointsXii;
    }
    return pointYii;
}

static void createFuncThree(std::vector<float> pointsXi, std::vector<float> pointsYi) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < pointsXi.size(); i++) {
        glVertex2f(pointsXi[i], pointsYi[i]);
    }
    glEnd();
}

// Função de callback responsável por desenhar os elementos na tela.
static void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, 800, 800);
    glBegin(GL_LINES);
    glColor3f(1, 1, 0);
    //Eixo X
    glVertex2f(-40.0f, 0.0f);
    glVertex2f(40.0f, 0.0f);

    //Eixo Y
    glVertex2f(0.0f, -40.0f);
    glVertex2f(0.0f, 40.0f);
    glEnd();
    glColor3f(0, 0, 1);
    createFuncThree(createFuncOne(true), createFuncOne(false));
    glColor3f(1, 0, 0);
    createFuncThree(createFuncTwo(true), createFuncTwo(false));
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
