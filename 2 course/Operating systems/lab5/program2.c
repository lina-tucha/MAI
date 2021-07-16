#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(){
        int num = 1;
        void* lib = dlopen("./lib1.so", RTLD_LAZY);
        if (lib == NULL) {
                printf("Failed to load dynamic link library!\n");
                return 1;
        }
        float (*SinIntegral) ( float, float, float );
        float (*E) (double);
        *(void**) (&SinIntegral) = dlsym(lib, "SinIntegral");
        *(void**) (&E) = dlsym(lib, "E");
        char* error = dlerror();
        if (error != NULL) {
                printf("%s", error);
        }
        int com;
        while(scanf("%d", &com) > 0) {
                if (com == 1) {
                        float A, B, e;
                        printf("Enter line segment and step: ");
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
                } else if (com == 0) {
                        if (dlclose(lib) != 0) {
                                printf("Failed to upload dynamic library!\n");
                        }
                        if (num == 1) {
                                lib = dlopen("./lib2.so", RTLD_LAZY);
                                num = 2;
                        } else {
                                lib = dlopen("./lib1.so", RTLD_LAZY);
                                num = 1;
                        }
                        if (lib == NULL) {
                                printf("Failed to load dynamic library!\n");
                                return 1;
                        }
                        *(void**) (&SinIntegral) = dlsym(lib, "SinIntegral");
                        *(void**) (&E) = dlsym(lib, "E");
                        char* error = dlerror();
                        if (error != NULL) {
                                printf("%s", error);
                        }
                } else {
                        printf("Wrong format\n");
                }
        }
}

