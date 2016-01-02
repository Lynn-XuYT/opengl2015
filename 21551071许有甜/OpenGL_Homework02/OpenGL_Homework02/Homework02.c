#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/wglew.h>
#include "TextureTool.h"
#include <stdio.h>
#include <math.h>
#pragma comment (lib, "freeglut.lib")
#pragma comment (lib, "glew32.lib")


#define MAXTEXTURE	4				// ��������������Ŀ

GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 0.0f };					// ���廷�������ɫ
GLfloat LightDiffuse[] = { 1.0f, 0.7f, 0.1f, 0.0f };					// ��������������ɫ
GLfloat LightPosition[] = { 0.0f, 0.0f, -5.0f, 1.0f };					// �����Դ��λ��
GLUquadricObj* quadric;

GLuint	texture[MAXTEXTURE];											// �������飬������������


// OpenGL��ʼ��
void initGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// ��������
	texture[0] = LoadTexture("Data/1.bmp");
	texture[1] = LoadTexture("Data/2.bmp");
	texture[2] = LoadTexture("Data/3.bmp");
	texture[3] = LoadTexture("Data/4.bmp");

	glEnable(GL_TEXTURE_2D);											// ����2D����ӳ��
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);						// ���û�����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);						// �����������
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	quadric = gluNewQuadric();											// ����һ���������ָ��
	gluQuadricTexture(quadric, GLU_TRUE);								// ������������
	gluQuadricDrawStyle(quadric, GLU_FILL);								// �������
	glEnable(GL_LIGHTING);												// �򿪹���
	glEnable(GL_LIGHT1);												// �򿪹�Դ1
}

//////////////////////////////////////////////////////////////////////////
// ̫�������������
// һ��12���£����蹲360�죬ÿ����30��
static int day = 100; // day�ı仯���� 0�� 359
void myDisplay(void)
{
	// ����ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);										// ������ϵ������Ļ8.0f
	glRotatef(10, 1.0f, 0.0f, 0.0f);									// ������ϵ��x����ת10��
	gluLookAt(0, 50, -50, 0, 0, 0, 0, 0, 1);
	
	// ���ƺ�ɫ��̫��
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture[2]);							// ������
	gluSphere(quadric, 14.0f, 32, 32);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);												// ��������

 	// ������ɫ�ĵ���
	glDisable(GL_LIGHT1);												// �رչ���
	glDisable(GL_LIGHTING);
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day / 360.0*360.0, 0.0f, 1.0f, 0.0f);						// ������ϵ��Y����ת�Ƕȣ����Ƶ���ת
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);									// ������ϵ��X����ת-90��
	glTranslatef(30.0f, 0.0f, 0.0f);
	glPushMatrix();														// ��ǰģ����ͼ������ջ
	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, 1.0f);						// ������ϵ��Z����ת�Ƕȣ����Ƶ�����ת
	glBindTexture(GL_TEXTURE_2D, texture[0]);							// ������
	gluSphere(quadric, 5.5f, 32, 32);									// ��������
	glPopMatrix();														// ��ǰģ����ͼ�����ջ
	glEnable(GL_LIGHTING);												// ��������
	glEnable(GL_LIGHT1);


 	// ���ư�ɫ������
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT1);// �رչ���
	glColor3f(1.0f, 1.0f, 1.0f);
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, 1.0f);	// ������ϵ��Z����תmp_Angle�Ƕȣ�����������ת
	glTranslatef(8.5f, 0.0f, 0.0f);										// ����0.5f
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, 1.0f);	// ������ϵ��Z����תms_Angle�Ƕȣ�����������ת
	glBindTexture(GL_TEXTURE_2D, texture[3]);							// ������
	gluSphere(quadric, 2.5f, 32, 32);									// ������������
	glEnable(GL_LIGHTING);												// ��������
	glEnable(GL_LIGHT1);
	
	glutSwapBuffers();
	glFlush();
}

void update(int p)
{
	day++;
	if (day > 360)
	{
		day = 0;
	}
	glutTimerFunc(30, update, 0);
	glutPostRedisplay();
}

// ���ô��ڸı��Сʱ�Ĵ�����
void Reshape(int width, int height)
{
	if (height == 0)
	{
		height = 600;
	}
	// �����ӿ�
	glViewport(0, 0, width, height);
	// ����ͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("̫��-����-����");
	initGL();
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(Reshape);	// ���ô��ڸı��Сʱ�Ĵ�����
	glutTimerFunc(30, update, 1);
	glutMainLoop();
	return 0;
}

