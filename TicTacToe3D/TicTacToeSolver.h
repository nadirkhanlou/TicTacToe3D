#pragma once
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
		int Utility(State& state, int* hint = nullptr);
		int FindBestActionMiniMax();
		int FindBestActionAlphaBeta();
		int MiniMax(State state, int action, bool isPlayerMax);


	}; // class TicTacToeSolver
} // namespace TicTacToe
