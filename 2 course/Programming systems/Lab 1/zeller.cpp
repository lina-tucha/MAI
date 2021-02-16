//zeller.cpp
#include "mlisp.h"
double day__of__week();
double zeller(double d, double m, double y, double c);
double neg__to__pos(double d);
double birthday(double dw);
extern double dd;
extern double mm;
extern double yyyy;

double day__of__week(){
        zeller(dd, ((mm < 3) ? (mm + 10) : (mm - 2)), remainder(((mm < 3) ? (yyyy - 1) : yyyy), 100), quotient(((mm < 3) ? (yyyy - 1) : yyyy), 100));
}

double zeller(double d, double m, double y, double c) {
        neg__to__pos(remainder(d + y + quotient(26*m-2, 10) + quotient(y, 4) + quotient(c, 4) - 2 * c, 7));
}

double neg__to__pos(double d){
        return (d < 0. ? d + 7.
                : true ? d
                : _infinity
        );
}

double birthday(double dw){
        display("Your were born on ");
        (dw == 1) ? display("Monday ")
                : (dw == 2) ? display("Tuesday ")
                : (dw == 3) ? display("Wednesday ")
                : (dw == 4) ? display("Thursday ")
                : (dw == 5) ? display("Friday ")
                : (dw == 6) ? display("Saturday ")
                : display("Sunday ");
        display(dd);
        display(".");
        display(mm);
        display(".");
        return  yyyy;
}

double dd = 06;
double mm = 03;
double yyyy = 2001;

int main(){
        display(birthday (day__of__week()));
        newline();
        std::cin.get();
        return 0;
}
