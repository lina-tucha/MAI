#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int a1, b1, a2, b2, a3 = 0, b3 = 0;
	cin >> a1 >> b1 >> a2 >> b2;
	if (a1 % a2 == 0) a3 = a1 / a2; 
    else a3 = a1 / a2 + 1;
	if (b1 % b2 == 0) b3 = b1 / b2; 
    else b3 = b1 / b2 + 1;
    cout << a3 * b3;
    return 0; 
}
