/*
Link al problema: https://vjudge.net/problem/UVA-1235
*/

#include <vector>
#include <iostream>
#include <limits>
using namespace std;
const int inf = numeric_limits<int>::max();

int cantRolls(int x, int y){
    int sumatoria = 0;
    for (int i=1;i<5;i++){
        int digito1 = x % 10;
        int digito2 = y % 10;
        int dif = abs(digito1 - digito2);
        if (dif > 5)
            dif = 10 - dif;
        sumatoria += dif;
        x = x/10;
        y = y/10;
    }
    return sumatoria;
}

int Prim(vector<vector<int>> &C, int n, int r, vector<int> &codigos){
    vector<int> T(n, -1), S(n, r);
    T[r] = r;
    for(int i = 0; i < n-1; ++i) {
        int w = 0;
        for(int z = 0; z < n; ++z){
            if(C[z][S[z]] < C[w][S[w]]) w = z;
        }
        T[w] = S[w]; S[w] = w;
        for(int z = 0; z < n; ++z) {
            if ((T[z] == -1) and (C[w][z] < C[z][S[z]]))
                S[z] = w;
        }
    }
    int cantTotalRolls = 0;
    for (int i=0;i<n;i++){
        if (T[i]==i) cantTotalRolls += cantRolls(codigos[i],0);
        else{
            cantTotalRolls += C[i][T[i]];
        }
    }
    return cantTotalRolls;
}

int masCercanoAl0000(vector<int> &codigos, int n){
    int r = 0;
    int distAnterior = cantRolls(0,codigos[0]);
    for (int i=1;i<n;i++){
        int distActual = cantRolls(0,codigos[i]);
        if (distAnterior > distActual){
            r = i;
            distAnterior = distActual;
        }

    }
    return r;
}

int main(){
    int T;
    cin >> T;
    vector<int> rtas(T,0);
    for (int i=0; i<T; i++){
        int N = 0;
        cin >> N;
        vector<int> codigos(N,0);
        for (int j=0;j<N;j++){
            int Ci;
            cin >> Ci;
            codigos[j]=Ci;
        }
        vector<vector<int>> C(N,vector<int>(N,inf));
        for (int fil=0;fil<N-1;fil++){
            for(int col=0;col<N;col++){
                if (col>fil){
                    C[fil][col]= cantRolls(codigos[fil],codigos[col]);
                    C[col][fil]=C[fil][col];
                }
            }
        }
        int r = masCercanoAl0000(codigos,N);
        int cantTotalRolls = Prim(C,N,r,codigos);
        rtas[i] = cantTotalRolls;
    }
    for (int rta : rtas){
        cout << rta << endl;
    }
    return 0;
}
