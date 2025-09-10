//
// Created by joaop on 9/10/2025.
//

#include "header/exAv01.h"
//
// Created by joaop on 9/8/2025.
//

#include "header/sru_srt.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>

using namespace std;

// Função de callback chamada sempre que a janela é redimensionada.
int x;
int y;
std::vector<int> pointsX;
std::vector<int> pointsY;
bool coordinateColor = true;

static void resize(int width, int height){
    glViewport(0, 0, width, height);
}

void desenharEixos(){
    glColor3f(1, 1, 0);
     glBegin(GL_LINES);
       glVertex2i(0, 40); //eixo Y
       glVertex2i(0, -40);
       glVertex2i(-40, 0);//eixo X
       glVertex2i(40, 0);
     glEnd();
}

void imprimirPonto(std::vector<int> pointsX, std::vector<int> pointsY) {
    for (int i = 0; i < pointsX.size(); i++) {
        glBegin(GL_POINTS);
        glColor3f(1,0,0);
        glVertex2i(pointsX[i], pointsY[i]);
        glEnd();
    }

}

// Função de callback responsável por desenhar os elementos na tela.
static void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // Se a flag estiver ligada, desenha os eixos
    if (coordinateColor) {
        desenharEixos();
    }

    // Se já clicou com o mouse, imprime o ponto também
    imprimirPonto(pointsX, pointsY);

    // Força a execução imediata dos comandos OpenGL
    glFlush();
}

// Função de callback para tratamento de eventos do teclado.
static void key(unsigned char key, int x, int y){
    if (key == 27) { // ESC para sair
        exit(0);
    }

    if (key == 'E' || key == 'e') { // alterna os eixos
        coordinateColor = !coordinateColor;
        glutPostRedisplay(); // força redesenho
    }
}
static std::vector<int> calculateCartesianPosition(int x, int y) {
    std::vector<int> coordenates;
    int xCartesian = x/5;
    int yCartesian = y/5;

    if (xCartesian < 40) {
        xCartesian = (-1)*(40-xCartesian);
    } else {
        xCartesian = xCartesian - 40;
    }

    if (yCartesian < 40) {
        yCartesian = (40-yCartesian);
    } else {
        yCartesian = (yCartesian - 40)*(-1);
    }
    coordenates.push_back(xCartesian);
    coordenates.push_back(yCartesian);
    return coordenates;
}

// Função de callback para tratamento de eventos do mouse.
static void mouse(int button, int state, int xTela, int yTela){
    std::vector<int>coordenates = calculateCartesianPosition(xTela, yTela);
    x = coordenates[0];
    y = coordenates[1];
    pointsX.push_back(x);
    pointsY.push_back(y);
    imprimirPonto(pointsX,pointsY);
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
            cout << "x_universo: " << coordenates[0] << "\t y_universo: " << coordenates[1] << endl;
    }
}

// Configurações iniciais de visualização (sistema de coordenadas).
void setup(){
    glViewport(0, 0, 400, 400);               // define a área inicial de renderização
    gluOrtho2D(-40.0f, 40.0f, -40.0f, 40.0f); // sistema de coordenadas 2D

    // Define a cor de desenho padrão como branco
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Limpa a janela de visualização aplicando a cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    // Configura a espessura da linha, define a cor amarela e desenha os eixos
    glLineWidth(2.0f);
    glViewport(0,0,400,400);
    desenharEixos();
    glPointSize(4.0);
}

// Programa principal
int main(int argc, char *argv[]){
    // Inicializa a biblioteca GLUT
    glutInit(&argc, argv);

    // Define o modo de exibição (buffer simples + modelo de cores RGB)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Define o tamanho inicial da janela em pixels
    glutInitWindowSize(400, 400);

    // Define a posição inicial da janela na tela
    glutInitWindowPosition(100, 100);

    // Cria a janela e define o título
    glutCreateWindow("Pratica 02 - Exemplo 01");

    // Registra as funções de callback do GLUT
    glutDisplayFunc(display);   // redesenho
    glutKeyboardFunc(key);      // eventos do teclado
    glutReshapeFunc(resize);    // redimensionamento da janela
    glutMouseFunc(mouse);    // eventos do mouse

    // Executa as configurações iniciais de visualização
    setup();

    // Inicia o loop principal de eventos da GLUT
    glutMainLoop();

    return 0;
}
