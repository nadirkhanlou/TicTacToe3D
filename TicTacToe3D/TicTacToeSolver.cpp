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

	bool TicTacToeSolver::TerminalCheck(State& state)
	{
		int size = state.GetSize();

		int indx = state.GetLastFill();
		char lastFill = state.Get(indx);

		bool isTerminal = true;
		int j = indx - (indx % size);
		for (j; j < size * size; j += 1) {
			if (state.Get(j) != lastFill) {
				isTerminal = false;
				break;
			}
		}

		if (isTerminal)
			return true;
		isTerminal = true;
		j = indx - (((indx / size) % size) * size);
		for (j; j < size * size; j += size) {
			if (state.Get(j) != lastFill) {
				isTerminal = false;
				break;
			}
		}

		if (isTerminal)
			return true;
		isTerminal = true;
		j = indx % (size * size);
		for (j; j < size * size; j += size * size) {
			if (state.Get(j) != lastFill) {
				isTerminal = false;
				break;
			}
		}

		if ((indx % (size * size)) % (size + 1) == 0) {
			if (isTerminal)
				return true;
			isTerminal = true;
			j = indx - (indx % (size * size));
			for (j; j < size * size; j += size + 1) {
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
			j = indx - (indx % (size * size));
			for (j; j < size * size; j += size - 1) {
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
			j = indx % size;
			for (j; j < size * size; j += size * size + size) {
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
			j = (size * size) - (size - (indx % size) - 1);
			for (j; j < size * size; j += size * size - size) {
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
			j = ((indx % (size * size)) / size) * size;
			for (j; j < size * size; j += size * size + 1) {
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
			j = ((indx % (size * size)) / size) * size + size - 1;
			for (j; j < size * size; j += size * size - 1) {
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
			j = 0;
			for (int j = 0; j < size * size; j += size * size + size + 1) {
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
			j = size - 1;
			for (int j = 0; j < size * size; j += size * size + size - 1) {
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
			j = size * size - size;
			for (int j = 0; j < size * size; j += size * size - size + 1) {
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
			j = size * size - size;
			for (int j = 0; j < size * size; j += size * size - size - 1) {
				if (state.Get(j) != lastFill) {
					isTerminal = false;
					break;
				}
			}
		}

		if (isTerminal)
			return true;
		return false;
	}

	int TicTacToeSolver::Minimax(State& state, int action, bool isPlayerMax, int depth = INT32_MAX)
	{
		if (IsTerminal(state))
		{
			return Utility(state);
		}
		if (depth < 0)
		{
			return Utility(state);
		}

		state.Get(state.GetLastFill()) == 'X' ? state.FillO(action) : state.FillX(action);
		unsigned int n = state.GetSize();
		if (isPlayerMax)
		{
			std::vector<int> scores = {} ;
			for (unsigned int idx = 0; idx < n * n * n; ++idx)
			{
				if (state.IsBlank(idx))
				{
					scores.push_back(Minimax(state, idx, !isPlayerMax, depth - 1));
				}
			}
			state.Unfill(action);
			return *std::max_element(scores.begin(), scores.end());
		}
		else
		{
			std::vector<int> scores = {};
			for (unsigned int idx = 0; idx < n * n * n; ++idx)
			{
				if (state.IsBlank(idx))
				{
					scores.push_back(Minimax(state, idx, !isPlayerMax, depth - 1));
				}
			}
			state.Unfill(action);
			return *std::min_element(scores.begin(), scores.end());
		}
	}

	int TicTacToeSolver::AlphaBeta(State& state, int action, bool isPlayerMax, int depth = INT32_MAX, int alpha = INT32_MIN, int beta = INT32_MAX)
	{
		if (IsTerminal(state))
		{
			return Utility(state);
		}
		if (depth < 0)
		{
			return Utility(state);
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