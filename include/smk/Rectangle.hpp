#ifndef SMK_RECTANGLE
#define SMK_RECTANGLE

#include <glm/glm.hpp>

namespace smk {

struct Rectangle {
  float left;
  float top;
  float right;
  float bottom;

  float width() const { return right - left; }
  float height() const { return bottom - top; }
};

}  // namespace smk

#endif /* end of include guard: SMK_RECTANGLE */
