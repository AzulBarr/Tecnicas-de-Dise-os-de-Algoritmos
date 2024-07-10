#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<int> Vecindario;
typedef vector<Vecindario> Grafo; // lista de adyacencias
typedef vector<int> PigeonValues;

void dfs_visit(Grafo &G, int i, vector<int> &tInicio, vector<int> &menorAlcanzable, vector<int> &padre, PigeonValues &PV, int t){
    int hijos = 0;
    tInicio[i]=t;
    menorAlcanzable[i]=t;
    t++;

    for (int j : G[i]){
        if (tInicio[j] == -1){
            hijos++;
            padre[j] = i;
            dfs_visit(G,j,tInicio,menorAlcanzable,padre,PV,t);
            menorAlcanzable[i]= min(menorAlcanzable[i],menorAlcanzable[j]);

            //es raiz y tiene más de 1 hijo, o no es raiz y su hijo no tiene una backedge a un ancestro suyo
            if ((padre[i]==-1 and hijos>1) or (padre[i]!=-1 and menorAlcanzable[j]>=tInicio[i]))
                PV[i]++;
        }
        else if (padre[i] != j)
            menorAlcanzable[i]= min(menorAlcanzable[i],tInicio[j]);
    }
}

void dfs(Grafo &G, int n, PigeonValues &PV){
    vector<int> tInicio(n,-1);
    vector<int> menorAlcanzable(n,-1);
    vector<int> padre(n,-1);
    int time = 0;
    for(int i = 0;i < n;i++){
        if (tInicio[i] == -1)
            dfs_visit(G,i,tInicio, menorAlcanzable, padre, PV, time);
    }
}

PigeonValues calcularPV(Grafo &G, int n){
    PigeonValues PV(n,1);
    dfs(G,n,PV);
    return PV;
}

bool clave(const pair<int, int> x, const pair<int, int> y){
    bool orden;
    if (x.second != y.second)
        orden = x.second > y.second;
    else
        orden = x.first < y.first;
    return orden;
}

int main(){
    vector<pair<int,int>> respuestas;
    vector<int> output;
    int n, m;
    bool seguir1 = true;
    while (seguir1){
        cin >> n >> m;
        if (n == 0 and m == 0) seguir1 = false;
        else{
            output.push_back(m);
            Grafo G(n, Vecindario());
            int x, y;
            bool seguir2 = true;
            while (seguir2){
                cin >> x >> y;
                if (x == -1 and y == -1) seguir2 = false;
                else{
                    G[x].push_back(y);
                    G[y].push_back(x);
                }
            }
            PigeonValues PV = calcularPV(G, n);
            vector<pair<int,int>> rta;
            for (int i = 0; i < n; i++)
                rta.push_back(make_pair(i,PV[i]));

            sort(rta.begin(),rta.end(),clave);
            vector<pair<int,int>> rta2(rta.begin(), rta.begin() + m);

            for (pair<int,int> par : rta2)
                respuestas.push_back(par);

        }
    }
    int k = 0;
    for (int i = 0; i < respuestas.size(); i++) {
        if (k == output[0]) {
            cout << "\n";
            output.erase(output.begin());
            k = -1;
        }
        cout << respuestas[i].first << " " << respuestas[i].second << endl;
        k++;
    }
    cout << "\n";
    return 0;

}
