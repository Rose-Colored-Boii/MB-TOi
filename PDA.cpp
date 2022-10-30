//
// Created by liam on 27/10/2022.
//

#include "PDA.h"

PDA::PDA(const string &filename) {
    ifstream input(filename);
    json j;
    input >> j;
    for (const auto& i : j["States"]){
        states.push_back(i);
    }
    for (const auto& i : j["Alphabet"]){
        alphabet.push_back(i);
    }
    for (const auto& i : j["StackAlphabet"]){
        stackAlphabet.push_back(i);
    }
    for (const auto& i : j["Transitions"]){
        string replacement;
        for (const auto& c : i["replacement"]){
            replacement += c;
        }
        transitions[{i["from"], i["input"], i["stacktop"]}] = {i["to"], replacement};
    }
    startState = j["StartState"];
    stack.push_back(j["StartStack"]);
}

CFG PDA::toCFG() {
    CFG cfg;
    vector<string> variables = {"S"};
    for (const auto& i : states){
        for (const auto& j : stackAlphabet){
            for (const auto& k : states){
                string s = "[" + i + "," + j + "," + k + "]";
                variables.push_back(s);
            }
        }
    }
    cfg.setVariables(variables);
    cfg.setStartingVariable("S");
    cfg.setTerminals(alphabet);
    map<string, vector<string>> productions;
    for (auto i : transitions){
        if (i.second[1].empty()){
            string leftside = "[" + i.first[0] + "," + i.first[2] + ",";
            leftside += i.second[0] + "]";
            productions[leftside].push_back(i.first[1]);
        }
        else{
            for (const auto& j : states){
                string leftside = "[" + i.first[0] + "," + i.first[2] + ",";
                leftside += j + "}";
                string rightside = i.first[1] + " " + "[" + leftside[1];
                for (auto k : i.second[1]){
                    rightside += k;
                    if (&k == &i.second[1][i.second[1].size()-1]){
                        rightside += leftside[3] + "}";
                        productions[leftside].push_back(rightside);
                    }
                    else{
                        for (auto l : states){
                            string temp = rightside;

                        }
                    }
                }
            }
        }
    }
    cfg.setProductions(productions);
    return cfg;
}
