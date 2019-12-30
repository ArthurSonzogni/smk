#include <smk/Touch.hpp>

namespace smk {

glm::vec2 Touch::position() {
  return data_points.back().position;
}

}  // namespace smk
