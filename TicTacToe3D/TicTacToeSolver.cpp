#include "TicTacToeSolver.h"
#include <math.h>

namespace TicTacToe {

	// Utility argmin and argmax functions. Source: http://www.jclay.host/dev-journal/simple_cpp_argmax_argmin.html
	template <typename T, typename A>
	int arg_max(std::vector<T, A> const& vec) {
		return static_cast<int>(std::distance(vec.begin(), max_element(vec.begin(), vec.end())));
	}

	template <typename T, typename A>
	int arg_min(std::vector<T, A> const& vec) {
		return static_cast<int>(std::distance(vec.begin(), min_element(vec.begin(), vec.end())));
	}

	TicTacToeSolver::TicTacToeSolver(State& state)
	{
		_state = &state;
		_isXTurn = _state->Get(_state->GetLastFill()) == 'O' ? true : false;
		_timerLength = INT32_MAX;
		int size = state.GetSize();
	}

	TicTacToeSolver::~TicTacToeSolver()
	{
	}

	bool TicTacToeSolver::IsTerminal(State& state)
	{
		int size = state.GetSize();

		int indx = state.GetLastFill();
		char lastFill = state.Get(indx);
		int counter = 0;

		bool isTerminal = true;
		int j = indx - (indx % size);
		for (j; j < size * size * size && counter < size; j += 1, counter++) {
			if (state.Get(j) != lastFill) {
				isTerminal = false;
				break;
			}
		}

		if (isTerminal)
			return true;
		//std::cout << "1\n";
		isTerminal = true;
		counter = 0;
		j = indx - (((indx / size) % size) * size);
		for (j; j < size * size * size && counter < size; j += size, counter++) {
			if (state.Get(j) != lastFill) {
				isTerminal = false;
				break;
			}
		}

		if (isTerminal)
			return true;
		//std::cout << "2\n";
		isTerminal = true;
		counter = 0;
		j = indx % (size * size);
		for (j; j < size * size * size && counter < size; j += size * size, counter++) {
			if (state.Get(j) != lastFill) {
				isTerminal = false;
				break;
			}
		}

		
		if ((indx % (size * size)) % (size + 1) == 0) {
			if (isTerminal)
				return true;
			//std::cout << "3\n";
			isTerminal = true;
			counter = 0;
			j = indx - (indx % (size * size));
			for (j; j < size * size * size && counter < size; j += size + 1, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if ((indx % (size * size)) % (size - 1) == 0) {
			if (isTerminal)
				return true;
			//std::cout << "4\n";
			isTerminal = true;
			counter = 0;
			j = (indx - (indx % (size * size))) + size - 1;
			for (j; j < size * size * size && counter < size; j += size - 1, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if (indx / (size * size) == (indx % (size * size) / size)) {
			if (isTerminal)
				return true;
			//std::cout << "5\n";
			isTerminal = true;
			counter = 0;
			j = indx % size;
			for (j; j < size * size * size && counter < size; j += size * size + size, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if (indx / (size * size) == (size - (indx % (size * size)) / size)) {
			if (isTerminal)
				return true;
			//std::cout << "6\n";
			isTerminal = true;
			counter = 0;
			j = (size * size) - (size - (indx % size) - 1);
			for (j; j < size * size * size && counter < size; j += size * size - size, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if (indx / (size * size) == (indx % size)) {
			if (isTerminal)
				return true;
			//std::cout << "7\n";
			isTerminal = true;
			counter = 0;
			j = ((indx % (size * size)) / size) * size;
			for (j; j < size * size * size && counter < size; j += size * size + 1, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if (indx / (size * size) == ((size - indx) % size)) {
			if (isTerminal)
				return true;
			//std::cout << "8\n";
			isTerminal = true;
			counter = 0;
			j = ((indx % (size * size)) / size) * size + size - 1;
			for (j; j < size * size * size && counter < size; j += size * size - 1, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}


		if (indx / (size * size) == indx % size && indx % size == (indx % (size * size)) / size) {
			if (isTerminal)
				return true;
			//std::cout << "9\n";
			isTerminal = true;
			counter = 0;
			j = 0;
			for (j; j < size * size * size && counter < size; j += size * size + size + 1, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if (indx / (size * size) == indx % size && size - (indx % size) - 1 == (indx % (size * size)) / size) {
			if (isTerminal)
				return true;
			//std::cout << "10\n";
			isTerminal = true;
			counter = 0;
			j = size - 1;
			for (j; j < size * size * size && counter < size; j += size * size + size - 1, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if (indx / (size * size) == (indx % size) && size - (indx / (size * size) == (indx % (size * size)) / size) - 1) {
			if (isTerminal)
				return true;
			//std::cout << "11\n";
			isTerminal = true;
			counter = 0;
			j = size * size - size;
			for (j; j < size * size * size && counter < size; j += size * size - size + 1, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if (indx / (size * size) == size - (indx % size) - 1 && size - (indx % size) - 1 == (indx % (size * size)) / size) {
			if (isTerminal)
				return true;
			//std::cout << "12\n";
			isTerminal = true;
			counter = 0;
			j = size * size - 1;
			for (j; j < size * size * size && counter < size; j += size * size - size - 1, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if ((size - 1 - (indx / (size * size))) == (indx % (size * size)) / size) {
			if (isTerminal)
				return true;
			//std::cout << "13\n";
			isTerminal = true;
			counter = 0;
			j = size * size - (size - (indx % size));
			for (j; j < size * size * size && counter < size; j += size * size - size, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if (indx % size == (size - 1 - (indx / (size * size)))) {
			if (isTerminal)
				return true;
			isTerminal = true;
			counter = 0;
			j = (indx % (size* size)) + (indx / (size * size));
			for (j; j < size * size * size && counter < size; j += size * size - 1, counter++) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		return isTerminal;
	}

	bool TicTacToeSolver::IsTerminal(State& state, int*& hint)
	{
		return false;
	}

	int TicTacToe::TicTacToeSolver::HighetWinningPotentialHeuristic(State& state, bool isXTurn)
	{
		int size = state.GetSize();

		char playerChar = isXTurn ? 'X' : 'O';
		char opponentChar = isXTurn ? 'O' : 'X';

		std::set<std::vector<int>> potentialSet = std::set<std::vector<int>>();
		for (int i = 0; i < size * size * size ; ++i) {
			if (state.Get(i) == playerChar)
				WinningPotentialCount(state, i, opponentChar, potentialSet);
		}

		return potentialSet.size();
	}

	int TicTacToeSolver::LeastLosingPotentialHeuristic(State& state, bool isXTurn)
	{
		return 0;
	}

	int TicTacToeSolver::PotentialSubtractionHeuristic(State& state, bool isXTurn)
	{
		return 0;
	}

	int TicTacToeSolver::WinningPotentialCount(State& state, int indx, char opponentChar, std::set<std::vector<int>>& potentialSet)
	{
		int size = state.GetSize();
		int counter = 0;

		bool opponentExists = false;
		int j = indx - (indx % size);
		std::vector<int> path = std::vector<int>();
		for (j; j < size * size * size && counter < size; j += 1, counter++) {
			if (state.Get(j) == opponentChar) {
				opponentExists = true;
			}
			path.push_back(j);
		}
		if (!opponentExists)
			potentialSet.emplace(path);

		opponentExists = true;
		counter = 0;
		j = indx - (((indx / size) % size) * size);
		path = std::vector<int>();
		for (j; j < size * size * size && counter < size; j += size, counter++) {
			if (state.Get(j) == opponentChar) {
				opponentExists = true;
			}
			path.push_back(j);
		}
		if (!opponentExists)
			potentialSet.emplace(path);

		opponentExists = false;
		counter = 0;
		j = indx % (size * size);
		path = std::vector<int>();
		for (j; j < size * size * size && counter < size; j += size * size, counter++) {
			if (state.Get(j) == opponentChar) {
				opponentExists = true;
			}
			path.push_back(j);
		}
		if (!opponentExists)
			potentialSet.emplace(path);

		if ((indx % (size * size)) % (size + 1) == 0) {
			opponentExists = false;
			counter = 0;
			path = std::vector<int>();
			j = indx - (indx % (size * size));
			for (j; j < size * size * size && counter < size; j += size + 1, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}

		if ((indx % (size * size)) % (size - 1) == 0) {
			opponentExists = false;
			counter = 0;
			path = std::vector<int>();
			j = (indx - (indx % (size * size))) + size - 1;
			for (j; j < size * size * size && counter < size; j += size - 1, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}

		if (indx / (size * size) == (indx % (size * size) / size)) {
			opponentExists = false;
			counter = 0;
			path = std::vector<int>();
			j = indx % size;
			for (j; j < size * size * size && counter < size; j += size * size + size, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}

		if (indx / (size * size) == (size - (indx % (size * size)) / size)) {
			opponentExists = false;
			counter = 0;
			path = std::vector<int>();
			j = (size * size) - (size - (indx % size) - 1);
			for (j; j < size * size * size && counter < size; j += size * size - size, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}

		if (indx / (size * size) == (indx % size)) {
			opponentExists = false;
			counter = 0;
			j = ((indx % (size * size)) / size) * size;
			path = std::vector<int>();
			for (j; j < size * size * size && counter < size; j += size * size + 1, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}

		if (indx / (size * size) == ((size - indx) % size)) {
			opponentExists = false;
			counter = 0;
			j = ((indx % (size * size)) / size) * size + size - 1;
			path = std::vector<int>();
			for (j; j < size * size * size && counter < size; j += size * size - 1, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}


		if (indx / (size * size) == indx % size && indx % size == (indx % (size * size)) / size) {
			opponentExists = false;
			counter = 0;
			j = 0;
			path = std::vector<int>();
			for (j; j < size * size * size && counter < size; j += size * size + size + 1, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}

		if (indx / (size * size) == indx % size && size - (indx % size) - 1 == (indx % (size * size)) / size) {
			opponentExists = false;
			counter = 0;
			j = size - 1;
			path = std::vector<int>();
			for (j; j < size * size * size && counter < size; j += size * size + size - 1, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}

		if (indx / (size * size) == size - (indx % size) - 1 && indx % size == (indx % (size * size)) / size) {
			opponentExists = false;
			counter = 0;
			j = size * size - size;
			path = std::vector<int>();
			for (j; j < size * size * size && counter < size; j += size * size - size + 1, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}

		if (indx / (size * size) == size - (indx % size) - 1 && size - (indx % size) - 1 == (indx % (size * size)) / size) {
			opponentExists = false;
			counter = 0;
			j = size * size - 1;
			path = std::vector<int>();
			for (j; j < size * size * size && counter < size; j += size * size - size - 1, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}
		
		if ((size - 1 - (indx / (size * size))) == (indx % (size * size)) / size) {
			opponentExists = false;
			counter = 0;
			j = size * size - (size - (indx % size));
			path = std::vector<int>();
			for (j; j < size * size * size && counter < size; j += size * size - size, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}

		if (indx % size == (size - 1 - (indx / (size * size)))) {
			opponentExists = false;
			counter = 0;
			j = (indx % (size * size)) + (indx / (size * size));
			path = std::vector<int>();
			for (j; j < size * size * size && counter < size; j += size * size - 1, counter++) {
				if (state.Get(j) == opponentChar) {
					opponentExists = true;
				}
				path.push_back(j);
			}
			if (!opponentExists)
				potentialSet.emplace(path);
		}
	}

	bool TicTacToeSolver::TerminalCheck(State& state)
	{
		return false;
	}

	int TicTacToeSolver::Utility(State& state, bool isPlayerMax, int* hint)
	{
		//
		return false;
	}

	int TicTacToeSolver::FindBestActionMinimax()
	{	
		_time0 = std::chrono::high_resolution_clock::now();
		int n = _state->GetSize();
		int max = INT32_MIN;
		int argMax = -1;
		int depth = 1;
		if (_state->GetBranchFactor() < 32)
			depth = 2;
		if (_state->GetBranchFactor() < 23)
			depth = 3;
		if (_state->GetBranchFactor() < 18)
			depth = 4;
		if (_state->GetBranchFactor() < 15)
			depth = 5;
		if (_state->GetBranchFactor() < 10)
			depth = 7;
		if (_state->GetBranchFactor() < 5)
			depth = 10;
		
		for (unsigned int idx = 0; idx < n * n * n; ++idx)
		{
			if (_state->IsBlank(idx))
			{
				int res = Minimax(*_state, idx, false, depth, true);
				//std::cout << idx << " " << res << "\n";
				if (res > max) {
					max = res;
					argMax = idx;
				}
			}
		}
		//std::cout << "max = "<< max << "\n";
		return argMax;
	}

	int TicTacToeSolver::FindBestActionAlphaBeta()
	{
		_time0 = std::chrono::high_resolution_clock::now();
		int n = _state->GetSize();
		int score = INT32_MIN;
		int argMax = -1;
		int depth = 2;
		if (_state->GetBranchFactor() < 35)
			depth = 3;
		if (_state->GetBranchFactor() < 23)
			depth = 4;
		if (_state->GetBranchFactor() < 20)
			depth = 5;
		if (_state->GetBranchFactor() < 15)
			depth = 6;
		if (_state->GetBranchFactor() < 10)
			depth = 7;
		if (_state->GetBranchFactor() < 8)
			depth = 8;

		int alpha = INT32_MIN;
		int beta = INT32_MAX;
		for (unsigned int idx = 0; idx < n * n * n; ++idx)
		{
			if (_state->IsBlank(idx))
			{
				int res = AlphaBeta(*_state, idx, false, depth);
				int tempScore = score;
				score = std::max(score, AlphaBeta(*_state, idx, false, depth - 1, alpha, beta));
				if (tempScore != score)
					argMax = idx;
				if (score >= beta)
				{
					return argMax;
				}
				alpha = std::max(alpha, score);
			}

		}
		return argMax;
	}

	int TicTacToeSolver::Minimax(State& state, int action, bool isPlayerMax, int depth, bool debugPar)
	{
		int prevLastFill = state.GetLastFill();
		//char lastFill = state.Get(state.GetLastFill());
		nodesExpanded++;

		if(prevLastFill != -1)
			state.Get(prevLastFill) == 'X' ? state.FillO(action) : state.FillX(action);
		else
			_isXTurn ? state.FillX(action) : state.FillO(action);

		if (IsTerminal(state))
		{
			/*if (state.Get(3) == 'O' && state.Get(13) == 'O' && state.Get(23) == 'X' && state.Get(11) == 'X') {
				std::cout << "\n";
				state.Print();
			}*/

			/*if (debugPar) {
				std::cout << "\n";
				state.Print();
				std::cout << "\n";
			}*/
			state.Unfill(action, prevLastFill);
			//return isPlayerMax ? INT32_MIN + 1 : INT32_MAX - 1;
			return isPlayerMax ? INT32_MIN + (state.GetSize() * state.GetSize()) - depth : INT32_MAX - (state.GetSize() * state.GetSize()) + depth;
		}

		auto time1 = std::chrono::high_resolution_clock::now();
		if (depth < 0)
		{
			//state.Unfill(action, prevLastFill);
			int h1 = HighetWinningPotentialHeuristic(state, _isXTurn);
			int h2 = HighetWinningPotentialHeuristic(state, !_isXTurn);
			state.Unfill(action, prevLastFill);
			return isPlayerMax ? h2 - h1 : h1 - h2;
		}
		else if (std::chrono::duration_cast<std::chrono::seconds>(time1 - _time0).count() > _timerLength - 1) {


			depth = 0;
		}

		unsigned int n = state.GetSize();
		if (isPlayerMax)
		{
			int max = INT32_MIN;
			for (unsigned int idx = 0; idx < n * n * n; ++idx)
			{
				if (state.IsBlank(idx))
				{
					int res = Minimax(state, idx, false, depth - 1, false);
					if (res > max)
						max = res;
				}
			}
			state.Unfill(action, prevLastFill);
			return max;
		}
		else
		{
			int min = INT32_MAX;
			for (unsigned int idx = 0; idx < n * n * n; ++idx)
			{
				if (state.IsBlank(idx))
				{
					int res = Minimax(state, idx, true, depth - 1, debugPar);
					if (res < min)
						min = res;
				}
			}
			state.Unfill(action, prevLastFill);
			return min;
		}
	}

	int TicTacToeSolver::AlphaBeta(State& state, int action, bool isPlayerMax, int depth, int alpha, int beta)
	{
		int prevLastFill = state.GetLastFill();
		
		nodesExpanded++;

		if (prevLastFill != -1)
			state.Get(prevLastFill) == 'X' ? state.FillO(action) : state.FillX(action);
		else
			_isXTurn ? state.FillX(action) : state.FillO(action);
		

		if (IsTerminal(state))
		{
			state.Unfill(action, prevLastFill);
			return isPlayerMax ? INT32_MIN + (state.GetSize() * state.GetSize()) - depth : INT32_MAX - (state.GetSize() * state.GetSize()) + depth;
		}

		auto time1 = std::chrono::high_resolution_clock::now();
		if (depth < 0)
		{
			int h1 = HighetWinningPotentialHeuristic(state, _isXTurn);
			int h2 = HighetWinningPotentialHeuristic(state, !_isXTurn);
			state.Unfill(action, prevLastFill);
			return isPlayerMax ? h2 - h1 : h1 - h2;
		}
		else if (std::chrono::duration_cast<std::chrono::seconds>(time1 - _time0).count() > _timerLength - 1) {
			
			
			depth = 0;
		}

		unsigned int n = state.GetSize();
		if (isPlayerMax)
		{
			int score = INT32_MIN;
			for (unsigned int idx = 0; idx < n * n * n; ++idx)
			{
				if (state.IsBlank(idx))
				{
					score = std::max(score, AlphaBeta(state, idx, !isPlayerMax, depth - 1, alpha, beta));
					if (score >= beta)
					{
						state.Unfill(action, prevLastFill);
						return score;
					}
					alpha = std::max(alpha, score);
				}
			}
			state.Unfill(action, prevLastFill);
			return score;
		}
		else
		{
			int score = INT32_MAX;
			for (unsigned int idx = 0; idx < n * n * n; ++idx)
			{
				if (state.IsBlank(idx))
				{
					score = std::min(score, AlphaBeta(state, idx, !isPlayerMax, depth - 1, alpha, beta));
					if (score <= alpha)
					{
						state.Unfill(action, prevLastFill);
						return score;
					}
					beta = std::min(beta, score);
				}
			}
			state.Unfill(action, prevLastFill);
			return score;
		}
	}

	void TicTacToeSolver::SetTurn(bool isXTurn)
	{
		_isXTurn = isXTurn;
	}

	void TicTacToeSolver::SetTimer(int length)
	{
		_timerLength = length;
	}
	
} //namespace TicTacToe