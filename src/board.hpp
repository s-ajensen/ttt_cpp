#pragma once

#include "immer/vector.hpp"

enum class Token : uint8_t { empty, x, o };

using Board = immer::vector<Token>;
constexpr int board_size = 9;

inline Board empty_board() {
  return {board_size, Token::empty};
}

enum class MoveError {
  out_of_bounds, position_occupied
};
using MoveResult = std::variant<Board, MoveError>;

inline MoveResult make_move(const Board & board, int pos, Token token) {
  if (pos < 0 || pos > board_size)
    return MoveError::out_of_bounds;
  if (board[pos] != Token::empty)
    return MoveError::position_occupied;
  return board.set(pos, token);
}