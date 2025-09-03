#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <math.h>

// Função de callback chamada sempre que a janela é redimensionada.
static void resize(int width, int height){
    glViewport(0, 0, width, height);
}

static void create_circle_point(int numPontos) {
    float angulo, incremento;
    glPointSize(4.0f);
    incremento = (2 * M_PI) / numPontos;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for(angulo = 0; angulo < (2*M_PI); angulo += incremento){
        glVertex2f(20*cos(angulo), 20*sin(angulo));
    }
    glEnd();
}

static void create_circle_line(int numPontos) {
    float angulo, incremento;
    glPointSize(4.0f);
    incremento = (2 * M_PI) / numPontos;
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    for(angulo = 0; angulo < (2*M_PI); angulo += incremento){
        glVertex2f(20*cos(angulo), 20*sin(angulo));
    }
    glEnd();
}
// Função de callback responsável por desenhar os elementos na tela.
static void display(){

    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, 200, 200);
    create_circle_point(7);

    glViewport(0, 200, 200, 200);
    create_circle_line(40);

    glViewport(200,200,200,200);
    create_circle_line(10);

    glViewport(200,0,200,200);
    create_circle_line(7);

    glFlush();
}

// Função de callback para tratamento de eventos do teclado.
static void key(unsigned char key, int x, int y){
    // Encerra o programa quando a tecla ESC (código 27) é pressionada.
    if (key == 27)
        exit(0);
}

// Configurações iniciais de visualização (sistema de coordenadas).
void setup(void){
    gluOrtho2D(-40.0f, 40.0f, -40.0f, 40.0f); // sistema de coordenadas 2D
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
    glutCreateWindow("Prática 01 - Exemplo 01");

    // Registra as funções de callback do GLUT
    glutDisplayFunc(display);   // redesenho
    glutKeyboardFunc(key);      // eventos do teclado
    glutReshapeFunc(resize);    // redimensionamento da janela

    // Executa as configurações iniciais de visualização
    setup();

    // Inicia o loop principal de eventos da GLUT
    glutMainLoop();

    return 0;
}
