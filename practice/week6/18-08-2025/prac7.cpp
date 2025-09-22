#include <iostream>
#include <fstream>

int main() {

    std::ofstream fout;
    fout.open("demo.txt");
    fout << "ABCDEFGH";
    fout.close();

    std::fstream file;
    file.open("demo.txt", std::ios::in | std::ios::out);

    file.seekg(0, std::ios::end);
    std::cout << "File size: " << file.tellg() << " bytes" << std::endl;
    
    file.seekp(2, std::ios::beg);
    file << "XYZ";

    file.seekg(0, std::ios::beg);
    std::string content;

    std::getline(file, content);
    std::cout << content << std::endl;

    file.close();
    return 0;
}