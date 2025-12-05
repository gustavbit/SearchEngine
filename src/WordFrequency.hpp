/*
Class description here
*/

#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

class WordFrequency{
    private: 
        //File -> Cantidad de Palabra en File
        unordered_map<string, int> table; 

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

        //Adds file to word's frequency table
        void addFile(string fileName){
            table[fileName]++; 
        }

        //Getter
        unordered_map<string, int> getTable(){return table;}

};
