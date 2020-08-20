#include<iostream>
#include<fstream>
using namespace std;

int main(){
    ofstream outFile;
    outFile.open("input.txt", ios::out);

    for(int i=0; i<10000000; i++){
        outFile << "1234567890" << i << "\n";
        cout << "\r" << i;
    }
    outFile.close();
}