// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <smk/View.hpp>

namespace smk {

void View::SetCenter(float x, float y) {
  x_ = x;
  y_ = y;
}
void View::SetSize(float width, float height) {
  width_ = width;
  height_ = height;
}

}  // namespace smk
