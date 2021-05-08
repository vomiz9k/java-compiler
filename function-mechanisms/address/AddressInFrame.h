//
// Created by akhtyamovpavel on 4/14/20.
//


#pragma once

#include "Address.h"
namespace IRT {

class MemExpression;

class AddressInFrame: public Address {
 public:
  AddressInFrame(
    Address* frame_address,
    int offset
  );

  AddressInFrame(
            Expression* expression
  );

  AddressInFrame() = default;

  void Update(Address* frame_address, int offset) {
      frame_address_ = frame_address;
      offset_ = offset;
  }

  ~AddressInFrame() = default;
  Expression *ToExpression() override;
 private:
  Address* frame_address_ = nullptr;
  int offset_ = 0;
  Expression* converted_ = nullptr;

};

}
