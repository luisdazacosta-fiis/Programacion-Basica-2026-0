#include <iostream>
#include <cmath>
using namespace std;
int main () {


    int base=8, altura=6;
    float area, perimetro, diagonal;
    area = base * altura;
    perimetro = 2*(base + altura);
    diagonal = sqrt((base*base)+(altura*altura));

    cout << "----<Estos son los resultados>----" << endl;
    cout << "El area es: " << area << endl;
    cout << "El perimetro es: " << perimetro << endl;
    cout << "La diagonal es: " << diagonal << endl;

     return 0;

}