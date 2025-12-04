//Cmake tests go here

#include "Directorio.hpp"

int main(){
    Directorio D("/home/gustav/SearchEngineLin/SearchEngine/TestFolder");   // <- input full path to directory

    D.search("The");

    // unordered_map<string, int> m = D.getRelatedFiles("the"); // <- input word

    // multiset<pair<int, string>> s;

    // for(pair<string, int> p : m){ //orders files in multiset
    //     s.insert({p.second, p.first});
    // }

    // ofstream outFile("example.txt");

    // auto msp = s.rbegin();
    // for(int i = 0; i < 3; ++i){ //takes last three files (subject to change depending on how many words are being searched at once)
    //     if(msp == s.rend()){
    //         cout << "found " << i << " file" << ((i == 1)? "" : "s") << endl;
    //         break;
    //     }
        
    //     cout << msp->first << ' ' << msp->second << endl;
    //     msp++;
    // }

    /*for(pair<int, string> p : s){
        outFile << p.first << ' ' << p.second << endl;
    }*/

    //outFile.close();
    
    return 0;
}
