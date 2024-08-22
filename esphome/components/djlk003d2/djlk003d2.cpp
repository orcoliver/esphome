#include "djlk003d2.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace djlk003d2 {

static const char *const TAG = "djlk003d2.sensor";

void Djlk003d2Component::loop() {
  uint8_t data;
  while (this->available() > 0) {
    this->read_byte(&data);
    if (this->buffer_.empty() && (data != 0xff))
      continue;
    buffer_.push_back(data);
    if (this->buffer_.size() == 4)
      this->check_buffer_();
  }
}

void Djlk003d2Component::check_buffer_() {
  uint8_t checksum = this->buffer_[0] + this->buffer_[1] + this->buffer_[2];
  if (this->buffer_[3] == checksum) {
    float distance = (this->buffer_[1] << 8) + this->buffer_[2];
    if (distance > 220) {
      float meters = distance / 1000.0;
      ESP_LOGV(TAG, "Distance from sensor: %f mm, %f m", distance, meters);
      this->publish_state(meters);
    } else {
      ESP_LOGW(TAG, "Invalid data read from sensor: %s", format_hex_pretty(this->buffer_).c_str());
    }
  } else {
    ESP_LOGW(TAG, "checksum failed: %02x != %02x", checksum, this->buffer_[3]);
  }
  this->buffer_.clear();
}

void Djlk003d2Component::dump_config() { LOG_SENSOR("", "Djlk003d2 Sensor", this); }

}  // namespace djlk003d2
}  // namespace esphome
