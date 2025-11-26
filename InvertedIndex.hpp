/*
Class description here
*/

#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class InvertedIndex{
    private: 
        string file;
        unordered_map<string, int> table;

    public:
        InvertedIndex(string f): file(f) {}

        void addWord(string word){
            table[word]++;
        }

};
