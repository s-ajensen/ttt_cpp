#include <iostream>

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

});
