//nobraces.cpp
#include "mlisp.h"
extern double a;
double f(double f);

double a = 7.;
double f(double f){
 f = f - 100./101.;
//??? {//let
  double 
        a(sin(f)),
        b(log(f)),
        f(0.);
  f = 5. * a * b;
  return f;
//??? }//let
}
int main(){
 display(f(1.));newline();
std::cin.get();
 return 0;
}
