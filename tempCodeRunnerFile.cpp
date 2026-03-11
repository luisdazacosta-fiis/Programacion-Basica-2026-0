#include <iostream>
using namespace std;

int main() {
    int x,c=0,s=0;

    while(true){
        cout << "Ingrese numero (-1 termina): ";
        cin >> x;
        if(x==-1) break;
        s+=x; c++;
    }
    if(c>0) cout << "Promedio: " << (double)s/c;
}
