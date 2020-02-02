#include "TicTacToeSolver.h"

//#define CONSOLE_APP

using namespace TicTacToe;

//If the configure type is .exe
#ifdef CONSOLE_APP
int main() {
    return 0;
}
#endif // CONSOLE_APP

//If the configure type is .dll
#ifndef CONSOLE_APP
extern "C" __declspec(dllexport) int GetBestMoveMiniMax(char* gameBoard, int gameSize, int lastFill)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    TicTacToeSolver solver(state);
    return solver.FindBestActionMiniMax();
}
extern "C" __declspec(dllexport) int GetBestMoveAlphaBeta(char* gameBoard, int gameSize, int lastFill)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    TicTacToeSolver solver(state);
    return solver.FindBestActionAlphaBeta();
}
extern "C" __declspec(dllexport) bool IsTerminal(char* gameBoard, int gameSize, int lastFill)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    return TicTacToeSolver::IsTerminal(state);
}
#endif // !CONSOLE_APP
