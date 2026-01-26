#include <iostream>
#include <cmath>
using namespace std;
int main () {


    int a=3, b=7, c=5;
    float p, S;

    p =(a+b+c)/2.0;
    S = sqrt(p*(p-a)*(p-b)*(p-c));

    cout << "----<Estos son los resultados>----" << endl;
    cout << "El Semi perimetro es: " << p << endl;
    cout << "El area es: " << S << endl;

     return 0;
     
}