#include<iostream> 
#include<cmath> 

using namespace std; 

int main () { 
    int x1, y1, r1, x2, y2, r2; 
    double d;
    cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2; 
    d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); 
    if (d <= r1 + r2 && d >= abs(r1 - r2)) {
        cout << "YES";
    } else cout << "NO";
    return 0;
}