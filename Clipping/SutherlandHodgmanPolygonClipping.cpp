#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<iostream>
#include<vector>

void display();
using namespace std;

float xmin,ymin,xmax,ymax;

int w=300;
double dw=300.0;

vector <float>x0,x1,x2,y0,y1,y2;


void drawAxis(){
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(0, w);
    glVertex2i(0, -w);
    glVertex2i(w, 0);
    glVertex2i(-w, 0);
    glEnd();
}

void init(void)
{

    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-dw,dw,-dw,dw);

}


void PolygonClip()
{
    int i,l;
    float x,y;

    // 1st Line

    l = x0.size();
    x1.clear();
    y1.clear();

    for(i=0;i<l;i++){

        if(i==0){

            float m=(y0[i]-y0[l-1])/(x0[i]-x0[l-1]);

            if(y0[l-1]>=ymin && y0[i]>=ymin){
                x1.push_back(x0[i]);
                y1.push_back(y0[i]);
            }

            else if(y0[l-1]<ymin && y0[i]>ymin){
                y1.push_back(ymin);
                x = x0[i] + (ymin - y0[i])/m;
                x1.push_back(x);

                x1.push_back(x0[i]);
                y1.push_back(y0[i]);
            }

            else if(y0[l-1]>=ymin && y0[i]<ymin){
                y1.push_back(ymin);
                x = x0[i] + (ymin - y0[i])/m;
                x1.push_back(x);
            }
        }

        else{

            float m=(y0[i]-y0[i-1])/(x0[i]-x0[i-1]);

            if(y0[i-1]>=ymin && y0[i]>=ymin){
                x1.push_back(x0[i]);
                y1.push_back(y0[i]);
            }

            else if(y0[i-1]<ymin && y0[i]>ymin){
                y1.push_back(ymin);
                x = x0[i] + (ymin - y0[i])/m;
                x1.push_back(x);

                x1.push_back(x0[i]);
                y1.push_back(y0[i]);
            }

            else if(y0[i-1]>=ymin && y0[i]<ymin){
                y1.push_back(ymin);
                x = x0[i] + (ymin - y0[i])/m;
                x1.push_back(x);
            }
        }
    }


    // 2nd Line


    l = x1.size();
    x0.clear();
    y0.clear();

    for(i=0;i<l;i++){

        if(i==0){

            float m=(y1[i]-y1[l-1])/(x1[i]-x1[l-1]);

            if(x1[l-1]<=xmax && x1[i]<=xmax){
                x0.push_back(x1[i]);
                y0.push_back(y1[i]);
            }

            else if(x1[l-1]>xmax && x1[i]<xmax){
                x0.push_back(xmax);
                y = y1[i] + (xmax - x1[i])*m;
                y0.push_back(y);

                x0.push_back(x1[i]);
                y0.push_back(y1[i]);
            }

            else if(x1[l-1]<=xmax && x1[i]>xmax){
                x0.push_back(xmax);
                y = y1[i] + (xmax - x1[i])*m;
                y0.push_back(y);
            }
        }

        else{

            float m=(y1[i]-y1[i-1])/(x1[i]-x1[i-1]);

            if(x1[i-1]<=xmax && x1[i]<=xmax){
                x0.push_back(x1[i]);
                y0.push_back(y1[i]);
            }

            else if(x1[i-1]>xmax && x1[i]<xmax){
                x0.push_back(xmax);
                y = y1[i] + (xmax - x1[i])*m;
                y0.push_back(y);

                x0.push_back(x1[i]);
                y0.push_back(y1[i]);
            }

            else if(x1[i-1]<=xmax && x1[i]>xmax){
                x0.push_back(xmax);
                y = y1[i] + (xmax - x1[i])*m;
                y0.push_back(y);
            }
        }
    }


    //3rd Line



    l = x0.size();
    x1.clear();
    y1.clear();

    for(i=0;i<l;i++){

        if(i==0){

            float m=(y0[i]-y0[l-1])/(x0[i]-x0[l-1]);

            if(y0[l-1]<=ymax && y0[i]<=ymax){
                x1.push_back(x0[i]);
                y1.push_back(y0[i]);
            }

            else if(y0[l-1]>ymax && y0[i]<ymax){
                y1.push_back(ymax);
                x = x0[i] + (ymax - y0[i])/m;
                x1.push_back(x);

                x1.push_back(x0[i]);
                y1.push_back(y0[i]);
            }

            else if(y0[l-1]<=ymax && y0[i]>ymax){
                y1.push_back(ymax);
                x = x0[i] + (ymax - y0[i])/m;
                x1.push_back(x);
            }
        }

        else{

            float m=(y0[i]-y0[i-1])/(x0[i]-x0[i-1]);

            if(y0[i-1]<=ymax && y0[i]<=ymax){
                x1.push_back(x0[i]);
                y1.push_back(y0[i]);
            }

            else if(y0[i-1]>ymax && y0[i]<ymax){
                y1.push_back(ymax);
                x = x0[i] + (ymax - y0[i])/m;
                x1.push_back(x);

                x1.push_back(x0[i]);
                y1.push_back(y0[i]);
            }

            else if(y0[i-1]<=ymax && y0[i]>ymax){
                y1.push_back(ymax);
                x = x0[i] + (ymax - y0[i])/m;
                x1.push_back(x);
            }
        }
    }



    // 4th Line


    l = x1.size();
    x0.clear();
    y0.clear();

    for(i=0;i<l;i++){

        if(i==0){

            float m=(y1[i]-y1[l-1])/(x1[i]-x1[l-1]);

            if(x1[l-1]>=xmin && x1[i]>=xmin){
                x0.push_back(x1[i]);
                y0.push_back(y1[i]);
            }

            else if(x1[l-1]<xmin && x1[i]>xmin){
                x0.push_back(xmin);
                y = y1[i] + (xmin - x1[i])*m;
                y0.push_back(y);

                x0.push_back(x1[i]);
                y0.push_back(y1[i]);
            }

            else if(x1[l-1]>=xmin && x1[i]<xmin){
                x0.push_back(xmin);
                y = y1[i] + (xmin - x1[i])*m;
                y0.push_back(y);
            }
        }

        else{

            float m=(y1[i]-y1[i-1])/(x1[i]-x1[i-1]);

            if(x1[i-1]>=xmin && x1[i]>=xmin){
                x0.push_back(x1[i]);
                y0.push_back(y1[i]);
            }

            else if(x1[i-1]<xmin && x1[i]>xmin){
                x0.push_back(xmin);
                y = y1[i] + (xmin - x1[i])*m;
                y0.push_back(y);

                x0.push_back(x1[i]);
                y0.push_back(y1[i]);
            }

            else if(x1[i-1]>=xmin && x1[i]<xmin){
                x0.push_back(xmin);
                y = y1[i] + (xmin - x1[i])*m;
                y0.push_back(y);
            }
        }
    }

    display();

}


void mykey(unsigned char key,int x,int y)
{
    if(key=='c'){
        PolygonClip();
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

    drawAxis();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<x0.size();i++){
        glVertex2i(x0[i],y0[i]);
    }
    glEnd();

    glFlush();
}


int main(int argc,char** argv)
{
    float x,y;
    int i,n;

    printf("Enter the number of vertex of the polygon to clip:\n");
    cin>>n;

    x0.clear();
    y0.clear();

    printf("Enter the vertices:\n");

    for(i=0;i<n;i++){
        cin>>x>>y;

        x0.push_back(x);
        y0.push_back(y);
    }


    printf("\nEnter clipping window co-ordinates (xmin,ymin) and (xmax,ymax):\n Enter 'c' to clip\n");
    cin>>xmin>>ymin>>xmax>>ymax;



    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Polygon Clipping");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}


/*
3
50 -150
150 100
125 150
-100 -100 100 100

9
-100 40
-50 -70
-20 -30
20 -70
70 10
60 30
60 150
-20 20
-40 100
-50 -50 50 50

3
-100 30
-20 30
-20 -20
-50 -50 50 50
*/
