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
#include <array>
#include <cmath>
#endif

#include <iostream>
#include <vector>

using namespace std;

int x;
int y;
std::vector<int> pointsY;
std::vector<int> pointsX;

std::vector<std::array<int, 2>> pointsInitial;
std::vector<std::array<int, 2>> pointsFinal;

float distance;

bool coordinateColor = true;
bool alternadorMouse = true;

float pointSize = 8.0;
float lineWidth = 3.0f;

static void resize(int width, int height){
    glViewport(0, 0, width, height);
}

void desenharEixos(){
    glColor3f(0, 0, 0);
     glBegin(GL_LINES);
       glVertex2i(0, 40);
       glVertex2i(0, -40);
       glVertex2i(-40, 0);
       glVertex2i(40, 0);
     glEnd();
}

void imprimirPonto(std::vector<int> pointsX, std::vector<int> pointsY) {
    for (int i = 0; i < pointsX.size(); i++) {
        glPointSize(pointSize);
        glBegin(GL_POINTS);
        glColor3f(1,0,0);
        glVertex2i(pointsX[i], pointsY[i]);
        glEnd();
    }
}

void imprimirLinha() {
    glColor3f(0, 0, 1);
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    for (size_t i = 0; i < pointsInitial.size() && i < pointsFinal.size(); i++) {
        glVertex2i(pointsInitial[i][0], pointsInitial[i][1]);
        glVertex2i(pointsFinal[i][0], pointsFinal[i][1]);
    }
    glEnd();
}

static std::vector<int> calculateCartesianPosition(int x, int y) {
    std::vector<int> coordenates;
    float xCartesian = x/11.25;
    float yCartesian = y/11.25;

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

static void mouseOne(int button, int state, int xTela, int yTela){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::vector<int> coordenates = calculateCartesianPosition(xTela, yTela);
        x = coordenates[0];
        y = coordenates[1];

        pointsX.push_back(x);
        pointsY.push_back(y);

        if (pointsX.size() % 2 == 1) {
            pointsInitial.push_back({x, y});
        }
        else {
            pointsFinal.push_back({x, y});

            int i = pointsFinal.size() - 1;
            float dist = sqrt(
                (pointsFinal[i][0] - pointsInitial[i][0]) * (pointsFinal[i][0] - pointsInitial[i][0]) +
                (pointsFinal[i][1] - pointsInitial[i][1]) * (pointsFinal[i][1] - pointsInitial[i][1])
            );

            cout << "x: " << coordenates[0] << "\t y: " << coordenates[1] << endl;

            cout << "Distancia entre os pontos (" << pointsInitial[i][0] << "," << pointsInitial[i][1] << ") e ("
                << pointsFinal[i][0] << "," << pointsFinal[i][1] << "): " << dist << endl;

            return;
        }

        cout << "x: " << coordenates[0] << "\t y: " << coordenates[1] << endl;

        glutPostRedisplay();
    }
}

static void mouseTwo(int button, int state, int xTela, int yTela){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::vector<int> coordenates = calculateCartesianPosition(xTela, yTela);
        x = coordenates[0];
        y = coordenates[1];

        pointsX.push_back(x);
        pointsY.push_back(y);

        size_t n = pointsX.size();

        if (n >= 2) {
            int x0 = pointsX[n - 2];
            int y0 = pointsY[n - 2];
            int x1 = pointsX[n - 1];
            int y1 = pointsY[n - 1];

            pointsInitial.push_back({x0, y0});
            pointsFinal.push_back({x1, y1});

            float dist = std::sqrt(
                (x1 - x0) * (x1 - x0) +
                (y1 - y0) * (y1 - y0)
            );

            std::cout << "x: " << coordenates[0] << "\t y: " << coordenates[1] << std::endl;
            std::cout << "Distancia entreeeeee os pontos (" << x0 << "," << y0 << ") e ("
                      << x1 << "," << y1 << "): " << dist << std::endl;
        } else {
            std::cout << "x: " << coordenates[0] << "\t y: " << coordenates[1] << std::endl;
        }

        glutPostRedisplay();
    }
}

static void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    if (coordinateColor) {
        desenharEixos();
    }
    imprimirPonto(pointsX, pointsY);
    imprimirLinha();
    glFlush();
}

static void key(unsigned char key, int x, int y){
    if (key == 27) { // ESC para sair
        exit(0);
    }

    if (key == 'E' || key == 'e') {
        coordinateColor = !coordinateColor;
        glutPostRedisplay();
    }

    if (key == '+') {
        pointSize += 2.0;
        lineWidth += 2.0f;
        glutPostRedisplay();
    } else if (key == '-') {
        pointSize -= 2.0;
        lineWidth -= 2.0f;
        glutPostRedisplay();
    }

    if (key == 'R' || key == 'r') {
        alternadorMouse = !alternadorMouse;
        if (alternadorMouse) {
            glutMouseFunc(mouseOne);
        } else {
            glutMouseFunc(mouseTwo);
        }
        glutPostRedisplay();
    }

    if ((key == 'Z' || key == 'z') && alternadorMouse) {
        if (pointsX.size() == 0 && pointsY.size() == 0) {
            glutPostRedisplay();
            return;
        }
        if (!pointsX.empty() && !pointsY.empty()) {
            pointsX.pop_back();
            pointsY.pop_back();
            pointsInitial.pop_back();
            pointsFinal.pop_back();
            //Correção quando for todas as linhas conjuntas
            pointsX.pop_back();
            pointsY.pop_back();
        }
        glutPostRedisplay();
    } else if ((key == 'Z' || key == 'z') && !alternadorMouse) {
        if (pointsX.size() == 0 && pointsY.size() == 0) {
            glutPostRedisplay();
            return;
        }
        if (!pointsX.empty() && !pointsY.empty()) {
            pointsX.pop_back();
            pointsY.pop_back();
            pointsInitial.pop_back();
            pointsFinal.pop_back();
        }
        glutPostRedisplay();
    }
}

void setup(){
    glViewport(0, 0, 400, 400);
    gluOrtho2D(-40.0f, 40.0f, -40.0f, 40.0f);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(lineWidth);
    glPointSize(pointSize);
    glViewport(0,0,900,900);
    desenharEixos();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(900, 900);

    glutInitWindowPosition(100, 100);

    glutCreateWindow("Atividade Avaliativa - Ex. solucao");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutReshapeFunc(resize);
    if (!alternadorMouse) {
        glutMouseFunc(mouseTwo);
    } else {
        glutMouseFunc(mouseOne);
    }

    setup();

    glutMainLoop();

    return 0;
}
