/*
Link al problema: https://vjudge.net/problem/CodeForces-1215C
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
set<long int> armarVector(string& S, string& T, long int N){
    set<long int> indicesMalos;
    for (int i = 0; i < N; i++){
        if (S[i] != T[i]){
            indicesMalos.insert(i);
        }
    }
    return indicesMalos;
}

long int swapLetters(set<long int>& indicesMalos, vector<long int>& indices, string& S){
    long int cantSwaps = 0;
    while (indicesMalos.size() > 1){
        long int i = 1;
        bool salir = false;
        while (i < indicesMalos.size() and !salir){
            auto it1 = indicesMalos.begin();
            auto it2 = indicesMalos.begin();
            advance(it2, i);
            if (S[*it1] == S[*it2]){
                cantSwaps += 1;
                indices.push_back(*it1 + 1);
                indices.push_back(*it2 + 1);
                indicesMalos.erase(it1);
                indicesMalos.erase(it2);
                salir = true;
            }
            i++;
        }
        if (!salir){
            auto it1 = indicesMalos.begin();
            auto it2 = indicesMalos.begin();
            advance(it2, 1);;
            cantSwaps += 2;
            indices.push_back(*it1 + 1);
            indices.push_back(*it1 + 1);
            indices.push_back(*it1 + 1);
            indices.push_back(*it2 + 1);
            indicesMalos.erase(it1);
            indicesMalos.erase(it2);
        }
    }
    return cantSwaps;
}

int main(){
    long int N;
    string S;
    string T;
    long int minCantSwaps = -1;
    vector<long int> indices;

    cin >> N >> S >> T; // input

    set<long int> indicesMalos = armarVector(S, T, N);
    if (indicesMalos.size() % 2 == 0) minCantSwaps = swapLetters(indicesMalos, indices, S);

    cout << minCantSwaps << endl; // output
    if (minCantSwaps != -1){
        for (int i = 0; i < indices.size()/2; i++){
            cout << indices[2*i] << " " << indices[2*i+1] << endl;
        }
    }

    return 0;
}
