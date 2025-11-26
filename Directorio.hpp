#include "InvertedIndex.hpp"
#include <unordered_set>
#include <fstream>

using namespace std;

class Directorio{

    private:
        unordered_map<string, unordered_set<InvertedIndex>> dir;
    public: 
        Directorio(){}

        //void setDir(string subdir)
        //string word;
        //ifstream inFile;
        //for(inFile in subdir){
        //  for(word << inFile) {
        //      if(dir[word].find(inFile) == dir[word].end()) {
        //          InvertedIndex I(inFile)
        //          dir[word].append(I);
        //      }
        //      dir[word].addWord(word);
        //  }
        //}


};