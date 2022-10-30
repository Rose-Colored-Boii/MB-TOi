#include <iostream>
#include "CFG.h"
#include "PDA.h"
using namespace std;

int main() {
    CFG cfg("input.json");
    cfg.ll();
    return 0;
}
