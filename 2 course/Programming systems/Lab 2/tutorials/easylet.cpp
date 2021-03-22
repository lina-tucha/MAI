//easylet.cpp
#include "mlisp.h"
extern double a;
extern double b;

double a = 7.;
double b = 8.;

int main(){
//#1
 display(
  (display("a="),display(a),newline(),a) +
  b
        );newline();
//#2
 display(
  (a<b ? a
       : (display("b="),display(b),newline(),b)
  )
        );newline();

 std::cin.get();
 return 0;
}
