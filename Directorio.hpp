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

        string relPath;
        unordered_map<string, InvertedIndex> dir; //word -> list of related files

        string getFileName(string path){ //returns file name from path
            string fileName = "";
            //reverse(path.begin(), path.end());
            for(int i = path.length()-1; path[i] != '/' || path[i] == '\\'; --i){
                fileName += path[i];
            }
            reverse(fileName.begin(), fileName.end());
            return fileName;
        }  

        string fixWord(string old){ //simple input validation (maybe fix in  constructor with getline)
            string fixed = "";
            for(char c : old){
                if(('A' <= c && 'Z' >= c)||('a' <= c && 'z' >= c)){
                    fixed += (c < 'a')? c+('a'-'A') : c;
                }
            }
            return fixed;
        }

    public:

        Directorio(){}

        void addDir(string inPath){ //Input is path to directory
            string word;
            string fileName;
            ifstream inFile;

            struct stat sb;

            for(const auto& entry : fs::directory_iterator(inPath)){
                fs::path outfilename = entry.path();
                string outfilename_str = outfilename.string();
                const char* path = outfilename_str.c_str();

                if(stat(path, &sb) == 0 && !(sb.st_mode &S_IFDIR)){ //checks if file isn't another subdirectory
                    fileName = getFileName(path);
                    inFile.open(path);

                    while(inFile >> word){
                        word = fixWord(word);
                        if(dir.find(word) == dir.end()){
                            InvertedIndex I;
                            dir[word] = I;
                        }
                        dir[word].addFile(fileName);
                    }

                    inFile.close();
                }
            }
        }

        unordered_map<string, int> getRelatedFiles(string s){
            s = fixWord(s);
            return dir[s].getTable();
        }

        /*tuple<string, string, string> search(string t){ //idk man
            vector<string> tokens;
            vector<multiset<pair<string, int>>> associatedFiles;
            string t;
            for(char c : t){
                if(c == ' ') {
                    if(!t.empty()) tokens.push_back(t);
                    t.clear(); 
                }
                else t += c;
            }
            for(string s : tokens){
                //add set of words with token
            }
        }*/
};
