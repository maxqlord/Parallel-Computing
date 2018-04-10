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
// 
#define N     600
#define TREE    1
#define FIRE    2
#define SPARK   3
#define BURNT   8
#define EMPTY   0
// 
char   t[N][N]     ;
int    pause = 0   ;
int    step        ;
double prob = 0.60 ;
// 
double r()
{
    return ( 1.0 * rand() ) / RAND_MAX ;
}
// 
void init( double prob )
{
    int x , y ;
    //
    for( x = 0 ; x < N ; x++ )
    {
        for( y = 0 ; y < N ; y++ )
        {
            if( r() < prob )
            {
                t[y][x] = TREE ;
            }
            else
            {
                t[y][x] = EMPTY ;
            }
        }
    }
    //
    step = 0 ;
}
// 
void fire()
{
    int y ;
    //
    for( y = 0 ; y < N ; y++ )
    {
        if( t[y][0] == TREE )
        {
            t[y][0] = FIRE ;
        }
    }
}
// 
void ck( int y , int x )
{
    if( y < 0 || y >= N || x < 0 || x >= N ) return ;
    //
    if( t[y][x] != TREE ) return ;
    //
    t[y][x] = SPARK ; // will be on fire shortly
}
// 
void idlefunc()
{
    int x , y    ;
    int fire = 0 ;
    //
    if( pause ) return ;
    //
    // first...
    //
    for( x = 0 ; x < N ; x++ )
    {
        for( y = 0 ; y < N ; y++ )
        {
            if( t[y][x] == FIRE )
            {
                ck( y - 1 , x     ) ;
                ck( y + 1 , x     ) ;
                ck( y     , x - 1 ) ;
                ck( y     , x + 1 ) ;
            }
        }
    }
    //
    // second...
    //
    for( x = 0 ; x < N ; x++ )
    {
        for( y = 0 ; y < N ; y++ )
        {
            if( t[y][x] == FIRE )
            {
                t[y][x] = BURNT ;
            }
            else if( t[y][x] == SPARK )
            {
                fire = 1;
                //
                t[y][x] = FIRE ;
            }
        }
    }
    //
    if( fire )
    {
        ++step ;
        //
        glutPostRedisplay(); // calls displayfunc
    }
}
void drawString( char* s )
{
    int k = 0 ;
    //
    while( s[k] != '\0' )
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,s[k]);
        //
        ++k ;
    }
}
/*
   GLUT_BITMAP_8_BY_13
   GLUT_BITMAP_9_BY_15
   GLUT_BITMAP_TIMES_ROMAN_10
   GLUT_BITMAP_TIMES_ROMAN_24
   GLUT_BITMAP_HELVETICA_10
   GLUT_BITMAP_HELVETICA_12
   GLUT_BITMAP_HELVETICA_18
*/
void conv( int n , char* str )
{
    int pow10 ;
    int j = 0 ;
    //
    if( n < 0 )
    {
        n = ( -n ) ; // possible bug at max negative int
        //
        str[0] = '-' ;
        //
        j = 1 ;
    }
    //
    pow10 = 1 ;
    while( pow10 <= n/10 ) pow10 *= 10 ;
    //
    while( pow10 > 0 )
    {
        str[j] = '0' + ( n / pow10 ) ;
        //
        n %= pow10 ;
        //
        ++j ;
        //
        pow10 /= 10 ;
    }
    //
    str[j] = '\0' ;
}
void displayfunc()
{
    int    x  , y  ;
    //
    double x1 , y1 ;
    double x2 , y2 ;
    double x3 , y3 ;
    //
    char stepstr[20]; // overkill... 20 digits
    //
    glClear(GL_COLOR_BUFFER_BIT); // white
    //
    for( x = 0 ; x < N ; x++ )
    {
        for( y = 0 ; y < N ; y++ )
        {
            if( t[y][x] == TREE )
            {
                glColor3f( 0.0 , 1.0 , 0.0 ) ; // green
            }
            else if( t[y][x] == FIRE )
            {
                glColor3f( 1.0 , 0.0 , 0.0 ) ; // red
            }
            else if( t[y][x] == BURNT )
            {
                glColor3f( 0.0 , 0.0 , 0.0 ) ; // black
            }
            else  // t[y][x] == EMPTY
            {
                glColor3f( 0.6 , 0.3 , 0.0 ) ; // brown
            }
            //
            glBegin(GL_POINTS);
            glVertex2f(x,y);
            glEnd();
        }
    }
    //
    glColor3f( 0.0 , 0.0 , 0.0 ) ; // black
    x1 = 0.825*N ; y1 = 0.875*N ;
    x2 = 0.950*N ; y2 = 0.875*N ;
    x3 = 0.950*N ; y3 = 0.950*N ;
    glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1); glVertex2f(x2,y2); glVertex2f(x3,y3);
    glEnd();
    x1 = 0.825*N ; y1 = 0.875*N ;
    x2 = 0.825*N ; y2 = 0.950*N ;
    x3 = 0.950*N ; y3 = 0.950*N ;
    glBegin(GL_TRIANGLES);
    glVertex2f(x1,y1); glVertex2f(x2,y2); glVertex2f(x3,y3);
    glEnd();
    //
    glColor3f( 1.0 , 1.0 , 1.0 ) ; // white
    glRasterPos2f(0.85*N,0.9*N);
    conv( step , stepstr ) ;
    drawString(stepstr);
    //
    glutSwapBuffers(); // single buffering... call glFlush();
}
void reshapefunc(int wscr,int hscr)
{
    glViewport(0,0,(GLsizei)N,(GLsizei)N);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1.0*N,0.0,1.0*N); // always a square
    glMatrixMode(GL_MODELVIEW);
}
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
}
void keyfunc(unsigned char key,int xscr,int yscr)
{
    if( key == ' ' )
    {
        pause = !pause ;
    }
    else if( key == 'q' )
    {
        exit( 0 ) ;
    }
}
int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(N,N);
    glutInitWindowPosition(100,50);
    glutCreateWindow("");
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_SMOOTH);
    //
    srand( 12345 ) ; // arbitrary random seed
    //
    init( prob ) ;
    fire( ) ;
    //
    glutIdleFunc(idlefunc);
    glutDisplayFunc(displayfunc);
    glutReshapeFunc(reshapefunc);
    glutMouseFunc(mousefunc);
    glutKeyboardFunc(keyfunc);
    //
    glutMainLoop();
    //
    return 0;
}
// 
// end of file
// 