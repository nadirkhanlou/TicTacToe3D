#pragma once

#include <iostream>
#include <iterator>

namespace TicTacToe {
	class TicTacToeState
	{
	private:
		unsigned int _n;
		char* _gameBoard;
		int _lastFill;

		~TicTacToeState();
	public:
		TicTacToeState(unsigned int size);
		TicTacToeState(const TicTacToeState& other);
		TicTacToeState(TicTacToeState&& other);
		TicTacToeState(char* gameBoard, unsigned int size);
		TicTacToeState& operator=(const TicTacToeState& other);
		TicTacToeState& operator=(TicTacToeState&& other);

		char Get(unsigned int idx);
		char Get(unsigned int i, unsigned int j, unsigned int k);
		void Print();
	}; // class TicTacToeState
} // namespace TicTacToe
