#include "TicTacToeSolver.h"
#include <iostream>
#include <fstream>

//#define CONSOLE_APP

using namespace TicTacToe;

//If the configure type is .exe
#ifdef CONSOLE_APP
int main() {
    //char* c = "------O-----O-----O--------";
    //char* c = "-------O-----O-----O-------";
    //char* c = "--O-------O-------O--------";
    //char* c = "-----O-------O-------O-----";
    int size = 3;
    char* c = new char[size * size * size];
    for (int i = 0; i < size * size * size; ++i) {
        c[i] = '-';
    }
    std::cin >> c;
    TicTacToeState s(c, size, 2);

    TicTacToeSolver solver(s);

    s.Print();

    if (solver.IsTerminal(s))
        std::cout << "true\n";

    return 0;
    for (int i = 0; i < size * size * size; i++) {
        if (s.IsBlank(i)) {
            s.FillX(i);
            if (solver.IsTerminal(s)) {
                std::cout << "ok\n";
                s.Print();
                std::cout << "\n";
            }
            s.Unfill(i, -1);
        }
    }
    for (int i = 0; i < size * size * size; i++) {
        if (s.IsBlank(i)) {
            s.FillO(i);
            if (solver.IsTerminal(s)) {
                std::cout << "ok\n";
                s.Print();
                std::cout << "\n";
            }
            s.Unfill(i, -1);
        }
    }
    bool terminated = false;
    bool isXTurn = false;

    return 0;
    while (!terminated) {
        s.Print();
        std::cout << "\n";
        solver.SetTurn(isXTurn);
        int a;

        a = solver.FindBestActionAlphaBeta();

        isXTurn ? s.FillX(a) : s.FillO(a);
        std::cout << "action = " << a << "\n";
        isXTurn = !isXTurn;
        std::cout << "\n";
        if (TicTacToeSolver::IsTerminal(s)) {
            terminated = true;
        }
    }
    s.Print();
    std::cout << solver.nodesExpanded << "\n";
    return 0;
}

int main1() {
    //char* c = "OX-XXX-X------O-O-X-XXOOO-O--OO-----OX-O-XOXXXX--------O------O-X";
    int size = 3;
    char* c = new char[size * size * size];
    for (int i = 0; i < size * size * size; ++i) {
        c[i] = '-';
    }

    TicTacToeState s(c, size, -1);

    TicTacToeSolver solver(s);

    
    bool terminated = false;
    bool isXTurn = false;

    while (!terminated) {
        s.Print();
        std::cout << "\n";
        solver.SetTurn(isXTurn);
        int a;

        if (isXTurn)
            a = solver.FindBestActionAlphaBeta();
        else
            std::cin >> a;

        isXTurn ? s.FillX(a) : s.FillO(a);
        std::cout << "action = " << a << "\n";
        isXTurn = !isXTurn;
        std::cout << "\n";
        if (TicTacToeSolver::IsTerminal(s)) {
            terminated = true;
        }
    }
    s.Print();
    std::cout << solver.nodesExpanded << "\n";
    return 0;
}

#endif // CONSOLE_APP

//If the configure type is .dll
#ifndef CONSOLE_APP
extern "C" __declspec(dllexport) bool test(char gameBoard[]) {
    return gameBoard[0] == '-';
}
extern "C" __declspec(dllexport) int GetBestMoveMinimax(char* gameBoard, int gameSize, int lastFill, int length)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    TicTacToeSolver solver(state);
    solver.SetTurn(state.GetLastFill() != 'X');
    solver.SetTimer(length);
    return solver.FindBestActionMinimax();
}
extern "C" __declspec(dllexport) int GetBestMoveAlphaBeta(char* gameBoard, int gameSize, int lastFill, int length)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    TicTacToeSolver solver(state);
    solver.SetTurn(state.GetLastFill() != 'X');
    solver.SetTimer(length);
    return solver.FindBestActionAlphaBeta();
}
extern "C" __declspec(dllexport) bool IsTerminal(char* gameBoard, int gameSize, int lastFill)
{
    TicTacToeState state(gameBoard, gameSize, lastFill);
    return TicTacToeSolver::IsTerminal(state);
}
#endif // !CONSOLE_APP
