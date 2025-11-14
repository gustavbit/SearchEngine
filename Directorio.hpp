#include "InvertedIndex.hpp"
#include <vector>

using namespace std;

class Directorio{

    private:
        unordered_map<string, vector<InvertedIndex>> dir;
    public: 
        Directorio(){}

};