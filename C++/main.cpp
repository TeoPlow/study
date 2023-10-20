#include <iostream>

using namespace std; 

int main () {
    double a = 2.4;
    cout << a << endl;
    double *p = &a;
    cout << *p << endl;
    double *pp = p;
    cout << *pp << endl;

    *pp = 9.1;
    cout << "-----" << endl;
    cout << a << endl;
    cout << *p << endl;
    cout << *pp << endl;

}