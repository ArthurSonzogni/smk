# SMK (Simple multimedia kit)

The story of this library is simple, I wanted to port a few SFML games to the
web by using WebAssembly. SFML isn't supporting WebAssembly (yet), so I had to
reimplement it myself. If you know the SFML, then SMK must be very familiar to
you.

What you can expect compared to the SFML:
- It works with WebAssembly \o/. One build for every platforms!
- No dependencies, everything is fetched and built from source thanks to
  CMake. See [cmake tutorial](./doc/build_with_cmake.md)
- Fewers features... but I am looking forward for your pull requests.
- Less qualitative ;-) It is just a hackish project and I am the main user. This
  is still WIP.
- The API is not meant to be stable for now. I am going to break your project.
- A few twist. Resources are move-only classes. Colors are glm::vec4. Key/Mouse
  are raw GLFW enum.

## Opening a new Window:
~~~bash
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
~~~
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
~~~
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
