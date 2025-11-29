/*
Class description here
*/

#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class InvertedIndex{
    private: 
        unordered_map<string, int> table; //related file -> amount of that word in file

    public:
        InvertedIndex() {}

        ~InvertedIndex(){
            table.clear();
        }

        InvertedIndex &operator=(const InvertedIndex& rs){
            table = rs.table;
            return *this;
        }

        InvertedIndex &operator=(InvertedIndex&& rs){
            table = rs.table;
            rs.table.clear();
            return *this;
        }

        InvertedIndex(const InvertedIndex &rs){
            table = rs.table;
        }

        InvertedIndex(InvertedIndex &&rs){
            table = rs.table;
            rs.table.clear();
        }

        void addFile(string fileName){
            table[fileName]++; //fix so that its ordered (maybe do two vectors and order based on file with most instances of word)
        }

        unordered_map<string, int> getTable(){return table;}

};
