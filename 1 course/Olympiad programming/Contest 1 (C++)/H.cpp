#include<iostream> 
#include<cmath> 

using namespace std; 

int main () { 
    int x1, y1, x2, y2, x3, y3, x4, y4, l = 0, t = 0, r = 0, b = 0; 
    int w = 0, h = 0; int tmp = 0;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    if (x2 < x1) {
        tmp = x1; 
        x1 = x2; 
        x2 = tmp;
    } 
    if (x4 < x3) {
        tmp = x4; 
        x4 = x3; 
        x3 = tmp;
    }
    if (y2 < y1) {
        tmp = y1; 
        y1 = y2; 
        y2 = tmp;
    }
    if (y4 < y3) {
        tmp = y4; 
        y4 = y3; 
        y3 = tmp;
    }
    if (x1 >= x3) l = x1; 
    else l = x3;
    if (x2 <= x4) r = x2; 
    else r = x4;
    if (y2 <= y4) t = y2; 
    else t = y4;
    if (y1 >= y3) b = y1; 
    else b = y3;
    if ((r > l) && (t > b)) cout << (r - l) * (t - b);
    else cout << 0;
return 0;
}