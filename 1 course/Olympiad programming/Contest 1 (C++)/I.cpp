#include<iostream> 
#include<cmath> 

using namespace std; 

int main () { 
    double x1, y1, x3, x2, y2, y3; 
    double S = 0; 
    double p = 0, a = 0, b = 0, c = 0;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    p = (a + b + c) / 2;
    S = sqrt(p * (p - a) * (p - b) * (p - c));
    cout.setf(ios::scientific);
    cout << S;
    return 0;
}