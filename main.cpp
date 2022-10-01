// Marcelo Eduardo Guillen Castillo A00831137
// Soeun Park A01721599
// Mariana Cortez de la Rosa A00830222

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print(string infoFiles[], string mcodes[]){
    cout << "Transmission codes" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Transmission " << i+1 << endl;
        cout << infoFiles[i] << endl;
    }
    cout << "malware codes" << endl;
    for (int i = 0; i < 10; i++){
        cout << mcodes[i] << endl;
    }
}

// Complexity: O(s*p)
int zFunction(string s, string patron, vector<int> &listaR){
    int pSize=patron.length();
    string t=patron+"$"+s;
    int n=t.length();
    vector<int> A(n, 0);
    for(int i=1; i<n; i++){
        for(int j=i; j<n; j++){
            if(t[j]==t[j-i]){
                A[i]++;
            }
            else{
                break;
            }
        }
    }
    int veces=0;
    for(int i=pSize; i<n; i++){
        if(A[i]==pSize){
            listaR.push_back(i-pSize);
            veces++;
        }
    }
    return veces;
}

// Complexity: O(s1*s2)
string longestCommonSbstr(string s1, string s2) {
    int maxLen = 0, pos;
    string maxStr;
    vector<int> temp(s2.size()+1, 0);
    vector<vector<int>> solve(s1.size()+1, temp);

    for (int i = 0; i <= s1.size(); i++) {
        for (int j = 0; j <= s2.size(); j++) {
            if (i == 0 || j == 0) {
                solve[i][j] = 0;
            }
            else if (s1[i - 1] == s2[j - 1]) {
                solve[i][j] = solve[i - 1][j - 1] + 1;
                if (solve[i][j] > maxLen){
                    maxLen = solve[i][j];
                    pos = i;
                }
            }
            else {
                solve[i][j] = 0;
            }
        }
    }
    pos -= maxLen;
    maxStr = s1.substr(pos, maxLen);
    return maxStr;
}

// Complexity: O(n)
string manacher(string text, int &iter){
    string T="";
    int n=text.length();
    for(int i=0; i<n; i++){
        T+="|";
        T+=text[i];
    }
    T+="|";
    n=T.length();
    vector<int> L(n);
    L[0]=0;
    L[1]=1;
    int maxLong=0, maxCentro=0;
    bool exp;
    for(int c=1, li=0, ri=2; ri<n; ri++){
        li=c-(ri-c);
        exp=false;
        if(c-maxLong <= ri && c+maxLong){
            if(L[li] < (c+L[c]-ri)){
                L[ri]=L[li];
            }
            else if(L[li] == (c+L[c]) - ri && (c+L[c]) == 2*n){
                L[ri] = L[li];
            }
            else if(L[li] == (c+L[c]) - ri && (c+L[c]) < 2*n){
                L[ri]=L[li];
                exp = true;
            }
            else if(L[li] > (c+L[c]) - ri && (c+L[c]) < 2*n){
                L[ri]=(c+L[c]-ri);
                exp=true;
            }
        }
        else{
            L[ri]=0;
            exp=true;
        }
        if(exp){
            while((ri+L[ri]<n) && (ri-L[ri]>0) && (T[ri-L[ri]-1]==T[ri+L[ri]+1])){
                L[ri]++;
            }
        }
        c=ri;
        if(L[ri]>maxLong){
            maxLong=L[ri];
            maxCentro=ri;
        }
    }
    int inicio = (maxCentro - maxLong)/2;
    iter=inicio+1;
    string salida="";
    for(int i=inicio; i<(inicio+maxLong); i++){
        salida+=text[i];
    }
    return salida;
}

int main() {
    string files[3];
    files[0] = "transmission1.txt";
    files[1] = "transmission2.txt";
    files[2] = "transmission3.txt";

    string infoFiles[3], mcodes[10];

    ifstream file;
    for (int i = 0; i < 3; i++) {
        file.open(files[i]);
        string text;
        while (file>>text) {
        infoFiles[i] = infoFiles[i] + text;
        }
        file.close();
    }
    file.open("mcode.txt");
    string text;
    int i=0;
    while(!file.eof()){
        file >> text;
        mcodes[i]=mcodes[i]+text;
        i++;
    }


    // print(infoFiles, mcodes);
    ofstream checking;
    checking.open("checking1.txt");
    // Subsequencia más larga y cuantas veces se repite 
    for(int i=0; i<10; i++){
        checking<<"Código: "<<mcodes[i]<<endl;
        for(int j=0; j<3; j++){
            vector<int> veces;
            checking<<files[j]<<" ==> "<<zFunction(infoFiles[j], mcodes[i], veces)<<" veces"<<endl;
            if(veces.size() > 0){
                checking<<veces[0];
            }
            for(int w=1; w<veces.size(); w++){
                checking<<", "<<veces[w];
            }
            checking<<endl;
        }
        // Buscar la subsecuencia más larga con un caracter menos
        checking<<"--------------"<<endl;
    }
    // Palíndromo más largo
    checking<<"===================="<<endl;
    checking<<"Palíndromo más grande:"<<endl;
    int iter=0;
    string palindromo=manacher(infoFiles[0], iter);
    checking<<files[0]<<" ==> Posición: "<<iter<<endl;
    checking<<palindromo<<endl;
    checking<<"----"<<endl;
    iter=0;
    palindromo=manacher(infoFiles[1], iter);
    checking<<files[1]<<" ==> Posición: "<<iter<<endl;
    checking<<palindromo<<endl;
    checking<<"----"<<endl;
    iter=0;
    palindromo=manacher(infoFiles[2], iter);
    checking<<files[2]<<" ==> Posición: "<<iter<<endl;
    checking<<palindromo<<endl;
    iter=0;
    // Longest Common Substring between...
    checking<<"============"<<endl<<"Los Substring más largos son:"<<endl;
    // T1-T2
    checking<<"T1-T2 ==> "<<longestCommonSbstr(infoFiles[0], infoFiles[1])<<endl;
    checking<<"T1-T3 ==> "<<longestCommonSbstr(infoFiles[0], infoFiles[2])<<endl;
    checking<<"T2-T3 ==> "<<longestCommonSbstr(infoFiles[1], infoFiles[2])<<endl;

    checking.close();
    return 0;
}
