#include <iostream>
#include <cmath>
using namespace std;
int main () {


    int lado=6;
    float area, perimetro, diagonal;
    area = pow(lado, 2);
    perimetro = 4 * lado;
    diagonal = lado * sqrt(2);

    cout << "----<Estos son los resultados>----" << endl;
    cout << "El area es: " << area << endl;
    cout << "El perimetro es: " << perimetro << endl;
    cout << "La diagonal es: " << diagonal << endl;

     return 0;

}