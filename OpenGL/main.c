//
// Created by Max Lord on 4/10/18.


//
// to compile type... make
// uses file named... Makefile
//
// a.out: fireGL.c
// 	gcc fireGL.c -lGL -lGLU -lglut
//
// tab character '\t' before gcc
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//
#include <GLUT/glut.h>
#include <math.h>
//
#define W     800
#define H     600
double x_scale = 2.0;
double y_scale = 1.5;
int maxSteps = 10;

//
void displayfunc()
{
    int    x  , y  ;


    //
    glClear(GL_COLOR_BUFFER_BIT); // white
    //
    for( x = 0 ; x < W ; x++ )
    {
        for( y = 0 ; y < H ; y++ )
        {
            double a = (1.0 * x/W) * (2*x_scale) - x_scale;
            double b = (1.0 * y/H) * (2*y_scale) - y_scale;

            double re = 0.0;
            double im = 0.0;

            int steps = 0;
                //glColor3f( 0.0 , 1.0 , 0.0 ) ; // green
            for(int i = 0; i < maxSteps; i++) {
                double n_re = pow(re, 2) - pow(im, 2) + a;
                im = (2 * re * im) + b;
                re = n_re;

                if (pow(re, 2) + pow(im, 2) > 4) {
                    break;
                }
                steps++;
            }

            if(steps == maxSteps) {
                glColor3f(1.0,1.0,1.0);
            } else {
                double scale = 1.0 - pow(1- (1.0*steps/maxSteps), 3);
                glColor3f(.6*scale, .3*scale, 0 * scale);
            }


            glBegin(GL_POINTS);
            glVertex2f(x,y);
            glEnd();
        }
    }
    //

    //
    glutSwapBuffers(); // single buffering... call glFlush();
}
void reshapefunc(int wscr,int hscr)
{
    glViewport(0,0,(GLsizei)W,(GLsizei)H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1.0*W,0.0,1.0*H); // always a square
    glMatrixMode(GL_MODELVIEW);
}
/*
void mousefunc(int button,int state,int xscr,int yscr)
{
    if(button==GLUT_LEFT_BUTTON)
    {
        if(state==GLUT_DOWN)
        {
            init( prob ) ;
            fire( ) ;
        }
    }
    else if(button==GLUT_RIGHT_BUTTON)
    {
        if(state==GLUT_DOWN)
        {
            srand( time(NULL) ) ;
        }
    }
}*/
void keyfunc(unsigned char key,int xscr,int yscr)
{
    if( key == 'q' )
    {
        exit( 0 ) ;
    }
    else if (key == 'w') {
        maxSteps *=2;
        glutPostRedisplay();
    } else if(key == 's') {
        maxSteps /= 2;
        glutPostRedisplay();

    }
}
int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W,H);
    glutInitWindowPosition(100,50);
    glutCreateWindow("");
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_SMOOTH);
    //
    srand( 12345 ) ; // arbitrary random seed
    //
    //
    //glutIdleFunc(idlefunc);
    glutDisplayFunc(displayfunc);
    glutReshapeFunc(reshapefunc);
    //glutMouseFunc(mousefunc);
    glutKeyboardFunc(keyfunc);
    //
    glutMainLoop();
    //
    return 0;
}

