#include <iostream>
using namespace std;

int main (){

    int numero, contador = 0;

    do {
        cout<<"Ingres numeros: "; cin>>numero;
        if (numero>0) {
            contador++;
        }
    } while (numero>0 || numero <0);

    cout<<"El numero de numeros mayores que cero son: "<<contador<<endl;

    return 0;
}