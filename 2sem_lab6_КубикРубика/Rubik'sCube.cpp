#include <iostream>
#include <glut.h>
#include "Cubik.hpp"

double Xrotate = 0;
double Yrotate = 0;
CubikRubik start;

void Keys(int k, int x, int y)
{
    //Заданное действие(для примера)
    if (k == GLUT_KEY_F1)
    {
        start.PifPaf();
    }
    //сборка
    else if (k == GLUT_KEY_F2)
    {

        start.RubiksCubeAssembler();

    }
    //разборка
    else if (k == GLUT_KEY_F3)
    {

        start.RubiksCubeDisassembler();

    }
    //Закрыть
    else if (k == GLUT_KEY_F4)
    {

        std::cout << "\nКонец работы программы\n";
        exit(EXIT_SUCCESS);

    }
    //Вращение кубика вокруг оси вправо
    else if (k == GLUT_KEY_RIGHT)
    {

    Yrotate = Yrotate + 8;

    }
    //Вращение кубика вокруг оси влево
    else if (k == GLUT_KEY_LEFT)
    {

    Yrotate = Yrotate - 8;

    }
    //Вращение кубика вокруг оси вверх
    else if (k == GLUT_KEY_UP)
    {

    Xrotate = Xrotate + 8;

    }
    //Вращение кубика вокруг оси вниз
    else if (k == GLUT_KEY_DOWN)
    {

    Xrotate = Xrotate - 8;

    }

    glutPostRedisplay();

}

void display()
{

    glClearColor(0.9, 0.8, 0.6, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(Xrotate, 1.0, 0.0, 0.0);
    glRotatef(Yrotate, 0.0, 1.0, 0.0);
    glScalef(0.2, 0.2, 0.2);
    start.draw();
    glFlush();
    glutSwapBuffers();


}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");
    start.getFile();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(GLUT_INIT_WINDOW_WIDTH / 3 , GLUT_INIT_WINDOW_HEIGHT / 7);
    glutCreateWindow("LAB №8 Maks Shein M3106");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glutDisplayFunc(display);
    glutSpecialFunc(Keys);
    glutMainLoop();

    return 0;

}