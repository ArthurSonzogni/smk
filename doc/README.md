SMK (Simple multimedia kit)
----------------------------

![header](header_logo.png)

#### Features:

  * Compatible with WebAssembly. One build for every platforms!
  * Fast & simple.
  * No dependencies: everything is fetched using cmake FetchContent.

#### Ready to start?

 * [WebAssembly demo](https://arthursonzogni.github.io/smk/examples/) from the ./examples directory.
 * [documentation](https://arthursonzogni.com/SMK/doc/)
 * [starter project](https://github.com/ArthurSonzogni/smk-starter)

### Open a new Window:

~~~cpp
  auto window = smk::Window(640, 480, "Title");
~~~

### The main loop:

~~~cpp
  void loop() {
    window.Clear(smk::Color::Black);

    [...] // Draw stuff

    window.Display();
  }
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

### Examples:
 * [framebuffer.cpp](@ref framebuffer.cpp)
 * [shape_2d.cpp](@ref shape_2d.cpp)
 * [shape_3d.cpp](@ref shape_3d.cpp)
 * [sound.cpp](@ref sound.cpp)
 * [sprite.cpp](@ref sprite.cpp)
 * [sprite_move.cpp](@ref sprite_move.cpp)
 * [text.cpp](@ref text.cpp)
 * [texture_subrectangle.cpp](@ref texture_subrectangle.cpp)
 * [touch.cpp](@ref touch.cpp)
 * [util.hpp](@ref util.hpp)
 * [vibrate.cpp](@ref vibrate.cpp)

## Games made using SMK

 * [InTheCube](https://github.com/ArthurSonzogni/InTheCube)
 * [IceMaze](https://github.com/ArthurSonzogni/IceMaze)
 * [pigami](https://github.com/ArthurSonzogni/pigami)
