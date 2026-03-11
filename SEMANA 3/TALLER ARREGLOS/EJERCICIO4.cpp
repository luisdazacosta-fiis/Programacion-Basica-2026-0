#include <iostream>
using namespace std;

int main (){

    int actual=0, maxima=0, dia;

    do{
        cout<<"Cuantos dias dea registrar: ";
        cin>>dia;
    } while (dia<1);

    float registro[dia];
    
    for (int i=1; i<=dia; i++){

        cout<<"Ingrese el registro del dia "<<i<<": "<<endl;
        cin>>registro[i];

    }

    for (int i=1; i<=dia; i++){

        if (registro[i]>0){
            actual++;
            if (actual>maxima){
                maxima=actual;
            }
        } else {
            actual = 0;
        }

    }

    cout << "\nMayor cantidad de dias consecutivos con ganancias positivas es: "<<maxima<< endl;

    return 0;
}