#include <iostream>
#include <vector>
using namespace std;

long int calcularUnidadesDeTrabajo(vector<long int>& vecindad, long int N){
    long int res = abs(vecindad[0]);
    for (long int i = 1; i < N-1; i++){
        vecindad[i] = vecindad[i] + vecindad[i-1];
        res += abs(vecindad[i]);
    }
    return res;
}

int main(){
    long int N = 1; // cantidad de vecinos 2 <= N <= 100000
    long int vecino = 0; // necesitad del vecino -1000 ≤ vecino ≤ 1000

    long int work_units = 0; // resultado óptimo
    vector<long int> resultados;

    while (true){ // input
        cin >> N;
        if (N == 0){
            break;
        }
        vector<long int> vecindad(N,0);
        for (long int i = 0; i < N; i++){
            cin >> vecino;
            vecindad[i] = vecino;
        }
        work_units = calcularUnidadesDeTrabajo(vecindad, N);
        resultados.push_back(work_units);
        vecindad.clear();
    }

    for (long int resultado : resultados){ // output
        cout << resultado << endl;
    }
    resultados.clear();
    return 0;
}