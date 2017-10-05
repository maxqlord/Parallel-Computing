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

int main( int argc , char* argv[] ) {
    int rseed;
    rseed = time(NULL);
    printf("%d", rseed);
    srand(rseed);

    float threshold; //70% chance of tree
    char forest[height][width];

    for (int x = 0; x <= 100; x += 5) {

        int time = 0;
        int stepsSum = 0;
        float normalized = 0;
        float theoreticalProb = 0;
        float actualProb = 0;
        int treeCounter = 0;
        threshold = (float) x / 100.0f;

        for(int y = 0; y < 100; y++) {

            time = 0;
            treeCounter = 0;


            //forest setup
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    double rand_num = myrand();
                    if (rand_num < threshold) {
                        forest[i][j] = 't';
                        treeCounter += 1;
                    } else {
                        forest[i][j] = ' ';
                    }
                }
            }




            bool fireLit = true;


            while (fireLit == true) {

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
                        if(temp[i][0] == 't') {
                            forest[i][0] = 'f';
                            fireLit = true;
                        }

                    }

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

                //delay(50);
                //system("clear");
                //printArr(forest);


                time += 1;
                //printf("%d", time);
                //printf("%d\n", fireLit);



            }
            stepsSum += time;
            normalized += (float) time / (float) width;
            theoreticalProb += threshold * 100;
            actualProb += ((float) treeCounter / (float) (height * width));

        }
        printf("Threshold: %f\t", threshold);
        float steps = (float)stepsSum/100.0f;
        printf("Steps: %f\t", steps);
        normalized = normalized / 100.0f;
        printf("Normalized: %f\t", normalized);
        theoreticalProb = theoreticalProb / 100.0f;
        printf("Theoretical: %f%s\t", theoreticalProb, "%");
        actualProb = actualProb / 100.0f;
        printf("Actual: %f%s\n", actualProb, "%");

    }
    //
    return 0;
}
//
// end of file
//