#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int a, b, c;
	cin >> a >> b >> c;
    double k=0;
	k = sqrt(b * b + c * c);
    if (a >= k) cout << "YES"; 
    else cout << "NO";
	return 0; 
}