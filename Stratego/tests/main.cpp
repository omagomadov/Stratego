/**
 * Runs this file to run the tests.
 * <p>
 * The <code>main</code> function is defined in the catch.hpp header
 */

#define CATCH_CONFIG_RUNNER
#include "Catch.h"
#define RUN_TEST 1 //change this value

#if RUN_TEST
int main(int argc, char* const argv [])
{
    Catch::Session().run(argc, argv);
}
#else
#include <iostream>
using namespace std;

int main()
{
    cout << "Regular main" << endl;
}
#endif
