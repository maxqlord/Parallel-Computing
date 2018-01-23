#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>


double distance_formula(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}
int * moon_location(int time, int* xy, double moon_r, double moonOrbit) {
    xy[0] = (int)(moon_r*cos(360*((double)time/moonOrbit) * (3.14159265/180.0)));
    xy[1] = (int)(moon_r*sin(360*((double)time/moonOrbit)* (3.14159265/180.0)));
    return xy;
}

int main() {

    double dt = 1.0;
    double moon_r = 384402000;  //	16457848
    double r = 384402000; //earth to moon
    double duration = 804000;//302400;//90*60 //90 minutes: 60 seconds per minute   604800- week
    double moonOrbit = 2358720;
    int n = (int)(duration / dt);


    double *x = malloc(sizeof(double) * 1000000);
    double *y = malloc(sizeof(double) * 1000000);
    double *vx = malloc(sizeof(double) * 1000000);
    double *vy = malloc(sizeof(double) * 1000000);
    double *v = malloc(sizeof(double) * 1000000);
    double *rm = malloc(sizeof(double) * 1000000);
    double g = 6.67408 * pow(10,-11);
    int altitude = 400000; //meters
    double velocity = 1527.048; //meters/second //7800 for circular   //12000 for hyperbola  //1527.048 for free return
    double R = 6371000; //meters
    double M = 5.97219 * pow(10,24); //kg earth
    double m = 7.34767309 * pow(10,22); //kg moon



    double angle = 33.0;//123.95;  //35 does earth free return
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
        int mx = moon_location(i, xy, moon_r, moonOrbit)[0];
        int my = moon_location(i, xy, moon_r, moonOrbit)[1];
        r = distance_formula((int)x[i], (int)y[i], mx, my);
        rm[i] = r;
        if(past == false && distance_formula((int)x[i], (int)y[i], 0, 0) > 384402000) {
            //printf("Past moon orbit\n");
            //double dist = distance_formula((int)x[i], (int)y[i], 0, 0);
            //printf("%d\t%d\t%d\t%d\t%d\t%f\n", i, (int)x[i], (int)y[i], mx, my, dist);
            past = true;

        }
        double aearth = (-g * M)/ (R*R);
        double amoon = (-g * m)/(r*r);
        //printf("%f\t%f\n", aearth, amoon);
        double axearth = aearth * (x[i]/R);
        double ayearth = aearth * (y[i]/R);
        double axmoon = amoon * ((x[i]-mx)/r);
        double aymoon = amoon * ((y[i]-my)/r);

        vx[i] = vx[i-1] + axmoon*dt;
        vx[i] = vx[i] + axearth*dt;
        vy[i] = vy[i-1] + aymoon*dt;
        vy[i] = vy[i] + ayearth*dt;
        v[i] = sqrt(vx[i]*vx[i] + vy[i]*vy[i]);
    }

    //printf("X\tY\n");

    for(int j = 1; j <= n; j++) {
        printf("%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f\n", 0, j, x[j], y[j], vx[j], vy[j], v[j], rm[j]);

            //printf("%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f\n", 0, a, x[a], y[a], vx[a], vy[a], v[a], rm[a]);
            //tbd N X Y Vx Vy V R

        //tbd N X Y Vx Vy V R
    }



    return 0;

}