#include <GL/freeglut.h>
#include <iostream>


GLboolean IsSolid = true;
GLboolean IsSmall = true;
GLfloat Delta = 0.0;

//화면에 어떤식으로 보이게 할지 결정하는 함수.
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.0, 0.5);
    //시간에 따라서 주전자의 크기가 점점 작아지도록 설정한다.
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

//Reshape 콜백
//윈도우 크기 조절에 따른 왜곡 방지를 위한 MyReshape함수
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
//Esc키를 누르면 종료할 수 있또록 설정한다.
void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
    if (KeyPressed == 27)
    {
        //'esc' 키의 아스키 코드 값
        exit(0);
    }
}

//Timer Callback
//시간이 지남에 따라 주전자의 크기가 작아지도록 하기 위한 함수.
void MyTimer(int Value) {
    Delta = Delta + 0.001;
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer, 1);
}


//Menu Callback(Cascaded Menu 사용)
//Solid인지 Wire인지 결정하는 함수.
void MyMainMenu(int entryID) {
    if (entryID == 1)
        IsSolid = true;                
    else if (entryID == 2)
        IsSolid = false;               
    else if (entryID == 3)
        exit(0);                        
    glutPostRedisplay();
}

//사이즈를 결정하기 위하여 IsSmall의 참, 거짓 유무를 결정.
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
    //아래 메뉴로 작은사이즈와 큰사이즈를 구분한다.
    GLint MySubMenuID = glutCreateMenu(MySubMenu);
    glutAddMenuEntry("Small One", 1);
    glutAddMenuEntry("Big One", 2);
    //아래 메뉴로 Solid를 사용할건지, Wire를 사용할건지 결정한다.
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