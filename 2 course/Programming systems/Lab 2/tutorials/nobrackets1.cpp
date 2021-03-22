//easylet1.cpp
#include "mlisp.h"
extern double a;
extern double b;
double a = 7.;
double b = 8.;

int main(){
//#1
 display(
 /*(*/display("a="),display(a),newline(),a/*)*/ +
  b
        );newline();

 std::cin.get();
 return 0;
}
