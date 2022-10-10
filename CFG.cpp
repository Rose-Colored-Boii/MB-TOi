//
// Created by liam on 3/10/22.
//

#include "CFG.h"

void CFG::print() const {
    cout << "V = {";
    for (int i = 0; i < variables.size(); i++){
        cout << variables[i];
        if (i != variables.size()-1){
            cout << ", ";
        }
    }
    cout << "}\nT = {";
    for (int i = 0; i < terminals.size(); i++){
        cout << terminals[i];
        if (i != terminals.size()-1){
            cout << ", ";
        }
    }
    cout << "}\nP = {\n";
    for (const auto& i : productions){
        for (const auto& j : i.second){
            cout << "    " << i.first << " -> " << '`' << j << '`' << endl;
        }
    }
    cout << "}\n";
    cout << "S = " << startingVariable;
}

CFG::CFG() {
    variables = {"BINDIGIT", "S"};
    terminals = {"0", "1", "a", "b"};
    productions["BINDIGIT"] = {"0", "1"};
    productions["S"] = {"", "a S b BINDIGIT"};
    startingVariable = "S";
}
