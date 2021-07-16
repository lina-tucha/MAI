#include <math.h>

float SinIntegral(float A, float B, float e){
        double integral = 0;
        for(float i = A; i < B; i+=e ){
                integral += sin(i) * e;
        }
        return integral;
}

float E(double x) {
        double k = 1 / x;
        double e = pow((1 + k), x);
        return e;
}


