/*
*  Кирил Николаев Павлов
*  81177
*  6 група
*/


#include <cstdlib>
#include<iostream>
#include <math.h>
#include <GL/glfw.h>

bool running()
{
    return( !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam( GLFW_OPENED) );
}

void init()
{
    int width, height;

    glfwInit();
    if( !glfwOpenWindow( 640, 480, 0, 0, 0, 0, 8, 0, GLFW_WINDOW ) ) return;

    glfwGetWindowSize( &width, &height );
    height = height > 0 ? height : 1;

    glViewport( 0, 0, width, height );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 65.0f, (GLfloat)width/(GLfloat)height, 1.0f, 100.0f );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(0.0f, -10.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f );
}

void finit()
{
    glfwTerminate();
}

GLvoid CalculateVectorNormal(float fVert1[], float fVert2[],
                             float fVert3[], float *fNormalX,
                             float *fNormalY, float *fNormalZ)
{
    GLfloat Qx, Qy, Qz, Px, Py, Pz;

    Qx = fVert2[0]-fVert1[0];
    Qy = fVert2[1]-fVert1[1];
    Qz = fVert2[2]-fVert1[2];
    Px = fVert3[0]-fVert1[0];
    Py = fVert3[1]-fVert1[1];
    Pz = fVert3[2]-fVert1[2];

    *fNormalX = Py*Qz - Pz*Qy;
    *fNormalY = Pz*Qx - Px*Qz;
    *fNormalZ = Px*Qy - Py*Qx;

}

