// g++ -Wall vetor.cpp

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {

    unsigned int n = 10;
    vector<int> v;

    // Gera um vetor de numeros aleatorios de 0 a 20
    srand(6);
    for(unsigned int i =0; i < n; i++) {
        v.push_back(rand()%20);
    }

    // Verifica se o vetor é vazio
    if(v.empty() == true)
        cout << "\nO vetor esta vazio";
    
    cout << "Vetor Inicial \n";
    // Imprime o vetor inicial    
    for(unsigned int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << "\n\n";
    
    /******** IMPLEMENTAR A PARTIR DAQUI **********/

    // a- Ordenar vetor e imprimir vetor ordenado
    sort(v.begin(), v.end());

    cout << "Vetor Ordenado\n";
    for(int elemento: v) {
        cout << elemento << " ";
    }
    cout << "\n\n";

    // b- Remover o primeiro elemento
    v.erase(v.begin());

    cout << "Novo tamanho: " << v.size();
    cout << "\n";

    // Imprime o vetor final
    cout << "Vetor final \n";
    for(unsigned int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << endl;

    return 0;

}
