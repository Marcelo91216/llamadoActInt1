// Marcelo Eduardo Guillen Castillo A00831137
// Soeun Park 
// Mariana 

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(){
    ifstream tran1("transmission1.txt");
    string text1;
    while(!tran1.is_open()){
        tran1>>text1;
        cout<<text1;
    }
    tran1.close();

    return 0;
}