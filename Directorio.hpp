#include "InvertedIndex.hpp"
#include <fstream>
#include <filesystem>
#include <sys/stat.h>
#include <iostream>
#include <algorithm>

namespace fs = std::filesystem;

using namespace std;

class Directorio{

    private:

        string relPath;
        unordered_map<string, InvertedIndex> dir; //word -> list of related files

        string getFileName(string path){ //returns file name from path
            string fileName = "";
            reverse(path.begin(), path.end());
            for(int i = 0; path[i] != '/'; ++i){
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

        Directorio(string relPath){
            string dirPath = "/home/gustav/SearchEngineLin/SearchEngine/" + relPath; //fix to get the path for current directory
            string word;
            string fileName;
            ifstream inFile;

            struct stat sb;

            for(const auto& entry : fs::directory_iterator(dirPath)){
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

           

};
