#include <windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include<iostream>
#include<vector>

void display();
using namespace std;

float xmin,ymin,xmax,ymax;
vector<float> xs,ys,xe,ye;

int w=300;
double dw=300.0;

int bit[3][4]={0};
int numLine=0;


void drawAxis(){
    glColor3f(1.0,1.0,0.0);
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

void region_code(float x,float y,int i)
{
    if(y>ymax)
    {
        bit[i][0]=1;
        //cout<<y<<endl<<ymax;
    }
    if(y<ymin){
        bit[i][1]=1;
        //cout<<y<<endl<<ymax;
    }
    if(x>xmax) bit[i][2]=1;
    if(x<xmin) bit[i][3]=1;

}

int AND(){

    bool result=0;
    for(int k=0;k<4;k++)
        if(bit[0][k] & bit[1][k] == 1) result=1;
    return result;
}

void LineClip(float xd1,float yd1,float xd2,float yd2,int i)
{
    region_code(xd1,yd1,0);
    region_code(xd2,yd2,1);

//    for(int i=0;i<2;i++)
//        for(int j=0;j<4;j++)
//            printf("%d\n",bit[i][j]);
//    printf("\n\n");

    printf("Line %d\n\n",i+1);

    printf("Region code of (%.0f,%.0f) is :%d%d%d%d\n",xs[i],ys[i],bit[0][0],bit[0][1],bit[0][2],bit[0][3]);
    printf("Region code of (%.0f,%.0f) is :%d%d%d%d\n\n",xe[i],ye[i],bit[1][0],bit[1][1],bit[1][2],bit[1][3]);

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
        //printf("ch - %d\n",ch);
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
            printf("Intersecting point with ymax is (%.0f,%.0f)\n",xd1,yd1);
        }
        if(bit[0][1]==1){

            bit[0][1]=0;
            yd1 = ymin;
            xd1 = x1+ 1.0/m*(yd1-y1);
            printf("Intersecting point with ymin is (%.0f,%.0f)\n",xd1,yd1);
        }
        if(bit[0][2]==1){
            bit[0][2]=0;
            xd1 = xmax;
            yd1 = y1+m*(xd1-x1);
            printf("Intersecting point with xmax is (%.0f,%.0f)\n",xd1,yd1);
        }
        if(bit[0][3]==1){
            bit[0][3]=0;
            xd1 = xmin;
            yd1 = y1+m*(xd1-x1);
            printf("Intersecting point with xmin is (%.0f,%.0f)\n",xd1,yd1);
        }

        // Second end point of line

        if(bit[1][0]==1){
            bit[1][0]=0;
            yd2 = ymax;
            xd2 = x2+ 1.0/m*(yd2-y2);
            printf("Intersecting point with ymax is (%.0f,%.0f)\n",xd1,yd1);
        }
        if(bit[1][1]==1){
            bit[1][1]=0;
            yd2 = ymin;
            xd2 = x2+ 1.0/m*(yd2-y2);
            printf("Intersecting point with ymin is (%.0f,%.0f)\n",xd1,yd1);
        }
        if(bit[1][2]==1){
            bit[1][2]=0;
            xd2 = xmax;
            yd2 = y2+m*(xd2-x2);
            printf("Intersecting point with xmax is (%.0f,%.0f)\n",xd1,yd1);
        }
        if(bit[1][3]==1){
            bit[1][3]=0;
            xd2 = xmin;
            yd2 = y2+m*(xd2-x2);
            printf("Intersecting point with xmin is (%.0f,%.0f)\n",xd1,yd1);
        }

        printf("\n");

        region_code(xd1,yd1,0);
        region_code(xd2,yd2,1);
    }

    xs[i] = xd1;
    ys[i] = yd1;
    xe[i] = xd2;
    ye[i] = yd2;

    bit[3][4]={0};
}

void mykey(unsigned char key,int x,int y)
{
    if(key=='c'){
        for(int i=0;i<numLine;i++) LineClip(xs[i],ys[i],xe[i],ye[i],i);
        display();
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
    glBegin(GL_LINES);
    for(int i=0;i<numLine;i++){
        glVertex2i(xs[i],ys[i]);
        glVertex2i(xe[i],ye[i]);
    }
    glEnd();

    glFlush();
}


int main(int argc,char** argv)
{
    printf("Enter 'c' after giving inputs of the co-ordinates to clip\n");
    printf("\nAll the co-ordinates must be within -300 and 300\n");

    printf("\nEnter the number of line to clip:\n");
    cin>>numLine;

    float x1,y1,x2,y2;
    xs.clear();
    ys.clear();
    xe.clear();
    ye.clear();

    printf("Enter serially the line co-ordinates as (x1,y1) and (x2,y2):\n");

    for(int i=0;i<numLine;i++){

        cin>>x1>>y1>>x2>>y2;
        xs.push_back(x1);
        ys.push_back(y1);
        xe.push_back(x2);
        ye.push_back(y2);
    }

    printf("\nEnter clipping window co-ordinates in order (xmin,ymin) and (xmax,ymax):\n");
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


3
-10 50 70 50
10 10 80 90
10 30 35 40
-10 -10
50 50


5
-200 -200 70 50
-100 -100 100 100
20 50 -30 10
-120 -130 140 150
150 150 150 0
-20 -20
70 70


5
-100 -100 100 100
70 -150 150 -50
-100 -100 100 100
-200 150 150 -120
-100 -100 100 100
-100 -100
100 100


5
-200 150 150 -120
-200 -200 70 50
20 50 -30 10
150 150 150 0
70 -150 150 -50
-100 -100
100 100

*/
