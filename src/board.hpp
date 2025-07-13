#pragma once

#include "immer/vector.hpp"

enum class Token : uint8_t { empty, x, o };

using Board = immer::vector<Token>;
constexpr int board_size = 9;
constexpr int row_len = 3;

inline Board empty_board() {
  return {board_size, Token::empty};
}

inline Board make_board(std::initializer_list<Token> tokens) {
  return Board{tokens.begin(), tokens.end()};
}

inline bool is_uniform(const Board &board, size_t row) {
  return board[row] == board[row + 1] &&
         board[row + 1] == board[row + 2];
}

inline bool is_won(const Board &board) {
  for (size_t row = 0; row < board_size; row += row_len) {
    if (board[row] != Token::empty && is_uniform(board, row)) {
      return true;
    }
  }
  return false;
}
