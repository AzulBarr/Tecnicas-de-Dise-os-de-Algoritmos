#include <iostream>
#include <string>
using namespace std;

bool equivalent_strings(string a, string b, int n) {
    bool iguales = true;
    if (n % 2 != 0) iguales = a == b;
    else{
        n = n/2;
        string a1 = a.substr(0,n);
        string a2 = a.substr(n);
        string b1 = b.substr(0,n);
        string b2 = b.substr(n);
        iguales = (equivalent_strings(a1,b2,n) and equivalent_strings(a2,b1,n)) or
                (equivalent_strings(a1,b1,n) and equivalent_strings(a2,b2,n));
    }

    return iguales;
}

int main(){
    string a = "";
    string b = "";
    cin >> a >> b;
    int n = a.size();
    bool iguales = equivalent_strings(a,b,n);
    if (iguales) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}

