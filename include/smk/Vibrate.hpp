// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef SMK_VIBRATE_HPP
#define SMK_VIBRATE_HPP

/// @example vibrate.cpp

namespace smk {

/// Produce a screen vibration of supported devices.
/// @param ms The number of millisecond the vibration must last.
void Vibrate(int ms);

}  // namespace smk

#endif /* end of include guard: SMK_VIBRATE_HPP */
