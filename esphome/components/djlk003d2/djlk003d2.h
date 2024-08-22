#pragma once

#include <vector>

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace djlk003d2 {

class Djlk003d2Component : public sensor::Sensor, public Component, public uart::UARTDevice {
 public:
  // Nothing really public.

  // ========== INTERNAL METHODS ==========
  void loop() override;
  void dump_config() override;

 protected:
  void check_buffer_();

  std::vector<uint8_t> buffer_;
};

}  // namespace djlk003d2
}  // namespace esphome
