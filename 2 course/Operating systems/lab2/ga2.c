#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PIPE_FD_SIZE 2

int main() {
        char c;
        int num = 0, res = 0, minus = 0, top = 1, pr = 0;
        while (scanf("%c", &c) > 0) {
                if (c == ' ' || c == '\t') {
                        if (num == 0) {
                                break;
                        } else {
                                if (top == 1)
                                        top = 0;
                                else if (minus == 1)
                                        res = (res / num) * (-1);
                                else res = res / num;
                        }
                        num = 0;
                        top = 0;
                        minus = 0;
                        pr = 1;
                } else if (c == '-') {
                        minus = 1;
                        pr = 0;
                } else if (c == '\n') {
                        if (num == 0) {
                                if (pr == 1) res = res / 1;
                                else break;
                        } else {
                                if (top == 1)
                                        top = 0;
                                else if (minus == 1)
                                        res = (res / num) * (-1);
                                else res = res / num;
                        }
                        write(1, &res, sizeof(int));
                        num = 0;
                        top = 1;
                        minus = 0;
                        res = 0;
                        pr = 0;
                } else if (c >= '0' && c <= '9') {
                        num = num *10 + c - '0';
                                if (top == 1)
                                        res = num;
                        pr = 0;
                }
        }
}