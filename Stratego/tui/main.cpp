#include <iostream>
#include "tui.h"

using namespace std;
using namespace stratego;

int main()
{
    Game game {};
    View view {game};
    Controller controller {game, view};
    controller.start();
}
