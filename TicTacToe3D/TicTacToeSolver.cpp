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