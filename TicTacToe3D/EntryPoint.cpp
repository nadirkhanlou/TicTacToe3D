#include "TicTacToeSolver.h"
#include <iostream>
#include <fstream>

#define CONSOLE_APP

using namespace TicTacToe;

//If the configure type is .exe
#ifdef CONSOLE_APP
int main() {
    //char* c = "OOO------------------------";
    int size = 3;
    char* c = new char[size * size * size];
    for (int i = 0; i < size * size * size; ++i) {
        c[i] = '-';
    }
    TicTacToeState s(c, size, -1);

    /*std::cin >> c;
    s.Print();
    if (TicTacToeSolver::IsTerminal(s))
        std::cout << "yes!\n";
    return 0;*/

    TicTacToeSolver solver(s);
    
    bool terminated = false;
    bool isXTurn = false;
    while (!terminated) {
        s.Print();
        std::cout << "\n";
        solver.SetTurn(isXTurn);
        int a = solver.FindBestActionAlphaBeta();
        isXTurn ? s.FillX(a) : s.FillO(a);
        std::cout << "action = " << a << "\n";
        isXTurn = !isXTurn;
        std::cout << "\n";
        if (TicTacToeSolver::IsTerminal(s)) {
            terminated = true;
        }
            
    }
    s.Print();
    return 0;
}
#endif // CONSOLE_APP

//If the configure type is .dll
#ifndef CONSOLE_APP
extern "C" __declspec(dllexport) bool test(char gameBoard[]) {
    return gameBoard[0] == '-';
}
extern "C" __declspec(dllexport) int GetBestMoveMinimax(char* gameBoard, int gameSize, int lastFill)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    TicTacToeSolver solver(state);
    solver.SetTurn(state.GetLastFill() != 'X');
    return solver.FindBestActionMinimax();
}
extern "C" __declspec(dllexport) int GetBestMoveAlphaBeta(char* gameBoard, int gameSize, int lastFill)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    TicTacToeSolver solver(state);
    solver.SetTurn(state.GetLastFill() != 'X');
    return solver.FindBestActionAlphaBeta();
}
extern "C" __declspec(dllexport) bool IsTerminal(char* gameBoard, int gameSize, int lastFill)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    return TicTacToeSolver::IsTerminal(state);
}
#endif // !CONSOLE_APP
