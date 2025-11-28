/*
Class description here
*/

#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class InvertedIndex{
    private: 
        //This is a change
        string file;
        unordered_map<string, int> table;

    public:
        InvertedIndex(string f): file(f) {}

        void addWord(string word){
            if(table.find(word) == table.end()){
                table[word] = 1;
            }
            else table[word]++;
        }

};
