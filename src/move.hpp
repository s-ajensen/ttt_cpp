#pragma once

#include "board.hpp"

enum class MoveError { out_of_bounds, position_occupied };

using MoveResult = std::variant<Board, MoveError>;

inline MoveResult make_move(const Board &board, int pos, Token token) {
  if (pos < 0 || pos > board_size) {
    return MoveError::out_of_bounds;
  }
  if (board[pos] != Token::empty) {
    return MoveError::position_occupied;
  }

  return board.set(pos, token);
}

enum class Minimax { maximizing, minimizing };

inline int eval_static(const Board &board, Minimax mode, int depth) {
  return 0;
}
