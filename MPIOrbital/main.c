#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mpi.h"
//    mpicc mpiDemo.c
//    time mpirun -np 4                                  a.out
//    time mpirun -np 4 --mca orte_base_help_aggregate 0 a.out
//    time mpirun -np 4 -mca btl ^openib                 a.out
//
//    time mpirun -np 6 -machinefile hosts.txt a.out



double angle = 20.0;

double distance_formula(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}
int * moon_location(int time, int* xy, double moon_r, double moonOrbit) {
    xy[0] = (int)(moon_r*cos(360*((double)time/moonOrbit) * (3.14159265/180.0)));
    xy[1] = (int)(moon_r*sin(360*((double)time/moonOrbit)* (3.14159265/180.0)));
    return xy;
}

int main( int argc , char* argv[] )
{
    //
    // MPI variables
    //
    int        rank    ;
    int        size    ;
    MPI_Status status  ;
    int        tag = 0 ;
    //
    // other variables
    //
    int        k , j, z  ;
    int     nbt ;
    //
    // boilerplate
    //
    MPI_Init(      &argc          , &argv ) ;
    MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
    MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different
    //
    // manager has rank = 0
    //

    if( rank == 0 ) {
        //printf("%d", size);
        //printf("\n");
        //
        // everyone gets the same probability
        //
        bool found = false;
        int array[size];
        for(int b = 0; b < size; b++) {
            array[b] = 0;
        }
        while (angle <= 50.0 && found == false) {
            for (j = 1; j < size; j++) //for each worker
            {
                if(angle <= 50.0) {
                    MPI_Send(&angle, 1, MPI_DOUBLE, j, tag, MPI_COMM_WORLD);
                    array[j] = 1;
                    //printf("%f\n", angle);
                    angle += .01;
                }

            }
            //printf("exited2\n");



            //get info
            for (k = 1; k < size; k++) {
                if(array[k] == 1) {
                    MPI_Recv(&nbt, 1, MPI_INT, k, tag, MPI_COMM_WORLD, &status); //reads returned val into nbt
                    //
                    //printf("exitedreceive\n");
                    j = status.MPI_SOURCE; //returns 1-something
                    //
                    if(nbt == 1) {
                        found = true;
                        printf("%d %d %d\n", j, size, nbt);
                    }



                }

            }
            //reset workers
            for (z = 1; z < size; z++) {
                array[z] = 0;
            }

        }
        //close workers
        angle = 100.0;
        for(int y = 1; y < size; y++) {
            MPI_Send(&angle, 1, MPI_DOUBLE, y, tag, MPI_COMM_WORLD);

        }


    }
        //
        // workers have rank > 0
        //
    else
    {
        MPI_Recv( &angle , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
        //run until it receives certain value



        while(angle != 100.0) {
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
            /*
            //printf("X\tY\n");
            for(int j = 1; j <= n; j++) {
                printf("%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f\n", 0, j, x[j], y[j], vx[j], vy[j], v[j], rm[j]);
                //tbd N X Y Vx Vy V R
            }*/

            //printf("X\tY\n");
            double temp = -1;
            int answer = 0;
            for(int a = 1; a <= n; a++) {
                if (x[a] < temp) {
                    answer = 1;
                    break;
                }
                temp = x[a];
            }
                /*
                if(angle == 33.0) {
                    printf("%f\n", x[a]);
                }
                 */
                //printf("%d\t%d\t%f\t%f\t%f\t%f\t%f\t%f\n", 0, a, x[a], y[a], vx[a], vy[a], v[a], rm[a]);
                //tbd N X Y Vx Vy V R


                //printf("%f\n", prob);
                //
                //printf("exitedforest\n");


            MPI_Send(&answer, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
            MPI_Recv( &angle , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
            answer = 0;
        }


    }
    //
    // boilerplate
    MPI_Finalize() ;
    //
    return 0;

}
// 
// end of file
// 