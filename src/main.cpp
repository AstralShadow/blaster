#include "globals.hpp"
#include "init.hpp"
#include "core.hpp"

#include "version.hpp"
#include <iostream>

using std::cout;
using std::endl;


int main(int, char**)
{
    cout << "Initializing..." << endl;
    init();

    cout << "Running " << PROJECT_NAME << ' '
         << VERSION_MAJOR << '.' << VERSION_MINOR << endl;

    run();

    cout << "Closing " << PROJECT_NAME << ' '
         << VERSION_MAJOR << '.' << VERSION_MINOR << endl;

    deinit();

    return 0;
}

