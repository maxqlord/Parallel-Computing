//
// Torbert, 8 February 2016
//
#include <stdio.h>
#include <math.h>
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

typedef struct {
    int r;
    int g;
    int b;
    //
} color;

typedef struct {
    triple c;
    double r;
    color h;
    //
} circle;
//

//triple g = { 0.00 , 1.25 , -0.50 } ; // the light

double dotp( triple t , triple u )
{
    return t.x * u.x + t.y * u.y + t.z * u.z ;
}
//
void diff( triple* t , triple u , triple v ) // t = u - v
{
    t->x = u.x - v.x ;
    t->y = u.y - v.y ;
    t->z = u.z - v.z ;
}
//

void init(circle a[4])
{
    a[0].c.x =      0.50 ;
    a[0].c.y = -20000.00 ; // the floor
    a[0].c.z =      0.50 ;
    a[0].r   =  20000.25 ;
    a[0].h.r =    205    ; // color is Peru
    a[0].h.g =    133    ;
    a[0].h.b =     63    ;
    //
    a[1].c.x =      0.50 ;
    a[1].c.y =      0.50 ;
    a[1].c.z =      0.50 ;
    a[1].r   =      0.25 ;
    a[1].h.r =      0    ; // color is Blue
    a[1].h.g =      0    ;
    a[1].h.b =    255    ;
    //
    a[2].c.x =      1.00 ;
    a[2].c.y =      0.50 ;
    a[2].c.z =      1.00 ;
    a[2].r   =      0.25 ;
    a[2].h.r =      0    ; // color is Green
    a[2].h.g =    255    ;
    a[2].h.b =      0    ;
    //
    a[3].c.x =      0.00 ;
    a[3].c.y =      0.75 ;
    a[3].c.z =      1.25 ;
    a[3].r   =      0.50 ;
    a[3].h.r =    255    ; // color is Red
    a[3].h.g =      0    ;
    a[3].h.b =      0    ;
}

int main(void) {

    int rgb[N][M][3]; // red-green-blue for each pixel
    circle array[4];
    triple e = { 0.50 , 0.50 , -1.00 } ; // the eye
    //
    init(array);
    int y, x;
    //
    FILE *fout;
    //
    for (y = 0; y < N; y++) {
        for (x = 0; x < M; x++) {

            //int discriminant = b * b - 4 * a * c
            //rgb[y][x][0] = 0; // red
            //rgb[y][x][1] = 255; // green
            //rgb[y][x][2] = 0; // blue

            double px = 1.333*x/M;
            double py = 1-(1.0*y/N);
            double pz = 0.0;

            double rx = px - e.x;
            double ry = py - e.y;
            double rz = pz - e.z;

            double magnitude = sqrt(rx*rx + ry*ry + rz*rz);

            rx /= magnitude;
            ry /= magnitude;
            rz /= magnitude;


            int sphere = -1;
            double tmin;
            for(int s = 0; s < 4; s++)
            {
                double a, b, c;
                a = 1.0;
                b = 2*(rx*(e.x - array[s].c.x) + ry*(e.y - array[s].c.y) + rz*(e.z - array[s].c.z));
                c = pow((e.x - array[s].c.x), 2) + pow((e.y - array[s].c.y), 2) + pow((e.z - array[s].c.z), 2) -(array[s].r * array[s].r);
                double t;
                if(pow(b, 2) - 4*a*c > 0)
                {
                    double t1 = (-b - sqrt(b*b - 4*a*c))/(2 * a);
                    double t2 = (-b + sqrt(b*b - 4*a*c))/(2 * a);
                    if(t1 > 0 && t2 > 0) {
                        t = fmin(t1, t2);
                    } else if(t2 > 0) {
                        t = t2;
                    }
                    else if(t1 > 0) {
                        t = t1;
                    } else {
                        t = fmax(t1, t2);
                    }


                    if((sphere < 0 || t < tmin)  && t > 0)
                    {
                        sphere = s;
                        tmin = t;
                    }
                }
            }
            if(sphere == -1)
            {
                rgb[y][x][0] = 0;
                rgb[y][x][1] = 0;
                rgb[y][x][2] = 0;
            }
            else
            {
                rgb[y][x][0] = array[sphere].h.r;
                rgb[y][x][1] = array[sphere].h.g;
                rgb[y][x][2] = array[sphere].h.b;
            }


        }

    }

    //
    //
    //
    //fout = fopen("allgreen.ppm", "w");
    fout = fopen("circles.ppm", "w");
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