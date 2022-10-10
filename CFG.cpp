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

CFG::CFG(const string &filename) {
    ifstream input(filename);
    json j;
    input >> j;

    for (const auto& i : j["Variables"]){
        variables.push_back(i);
    }

    for (const auto& i : j["Terminals"]){
        terminals.push_back(i);
    }

    for (const auto& i : j["Productions"]){
        if (i["body"].empty()){
            productions[i["head"]].push_back("");
        }
        else{
            string s;
            for (const auto& m : i["body"]){
                s += m;
                if (m != i["body"].back()){
                    s += " ";
                }
            }
            productions[i["head"]].push_back(s);
        }
    }

    startingVariable = j["Start"];
}
