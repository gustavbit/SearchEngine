#include "Directorio.hpp"

using namespace std;

int main() {

    int menuOp; // Create Repetiton Variable for the Menu Loop
    cout << "Welcome to Looky Search!\n";
    Directorio directorio(""); // Input path
    cout << "Directory Made!\n";
    
    // Menu Loop, its Repetition Condition is the menuOP not being -1.
    do {
        string searchPhrase = ""; // Create variable which holds Phrase/Word

        cout << "\nSearch: ";
        getline(cin, searchPhrase); // Asigns input to variable

        /*
        Create a vector which holds the result of the search funcition, which are files
        The files being the most relevant files that contain the searched word
        */
        vector<string> totalFiles = directorio.search(searchPhrase); 
        cout << '\n';

        // Display the files in vector                                                                
        if(totalFiles.size() != 0) cout << "The searched phrase/word is contained in:\n";
        else cout << "Found no files that contains phrase/word\n";

        for (int i = 0; i < totalFiles.size(); i++) {
            cout << (i + 1) << ". " << totalFiles[i] << endl;
        }

        if(0 < totalFiles.size() && totalFiles.size() < 3 ) cout << "Found only " << totalFiles.size() << " file" << (totalFiles.size() == 1)? 's' : ' ' <<'\n';

        cout << "\nIf you wish to make another search, enter 0.\n";
        cout << "If you wish to exit Looky Search, enter -1 (Default is 0)\n";
        cout << "Enter Selection: ";
        cin >> menuOp; // Recieves the users input to either make another search, or exit the program

        //Clears cin's \n for earlier getline to work
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


    } while (menuOp != -1);

    cout << "Thank you for using Looky Search!\n";

    return 0;
}