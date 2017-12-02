#include <windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<iostream>
#include<vector>

void display();

using namespace std;

float xmin,ymin,xmax,ymax;

int w = 300;
double dw = 300.0;
int num_polygon=0;
vector <float>x0[100],x1,x2,y0[100],y1,y2;


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

    for(int ind=0; ind<num_polygon; ind++){

        /// 1st Line
        l = x0[ind].size();
        x1.clear();
        y1.clear();

        for(i=0;i<l;i++){

            if(i==0){

                float m=(y0[ind][i]-y0[ind][l-1])/(x0[ind][i]-x0[ind][l-1]);

                if(y0[ind][l-1]>=ymin && y0[ind][i]>=ymin){
                    x1.push_back(x0[ind][i]);
                    y1.push_back(y0[ind][i]);
                }
                else if(y0[ind][l-1]<ymin && y0[ind][i]>ymin){
                    y1.push_back(ymin);
                    x = x0[ind][i] + (ymin - y0[ind][i])/m;
                    x1.push_back(x);

                    x1.push_back(x0[ind][i]);
                    y1.push_back(y0[ind][i]);
                }

                else if(y0[ind][l-1]>=ymin && y0[ind][i]<ymin){
                    y1.push_back(ymin);
                    x = x0[ind][i] + (ymin - y0[ind][i])/m;
                    x1.push_back(x);
                }
            }

            else{

                float m=(y0[ind][i]-y0[ind][i-1])/(x0[ind][i]-x0[ind][i-1]);

                if(y0[ind][i-1]>=ymin && y0[ind][i]>=ymin){
                    x1.push_back(x0[ind][i]);
                    y1.push_back(y0[ind][i]);
                }

                else if(y0[ind][i-1]<ymin && y0[ind][i]>ymin){
                    y1.push_back(ymin);
                    x = x0[ind][i] + (ymin - y0[ind][i])/m;
                    x1.push_back(x);

                    x1.push_back(x0[ind][i]);
                    y1.push_back(y0[ind][i]);
                }

                else if(y0[ind][i-1]>=ymin && y0[ind][i]<ymin){
                    y1.push_back(ymin);
                    x = x0[ind][i] + (ymin - y0[ind][i])/m;
                    x1.push_back(x);
                }
            }
        }

        // 2nd Line
        l = x1.size();
        x0[ind].clear();
        y0[ind].clear();

        for(i=0;i<l;i++){

            if(i==0){

                float m=(y1[i]-y1[l-1])/(x1[i]-x1[l-1]);

                if(x1[l-1]<=xmax && x1[i]<=xmax){
                    x0[ind].push_back(x1[i]);
                    y0[ind].push_back(y1[i]);
                }

                else if(x1[l-1]>xmax && x1[i]<xmax){
                    x0[ind].push_back(xmax);
                    y = y1[i] + (xmax - x1[i])*m;
                    y0[ind].push_back(y);

                    x0[ind].push_back(x1[i]);
                    y0[ind].push_back(y1[i]);
                }

                else if(x1[l-1]<=xmax && x1[i]>xmax){
                    x0[ind].push_back(xmax);
                    y = y1[i] + (xmax - x1[i])*m;
                    y0[ind].push_back(y);
                }
            }

            else{

                float m=(y1[i]-y1[i-1])/(x1[i]-x1[i-1]);

                if(x1[i-1]<=xmax && x1[i]<=xmax){
                    x0[ind].push_back(x1[i]);
                    y0[ind].push_back(y1[i]);
                }

                else if(x1[i-1]>xmax && x1[i]<xmax){
                    x0[ind].push_back(xmax);
                    y = y1[i] + (xmax - x1[i])*m;
                    y0[ind].push_back(y);

                    x0[ind].push_back(x1[i]);
                    y0[ind].push_back(y1[i]);
                }

                else if(x1[i-1]<=xmax && x1[i]>xmax){
                    x0[ind].push_back(xmax);
                    y = y1[i] + (xmax - x1[i])*m;
                    y0[ind].push_back(y);
                }
            }
        }

        //3rd Line
        l = x0[ind].size();
        x1.clear();
        y1.clear();

        for(i=0;i<l;i++){

            if(i==0){

                float m=(y0[ind][i]-y0[ind][l-1])/(x0[ind][i]-x0[ind][l-1]);

                if(y0[ind][l-1]<=ymax && y0[ind][i]<=ymax){
                    x1.push_back(x0[ind][i]);
                    y1.push_back(y0[ind][i]);
                }

                else if(y0[ind][l-1]>ymax && y0[ind][i]<ymax){
                    y1.push_back(ymax);
                    x = x0[ind][i] + (ymax - y0[ind][i])/m;
                    x1.push_back(x);

                    x1.push_back(x0[ind][i]);
                    y1.push_back(y0[ind][i]);
                }

                else if(y0[ind][l-1]<=ymax && y0[ind][i]>ymax){
                    y1.push_back(ymax);
                    x = x0[ind][i] + (ymax - y0[ind][i])/m;
                    x1.push_back(x);
                }
            }

            else{

                float m=(y0[ind][i]-y0[ind][i-1])/(x0[ind][i]-x0[ind][i-1]);

                if(y0[ind][i-1]<=ymax && y0[ind][i]<=ymax){
                    x1.push_back(x0[ind][i]);
                    y1.push_back(y0[ind][i]);
                }

                else if(y0[ind][i-1]>ymax && y0[ind][i]<ymax){
                    y1.push_back(ymax);
                    x = x0[ind][i] + (ymax - y0[ind][i])/m;
                    x1.push_back(x);

                    x1.push_back(x0[ind][i]);
                    y1.push_back(y0[ind][i]);
                }

                else if(y0[ind][i-1]<=ymax && y0[ind][i]>ymax){
                    y1.push_back(ymax);
                    x = x0[ind][i] + (ymax - y0[ind][i])/m;
                    x1.push_back(x);
                }
            }
        }

        // 4th Line
        l = x1.size();
        x0[ind].clear();
        y0[ind].clear();

        for(i=0;i<l;i++){

            if(i==0){

                float m=(y1[i]-y1[l-1])/(x1[i]-x1[l-1]);

                if(x1[l-1]>=xmin && x1[i]>=xmin){
                    x0[ind].push_back(x1[i]);
                    y0[ind].push_back(y1[i]);
                }

                else if(x1[l-1]<xmin && x1[i]>xmin){
                    x0[ind].push_back(xmin);
                    y = y1[i] + (xmin - x1[i])*m;
                    y0[ind].push_back(y);

                    x0[ind].push_back(x1[i]);
                    y0[ind].push_back(y1[i]);
                }

                else if(x1[l-1]>=xmin && x1[i]<xmin){
                    x0[ind].push_back(xmin);
                    y = y1[i] + (xmin - x1[i])*m;
                    y0[ind].push_back(y);
                }
            }

            else{

                float m=(y1[i]-y1[i-1])/(x1[i]-x1[i-1]);

                if(x1[i-1]>=xmin && x1[i]>=xmin){
                    x0[ind].push_back(x1[i]);
                    y0[ind].push_back(y1[i]);
                }

                else if(x1[i-1]<xmin && x1[i]>xmin){
                    x0[ind].push_back(xmin);
                    y = y1[i] + (xmin - x1[i])*m;
                    y0[ind].push_back(y);

                    x0[ind].push_back(x1[i]);
                    y0[ind].push_back(y1[i]);
                }

                else if(x1[i-1]>=xmin && x1[i]<xmin){
                    x0[ind].push_back(xmin);
                    y = y1[i] + (xmin - x1[i])*m;
                    y0[ind].push_back(y);
                }
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

    for(int j=0; j<num_polygon; j++)
    {
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<x0[j].size();i++){
            glVertex2i(x0[j][i],y0[j][i]);
        }
        glEnd();
    }
    glFlush();
}

int main(int argc,char** argv)
{
    float x,y;
    int n;

    for(int i=0; i<num_polygon; i++)
    {
        x0[i].clear();
        y0[i].clear();
    }

    printf("Enter 'c' after giving inputs of the co-ordinates to clip\n");
    printf("\nAll the co-ordinates must be within -300 and 300\n");
    printf("\nEnter clipping window co-ordinates in order (xmin,ymin) and (xmax,ymax):\n");
    cin>>xmin>>ymin>>xmax>>ymax;


    printf("Enter number of polygon:\n");
    cin >> num_polygon;

    for(int i=0; i<num_polygon; i++){

        printf("Enter the number of vertex of polygon %d:\n",i+1);
        cin >> n;
        printf("Enter the vertices:\n");
        for(int j=0; j<n; j++){
            cin>>x>>y;
            x0[i].push_back(x);
            y0[i].push_back(y);
        }
    }

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
-100 -100 100 100
2
3
50 -150
150 100
125 150
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

*/
