#include <SFML/Graphics.hpp>
#include "ChessGameGUI.hpp"

int main() {
    ChessGameGUI new_game;
    new_game.MainGameLoop();
    return 0;
}


// int main() {
//   ChessGame* game = new ChessGame();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->undo();
//   game->Print();
//   game->move({{1, 2}, {3, 2}});
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->MakeCPUMove();
//   game->Print();
//   game->move({6, 1}, {4, 1});
//   game->Print();
//   game->move({{3, 2}, {4, 1}});
//   game->Print();
//   game->move({6, 2}, {5, 2});
//   game->Print();
//   game->move({1, 1}, {3, 1});
//   game->Print();
//   game->move({5, 2}, {4, 1});
//   game->Print();
//   game->move({1, 0}, {3, 0});
//   game->Print();
//   game->move({4, 1}, {3, 0});
//   game->Print();
//   game->move({0, 0}, {2, 0});
//   game->Print();
//   game->move({6, 0}, {4, 0});
//   game->Print();
//   game->move({2, 0}, {0, 0});
//   game->Print();
//   game->move({7, 2}, {6, 1});
//   game->Print();
//   game->move({0, 1}, {2, 2});
//   game->Print();
//   game->move({6, 3}, {4, 3});
//   game->Print();
//   game->move({1, 3}, {3, 3});
//   game->Print();
//   game->move({7, 4}, {4, 1});
//   game->Print();
//   game->move({2, 2}, {4, 1});
//   game->Print();
//   return 0;
// }
