#include <iostream>
#include <string>

using namespace std;

template <typename tipo> class exemploclasse {
    public:
        tipo soma(tipo a, tipo b) {
            return a+b;    
        }

        tipo maior(tipo a, tipo b) {
            return a > b ? a : b;
        }

        void swap(tipo &a, tipo &b) {
            tipo aux;
            aux = a;
            a = b;
            b = aux;
        }
};

int main() {
    exemploclasse<float> valores;
    float a = 69.69, b = 96.96;

    cout << "Antes do swap: " << a << " " << b << endl;
    valores.swap(a, b);
    cout << "Depois do swap: " << a << " " << b << endl;
    cout << "Soma: " << valores.soma(a, b) << endl; 
}