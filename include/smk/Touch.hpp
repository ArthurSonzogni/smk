#ifndef SMK_TOUCH_HPP
#define SMK_TOUCH_HPP

#include <glm/glm.hpp>
#include <vector>

namespace smk {

struct TouchDataPoint {
  glm::vec2 position;
  float time;
};

struct Touch {
  int finger_id;
  std::vector<TouchDataPoint> data_points;

  glm::vec2 position();
};

}  // namespace smk

#endif /* end of include guard: SMK_TOUCH_HPP */
