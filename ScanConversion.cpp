#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;

#define pi 2.0*acos(0)
int w=300;
double dw=300.0;

int choice=0,lchoice=0,cchoice=0;
int x0,y0,x1,y1;
int xc,yc,r;

void init(void){
    glClearColor(0.1,0.1,0.1,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-dw,dw,-dw,dw);
}

int setPixel(int x,int y){

    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    return 0;
}

void setPixelCircle(GLint x,GLint y){
    glBegin(GL_POINTS);
    glVertex2i(xc+x,yc+y);
    glVertex2i(xc-x,yc-y);
    glVertex2i(xc+y,yc+x);
    glVertex2i(xc-y,yc-x);
    glVertex2i(xc-x,yc+y);
    glVertex2i(xc+x,yc-y);
    glVertex2i(xc+y,yc-x);
    glVertex2i(xc-y,yc+x);
    glEnd();
}

void swap(int a,int b){
    int temp=a;
    a=b;
    b=temp;
}


void drawHorizontal(){
    int x=x0;
    int y=y0;

    while(x<=x1){
        setPixel(x,y);
        x++;
    }
}

void drawVertical(){
    int x=x0;
    int y=y0;

    while(y<=y1){
        setPixel(x,y);
        y++;
    }
}

void directLine(){
    int dx = x1-x0;
    int dy = y1-y0;

    double x=x0, y=y0;
    double m=(double)dy/(double)dx;
    double b=y0-m*x0;

    //printf("m = %lf b = %lf",&m,&b);

    if(abs(dx)>=abs(dy)){
        while(x<=x1){
            setPixel((int)x,(int)y);
            x++;
            y = m*x + b;
        }
    }
    else{
        int k = y0<y1 ? 1 : -1;
        while(y<=y1){
            setPixel((int)x,(int)y);
            y+=k;
            x = (y-b)/m;
        }
    }
}


void DDA(){
    int dx = x1-x0;
    int dy = y1-y0;

    if(abs(dy)<=abs(dx)){
        if(x0>x1){
            swap(x0,x1);
            swap(y0,y1);
        }
        double x=x0,y=y0;
        double m = (double)dy/(double)dx;

        while(x<=x1){
            setPixel((int)x,(int)y);
            x++;
            y=m+y;
        }
    }
    else{
        if(y0>y1){
            swap(x0,x1);
            swap(y0,y1);
        }
        double x=x0,y=y0;
        double m = (double)dx/(double)dy; //Here m = (1/m)

        while(y<=y1){
            setPixel((int)x,(int)y);
            y++;
            x=m+x;
        }
    }
}


void BresenhamLine() {
    int dx=x1-x0;
    int dy=y1-y0;

        int x = x0;
        int y = y0;
        int p = 2*dy-dx;
        int ps = 2*dy;
        int pt = 2*dy-2*dx;

        while(x<=x1){
            setPixel(x,y);
            if(p<0){
                x++;
                p=p+ps;
            }
            else{
                x++;
                y++;
                p=p+pt;
            }
        }
}


void Circle(){

    int x=0,y=r,r2=r*r;
    int xe = (double)r/sqrt(2.0);

    while(x<=xe){
        setPixelCircle(x,y);
        x++;
        y = sqrt(r2-x*x);
    }
}


void trigonometricCircle(){

    int theta=0;
    int theta_end = 45;
    int x,y;
    double s = pi/180.0;

    while(theta<=theta_end){

        x = r*cos(theta*s);
        y = r*sin(theta*s);
        setPixelCircle(x,y);
        theta++;
    }
}


void BresenhamCircle(){

    int x=0,y=r;
    int d=3-2*r;
    int t=xc+r;

    while(x<=y){
        setPixelCircle(x,y);
        if(d<0){
            d=d+4*x+6;
            x++;
        }
        else{
            d=d+4*(x-y)+10;
            x++;
            y--;
        }
    }
}


void midPointCircle()
{

    int x=0,y=r;
    int d=1-r;

    setPixelCircle(x,y);

    while(x<=y){

        if(d<0){
            d=d+2*x+3;
        }
        else{
            d=d+2*(x-y)+5;
            y--;
        }
        setPixelCircle(x,y);
        x++;
    }

}



void drawAxis(){
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(0, w);
    glVertex2i(0, -w);
    glVertex2i(w, 0);
    glVertex2i(-w, 0);
    glEnd();
}


void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawAxis();

    glColor3f(1.0,1.0,1.0);

    if(lchoice==1){

        if(x0>x1){
            swap(x0,x1);
            swap(y0,y1);
        }

        if(y0==y1) drawHorizontal();
        else if(x0==x1) drawVertical();
        else directLine();
        glFlush();
    }

    else if(lchoice==2){

        if(y0 == y1) drawHorizontal();
        else if(x0 == x1) drawVertical();
        else DDA();
        glFlush();
    }

    else if(lchoice==3){

        if(y0 == y1) drawHorizontal();
        else if(x0 == x1) drawVertical();
        else BresenhamLine();
        glFlush();
    }

    else if(cchoice==1){
        Circle();
        setPixel(xc,yc);
        glFlush();
    }

    else if(cchoice==2){
        trigonometricCircle();
        setPixel(xc,yc);
        glFlush();
    }

    else if(cchoice==3){

        BresenhamCircle();
        setPixel(xc,yc);
        glFlush();
    }

    else if(cchoice==4){
        midPointCircle();
        setPixel(xc,yc);
        glFlush();
    }

    glutSwapBuffers();

}



int main(int argc, char *argv[]){

    printf("What do you want to draw:\n");
    printf("1.Line\n2.Circle\n");
    scanf("%d",&choice);

    if(choice==1){

        printf("Enter your choice:\n");
        printf("1.Direct\n");
        printf("2.DDA\n");
        printf("3.Bresenham\n");
        scanf("%d",&lchoice);

        printf("Enter(x0,y0) and (x1,y1):\n");
        scanf("%d%d%d%d",&x0,&y0,&x1,&y1);

        if(lchoice==3){
            if(x0 > x1) {
                swap(x0, x1);
                swap(y0, y1);
            }

            int dx=x1-x0;
            int dy=y1-y0;

            if(abs(dy)>=abs(dx) || y0>y1){
                printf("\n(y1-y0) / (x1-x0) must be smaller than 1 and greater than 0 to apply Bresenham's algorithm.\n");
                printf("Enter(x0,y0) and (x1,y1):\n");
                scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
            }
        }
    }

    else if(choice==2){
        printf("Enter your choice:\n");
        printf("1.Second Degree Polynomial\n");
        printf("2.Trigonometry\n");
        printf("3.Bresenham\n");
        printf("4.Midpoint\n");
        scanf("%d",&cchoice);

        printf("Enter the center point(x,y) and radius:\n");
        scanf("%d%d%d",&xc,&yc,&r);

        while(r<0){
            printf("You can't draw a circle with negative radius.\nEnter radius again:\n");
            scanf("%d",&r);
        }
    }

    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(400,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("SCAN CONVERSION");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;

}

