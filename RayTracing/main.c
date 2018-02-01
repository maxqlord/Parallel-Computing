//
// Torbert, 8 February 2016
//
#include <stdio.h>
//
#define M 640
#define N 480
//
typedef struct {
    double x;
    double y;
    double z;
    //
} triple;
//

//triple g = { 0.00 , 1.25 , -0.50 } ; // the light
int main(void) {

    int rgb[N][M][3]; // red-green-blue for each pixel
    triple e = { 0.50 , 0.50 , -1.00 } ; // the eye
    //
    int y, x;
    //
    FILE *fout;
    //
    for (y = 0; y < N; y++) {
        for (x = 0; x < M; x++) {

            int discriminant = b * b - 4 * a * c
            rgb[y][x][0] = 0; // red
            rgb[y][x][1] = 255; // green
            rgb[y][x][2] = 0; // blue
        }
    }
    //
    //
    //
    fout = fopen("allgreen.ppm", "w");
    //
    fprintf(fout, "P3\n");
    fprintf(fout, "%d %d\n", M, N);
    fprintf(fout, "255\n");
    //
    for (y = 0; y < N; y++)  //set everything to green
    {
        for (x = 0; x < M; x++)  //writing to file
        {
            fprintf(fout, "%d %d %d\n",
                    rgb[y][x][0], rgb[y][x][1], rgb[y][x][2]);
        }
    }
    fclose(fout);
    //
    return 0;
}

//a = 1.0
//b = 2dxrx + 2dyry + 2dzrz
//c = dx^2 + dy^2 + dz^2 - R^2


//
// end of file
//