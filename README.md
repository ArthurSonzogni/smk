SMK (Simple multimedia kit)
----------------------------
[![travis][badge.travis]][travis]
[![issues][badge.issues]][issues]
[![license][badge.license]][license]
[![contributors][badge.contributors]][contributors]

[badge.travis]: https://img.shields.io/travis/com/arthursonzogni/smk?logo=travis
[badge.issues]: https://img.shields.io/github/issues-raw/arthursonzogni/smk
[badge.license]: https://img.shields.io/github/license/arthursonzogni/smk?color=black
[badge.contributors]: https://img.shields.io/github/contributors/arthursonzogni/smk?color=blue

[travis]: https://travis-ci.com/ArthurSonzogni/smk
[issues]: https://github.com/ArthurSonzogni/smk/issues
[license]: http://opensource.org/licenses/MIT
[contributors]: https://github.com/ArthurSonzogni/smk/graphs/contributors

![header](./doc/header_logo.png)

#### Features:

  * Compatible with WebAssembly. One build for every platforms!
  * Fast & simple.
  * No dependencies: everything is fetched using cmake FetchContent.

#### Ready to start?

 * [WebAssembly demo](https://arthursonzogni.github.io/smk/examples/) from the ./examples directory.
 * [documentation](https://arthursonzogni.com/SMK/doc/)
 * [starter project](https://github.com/ArthurSonzogni/smk-starter)
 * [tutorial](./doc/build_with_cmake.md)

### Open a new Window:

~~~cpp
  auto window = smk::Window(640, 480, "Title");
~~~

### The main loop:

~~~cpp
  window.ExecuteMainLoop([&] {
    window.Clear(smk::Color::Black);

    [...] // Draw stuff

    window.Display();
  });
~~~

### Images

Load textures:
~~~cpp
  auto ball_texture = smk::Texture("./ball.png");
~~~

Display images:
~~~cpp
  auto ball_sprite = smk::Sprite(ball_texture);
  ball_sprite.SetPosition({200,200});
  window.Draw(ball_sprite);
~~~

### Text

Load font:
~~~cpp
  auto font_arial = smk::Font("./arial.ttf", 32);
~~~

Display text:
~~~cpp
  auto text = smk::Text(font_arial, "hello world");
  text.SetPosition({200,200});
  window.Draw(text);
~~~

### Sound

Load sound:
~~~cpp
  auto sound_buffer = smk:SoundBuffer("./boing.ogg");
~~~

Play sound:
~~~cpp
  auto sound = smk::Sound(sound_buffer);
  sound.Play();
~~~

### Transform the view

~~~cpp
  auto view = smk::View();
  view.SetCenter({200, 200});
  view.SetSize(320,240);
  window.SetView(view);
~~~

## Library made using SMK

 * [smkflow](https://github.com/ArthurSonzogni/smkflow) => A node editor library.

## Games made using SMK

 * [InTheCube](https://github.com/ArthurSonzogni/InTheCube)
 * [IceMaze](https://github.com/ArthurSonzogni/IceMaze)
 * [pigami](https://github.com/ArthurSonzogni/pigami)

Please add yours.

## Story

I needed to port several games made using the
[SFML](https://www.sfml-dev.org/) to WebAssembly. SFML isn't supporting
WebAssembly (yet), so I had to reimplement it myself. If you know the SFML, then
SMK must be very familiar to you.

## Minimal packages to install for building/executing:

They should already be installed. If they aren't you need to execute:
~~~bash
sudo apt install xorg-dev libgl1-mesa-dev libpulse-dev
~~~

## Thanks

SMK depends directly on many great projects listed below:
- [Freetype](https://github.com/aseprite/freetype2)
- [GLEW](https://github.com/nigels-com/glew)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [OpenAL-soft](https://github.com/kcat/openal-soft)
- [libnyquist](https://github.com/ddiakopoulos/libnyquist)
- [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)


SMK is also made possible thanks to:
 * [CMake](https://cmake.org/)
 * [Emscripten](https://github.com/kripken/emscripten)
 * [FLAC](https://github.com/xiph/flac)
 * [Git](https://git-scm.com/)
 * [LLVM](https://llvm.org/)
 * [NeoVim](https://neovim.io/)
 * [OpenGL](https://www.opengl.org/)
 * [WebAssembly](https://webassembly.org/)
 * [libogg](https://xiph.org/ogg/)
 * [libvorbis](https://www.xiph.org/vorbis/)
 * [minimp3](https://github.com/lieff/minimp3)
 * [musepack](https://github.com/ralph-irving/musepack)
 * [opus](https://github.com/xiph/opus)
 * [rtaudio](https://github.com/thestk/rtaudio)
 * [wabpack](dbry/WavPack)