void Draw3DCurve(float x, float y, float z, float r, float alphaStart, float alphaEnd,float size,float sizey)
{
    int n = 64;
    float stepA = 2*M_PI/n;
    float alpha = alphaStart;
    float xt1,xt2,xt3,yt1,yt2,yt3,zt1,zt2,zt3;

    while(alpha <= alphaEnd)
    {
        alpha+=stepA;
    }
    alphaEnd=alpha;

    alpha = alphaStart;
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0.0,-1.0,0.0);
    while(alpha <= alphaEnd)
    {
        glVertex3f(x+r*cos(alpha), y, z+r*sin(alpha));
        glVertex3f(x+(size+r)*cos(alpha), y, z+(size+r)*sin(alpha));
        alpha+=stepA;
    }
    glEnd();


    alpha = alphaStart;
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0.0, 0.0, +1.0);
    while(alpha <= alphaEnd)
    {
        float fNormalX,fNormalY,fNormalZ;
        float fVert1[3]={x+(size+r)*cos(alpha-stepA),y,z+(size+r)*sin(alpha-stepA)};
        float fVert2[3]={x+(size+r)*cos(alpha),y,z+(size+r)*sin(alpha)};
        float fVert3[3]={x+(size+r)*cos(alpha-stepA),y+size,z+(size+r)*sin(alpha-stepA)};
        CalculateVectorNormal(fVert1, fVert2, fVert3, &fNormalX, &fNormalY, &fNormalZ);
        glNormal3f(fNormalX, fNormalY, fNormalZ);
        glVertex3f(x+(size+r)*cos(alpha), y, z+(size+r)*sin(alpha));
        glVertex3f(x+(size+r)*cos(alpha), y+sizey, z+(size+r)*sin(alpha));
        alpha+=stepA;
    }
    glEnd();


    alpha = alphaStart;
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0.0, +1.0, 0.0);
    while(alpha <= alphaEnd)
    {
        glVertex3f(x+r*cos(alpha), y+sizey, z+r*sin(alpha));
        glVertex3f(x+(size+r)*cos(alpha), y+sizey, z+(size+r)*sin(alpha));
        alpha+=stepA;
    }
    glEnd();


    alpha = alphaStart;
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0.0, 0.0, -1.0);
    while(alpha <= alphaEnd)
    {
        float fNormalX,fNormalY,fNormalZ;
        float fVert1[3]={x+r*cos(alpha-stepA),y+sizey,z+r*sin(alpha-stepA)};
        float fVert2[3]={x+r*cos(alpha),y+sizey,z+r*sin(alpha)};
        float fVert3[3]={x+r*cos(alpha-stepA), y, z+r*sin(alpha-stepA)};
        CalculateVectorNormal(fVert1, fVert2, fVert3, &fNormalX, &fNormalY, &fNormalZ);
        glNormal3f(fNormalX, fNormalY, fNormalZ);
        glVertex3f(x+r*cos(alpha), y+sizey, z+r*sin(alpha));
        glVertex3f(x+r*cos(alpha), y, z+r*sin(alpha));
        alpha+=stepA;
    }
    glEnd();


    glBegin(GL_QUAD_STRIP);
        float fNormalX,fNormalY,fNormalZ;
        float fVert1[3]={x+r*cos(alphaStart), y, z+r*sin(alphaStart)};
        float fVert2[3]={x+(size+r)*cos(alphaStart), y, z+(size+r)*sin(alphaStart)};
        float fVert3[3]={x+r*cos(alphaStart), y+sizey, z+r*sin(alphaStart)};
        CalculateVectorNormal(fVert1, fVert2, fVert3, &fNormalX, &fNormalY, &fNormalZ);
        glNormal3f(fNormalX, fNormalY, fNormalZ);

        glVertex3f(x+r*cos(alphaStart), y, z+r*sin(alphaStart));
        glVertex3f(x+(size+r)*cos(alphaStart), y, z+(size+r)*sin(alphaStart));
        glVertex3f(x+r*cos(alphaStart), y+sizey, z+r*sin(alphaStart));
        glVertex3f(x+(size+r)*cos(alphaStart), y+sizey, z+(size+r)*sin(alphaStart));
    glEnd();

    glBegin(GL_QUAD_STRIP);
        float fNormalX1,fNormalY1,fNormalZ1;
        float fVert11[3]={x+r*cos(alphaEnd), y, z+r*sin(alphaEnd)};
        float fVert21[3]={x+(size+r)*cos(alphaEnd), y, z+(size+r)*sin(alphaEnd)};
        float fVert31[3]={x+r*cos(alphaEnd), y+sizey, z+r*sin(alphaEnd)};
        CalculateVectorNormal(fVert11, fVert21, fVert31, &fNormalX1, &fNormalY1, &fNormalZ1);
        glNormal3f(fNormalX1, fNormalY1, fNormalZ1);

        glVertex3f(x+r*cos(alphaEnd), y, z+r*sin(alphaEnd));
        glVertex3f(x+(size+r)*cos(alphaEnd), y, z+(size+r)*sin(alphaEnd));
        glVertex3f(x+r*cos(alphaEnd), y+sizey, z+r*sin(alphaEnd));
        glVertex3f(x+(size+r)*cos(alphaEnd), y+sizey, z+(size+r)*sin(alphaEnd));
    glEnd();
}
void myParallelepiped(float startX,float y,float z,float endX,float sizez,float sizey,float zotmestvane)
{
    float x1=startX,x2=endX;
    //po -Y
    glBegin(GL_QUAD_STRIP);
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(x1, y, z);
        glVertex3f(x1, y, z-sizez);
        glVertex3f(x2, y, z+zotmestvane);
        glVertex3f(x2, y, z-sizez+zotmestvane);
    glEnd();

    //po +Z
    glBegin(GL_QUAD_STRIP);
        glNormal3f(0.0, 0.0, +1.0);
        glVertex3f(x1, y, z);
        glVertex3f(x1, y+sizey, z);
        glVertex3f(x2, y, z+zotmestvane);
        glVertex3f(x2, y+sizey, z+zotmestvane);
    glEnd();

    //po +Y
    glBegin(GL_QUAD_STRIP);
        glNormal3f(0.0, +1.0, 0.0);
        glVertex3f(x1, y+sizey, z);
        glVertex3f(x1, y+sizey, z-sizez);
        glVertex3f(x2, y+sizey, z+zotmestvane);
        glVertex3f(x2, y+sizey, z-sizez+zotmestvane);
    glEnd();

    //po -Z
    glBegin(GL_QUAD_STRIP);
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(x1, y+sizey, z-sizez);
        glVertex3f(x1, y, z-sizez);
        glVertex3f(x2, y+sizey, z-sizez+zotmestvane);
        glVertex3f(x2, y, z-sizez+zotmestvane);
    glEnd();

    //po -x
    glBegin(GL_QUAD_STRIP);
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(x1, y, z);
        glVertex3f(x1, y+sizey, z);
        glVertex3f(x1, y, z-sizez);
        glVertex3f(x1, y+sizey, z-sizez);
    glEnd();
    //po +x
    glBegin(GL_QUAD_STRIP);
        glNormal3f(+1.0, 0.0, 0.0);
        glVertex3f(x2, y, z+zotmestvane);
        glVertex3f(x2, y+sizey, z+zotmestvane);
        glVertex3f(x2, y, z-sizez+zotmestvane);
        glVertex3f(x2, y+sizey, z-sizez+zotmestvane);
    glEnd();
}
int main()
{
    init();

    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_COLOR_MATERIAL );
    glEnable( GL_LIGHT0 );



    while( running() )
    {
        glClear( GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT );
        glRotatef( 0.05, 0.4, -0.2, 0.7);

        glColor3ub( 255, 200, 0 );
        myParallelepiped(0,0,3.5,5,0.7,1.7,0);
        myParallelepiped(0,0,2.8,0.7,1,1.7,0);
        myParallelepiped(4.3,0,2.8,5,1,1.7,0);
        myParallelepiped(0,0,1.8,5,0.7,1.7,0);
        myParallelepiped(0,0,1.1,0.7,2.85,1.7,0);

        Draw3DCurve(-3,0,-1.6,3, 7*M_PI/4, 2*M_PI, 0.7,1.7);
        Draw3DCurve(-4,0,-1.2,3, 7*M_PI/4, 2*M_PI, 0.7,1.7);
        Draw3DCurve(-4,0,-1.2,3, M_PI/9, M_PI/4, 0.7,1.7);
        Draw3DCurve(-3.5,0,1,3, M_PI/9, M_PI/4, 0.7,1.7);

        myParallelepiped(1,0,-1.95,5,0.7,1.7,0);
        myParallelepiped(2.65,0,-1.25,3.35,3*0.7,1.7,0);
        myParallelepiped(0.4,0,-3.35,5.6,0.7,1.7,0);

        myParallelepiped(1,0,0.8,5.4,0.7,1.7,0);
        myParallelepiped(1,0,-0.8,4.5,0.5,1.7,0.2);

        Draw3DCurve(0,0,-5,6, M_PI/5, M_PI/4+0.09, 0.4,1.7);

        myParallelepiped(1.5,0,-0.8,2.7,0.5,1.7,1.5);
        glfwSwapBuffers();
    }

    finit();
    return 0;
}
