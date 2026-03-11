#include <iostream>
using namespace std;

int main (){

    float temperatura[8], maximo=0, minimo=999;
    int mayor=0, diamax, diamin;

    for (int i=1; i<=7; i++){

        cout<<"Ingrese temperatura del dia "<<i<<": "<<endl;
        cin>>temperatura[i];

        if (temperatura[i]>maximo){
            maximo=temperatura[i];
            diamax = i;
        }

        if (temperatura[i]<minimo){
            minimo=temperatura[i];
            diamin = i;
        }

        if (temperatura[i]>30){
            mayor++;
        }
    }

    cout<<"Maximo: "<<maximo<<" (dia "<<diamax<<")"<<endl;
    cout<<"Minimo: "<<minimo<<" (dia "<<diamin<<")"<<endl;
    cout<<"Dias mayores a 30: "<<mayor<<endl;

    return 0;
}