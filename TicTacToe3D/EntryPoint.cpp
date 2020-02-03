#include "TicTacToeSolver.h"
#include <iostream>

#define CONSOLE_APP

using namespace TicTacToe;

//If the configure type is .exe
#ifdef CONSOLE_APP
int main() {
    //char* c = "---------------------------";
    char* c = new char[28];
    std::cin >> c;
    TicTacToeState s(c, 3, -1);
    s.Print();
    //if (TicTacToeSolver::IsTerminal(s))
    //    std::cout << "yes!\n";
    TicTacToeSolver solver(s);
    int a = solver.FindBestActionMinimax();
    std::cout << a << "\n";
    return 0;
}
#endif // CONSOLE_APP

//If the configure type is .dll
#ifndef CONSOLE_APP
extern "C" __declspec(dllexport) int GetBestMoveMinimax(char* gameBoard, int gameSize, int lastFill)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    TicTacToeSolver solver(state);
    return solver.FindBestActionMinimax();
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
