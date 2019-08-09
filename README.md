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
  auto ball_sprite = smk::Sprite(ball_texture);
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
  auto text = smk::Text(font_arial, "hello world");
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
  auto sound = smk::Sound(sound_buffer);
  sound.Play();
~~~

## Transforming the view
~~~cpp
  auto view = smk::View();
  view.SetCenter({200, 200});
  view.SetSize(320,240);
  screen.SetView(view);
~~~

# Games made using SMK
 * [InTheCube](https://github.com/ArthurSonzogni/InTheCube)
 * [IceMaze](https://github.com/ArthurSonzogni/IceMaze)

(Feel free to add yours)

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
