#include "catch.hpp"
#include "bdd.hpp"
#include "board.hpp"

describe("Board", []{

  it("starts with no moves", [] {
    Board b = empty_board();
    should_eq(9, b.size());
    for (Token t: b) {
    should_eq(Token::empty, t);
    }
    });

  context("win detection", [] {

    it("does not count empty game", [] {
      Board board = empty_board();
      should_not(is_won(board));
      })});

  it("does not count unfinished game", [] {
    Board board = make_board({
      Token::x, Token::o, Token::empty,
      Token::empty, Token::empty, Token::empty,
      Token::empty, Token::empty, Token::empty});
    should_not(is_won(board));
    });

  context("by row", [] {

    it("top", [] {
      Board board = make_board({
        Token::x, Token::x, Token::x,
        Token::o, Token::o, Token::x,
        Token::x, Token::o, Token::o});
      should(is_won(board));
      });
    });
  });
