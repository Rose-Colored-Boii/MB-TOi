#include <iostream>
#include "CFG.h"

using namespace std;

int main() {
    CFG cfg("input.json");
    cfg.accepts("baaba"); //moet true geven
    cfg.accepts("abba"); //moet false geven
    return 0;
}
