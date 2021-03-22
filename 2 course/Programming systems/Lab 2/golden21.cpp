//golden21.cpp
#include "mlisp.h"
#include <cmath>

double a = -5.;
double b = -3.;
double mphi = (3. - sqrt(5.)) / 2.;
extern double xmin;
extern double total__iterations;
extern double ya;
extern double yb;
extern double tolerance;

double fun(double x);
double golden__section__search(double a, double b);
double golden__start(double a, double b);
double __KAS__try(double a, double b, double xa, double ya, double xb, double yb);
double close__enough_Q(double x, double y);

double fun(double x) {
    x = x - (28. / 29.);
    return (pow(M_E, -x) * sin(x + M_PI) + cos(x) - 1.13);
}

double golden__section__search(double a, double b) {
    xmin = (a < b) ? (golden__start(a, b)) : (golden__start(b, a));
    newline();
    return xmin;
}

double golden__start(double a, double b) {
    double total__iterations(0.),
    xa(a + mphi * (b - a)),
    xb(b - mphi * (b - a));
    __KAS__try(a, b, xa, fun(xa), xb, fun(xb));
}

double __KAS__try(double a, double b, double xa, double ya, double xb, double yb) {
    if (close__enough_Q(a, b)) {
        return (a + b) * 0.5;
    } else {
        display("+");
        total__iterations++;
        ya < yb ? b = xb, xb = xa, yb = ya, xa = a + mphi * (b - a), __KAS__try(a, b, xa, fun(xa), xb, yb)
            : (a = xa, xa = xb, ya = yb, xb = b - mphi * (b - a), __KAS__try(a, b, xa, ya, xb, fun(xb)));

    }
}

double close__enough_Q(double x, double y) {
    return (abs(x - y) < tolerance);
}

double tolerance = 0.001;
double total__iterations = 0.;
double xmin = 0.;

int main(){
    xmin = golden__section__search(a, b);
    display("Interval=\t[");
    display(a);
    display(" , ");
    display(b);
    display("]\n");
    display("Total number of iteranions=");
    display(total__iterations);
    display("\nxmin=\t\t");
    display(xmin);
    display("\nf(xmin)=\t");
    display(fun(xmin));
    newline();
    std::cin.get();
    return 0;
}
