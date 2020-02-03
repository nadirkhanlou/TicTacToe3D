#pragma once

#include <vector>
#include <algorithm>

#include "TicTacToeState.h"

namespace TicTacToe {

	typedef TicTacToeState State;

	class TicTacToeSolver {
	private:
		State* _state;
		bool _isXTurn;
	public:
		TicTacToeSolver(State& state);
		~TicTacToeSolver();

		static bool IsTerminal(State& state);
		static bool IsTerminal(State& state, int*& hint);
		static int HighetWinningPotentialHeuristic(State& state, bool isXTurn);
		static int LeastLosingPotentialHeuristic(State& state, bool isXTurn);
		static int PotentialSubtractionHeuristic(State& state, bool isXTurn);
		static int WinningPotentialCount(State& state, bool isXTurn, int indx);
		static bool TerminalCheck(State& state);
		int Utility(State& state, int* hint = nullptr);
		int FindBestActionMinimax();
		int FindBestActionAlphaBeta();
		int Minimax(State& state, int action, bool isPlayerMax, int depth = INT32_MAX);
		int AlphaBeta(State& state, int action, bool isPlayerMax, int alpha, int beta, int depth = INT32_MAX);


	}; // class TicTacToeSolver
} // namespace TicTacToe
