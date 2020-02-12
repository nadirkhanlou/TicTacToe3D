#include "TicTacToeState.h"

namespace TicTacToe {
	TicTacToeState::TicTacToeState(unsigned int size) : _n(size), _lastFill(-1), _branchFactor(size * size * size)
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
		_branchFactor = other._branchFactor;
	}

	TicTacToeState::TicTacToeState(TicTacToeState&& other)
		: _n(other._n), _lastFill(other._lastFill), _branchFactor(other._branchFactor)
	{
		this->_gameBoard = other._gameBoard;
		other._gameBoard = nullptr;
	}

	TicTacToeState::TicTacToeState(char* gameBoard, unsigned int size, int lastFill)
		:_n(size), _lastFill(lastFill)
	{
		_gameBoard = gameBoard;
		_branchFactor = 0;
		for (int i = 0; i < size * size * size; ++i)
			if (gameBoard[i] == '-')
				_branchFactor++;
	}

	TicTacToeState& TicTacToeState::operator=(const TicTacToeState& other)
	{
		this->_n = other._n;
		this->_lastFill = other._lastFill;
		this->_branchFactor = other._branchFactor;
		delete[] this->_gameBoard;
		this->_gameBoard = new char[_n * _n * _n];
		for (unsigned int i = 0; i < _n * _n * _n; ++i)
		{
			this->_gameBoard[i] = other._gameBoard[i];
		}
		return *this;
	}

	TicTacToeState& TicTacToeState::operator=(TicTacToeState&& other)
	{
		this->_n = other._n;
		this->_lastFill = other._lastFill;
		this->_branchFactor = other._branchFactor;
		delete[] this->_gameBoard;
		this->_gameBoard = other._gameBoard;
		other._gameBoard = nullptr;
		return *this;
	}

	TicTacToeState::~TicTacToeState()
	{
		delete[] this->_gameBoard;
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

	bool TicTacToeState::IsBlank(unsigned int index)
	{
		if (index >= _n * _n * _n)
		{
			return false;
		}
		return _gameBoard[index] == '-';
	}

	void TicTacToeState::FillX(unsigned int index)
	{
		if (index >= _n * _n * _n)
		{
			return;
		}
		_gameBoard[index] = 'X';
		_lastFill = index;
		_branchFactor--;
	}

	void TicTacToeState::FillO(unsigned int index)
	{
		if (index >= _n * _n * _n)
		{
			return;
		}
		_gameBoard[index] = 'O';
		_lastFill = index;
		_branchFactor--;
	}

	void TicTacToeState::Unfill(unsigned int index, int prevLastFill)
	{
		if (index >= _n * _n * _n)
		{
			return;
		}
		_gameBoard[index] = '-';
		_lastFill = prevLastFill;
		_branchFactor++;
	}

	void TicTacToeState::Print()
	{
		std::ostream_iterator<char> outIt(std::cout, " ");
		std::cout << "(" << _lastFill / (_n * _n) << ", " << _lastFill % (_n * _n) << ")\n";
		for (unsigned int j = 0; j < _n; ++j)
		{
			for (unsigned int i = 0; i < _n; i++)
			{
				std::copy(_gameBoard + i * _n * _n + j * _n, _gameBoard + i * _n * _n + j * _n + _n, outIt);
				std::cout << '\t';
			}
			std::cout << '\n';
		}
		for (unsigned int j = 0; j < _n * _n * _n; ++j)
			std::cout << _gameBoard[j];
		std::cout << '\n';
	}

} // namespace TicTacToe

