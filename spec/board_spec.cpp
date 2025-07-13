#include <iostream>

#include "catch.hpp"
#include "bdd.hpp"
#include "board.hpp"

Board successful_move(const Board & board, int idx, Token token) {
  MoveResult result = make_move(board, idx, token);
  return std::get<Board>(result);
}

describe("Board", []{

  it("starts with no moves", [] {
    Board b = empty_board();
    should_eq(9, b.size());
    for (Token t: b) {
      should_eq(Token::empty, t);
    }
  });

  context("makes move", [] {

    it("makes a move as X", [] {
      Board board = successful_move(empty_board(), 0, Token::x);
      should_eq(Token::x, board[0]);
    });

    it ("makes a move as O", [] {
      Board board = successful_move(empty_board(), 8, Token::o);
      should_eq(Token::o, board[8]);
    });

    it("makes multiple moves", [] {
      Board b2 = successful_move(empty_board(), 0, Token::o);
      Board b3 = successful_move(b2, 5, Token::x);
      Board b4 = successful_move(b3, 8, Token::o);
      should_eq(Token::o, b2[0]);
      should_eq(Token::o, b3[0]);
      should_eq(Token::o, b4[0]);
      should_eq(Token::empty, b2[5]);
      should_eq(Token::x, b3[5]);
      should_eq(Token::x, b4[5]);
      should_eq(Token::empty, b2[8]);
      should_eq(Token::empty, b3[8]);
      should_eq(Token::o, b2[0]);
    });

    it("fails when space occupied", [] {
      Board b1 = successful_move(empty_board(), 0, Token::x);
      auto result = make_move(b1, 0, Token::o);
      should(std::holds_alternative<MoveError>(result));
      should_eq(MoveError::position_occupied, std::get<MoveError>(result));
    });

    it("fails when position is too small", [] {
      auto result = make_move(empty_board(), -1, Token::o);
      should(std::holds_alternative<MoveError>(result));
      should_eq(MoveError::out_of_bounds, std::get<MoveError>(result));
    });

    it("fails when position is too large", [] {
      auto result = make_move(empty_board(), 10, Token::o);
      should(std::holds_alternative<MoveError>(result));
      should_eq(MoveError::out_of_bounds, std::get<MoveError>(result));
    });
  });
});
