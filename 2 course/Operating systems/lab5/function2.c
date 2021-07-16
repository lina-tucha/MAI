#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> // Для динамической загрузки библиотек

#include "lib.h"

int main() {
    printf("0 - change library\n");
    printf("1 row length - count 'Pi' number\n");
    printf("2 x - count 'e' number\n");

    int variant; // Вариант функции на выполнение (1. Подсчёт Пи; 2. Подсчёт E) или смена библиотеки
    int current_library = 1; // Для определения текущей используемой библиотеки

    void *handler = dlopen("lib1.so", RTLD_LAZY); // Загрузка библиотеки, handler - указатель на библиотеку
    if (!handler) {
        printf("%s\n", dlerror());
        return 1;
    }

    //resolving functions from library
    // Определение функций, используемых в библиотеках
    double (*Pi)(int);
    double (*E)(int);
    Pi = dlsym(handler, "Pi"); // "Pi" - имя функции в библиотеке
    E = dlsym(handler, "E"); // "E" - имя функции в библиотеке
    if (dlerror() != NULL) {
        printf("%s\n", dlerror());
        return 2;
    }

    while (scanf("%d", &variant) > 0) {
        if (variant == 0) {
            if (dlclose(handler) < 0) {
                perror("Can't close dinamic library!\n");
                return 3;
            }

            //Смена библиотеки
            if (current_library == 1) {
                handler = dlopen("lib2.so", RTLD_LAZY);
                if (!handler) {
                    printf("%s\n", dlerror());
                    return 1;
                }
                current_library = 2;
            } else {
                handler = dlopen("lib1.so", RTLD_LAZY);
                if (!handler) {
                    printf("%s\n", dlerror());
                    return 1;
                }
                current_library = 1;
            }

            // Переопределение функций
            Pi = dlsym(handler, "Pi");
            E = dlsym(handler, "E");
            if (dlerror() != NULL) {
                printf("%s\n", dlerror());
                return 2;
            }
        } else if (variant == 1) {
            int row_length;
            scanf("%d", &row_length);
            printf("Result of counting 'Pi': %.10lf\n", Pi(row_length));
        } else if (variant == 2) {
            int x;
            scanf("%d", &x);
            printf("Result of counting 'e': %.10lf\n", E(x));
        } else {
            printf("Entered invalid command!\n");
        }
    }
    dlclose(handler); // Закрытие библиотеки
}