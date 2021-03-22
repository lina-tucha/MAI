//block.cpp
#include "mlisp.h"
double f(double x);

double f(double x){
 x = x - 100./101.;
 {//let
  double 
        a(sin(x)),
        b(log(x)),
        x(0.);
  x = 5. * a * b;
  return x;
 }//let
}
int main(){
 display(f(1.));newline();
std::cin.get();
 return 0;
}
