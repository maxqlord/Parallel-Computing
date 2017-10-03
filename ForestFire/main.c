// Max Lord
// Period 1
// 9/29/17
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int width = 40;
int height = 30;


void printArr(char arr[height][width])
{
    for(int i = 0; i < height; i++)  {
        for(int j = 0; j < width; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }

    /*printf("\n");
    printf("\n");
    printf("\n");*/
}

double myrand()
{
    return ( rand() % 100 ) / 100.0 ;
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}

// Driver code to test above function

int main( int argc , char* argv[] )
{
    int rseed;
    rseed = time( NULL ) ;
    srand( rseed ) ;

    float threshold = .6; //70% chance of tree
    char forest[height][width];
    int treeCounter = 0;

    //forest setup
    for(int i = 0; i < height; i++)  {
        for(int j = 0; j < width; j++) {
            double rand_num = myrand();
            if(rand_num < threshold) {
                forest[i][j] = 't';
                treeCounter+=1;
            } else{
                forest[i][j] = ' ';
            }
        }
    }


            int time = 0;
            bool fireLit = true;


            while (fireLit == true) { //something is very wrong

                int steps;
                float normalized;
                float theoreticalProb;
                float actualProb;

                fireLit = false;
                //printf("%d ", fireLit);

                //create temp array
                char temp[height][width];
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        temp[i][j] = forest[i][j];
                    }
                }
                //light fire
                if (time == 0) {

                    for (int i = 0; i < height; i++) {
                        forest[i][0] = 'f';
                    }
                    fireLit = true;
                }

                //printf("%d ", fireLit);

                // from [i][j] do [i+1][j], [i-1][j], [i][j+1], i[j-1]
                //move up down right left
                for (int j = 0; j < width; j++) {
                    for (int i = 0; i < height; i++) {
                        if (temp[i][j] == 'f') {
                            //set fire to sides

                            //down
                            if (i + 1 < height && temp[i + 1][j] == 't') {
                                forest[i + 1][j] = 'f';
                                fireLit = true;
                            }

                            //up
                            if (i - 1 >= 0 && temp[i - 1][j] == 't') {
                                forest[i - 1][j] = 'f';
                                fireLit = true;
                            }

                            //right
                            if (j + 1 < width && temp[i][j + 1] == 't') {
                                forest[i][j + 1] = 'f';
                                fireLit = true;
                            }

                            //left
                            if (j - 1 >= 0 && temp[i][j - 1] == 't') {
                                forest[i][j - 1] = 'f';
                                fireLit = true;
                            }
                        }
                    }
                }

                delay(50);
                system("clear");
                printArr(forest);


                time += 1;
                //printf("%d", time);
                //printf("%d\n", fireLit);


                steps = time;
                normalized = (float)steps/(float)width;
                theoreticalProb = threshold*100;
                actualProb = 100*((float)treeCounter/(float)(height*width));

                printf("Steps: %d\t", steps);
                printf("Normalized: %f\t", normalized);
                printf("Theoretical: %f%s\t", theoreticalProb, "%");
                printf("Actual: %f%s\n", actualProb, "%");
            }


    //
    return 0;
}
//
// end of file
//