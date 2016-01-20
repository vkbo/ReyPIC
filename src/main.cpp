/**
 * ReyPIC – Main File
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

#include "build.hpp"
#include "config.hpp"
#include "clsSpecies.hpp"

using namespace std;
using namespace reypic;

int main(int argc, char* argv[]) {

    cout << endl;
    cout << "  ReyPIC  " << endl;
    cout << "**********" << endl;
    cout << endl;
    cout << "  Version: " << VERSION << "-R" << REVISION << endl;
    cout << "  Build:   " << BUILD_NO+1 << endl;
    cout << "  Date:    " << BUILD_DATE << endl;
    cout << endl;

    return 0;
}
