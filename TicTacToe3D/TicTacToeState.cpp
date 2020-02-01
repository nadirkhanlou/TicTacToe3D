#include "TicTacToeState.h"

namespace TicTacToe {
	TicTacToeState::TicTacToeState(unsigned int size) : _n(size), _lastFill(-1)
	{
		this->_gameBoard = new char[_n * _n * _n];
		for (unsigned int i = 0; i < _n * _n * _n; ++i)
		{
			this->_gameBoard[i] = '-';
		}
	}

	TicTacToeState::TicTacToeState(const TicTacToeState& other)
		: _n(other._n), _lastFill(other._lastFill)
	{
		this->_gameBoard = new char[_n * _n * _n];
		for (unsigned int i = 0; i < _n * _n * _n; ++i)
		{
			this->_gameBoard[i] = other._gameBoard[i];
		}
	}

	TicTacToeState::TicTacToeState(TicTacToeState&& other)
		: _n(other._n), _lastFill(other._lastFill)
	{
		this->_gameBoard = other._gameBoard;
		other._gameBoard = nullptr;
	}

	TicTacToeState& TicTacToeState::operator=(const TicTacToeState& other)
	{
		this->_n = other._n;
		this->_lastFill = other._lastFill;
		delete[] this->_gameBoard;
		this->_gameBoard = new char[_n * _n * _n];
		for (unsigned int i = 0; i < _n * _n * _n; ++i)
		{
			this->_gameBoard[i] = other._gameBoard[i];
		}
	}

	TicTacToeState& TicTacToeState::operator=(TicTacToeState&& other)
	{
		this->_n = other._n;
		this->_lastFill = other._lastFill;
		delete[] this->_gameBoard;
		this->_gameBoard = other._gameBoard;
		other._gameBoard = nullptr;
	}

	char TicTacToeState::Get(unsigned int idx)
	{
		if (idx >= _n * _n * _n)
		{
			return '/0';
		}
		return _gameBoard[idx];
	}

	char TicTacToeState::Get(unsigned int i, unsigned int j, unsigned int k)
	{
		return Get(i * _n * _n + j * _n + k);
	}

	void TicTacToeState::Print()
	{
		std::ostream_iterator<char> outIt(std::cout, " ");
		for (unsigned int j = 0; j < _n; ++j)
		{
			for (unsigned int i = 0; i < _n; i++)
			{
				std::copy(_gameBoard + i * _n * _n + j * _n, _gameBoard + i * _n * _n + j * _n + _n, outIt);
				std::cout << '\t';
			}
			std::cout << '\n';
		}
	}

} // namespace TicTacToe

