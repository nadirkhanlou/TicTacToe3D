#include "TicTacToeSolver.h"

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
			//std::cout << j << "-" << state.Get(j) << "\n";
			if (state.Get(j) != lastFill) {
				isTerminal = false;
				break;
			}
		}

		if (isTerminal)
			return true;
		//std::cout << "test\n";
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
			isTerminal = true;
			counter = 0;
			j = indx - (indx % (size * size));
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

		if (indx / (size * size) == size - (indx % size) - 1 && indx % size == (indx % (size * size)) / size) {
			if (isTerminal)
				return true;
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

		return isTerminal;
	}

	bool TicTacToeSolver::IsTerminal(State& state, int*& hint)
	{
		return false;
	}

	int TicTacToe::TicTacToeSolver::HighetWinningPotentialHeuristic(State& state, bool isXTurn)
	{
		int size = state.GetSize();
		bool* checked = new bool[size];
		
		for (int i = 0; i < size * size; ++i) {
			checked[i] = false;
		}
		for (int i = 0; i < size * size; ++i) {
			if (!checked[i]) {

				
			}
		}
		return 0;
	}

	int TicTacToeSolver::LeastLosingPotentialHeuristic(State& state, bool isXTurn)
	{
		return 0;
	}

	int TicTacToeSolver::PotentialSubtractionHeuristic(State& state, bool isXTurn)
	{
		return 0;
	}

	int TicTacToeSolver::WinningPotentialCount(State& state, bool isXTurn, int indx)
	{
		return 0;
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
		int n = _state->GetSize();
		int max = INT_MIN;
		int argMax = -1;
		for (unsigned int idx = 0; idx < n * n * n; ++idx)
		{
			if (_state->IsBlank(idx))
			{
				int res = Minimax(*_state, idx, false, 3);
				if (res > max) {
					max = res;
					argMax = idx;
				}
			}
		}
		return argMax;
	}

	int TicTacToeSolver::FindBestActionAlphaBeta()
	{
		return 0;
	}

	int TicTacToeSolver::Minimax(State& state, int action, bool isPlayerMax, int depth)
	{
		if (IsTerminal(state))
		{
			state.Print();
			return isPlayerMax ? -1 : +1;
		}
		if (depth < 0)
		{
			return 0;
		}

		if(action != -1)
			state.Get(state.GetLastFill()) == 'X' ? state.FillO(action) : state.FillX(action);
		unsigned int n = state.GetSize();
		if (isPlayerMax)
		{
			int max = INT_MIN;
			for (unsigned int idx = 0; idx < n * n * n; ++idx)
			{
				if (state.IsBlank(idx))
				{
					int res = Minimax(state, idx, !isPlayerMax, depth - 1);
					if (res > max)
						max = res;
				}
			}
			state.Unfill(action);
			return max;
		}
		else
		{
			int min = INT_MAX;
			for (unsigned int idx = 0; idx < n * n * n; ++idx)
			{
				if (state.IsBlank(idx))
				{
					int res = Minimax(state, idx, !isPlayerMax, depth - 1);
					if (res < min)
						min = res;
				}
			}
			state.Unfill(action);
			return min;
		}
	}

	int TicTacToeSolver::AlphaBeta(State& state, int action, bool isPlayerMax, int depth, int alpha, int beta)
	{
		if (IsTerminal(state))
		{
			return Utility(state, isPlayerMax);
		}
		if (depth < 0)
		{
			return Utility(state, isPlayerMax);
		}

		state.Get(state.GetLastFill()) == 'X' ? state.FillO(action) : state.FillX(action);
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
						return score;
					}
					alpha = std::max(alpha, score);
				}
			}
			state.Unfill(action);
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
						return score;
					}
					beta = std::min(beta, score);
				}
			}
			state.Unfill(action);
			return score;
		}
	}
	
} //namespace TicTacToe