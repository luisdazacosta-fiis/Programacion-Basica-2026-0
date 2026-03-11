#include <iostream>
#include <vector>
using namespace std;

void duplicar(vector<int>& v) {
    for(int &x : v) x *= 2;
}

int main() {
    vector<int> a = {1,2,3};
    duplicar(a);
    for(int x : a) cout << x << " ";
    return 0;
}
