#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

typedef struct {
        int width;
        int height;
        int a;
        int b;
        int c;
        int d;
        int f;
        int number;
        int **array;
        int *result;
} Data;

void* thread_function(void* thread_data) {
        Data *data = (Data*) thread_data;
        int m = data -> width;
        int n = data -> height;
        int h = data -> number;
        int n1 = data -> a;
        int m1 = data -> b;
        int n2 = data -> c;
        int m2 = data -> d;
        int k = data -> f;
        const int n_1 = sqrt(n) / 1;
        const int m_1 = sqrt(m) / 1;
        if ((h + 1) % m2 == 0) {
                int t1 = m - m1 * (m2 - 1);
                m1 = t1;
                if (h / m2 == n2 - 1) {
                        int t2 = n - n1 * (n2 - 1);
                        n1 = t2;
                }
        }
        else if (h / m2 == n2 - 1) {
                int t2 = n - n1 * (n2 - 1);
                n1 = t2;
        }
        printf("We are in %d thread \n", h + 1);
        for (int i = (h % m2) * m_1; i < (h % m2) * m_1 + m1; i++) {
                for (int j = (h / m2) * n_1; j < (h / m2) * n_1 + n1; j++) {
                        data -> result[i] = data -> result[i] + data -> array[j][i];
                        printf("result[%d]: %d\n", i, data -> result[i]);
                }
        }
        printf("\n");
        printf("\n");
        return NULL;
}

int main() {
        int N, M;
        printf("Enter the number of arrays: ");
        scanf("%d", &N);
        printf("Enter the size of the arrays: ");
        scanf("%d", &M);
        int n1 = (sqrt(N)) / 1;
        int m1 = sqrt(M) / 1;
        int n2 = (N + n1 - 1) / n1;
        int m2 = (M + m1 - 1) / m1;
        int k = n2 * m2;
        printf("Partitioning the matrix into %d x %d cells.\n", n2, m2);
        printf("Each cell size %d x %d, except for the outermosts.\n", n1, m1);
        printf("\n");
        int** matrix = (int**) malloc (N * sizeof(int*));
        int* result_array = (int*) malloc (M * sizeof(int*));
        for (int i = 0; i < N; i++) {
                matrix[i] = (int*) malloc (M * sizeof(int));
        }
        srand(time(NULL));
        int r;
        for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                        r = rand() % 1000;
                        matrix[i][j] = r;
                        result_array[j] = 0;
                }
        }
        for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                        printf("Element[%d][%d] = %d\n", i, j, matrix[i][j]);
                }
        }
        printf("\n");
        for (int i = 0; i < N; i++) {
                printf("\n");
                for (int j = 0; j < M; j++) {
                        printf("%d\t", matrix[i][j]);
                }
        }
        printf("\n");
        printf("\n");
        pthread_t* array_of_threads = (pthread_t*) malloc (k * sizeof(pthread_t));
        Data* d = (Data*) malloc (k * sizeof(Data));
        for (int i = 0; i < k; i++) {
                d[i].height = N;
                d[i].width = M;
                d[i].number = i;
                d[i].a = n1;
                d[i].b = m1;
                d[i].c = n2;
                d[i].d = m2;
                d[i].f = k;
                d[i].array = matrix;
                d[i].result = result_array;
                pthread_create(&(array_of_threads[i]), NULL, thread_function, &d[i]);
        }
        for (int i = 0; i < k; i++) {
                pthread_join(array_of_threads[i], NULL);
        }
        printf("\n");
        for (int i = 0; i < M; i++) {
                printf("result[%d] = %d\n", i, result_array[i]);
        }
        printf("\n");
        for (int i = 0; i < M; i++) {
                printf("%d\t", result_array[i]);
        }
        printf("\n");
        free(array_of_threads);
        free(d);
        for(int i = 0; i < N; i++) {
                free(matrix[i]);
        }
        free(matrix);
        free(result_array);
        return 0;
}