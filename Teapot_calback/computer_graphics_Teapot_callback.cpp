#include <GL/freeglut.h>
#include <iostream>


GLboolean IsSolid = true;
GLboolean IsSmall = true;
GLfloat Delta = 0.0;

//ȭ�鿡 ������� ���̰� ���� �����ϴ� �Լ�.
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.0, 0.5);
    //�ð��� ���� �������� ũ�Ⱑ ���� �۾������� �����Ѵ�.
    if ((IsSolid) && (IsSmall))
    {
        if (Delta >= 0.3)
            return;
        glutSolidTeapot(0.3 - Delta);
    }
    else if ((IsSolid) && (!IsSmall))
    {
        if (Delta >= 0.6)
            return;
        glutSolidTeapot(0.6 - Delta);
    }
    else if ((!IsSolid) && (IsSmall))
    {
        if (Delta >= 0.3)
            return;
        glutWireTeapot(0.3 - Delta);
    }
    else
    {
        if (Delta >= 0.6)
            return;
        glutWireTeapot(0.6 - Delta);
    }
    glFlush();
}

//Reshape �ݹ�
//������ ũ�� ������ ���� �ְ� ������ ���� MyReshape�Լ�
void MyReshape(int NewWidth, int NewHeight) {
    glViewport(0, 0, NewWidth, NewHeight);
    GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)300;
    GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)300;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor,
        -1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}

//Keyboard Callback
//EscŰ�� ������ ������ �� �ֶǷ� �����Ѵ�.
void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
    if (KeyPressed == 27)
    {
        //'esc' Ű�� �ƽ�Ű �ڵ� ��
        exit(0);
    }
}

//Timer Callback
//�ð��� ������ ���� �������� ũ�Ⱑ �۾������� �ϱ� ���� �Լ�.
void MyTimer(int Value) {
    Delta = Delta + 0.001;
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer, 1);
}


//Menu Callback(Cascaded Menu ���)
//Solid���� Wire���� �����ϴ� �Լ�.
void MyMainMenu(int entryID) {
    if (entryID == 1)
        IsSolid = true;                
    else if (entryID == 2)
        IsSolid = false;               
    else if (entryID == 3)
        exit(0);                        
    glutPostRedisplay();
}

//����� �����ϱ� ���Ͽ� IsSmall�� ��, ���� ������ ����.
void MySubMenu(int entryID) {
    if (entryID == 1)
        IsSmall = true;                 
    else if (entryID == 2)
        IsSmall = false;                
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Teapot project");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    //�Ʒ� �޴��� ����������� ū����� �����Ѵ�.
    GLint MySubMenuID = glutCreateMenu(MySubMenu);
    glutAddMenuEntry("Small One", 1);
    glutAddMenuEntry("Big One", 2);
    //�Ʒ� �޴��� Solid�� ����Ұ���, Wire�� ����Ұ��� �����Ѵ�.
    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("Solid Teapot", 1);
    glutAddMenuEntry("Wire Teapot", 2);
    glutAddSubMenu("Change Size", MySubMenuID);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutTimerFunc(40, MyTimer, 1);

    glutMainLoop();
    return 0;
}