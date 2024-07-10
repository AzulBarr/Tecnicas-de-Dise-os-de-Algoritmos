/*
Link al problema: https://vjudge.net/problem/UVA-11790
*/

#include <iostream>
#include <vector>
using namespace std;

// calcula la sumatoria más grande de subsecuencias ordenadas de edificios crecientes o decrecientes. Implementación bottom-up
int sumaMaximaEdificios(int cantidadEdificios, vector<int>& alturas, vector<int>& anchos, bool crece){
    vector<int> sumasMemoria(cantidadEdificios, 0); // estructura de memoización
    int maximo = 0;
    for (int i = 0; i < cantidadEdificios; i++) {
        sumasMemoria[i] = anchos[i];
        for (int j = 0; j < i; j++) {
            if ((alturas[j] < alturas[i] and crece) or (alturas[j] > alturas[i] and !crece) ) {
                sumasMemoria[i] = max(sumasMemoria[i], sumasMemoria[j] + anchos[i]);
            }
        }
        maximo = max(sumasMemoria[i], maximo);
    }
    return maximo;
}

int main(){
    int N; // cantidad de edificios
    vector<int> alturas; // se guardan las alturas de los edificios de izquierda a derecha
    vector<int> anchos; // se guardan los anchos de los edificios de izquierda a derecha
    int T = 0;
    int num = 0;
    vector<int> valoresSubseqCrecientes;
    vector<int> valoresSubseqDecrecientes;
    // input
    cin >> T; // cantidad de casos
    for(int i = 0; i < T; i++){
        cin >> N; // cantidad de edificios
        for(int j = 0; j < N; j++){
            cin >> num; // altura
            alturas.push_back(num);
        }
        for(int k = 0; k < N; k++){
            cin >> num; // ancho
            anchos.push_back(num);
        }
        valoresSubseqDecrecientes.push_back(sumaMaximaEdificios(N,alturas,anchos, false));
        valoresSubseqCrecientes.push_back(sumaMaximaEdificios(N,alturas,anchos, true));

        alturas.clear();
        anchos.clear();
    }

    // output
    for(int i = 1; i < T+1; i++){
        int A = valoresSubseqCrecientes[i-1];
        int B = valoresSubseqDecrecientes[i-1];
        if (A >= B){                      // pregunta si es creciente
            cout << "Case " << i << ". Increasing (" << A << "). Decreasing (" << B << ")."<< endl;
        }
        else{
            cout << "Case " << i << ". Decreasing (" << B << "). Increasing (" << A << ")."<< endl;
        }
    }
    return 0;
}
