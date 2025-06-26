// repl.cpp
#include <map>           // für std::map
#include <sstream>       // für std::istringstream und std::ostringstream
#include <iostream>
#include <string>
using namespace std;

// Function declarations to avoid including arithmetic.cpp
float evaluate_infix(std::string inp);

//wenn set merken für namen wenn zahl rechnen wenn vorher set speichern
int main() {
    cout << "*** Sokrates ***" << endl;

    map<string, float> variables;
    string pending_var;

    while (true) {
        string input;
        cout << "Was soll ich tun? ";
        getline(cin, input);

        if(!getline(cin,input)) break; //wenn kein Input verfügbar
        if(input.empty()) continue; //leere Zeile

        if(input.empty()) continue; //leere Zeile

        // Check for variable assignment
        //hab hier alles nach set in varname extrahiert und prüfe ob das nicht leer ist
        if (input.rfind("set ", 0) == 0) {
            string varname = input.substr(4);
            if (varname.empty()) {
                cerr << "Fehler: Variablenname erwartet nach 'set'" << endl;
                continue;
            }
            pending_var = varname;
            continue;
        }


        // Replace variables with their values
        istringstream iss(input);
        ostringstream modified;
        string token;

        while (iss >> token) {
            if (variables.count(token)) {
                modified << variables[token];
            } else {
                modified << token;
            }
            modified << " ";
        }

        try {
            float result = evaluate_infix(modified.str());

            if (!pending_var.empty()) {
                variables[pending_var] = result;
                pending_var = "";
                cout << "🔨 Variable definiert als: " << result << endl;

            }
            else {
                cout << "🤓: " << result << endl;
            }


        } catch (const exception& e) {
            cerr << "Fehler: " << e.what() << endl;
        }
    }
    return 0;
}
