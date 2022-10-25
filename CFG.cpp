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
    cout << "S = " << startingVariable << endl;
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
                s += " ";
                if (&m == &i["body"].back()){
                    s = s.substr(0, s.size()-1);
                }
            }
            productions[i["head"]].push_back(s);
        }
    }

    startingVariable = j["Start"];

    std::sort(variables.begin(), variables.end());
    std::sort(terminals.begin(), terminals.end());
    for (auto& i : productions){
        std::sort(i.second.begin(), i.second.end());
    }
}

void CFG::elimNull(){
    vector<string> nullables;
    for (const auto& i : this->productions){
        for (const auto& j : i.second){
            if (j.empty()){
                nullables.push_back(i.first);
                break;
            }
        }
    }
    for (const auto& i : nullables){
        cout << i;
        if (i != nullables.back()){
            cout << ',';
        }
        else{
            cout << '}' << endl;
        }
    }
    for (const auto& i : this->productions){
        for (const auto& j : nullables){
            if (i.first == j){
                vector<string> newProductions;
                for (const auto& k : i.second){
                    if (!k.empty()){
                        newProductions.push_back(k);
                        for (int l = 0; l < k.size(); l++){
                            for (const auto& m : nullables){
                                if (to_string(l) == m){
                                    string n = k;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CFG::toCNF() {
    cout << "Original CFG:" << endl << endl;
    this->print();
    cout << endl << endl << "-------------------------------------" << endl << endl;
    cout << " >> Eliminating epsilon productions" << endl;
    cout << "  Nullables are {";
    elimNull();
}

bool CFG::accepts(const string& input) {
    vector<vector<set<string>>> allIter;
    vector<set<string>> firstIter(input.size());
    for (int i = 0; i < input.size(); i++){
        for (const auto& j : productions){
            for (const auto& k : j.second){
                string s;
                s+=input[i];
                if (k == s){
                    firstIter[i].insert(j.first);
                }
            }
        }
    }
    allIter.push_back(firstIter);
    int n = input.size() - 1;
    while (n > 0){
        vector<set<string>> nextIter;
        for (int i = 0; i < n; i++){
            set<string> newEntry;
            if (allIter.size() == 1){
                set<string> vec1 = allIter[0][i];
                set<string> vec2 = allIter[0][i+1];
                for (auto s : vec1){
                    for (auto s2 : vec2){
                        string m = s + " " + s2;
                        for (auto production : productions){
                            for (auto rs : production.second){
                                if (m == rs){
                                    newEntry.insert(production.first);
                                    break;
                                }
                            }
                        }
                    }
                }
                nextIter.push_back(newEntry);
            }
            else{
                for (int p = 0; p < allIter.size(); p++){
                    set<string> vec1 = allIter[p][i];
                    set<string> vec2 = allIter[allIter.size()-p-1][p+i+1];
                    for (auto s : vec1){
                        for (auto s2 : vec2){
                            string m = s + " " + s2;
                            for (auto production : productions){
                                for (auto rs : production.second){
                                    if (m == rs){
                                        newEntry.insert(production.first);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                nextIter.push_back(newEntry);
            }
        }
        allIter.push_back(nextIter);
        n--;
    }
    bool result = false;
    for (const auto& i : allIter.back()[0]){
        if (i == this->startingVariable){
            result = true;
            break;
        }
    }
    vector<int> columnsizes(input.size(), 0);
    for (int i = 0; i < allIter.size(); i++){
        for (int j= 0; j < allIter[i].size(); j++){
            if (6 + 3*(allIter[i][j].size()-1) > columnsizes[j]){
                columnsizes[j] = 6 + 3*(allIter[i][j].size()-1) ;
            }
        }
    }
    for (int i = allIter.size()-1; i >= 0 ; i--){
        for (int j = 0; j < allIter[i].size(); j++){
            string column;
            vector<string> vset;
            for (auto s : allIter[i][j]){
                vset.push_back(s);
            }
            if (vset.empty()){
                cout << '|';
                column += " {}  ";
                while (column.size() < columnsizes[j]){
                    column += " ";
                }
            }
            else if (vset.size() == 1){
                cout << '|';
                column += " {" + vset[0] + "}  ";
                while (column.size() < columnsizes[j]){
                    column += " ";
                }
            }
            else{
                for (const auto& s : vset){
                    if (&s == &vset[0]){
                        cout << '|';
                        column += " {" + s + ", ";
                    }
                    else if (&s == &vset.back()){
                        column += s + "}  ";
                        while (column.size() < columnsizes[j]){
                            column += " ";
                        }
                    }
                    else{
                        column += s + ", ";
                    }
                }
            }
            cout << column;
        }
        cout << "|" << endl;
    }
    cout << boolalpha << result << endl;
    return result;
}
