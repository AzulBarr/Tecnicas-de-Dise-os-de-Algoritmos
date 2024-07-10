#include <iostream>
#include <vector>
using namespace std;

int maximo(vector<int> &v, int n){
    int res = 0;
    for (int i = 0; i < n; i++){
        res = max(v[i], res);
    }
    return res;
}

int maxNumBell(vector<vector<int>> &arboles, int f, int h, int t){
    vector<int> resultadosParciales(h,0);
    //vector<int> resultadosAnteriores(arboles[0].begin(), arboles[0].end());
    vector<int> resultadosAnteriores(t, 0);
    for (int k = 0; k < t; k++){
        resultadosAnteriores[k] = arboles[k][h-1];
    }
    resultadosParciales[h-1] = maximo(resultadosAnteriores, t);

    for (int altura = h-2; altura >= 0; altura--){
        int salto = altura + f;
        bool puedeSaltar = salto < h;
        for (int arbol = 0; arbol < t; arbol++){
            int x = resultadosAnteriores[arbol];
            if (puedeSaltar) x = max(x, resultadosParciales[salto]);
            resultadosAnteriores[arbol] = x + arboles[arbol][altura];
        }
        resultadosParciales[altura] = maximo(resultadosAnteriores, t);
    }
    return resultadosParciales[0];
}

int main(){
    int c = 0; // cantidad de casos
    int t = 0; // cantidad de árboles, t >= 1
    int h = 0; // altura de los árboles, h <= 2000
    int f = 0; // descenso al cambiar de árbol, 1 <= f <= 500
    int a = 0; // cantidad de bellotas, 0 <= a <= 2000
    int n = 0; // altura de la bellota

    // input
    cin >> c;
    vector<int> resultados;
    for (int i = 0; i < c; i++){
        cin >> t >> h >> f;
        vector<vector<int>> arboles(t, vector<int>(h,0));
        for (int j = 0; j < t; j++){
            cin >> a;
            for (int k = 0; k < a; k++){
                cin >> n;
                arboles[j][n-1] += 1;
            }
        }
        resultados.push_back(maxNumBell(arboles, f, h, t));
        arboles.clear();
    }
    int cero = 0;
    cin >> cero;

    // output
    for (int i = 0; i < c; i++){
        cout << resultados[i] << endl;
    }

    resultados.clear();
    return 0;
}
