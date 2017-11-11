#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<iostream>

void display();
using namespace std;

float xmin,ymin,xmax,ymax;
float xd1,yd1,xd2,yd2;

int w=300;
double dw=300.0;

int bit[3][4]={0};

void init(void)
{

    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-dw,dw,-dw,dw);

}

void region_code(float x,float y,int i)
{
    if(y>ymax) bit[i][0]=1;
    if(y<ymin) bit[i][1]=1;
    if(x>xmax) bit[i][2]=1;
    if(x<xmin) bit[i][3]=1;
}

int AND(){

    bool result=0;
    for(int k=0;k<4;k++)
        if(bit[0][k] & bit[1][k] == 1) result=1;
    return result;
}

void LineClip()
{
    region_code(xd1,yd1,0);
    region_code(xd2,yd2,1);

//    for(int i=0;i<2;i++)
//        for(int j=0;j<4;j++)
//            printf("%d\n",bit[i][j]);
//    printf("\n\n");

    float m=(yd2-yd1)/(xd2-xd1);

    int cnt=0;
    while(true)
    {
        cnt++;

        float x1=xd1,y1=yd1,x2=xd2,y2=yd2;

        int ch=0;

        for(int k=0;k<4;k++)
            if(bit[0][k]==1 || bit[1][k]==1) ch=1;

        //Visible

        if(ch==0) break;

        ch=AND();

        // Non-visible

        if(ch==1 || cnt>6){
           xd1=0,xd2=0,yd1=0,yd2=0;
           break;
        }

        // Clipping candidate

        // First end point of line

        if(bit[0][0]==1){

            bit[0][0]=0;
            yd1 = ymax;
            xd1 = x1+ 1.0/m*(yd1-y1);
        }
        if(bit[0][1]==1){

            bit[0][1]=0;
            yd1 = ymin;
            xd1 = x1+ 1.0/m*(yd1-y1);
        }
        if(bit[0][2]==1){
            bit[0][2]=0;
            xd1 = xmax;
            yd1 = y1+m*(xd1-x1);
        }
        if(bit[0][3]==1){
            bit[0][3]=0;
            xd1 = xmin;
            yd1 = y1+m*(xd1-x1);
        }

        // Second end point of line

        if(bit[1][0]==1){
            bit[1][0]=0;
            yd2 = ymax;
            xd2 = x2+ 1.0/m*(yd2-y2);
        }
        if(bit[1][1]==1){
            bit[1][1]=0;
            yd2 = ymin;
            xd2 = x2+ 1.0/m*(yd2-y2);
        }
        if(bit[1][2]==1){
            bit[1][2]=0;
            xd2 = xmax;
            yd2 = y2+m*(xd2-x2);
        }
        if(bit[1][3]==1){
            bit[1][3]=0;
            xd2 = xmin;
            yd2 = y2+m*(xd2-x2);
        }

        region_code(xd1,yd1,0);
        region_code(xd2,yd2,1);

//        for(int i=0;i<2;i++)
//        for(int j=0;j<4;j++)
//            printf("%d\n",bit[i][j]);
//        printf("\n\n");
    }

    display();

}

void mykey(unsigned char key,int x,int y)
{
    if(key=='c'){
        LineClip();
        glFlush();
    }
}
void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin,ymin);
    glVertex2i(xmin,ymax);
    glVertex2i(xmax,ymax);
    glVertex2i(xmax,ymin);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(xd1,yd1);
    glVertex2i(xd2,yd2);
    glEnd();

    glFlush();
}


int main(int argc,char** argv)
{
    printf("Enter 'c' after giving input of the co-ordinates to clip\n\n");
    printf("Enter line co-ordinate (x1,y1) and (x2,y2):\n");
    cin>>xd1>>yd1>>xd2>>yd2;

    printf("\nEnter clipping window co-ordinates (xmin,ymin) and (xmax,ymax):\n");
    cin>>xmin>>ymin>>xmax>>ymax;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Line Clipping");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}


/*
-200 -200 70 50
-100 -100 100 100

20 50 -30 10
-100 -100 100 100

150 150 150 0
-100 -100 100 100

70 -150 150 -50
-100 -100 100 100

-200 150 150 -120
-100 -100 100 100

*/
