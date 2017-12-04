#include <stdio.h>
#include <math.h>
#include <stdbool.h>

const double dt = 1.0;
double moon_r = 384402000;
double r = 384402000; //earth to moon
const double duration = 302400;//90*60 //90 minutes: 60 seconds per minute
double moonOrbit = 2332800;
const int n = (int)(duration / dt);
double x[n];
double y[n];
double vx[n];
double vy[n];
double v[n];
double rm[n]; //apollo to center of moon

double distance_formula(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}
int * moon_location(int time, int* xy) {
    xy[0] = -1*(int)(moon_r*sin(360*((double)time/moonOrbit) * (3.14159265/180.0)));
    xy[1] = (int)(moon_r*cos(360*((double)time/moonOrbit)* (3.14159265/180.0)));
    return xy;
}

int main() {


    double g = 6.67408 * pow(10,-11);
    int altitude = 400000; //meters
    double velocity = 1527.048; //meters/second //7800 for circular   //12000 for hyperbola
    double R = 6371000; //meters
    double M = 5.97219 * pow(10,24); //kg earth
    double m = 7.34767309 * pow(10,22); //kg moon



    double angle = 115.0;
    x[0] = 202751774*cos(angle * (3.14159265/180.0));
    y[0] = 202751774*sin(angle * (3.14159265/180.0));

    vx[0] = velocity * cos(angle * (3.14159265/180.0));
    vy[0] = velocity * sin(angle * (3.14159265/180.0));
    //printf("%f\t%f\n", vx[0], vy[0]);
    v[0] = velocity;
    rm[0] = r;
    bool past = false;


    for(int i = 1; i <= n; i++) { //for each time step
        x[i] = (x[i-1] + (vx[i-1]*dt));
        y[i] = (y[i-1] + (vy[i-1]*dt));
        R = sqrt(x[i]*x[i] + y[i]*y[i]);
        int xy[2];
        int mx = moon_location(i, xy)[0];
        int my = moon_location(i, xy)[1];
        r = distance_formula((int)x[i], (int)y[i], mx, my);
        rm[i] = r;
        if(past == false && distance_formula((int)x[i], (int)y[i], 0, 0) > 384402000) {
            //printf("Past moon orbit\n");
            //double dist = distance_formula((int)x[i], (int)y[i], 0, 0);
            //printf("%d\t%d\t%d\t%d\t%d\t%f\n", i, (int)x[i], (int)y[i], mx, my, dist);
            past = true;

        }
        double a = ((-g * M)/ (R*R)) + ((-g * m)/(r*r));
        double ax = a * (x[i]/R);
        double ay = a * (y[i]/R);
        vx[i] = vx[i-1] + ax*dt;
        vy[i] = vy[i-1] + ay*dt;
        v[i] = sqrt(vx[i]*vx[i] + vy[i]*vy[i]);
    }

    //printf("X\tY\n");
    for(int j = 1; j <= n; j++) {
        printf("%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f\n", 0, j, x[j], y[j], vx[j], vy[j], v[j], rm[j]);
        //tbd N X Y Vx Vy V R
    }


/*
    double xcor[360*2];
    double xmcor[360*2];
    double ycor[360*2];
    double ymcor[360*2];
    double R = 6371000.0;


    for(int i = 0; i <= 360; i++) {
        xcor[i] = R*sin(i * (3.14159265/180.0));
        xmcor[i] = r*sin(i * (3.14159265/180.0));
        ycor[i] = R*cos(i * (3.14159265/180.0));
        ymcor[i] = r*cos(i * (3.14159265/180.0));
    }
    for(int j = 0; j <= 360; j++) {
        printf("%f\t%f\t%f\t%f\n", xcor[j],ycor[j],xmcor[j], ymcor[j]);
    }

    */

    return 0;

}