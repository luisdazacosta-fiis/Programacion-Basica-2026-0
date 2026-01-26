#include <iostream>
#include <cmath>
using namespace std;
int main () {


    int D=8, d=6;
    float area, lado, perimetro;

    area = (D*d)/2;
    lado = sqrt(pow((D/2), 2) + pow((d/2), 2));
    perimetro = 4*lado;

    cout << "----<Estos son los resultados>----" << endl;
    cout << "El area es: " << area << endl;
    cout << "El lado es: " << lado << endl;
    cout << "EL perimetro es: " << perimetro << endl;

     return 0;
     
}