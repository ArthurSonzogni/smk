# SMK (Simple multimedia kit)

![header](./doc/header_logo.png)

**Story**:
~~~
I needed to port several games made using the
[SFML](https://www.sfml-dev.org/) to WebAssembly. SFML isn't supporting
WebAssembly (yet), so I had to reimplement it myself. If you know the SFML, then
SMK must be very familiar to you.
~~~

Features:
  * Compatible with WebAssembly. One build for every platforms!
  * No dependencies, everything is fetched using cmake FetchContent.
  * Fast & simple.

Ready to start? See [tutorial](./doc/build_with_cmake.md) on how to depend on
the smk.

## Opening a new Window:
~~~cpp
  auto screen = smk::Screen(640, 480, "Title");
~~~

## The main loop:
~~~cpp
  void loop() {
    screen.Clear(smk::Color::Black);

    [...] // Draw stuff

    screen.Display();
  }
~~~

## Images

### Loading textures
~~~cpp
  auto ball_texture = Texture("./ball.png");
~~~

### Displaying image
~~~cpp
  Sprite ball_sprite;
  ball_sprite.SetTexture(ball_texture);
  ball_sprite.SetPosition({200,200});
  screen.Draw(ball_sprite);
~~~

## Text
### Loading font
~~~cpp
  auto font_arial = Font("./arial.ttf", 32);
~~~

### Displaying text
~~~cpp
  Text text;
  text.SetFont(font_arial);
  text.SetPosition({200,200});
  screen.Draw(text);
~~~

## Sound

### Loading sound.
~~~cpp
  auto sound_buffer = smk:SoundBuffer("./boing.ogg");
~~~

### Playing sound.
~~~cpp
  smk::Sound sound;
  sound.SetBuffer(sound);
  sound.Play();
~~~

## Transforming the view
~~~cpp
  View view;
  view.SetCenter({200, 200});
  view.SetSize(320,240);
  screen.SetView(view);
~~~

# Thanks

SMK depends directly on many great projects listed below:
- [Freetype](https://github.com/aseprite/freetype2)
- [GLEW](https://github.com/nigels-com/glew)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [OpenAL-soft](https://github.com/kcat/openal-soft)
- [libnyquist](https://github.com/ddiakopoulos/libnyquist)
- [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)


SMK is also made possible thanks to (indirectly dependencies, tools used, non-exhaustive):
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
