//Cmake tests go here

#include "Directorio.hpp"

int main(){
    Directorio D("books_description_files"); //takes about a minute to load all files in folder

    unordered_map<string, int> m = D.getRelatedFiles("the");

    ofstream outFile("example.txt");

    for(pair<string, int> p : m){
        outFile << p.first << ' ' << p.second << endl;
    }

    outFile.close();
    
    return 0;
}
