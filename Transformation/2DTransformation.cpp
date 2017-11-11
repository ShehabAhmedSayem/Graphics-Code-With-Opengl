#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;

#define pi 2.0*acos(0)
int w=300;
double dw=300.0;

int tx,ty,rfx,rfy,b;
int choice=0,roch=0,rfch=0,sch=0;
double sx,sy,shx,shy,m,ang;

vector <int>xc,xcc;
vector <int>yc,ycc;


void init(void){
    glClearColor(0.1,0.1,0.1,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-dw,dw,-dw,dw);
}

int draw_line(int xs,int ys,int xe,int ye){

    glBegin(GL_LINES);

    glVertex2f(xs,ys);
    glVertex2f(xe,ye);

    glEnd();

    return 0;
}


int setPixel(int x,int y){

    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    return 0;
}


int translate(int x, int y){

    int i;

    for(i=0;i<xc.size();i++){
        xc[i] = xc[i]+x;
        yc[i] = yc[i]+y;
    }

    return 0;
}


int rotation(double angle){

    int i,temp;

    for(i=0;i<xc.size();i++){
        double angle_rad = pi / 180.0;

        temp = (double)xc[i]*cos(angle_rad * angle) - (double)yc[i]*sin(angle_rad * angle);
        yc[i] = (double)xc[i]*sin(angle_rad * angle) + (double)yc[i]*cos(angle_rad * angle);
        xc[i] = temp;
    }
    return 0;
}


int scale(double x,double y){

    int i;

    for(i=0;i<xc.size();i++){
        xc[i] = (double)xc[i]*x;
        yc[i] = (double)yc[i]*y;
    }
    return 0;
}

int reflection_x(){
    int i;

    for(i=0;i<xc.size();i++){
        xc[i] = xc[i];
        yc[i] = -yc[i];
    }
    return 0;
}

int reflection_y(){
    int i;

    for(i=0;i<xc.size();i++){
        xc[i] = -xc[i];
        yc[i] = yc[i];
    }
    return 0;
}

int shear(double x,double y){

    int i;

    for(i=0;i<xc.size();i++){
        int temp = xc[i]+(double)yc[i]*x;
        yc[i] = yc[i]+(double)xc[i]*y;
        xc[i] = temp;
    }
    return 0;
}

int scale_wrt_p(double x,double y,int px,int py){

    int i;

    translate(-px,-py);
    scale(x,y);
    translate(px,py);
    return 0;
}

int rotation_wrt_p(double angle,int px,int py){

    translate(-px,-py);
    rotation(angle);
    translate(px,py);
    return 0;
}

int reflection_wrt_l(double m,int b){

    int i;
    double y;
    double angle = (atan(m)*180.0);
    angle/=pi;

    translate(0,-b);

    rotation(-angle);

    reflection_x();

    rotation(angle);

    translate(0,b);

    for(i=-200;i<=200;i++){
        y=m*(double)i+b;
        setPixel(i,(int)y);
    }

    return 0;
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

    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxis();

    glColor3f(1.0,1.0,1.0);

    for(i=1;i<xc.size();i++) draw_line(xc[i-1],yc[i-1],xc[i],yc[i]);
    draw_line(xc[0],yc[0],xc[xc.size()-1],yc[xc.size()-1]);


    if(choice==1){
        glColor3f(1.0,0.0,0.0);
        translate(tx,ty);

    }

    else if(roch==1){

        glColor3f(1.0,0.0,0.0);
        rotation(ang);

    }

    else if(sch==1){
        glColor3f(0.0,0.0,1.0);
        scale(sx,sy);

    }

    else if(rfch==1){
        glColor3f(0.0,0.0,1.0);
        reflection_x();

    }

    else if(rfch==2){
        glColor3f(0.0,0.0,1.0);
        reflection_y();

    }

    else if(roch==2){
        glColor3f(0.0,1.0,0.0);
        rotation_wrt_p(ang,rfx,rfy);

    }

    else if(sch==2){
        glColor3f(0.0,0.0,1.0);
        scale_wrt_p(sx,sy,rfx,rfy);

    }

    else if(rfch==3){

        reflection_wrt_l(m,b);
        glColor3f(0.0,1.0,1.0);

    }

    else if(choice==5){
        glColor3f(0.0,0.0,1.0);
        shear(shx,shy);

    }

    for(i=1;i<xc.size();i++) draw_line(xc[i-1],yc[i-1],xc[i],yc[i]);
    draw_line(xc[0],yc[0],xc[xc.size()-1],yc[xc.size()-1]);


    glutSwapBuffers();
}


int main(int argc, char *argv[]){

    int i,x,y,n;

    printf("Enter the number of vertex:\n");
    scanf("%d",&n);

    xc.clear();
    yc.clear();

    printf("Enter the vertices:\n");

    for(i=0;i<n;i++){
        scanf("%d%d",&x,&y);

        xc.push_back(x);
        xcc.push_back(x);
        yc.push_back(y);
        ycc.push_back(y);
    }

    while(true){

        printf("Enter your choice:\n");
        printf("1.Translation\n2.Rotation\n3.Scaling\n4.Reflection\n5.Shearing\n");

        scanf("%d",&choice);
        if(choice==2){
            printf("1.Wrt origin\n2.Wrt a fixed point\n");
            scanf("%d",&roch);
        }

        if(choice==3){
            printf("1.Wrt origin\n2.Wrt a fixed point\n");
            scanf("%d",&sch);
        }

        if(choice==4){
            printf("1.Wrt x-axis\n2.Wrt y-axis\n3.Wrt a line\n");
            scanf("%d",&rfch);
        }

        if(choice==1){
            printf("Enter (x,y) value for translation:\n");
            scanf("%d%d",&tx,&ty);
            break;
        }

        else if(roch==1){
            printf("Enter angle value for rotation:\n");
            scanf("%lf",&ang);
            break;
        }

        else if(sch==1){
            printf("Enter (sx,sy) value for scaling:\n");
            scanf("%lf%lf",&sx,&sy);
            break;
        }

        else if(rfch==1){
            break;
        }

        else if(rfch==2){
           break;
        }

        else if(roch==2){
            printf("Enter angle value for rotation:\n");
            scanf("%lf",&ang);
            printf("Enter reference point:\n");
            scanf("%d%d",&rfx,&rfy);
            break;
        }

        else if(sch==2){
            printf("Enter (sx,sy) value for scaling:\n");
            scanf("%lf%lf",&sx,&sy);
            printf("Enter reference point:\n");
            scanf("%d%d",&rfx,&rfy);
            break;
        }

        else if(rfch==3){
            printf("Enter slope and y-intercept for reference line:\n");
            scanf("%lf%d",&m,&b);
            break;
        }

        else if(choice==5){
            printf("Enter (shx,shy) value for shearing:\n");
            scanf("%lf%lf",&shx,&shy);
            break;
        }

        else printf("Enter a right choice!\n");
    }

    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(400,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("TRANSFORMATION");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;

}


/*

4
-10 10
30 10
30 -20
-10 -20

4
-20 0
0 -40
20 0
0 40

4
-5 0
0 -10
5 0
0 10
8

3
10 10
150 100
125 150

4
0 0
1 0
1 1
0 1

*/
