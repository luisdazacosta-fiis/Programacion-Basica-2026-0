#include <iostream>
using namespace std;

int main (){

    float gasto[8], promedio, gasto_total=0;
    int mayor=0;

    for (int i=1; i<=7; i++){

        cout<<"Cual es el gasto del dia "<<i<<": "<<endl;
        cin>>gasto[i];

        gasto_total += gasto[i];
    }

    promedio = gasto_total / 7;

    for (int i=1; i<=7; i++){
        if (gasto[i]>promedio){
            mayor++;
        }
    }

    cout.precision(4);
    cout<<"Total: "<<gasto_total<<endl;
    cout<<"Promedio: "<<promedio<<endl;
    cout<<"Dias con gasto mayor al promedio: "<<mayor<<endl;

    return 0;
}