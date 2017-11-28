
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 
#include "mpi.h"
//

int width = 160;
int height = 120;
double prob = 0;

double myrand()
{
    return ( rand() % 100 ) / 100.0 ;
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
    int        k , j, x  ;
    double     nbt ;
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
        int array[size];
        for(int z = 0; z < size; z++) {
            array[z] = 0;
        }
        while (prob <= 1.04) {
            for (j = 1; j < size; j++) //for each worker
            {
                if(prob <= 1.04) {
                    MPI_Send(&prob, 1, MPI_DOUBLE, j, tag, MPI_COMM_WORLD);
                    array[j] = 1;
                    printf("%f\n", prob);
                    prob += .05;
                }

            }
            //printf("exited2\n");



            //
            for (k = 1; k < size; k++) {
                if(array[k] == 1) {
                    MPI_Recv(&nbt, 1, MPI_DOUBLE, k, tag, MPI_COMM_WORLD, &status); //reads returned val into nbt
                    //
                    //printf("exitedreceive\n");
                    j = status.MPI_SOURCE; //returns 1-something
                    //
                    printf("%d %d %20.16f\n", j, size, nbt);
                }

            }
            for (x = 1; x < size; x++) {
                array[x] = 0;
            }
            //
            //printf("exited3\n");

            //printf("\n");
        }
        prob = 2.0;
        for(int y = 1; y < size; y++) {
            MPI_Send(&prob, 1, MPI_DOUBLE, y, tag, MPI_COMM_WORLD);

        }

    }
        //
        // workers have rank > 0
        //
    else
    {
        //run until it receives certain value
        int t;

        MPI_Recv( &prob , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
        double response = 0;
        double average = 0;
        while(prob != 2.0) {
            for (t = 0; t < 10; t++) {
                //printf("%f\n", prob);
                //
                //printf("exitedforest\n");
                int time;
                int treeCounter;
                char forest[height][width];


                time = 0;
                treeCounter = 0;


                //forest setup
                for (int c = 0; c < height; c++) {
                    for (int d = 0; d < width; d++) {
                        double rand_num = myrand();
                        if (rand_num < prob) {
                            forest[c][d] = 't';
                            treeCounter += 1;
                        } else {
                            forest[c][d] = ' ';
                        }
                    }
                }


                bool fireLit = true;


                while (fireLit == true) {

                    fireLit = false;
                    //printf("%d ", fireLit);

                    //create temp array
                    char temp[height][width];
                    for (int x = 0; x < height; x++) {
                        for (int y = 0; y < width; y++) {
                            temp[x][y] = forest[x][y];
                        }
                    }
                    //light fire
                    if (time == 0) {

                        for (int z = 0; z < height; z++) {
                            if (temp[z][0] == 't') {
                                forest[z][0] = 'f';
                                fireLit = true;
                            }

                        }

                    }

                    //printf("%d ", fireLit);

                    // from [i][j] do [i+1][j], [i-1][j], [i][j+1], i[j-1]
                    //move up down right left
                    for (int a = 0; a < width; a++) {
                        for (int b = 0; b < height; b++) {
                            if (temp[b][a] == 'f') {
                                //set fire to sides

                                //down
                                if (b + 1 < height && temp[b + 1][a] == 't') {
                                    forest[b + 1][a] = 'f';
                                    fireLit = true;
                                }

                                //up
                                if (b - 1 >= 0 && temp[b - 1][a] == 't') {
                                    forest[b - 1][a] = 'f';
                                    fireLit = true;
                                }

                                //right
                                if (a + 1 < width && temp[b][a + 1] == 't') {
                                    forest[b][a + 1] = 'f';
                                    fireLit = true;
                                }

                                //left
                                if (a - 1 >= 0 && temp[b][a - 1] == 't') {
                                    forest[b][a - 1] = 'f';
                                    fireLit = true;
                                }
                            }
                        }
                    }

                    //delay(50);
                    //system("clear");
                    //printArr(forest);


                    time += 1;
                    //printf("%d", time);
                    //printf("%d\n", fireLit);



                }

                response += (double) time / (double) width;
            }

            average = response/(double)t;
            MPI_Send(&average, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
            MPI_Recv( &prob , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
            response = 0;
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