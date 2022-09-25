// Marcelo Eduardo Guillen Castillo A00831137
// Soeun Park A01721599
// Mariana Cortez de la Rosa A00830222

#include <fstream>
#include <iostream>
#include <vector>

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

    print(infoFiles, mcodes);
    

    return 0;
}
