/*
Class description here
*/

#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class WordFrequency{
    private: 
        unordered_map<string, int> table; //related file -> amount of that word in file

    public:

        /* BIG FIVES */
        WordFrequency() {} 

        ~WordFrequency(){
            table.clear();
        }

        WordFrequency &operator=(const WordFrequency& rs){
            table = rs.table;
            return *this;
        }

        WordFrequency &operator=(WordFrequency&& rs){
            table = rs.table;
            rs.table.clear();
            return *this;
        }

        WordFrequency(const WordFrequency &rs){
            table = rs.table;
        }

        WordFrequency(WordFrequency &&rs){
            table = rs.table;
            rs.table.clear();
        }

        void addFile(string fileName){
            table[fileName]++; 
        }

        unordered_map<string, int> getTable(){return table;}

};
