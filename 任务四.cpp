#include <iostream>
using namespace std;

void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a, b;
    
    cout << "ÊäÈë: ";
    cin >> a >> b;

    cout << "\nÊä³ö:" << endl;
    cout << "Before swap: x=" << a << ", y=" << b << endl;

    swap(a, b); 

    cout << "After  swap: x=" << a << ", y=" << b << endl;

    return 0;
}

