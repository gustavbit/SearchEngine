#include "InvertedIndex.hpp"
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

namespace fs = std::filesystem;

using namespace std;

class Directorio{

    private:

        string Path;
        unordered_map<string, InvertedIndex> dir; //word -> list of related files
        int fileAmount;

        string fixWord(string old){ //simple input validation (maybe fix in  constructor with getline)
            string fixed = "";
            for(char c : old){
                if(('A' <= c && 'Z' >= c)||('a' <= c && 'z' >= c)){
                    fixed += (c < 'a')? c+('a'-'A') : c;
                }
            }
            return fixed;
        }

        vector<pair<string, int>> sortSearch(const unordered_map<string, int> &m){
        
            multiset<pair<int, string>> s;
            vector<pair<string, int>> mostSearchedWords;

            for(pair<string, int> p : m){ //orders files in multiset
                s.insert({p.second, p.first});
            }

            auto msp = s.rbegin();
            //takes last three files 
            for(int i = 0; i < 3; ++i){ 
                if(msp == s.rend()){
                    cout << "found " << i << " file" << ((i == 1)? "" : "s") << endl;
                    break;
                }
                mostSearchedWords.push_back({msp->second, msp->first});                
                cout << msp->second << ' ' << msp->first << endl;
                msp++;
            }

            return mostSearchedWords;

        }

    public:

        Directorio(){}

        void addDir(string inPath){ //Input is path to directory

            //----------------------

            int counter = 0;

            //Iterates through all the files in directory
            for(const auto& entry : fs::directory_iterator(inPath)){
                if(entry.is_regular_file()){
                    ifstream file(entry.path());
                    if(!file.is_open()){
                        std::cerr << "No se pudo abrir archivo: " << entry.path() << endl;
                        continue;
                    }
                    ++counter;
                    string word;
                    while(file >> word){
                        word = fixWord(word);
                        if(dir.find(word) == dir.end()){
                            InvertedIndex I;
                            dir[word] = I;

                        }
                        dir[word].addFile(entry.path().filename().string());
                    }

                    file.close();
                }
            }
        }

        unordered_map<string, int> getRelatedFiles(string s){
            s = fixWord(s);
            return dir[s].getTable();
        }

        vector<pair<string, int>> search(string p){ //idk man
            string palabra;
            stringstream phrase(p);
            phrase >> palabra;
            palabra = fixWord(palabra);
            unordered_map<string, int> freq = getRelatedFiles(palabra);

            while(phrase >> palabra){
                palabra = fixWord(palabra);
                unordered_map<string, int> k = getRelatedFiles(palabra);

                for(auto it = freq.begin(); it != freq.end(); ) {
                    if (k.find(it->first) == k.end()) {
                        it = freq.erase(it);  // returns next iterator
                    } 
                    else {
                        it->second += k[it->first];
                        ++it;
                    }
                    if (freq.empty()) return {};
                }

            }

            return sortSearch(freq);
        }
};
