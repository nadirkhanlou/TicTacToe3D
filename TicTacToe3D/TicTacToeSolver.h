#pragma once

#include <vector>
#include <algorithm>
#include <set>
#include <chrono>

#include "TicTacToeState.h"

namespace TicTacToe {

	typedef TicTacToeState State;

	class TicTacToeSolver {
	private:
		State* _state;
		bool _isXTurn;
		std::chrono::steady_clock::time_point _time0;
		int _timerLength;
		
		
	public:
		int nodesExpanded = 0;
		TicTacToeSolver(State& state);
		~TicTacToeSolver();

		static bool IsTerminal(State& state);
		static bool IsTerminal(State& state, int*& hint);
		static int HighetWinningPotentialHeuristic(State& state, bool isXTurn);
		static int LeastLosingPotentialHeuristic(State& state, bool isXTurn);
		static int PotentialSubtractionHeuristic(State& state, bool isXTurn);
		static int WinningPotentialCount(State& state, int indx, char opponentChar, std::set<std::vector<int>>& potentialSet);
		static bool TerminalCheck(State& state);
		int Utility(State& state, bool isPlayerMax, int* hint = nullptr);
		int FindBestActionMinimax();
		int FindBestActionAlphaBeta();
		int Minimax(State& state, int action, bool isPlayerMax, int depth = INT32_MAX, bool debugPar = false);
		int AlphaBeta(State& state, int action, bool isPlayerMax, int alpha = INT32_MIN, int beta = INT32_MAX, int depth = INT32_MAX);
		void SetTurn(bool isXTurn);
		void SetTimer(int length);

	}; // class TicTacToeSolver
} // namespace TicTacToe
