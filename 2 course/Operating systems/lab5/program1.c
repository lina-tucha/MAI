#include <stdio.h>
#include <stdlib.h>

float SinIntegral(float A, float B, float e);
float E(double);

int main(){
        int com;
        while(scanf("%d", &com) > 0) {
                if ( com == 1 ) {
                        printf("Enter line segment and step: ");
                        float A,B,e;
                        if (scanf("%f%f%f", &A, &B, &e) != 3) {
                                printf("Data entry error!\n");
                        }
                        printf("Result: %f\n", SinIntegral( A, B, e));
                } else if (com == 2) {
                        printf("Enter number: ");
                        double h;
                        if (scanf("%lf", &h) != 1) {
                                printf("Data entry error!\n");
                        }
                        printf("Result: %f\n", E(h));
                }else{
                        printf("Wrong format\n");
                }
        }
}
