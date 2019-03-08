// Name: Shuang Wu
// Quarter, Year: Winter, 2019
// Lab: 07
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

vector<vec3> points;

float factorial(int n){if(n==0){return 1;} return(n*factorial(n-1));}
float combination(int n, int k){return(factorial(n)/(factorial(k)*factorial(n-k)));}
float binomial(int n, int k, float t){return(combination(n,k)*pow(t,k)*pow(1-t,n-k));}


void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f,0.0f,0.0f);
    // just for example, remove if desired
    for(float t = 0; t < 1; t = t + 0.01)
    {
        vec3 B(0,0,0);
        int n =2;
        for( int i = 0; i<int(points.size()); i++)
        {
            B = B + binomial(points.size()-1, i, t) * points[i];
        }
        glVertex2f(B[0],B[1]);
    }
 //   glVertex2f(points[0][0],points[0][1]);
  //  glVertex2f(points[1][0],points[1][1]);
    glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
        glutPostRedisplay();
        vec3 a(px,py,dummy_z);
        points.push_back(a);
        /*for ( int i =0; i<100;i++)
        {
            if(points[i][0] == 0.00&& points[i][1] == 0.00)
            {
                points[i] = a;
                break;
            }
        }*/
        
        
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - Shuang Wu");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
