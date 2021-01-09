#include <iostream>

using namespace std;

int main() {
	int a1, b1, a2, b2, a3, b3, a4 = 0, b4 = 0, n;
	cin >> a1 >> b1 >> a2 >> b2 >> a3 >> b3 >> n;
	b4 = (b1 + (b2 * n + b3 * (n - 1))) % 60;
	a4 = (a1 + (a2 * n + a3 * (n - 1) + (b1 + (b2 * n + b3 * (n - 1))) / 60));
	cout << a4 << ' ' << b4;
	return 0; 
}