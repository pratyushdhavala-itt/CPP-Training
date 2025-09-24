#include <iostream>
#include <fstream>

using namespace std;

int main() {
    
    fstream fout;
    fout.open("demo3.txt", ios::app);

    // fout << "HIIII" << endl << "BYEEEEE" << endl;

    fout << "PRATTT" << endl;
    return 0;
}