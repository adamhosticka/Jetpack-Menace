#include <iostream>
#include <iomanip>

#include "CMenu.h"

using namespace std;

int main () {
    CMenu menu(cin, cout);

    menu.Run();

    return 0;
}
