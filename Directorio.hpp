#include "InvertedIndex.hpp"
#include <unordered_set>
#include <fstream>

using namespace std;

class Directorio{

    private:
        unordered_map<string, unordered_set<InvertedIndex>> dir;
    public: 
        Directorio(){}

};
