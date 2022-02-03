#pragma once

#include <fmt/format.h>
#include "ALabel.hpp"

namespace waybar::modules {

class Wg : public ALabel {
 public:
  Wg(const std::string&, const Json::Value&);
  ~Wg();
  auto update() -> void;

 private:
};

}  // namespace waybar::modules
