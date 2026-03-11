#include <iostream>
using namespace std;

int main (){

    int estudiantes, asistencia[6], asistencia_total= 0;

    do{
        cout<<"Ingrese la cantidad de estudiantes del aula: ";
        cin>>estudiantes;
    } while (estudiantes<1);

    for (int i=1; i<=estudiantes; i++){

        int contador=0;
        
        cout<<"Ingrese las asistencias del alumno "<<i<<" durante la semana: "<<endl;

        for (int j=1; j<=5; j++){

            cout<<"Ingrese la asistencia del dia "<<j<<" (1 = asistio, 0 = no asistio): "<<endl;
            cin>>asistencia[j];

            if (asistencia[j]==1){
                contador++;
            }
        }

        cout<<"El estudiante "<<i<<" tiene "<<contador<<" asistencias."<<endl;


        if (contador == 5){
            cout<<"Este estudiante tiene asistencia perfecta."<<endl;
        }

        asistencia_total += contador;
    }

    cout<<"El total de asistencias del aula es: "<<asistencia_total<<endl;

    return 0;
}