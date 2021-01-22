#include <iostream>

using namespace std;

int main() {
    int a, b; 
    long long k = 0;
    cin >> a >> b;
    if (a < b) {
        for (int i = a; i <= b; i++)
	    k = k + i;
        cout << k;
    } else {
	for (int i = b; i <= a; i++)
	    k = k + i;
        cout << k;
    }
    return 0; 
}
