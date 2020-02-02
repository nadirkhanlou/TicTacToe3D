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

	public:
		TicTacToeState(unsigned int size);
		TicTacToeState(const TicTacToeState& other);
		TicTacToeState(TicTacToeState&& other);
		TicTacToeState(char* gameBoard, unsigned int size, int lastFill);
		~TicTacToeState();
		TicTacToeState& operator=(const TicTacToeState& other);
		TicTacToeState& operator=(TicTacToeState&& other);

		char Get(unsigned int idx);
		char Get(unsigned int i, unsigned int j, unsigned int k);
		int GetLastFill() const { return _lastFill; }
		unsigned int GetSize() const { return _n; }
		bool IsBlank(unsigned int index);
		void FillX(unsigned int index);
		void FillO(unsigned int index);
		void Unfill(unsigned int index);

		void Print();
	}; // class TicTacToeState
} // namespace TicTacToe
