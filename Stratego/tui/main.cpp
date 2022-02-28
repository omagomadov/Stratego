#include <iostream>
#include "tui.h"

using namespace std;

int main()
{
    Game game {};
    View view {game};
    Controller controller {game, view};
    view.displayPlayer();
    view.askDirection();
    view.askPosition();
    view.displayBoard();
}
