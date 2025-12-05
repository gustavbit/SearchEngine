#include "WordFrequency.hpp"
#include <filesystem>
#include <iostream>
#include <set>
#include <vector>

namespace fs = std::filesystem;

using namespace std;

class Directorio{

    private:

        string path;
        unordered_map<string, WordFrequency> dir; //word -> list of related files
        int fileAmount;

        /*
        INPUT VALIDATION:
            Convierte todas las palabras a minusculas
            - Hace que el programa no sea "cap sensitive"

            Implementación usando ASCII
        */
        string fixWord(string old){ 
            string fixed = "";
            for(char c : old){
                if(('A' <= c && 'Z' >= c)||('a' <= c && 'z' >= c)){ 
                    fixed += (c < 'a')? c+('a'-'A') : c;
                }
            }
            return fixed;
        }

        /*
        SORT SEARCH:
            1. Guarda files donde aparecen las palabras que buscamos
            y los añade a un multiset donde guarda frecuencia[palabra].
            - Cuando se colocan en multiset se guardan de menor a mayor

            2. Coloca iterador en ultimo file (el de mayor frecuencia) y 
            recorre ultimos tres elementos del multiset para poder guardar
            3 files mas relevantes en un vector

            Implementacion utilizando sets
        */
        vector<string> sortSearch(const unordered_map<string, int> &m){
        
            multiset<pair<int, string>> s;
            vector<string> mostSearchedWords;

            for(pair<string, int> p : m){ //ordena files en multiset
                s.insert({p.second, p.first}); // par de {frecuencia, palabra}
            }

            auto msp = s.rbegin();
            //toma ultimos tres files 
            for(int i = 0; i < 3; ++i){ 
                if(msp == s.rend()){
                    break;
                }
                mostSearchedWords.push_back(msp->second); //guarda files más relevantes en vector             
                msp++; //incrementa iterador
            }

            return mostSearchedWords; //devuelve vector de files mas relevantes

        }

    public:

        Directorio(string inPath){ //Input el path al directorio

            path = inPath;

            int counter = 0;

            //Itera por todos los files del directory
            for(const auto& entry : fs::directory_iterator(inPath)){
                if(entry.is_regular_file()){
                    ifstream file(entry.path());
                    if(!file.is_open()){
                        std::cerr << "No se pudo abrir archivo: " << entry.path() << endl;
                        continue;
                    }
                    ++counter;
                    string word;
                    while(file >> word){
                        word = fixWord(word);
                        if(dir.find(word) == dir.end()){
                            WordFrequency wf;
                            dir[word] = wf;
                        }
                        dir[word].addFile(entry.path().filename().string());
                    }

                    file.close();
                }
            }

            fileAmount = counter;
        }

        /* GET FILES RELACIONADOS A LA PALABRA*/
        unordered_map<string, int> getRelatedFiles(string s){
            s = fixWord(s); //input validation
            return dir[s].getTable();
        }

        /*
        SEARCH:
            Busca palabra que buscamos en los files y calcula frecuencia en cada uno
            1. Añade primera palabra al mapa y todos los files al que aparece
            2. Recorre la frase y por cada palabra:
                2.1. Si la palabra no se encuentra en los files de la plabra anterior, elimina el file,
                sino va a sumar frecuencias
                2.2 Si el mapa termina vacio va a devolver un vector vacio
            3. Devuelve 3 files mas relevantes en un vector

            - Tambien funciona para busquedas de una sola palabra

            Implementacion utilizando unordered_map
        */
        vector<string> search(string p){ 
            string palabra;
            stringstream phrase(p);
            phrase >> palabra; // lee primera palabra
            palabra = fixWord(palabra); //input validation (anti-case sensitive)
            unordered_map<string, int> freq = getRelatedFiles(palabra); // añade primera palabra a mapa

            while(phrase >> palabra){ //para cada palabra de la frase:
                palabra = fixWord(palabra);
                unordered_map<string, int> k = getRelatedFiles(palabra);

                for(auto it = freq.begin(); it != freq.end(); ) { //recorre files a donde pertenece
                    if (k.find(it->first) == k.end()) { //si palabra se encuentra en file de palabra anterior
                        it = freq.erase(it);  // returns next iterator, elimina el file
                    } 
                    else {
                        it->second += k[it->first]; //suma frecuencias
                        ++it; //actualiza iterador
                    }
                    if (freq.empty()) return {}; //si mapa esta vacio devuelve vector vacio
                }

            }

            return sortSearch(freq); //devuelve 3 files mas relevantes
        }
};
