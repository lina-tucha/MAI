/*Хренникова Ангелина
Лабораторная работа №8
Вариант - 1*/

#include <iostream>
#include <vector>

int main()
{
    int N, p;
    unsigned int M;
    std::cin >> N >> p >> M;
    int k = N - 1;
    std::vector<int> p_arr(N);
    std::vector<int> res_arr(N);
    int current = 1;
    for (int i = 0; i < N; ++i) {
        p_arr[i] = current;
        current = current * p;
    }
    while (M > 0) {
        int count = M / p_arr[k];
        if (count == 0) {
            k--;
        }
        else {
            M = M - count * p_arr[k];
            res_arr[k] = count;
            k--;
        }
    }
    for (int i = 0; i < N; ++i) {
        std::cout << res_arr[i] << '\n';
    }
    return 0;
}