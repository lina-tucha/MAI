#include <math.h>

float SinIntegral( float A, float B, float e){
        double integral = 0;
        for(float i = A + e; i < B; i+=e ){
                integral += (sin(i) + sin(i - e)) / 2 * e;
        }
        return integral;
}
int factorial(double count){
    double num = 1;
    for (double i = 1; i <= count; i++)
        num = num * i;
    return num;
}

float E(double x) {
        double s = 1;
        for (int i = 1; i <= x; i++) {
        double k = factorial(i);
                s += (1 / k);
        }
        return s;
}



