//
// Created by akhtyamovpavel on 4/8/20.
//

#pragma once

#include <string>
namespace IRT {
enum class BinaryOperatorType : char {
  PLUS,
  MINUS,
  MUL,
  DIV,
  PERCENT,
  AND,
  OR
};

std::string ToString(BinaryOperatorType type);
}