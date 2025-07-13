#pragma once

#include "immer/vector.hpp"
// #include <cstdint>

enum class Token : uint8_t {empty, x, o};
using Board = immer::vector<Token>;

inline Board empty_board() {
  return {9, Token::empty};
}
