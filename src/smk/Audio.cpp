// Copyright 2019 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include <AL/al.h>
#include <AL/alc.h>

#include <cstring>
#include <iostream>
#include <smk/Audio.hpp>
#include <string>
#include <vector>
namespace smk {

namespace {
int g_ref_count = 0;                    // NOLINT
ALCdevice* g_audio_device = nullptr;    // NOLINT
ALCcontext* g_audio_context = nullptr;  // NOLINT

void GetDevices(std::vector<std::string>& devices) {
  devices.clear();
  const ALCchar* device_list = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
  if (!device_list) {
    return;
  }

  while (std::strlen(device_list) > 0) {
    devices.emplace_back(device_list);
    device_list += std::strlen(device_list) + 1; // NOLINT
  }
}

}  // namespace

Audio::Audio() {
  if (g_ref_count++) {
    return;
  }
  std::vector<std::string> devices;
  GetDevices(devices);
  std::cout << "Audio devices found " << devices.size() << ":" << std::endl;

  for (auto& it : devices) {
    std::cout << "* " << it << std::endl;
  }

  std::cout << std::endl;

  g_audio_device = alcOpenDevice(devices[0].c_str());

  if (!g_audio_device) {
    std::cerr << "Failed to get an OpenAL device. Please check you have some "
                 "backend configured while building your application. For "
                 "instance PulseAudio with libpulse-dev"
              << std::endl;
    return;
  }

  g_audio_context = alcCreateContext(g_audio_device, nullptr);
  if (!g_audio_context) {
    std::cerr << "Failed to get an OpenAL context" << std::endl;
    return;
  }

  if (!alcMakeContextCurrent(g_audio_context)) {
    std::cerr << "Failed to make the OpenAL context active" << std::endl;
    return;
  }
}

Audio::~Audio() {
  if (--g_ref_count) {
    return;
  }
  // Destroy the context
  alcMakeContextCurrent(nullptr);
  if (g_audio_context) {
    alcDestroyContext(g_audio_context);
    g_audio_context = nullptr;
  }

  // Destroy the device
  if (g_audio_device) {
    alcCloseDevice(g_audio_device);
    g_audio_device = nullptr;
  }
}

/// @return true if there is at least one Audio class instanciated.
// static
bool Audio::Initialized() {
  return g_ref_count;
}

}  // namespace smk
