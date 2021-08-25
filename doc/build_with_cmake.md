Use SMK with CMake
==================

Add the files.
--------------

Start with a main.cpp and CMakeLists.txt files:

### main.cpp

~~~cpp
#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

int main() {
  auto window = smk::Window(640, 480, "test");
  auto circle = smk::Shape::Circle(200);
  circle.SetColor(smk::Color::Red);
  circle.SetPosition(320,240);

  while (!window.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    window.PoolEvents();
    window.Clear(smk::Color::Black);
    window.Draw(circle);
    window.Display();
    window.LimitFrameRate(60 /* fps */);
  }
  return 0;
}
~~~

### CMakeLists.txt

~~~cmake
cmake_minimum_required (VERSION 3.11)

FetchContent_Declare(smk GIT_REPOSITORY https://github.com/ArthurSonzogni/smk.git)
FetchContent_GetProperties(smk)
if(NOT smk_POPULATED)
  FetchContent_Populate(smk)
  add_subdirectory(${smk_SOURCE_DIR} ${smk_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

project(Example
  LANGUAGES CXX
  VERSION 0.1.0
)

add_executable(main main.cpp)
target_link_libraries(main smk)
~~~

Build for the desktop.
----------------------

~~~bash
mkdir build
cd build
cmake ..
make -j
./main
~~~

Build for the Web.
------------------

~~~bash
mkdir build
cd build
emcmake cmake ..
make -j
~~~

Then you will need to import the generated "main.js" into an html file like this
one:
~~~html
<canvas id="canvas" oncontextmenu="event.preventDefault()">
    Loading... 
</canvas>

<script>
  let Module = {
    print: console.log;
    printerr: console.err
    canvas: document.getElementById('canvas')
  };
</script>

<script async src="main.js"></script>
~~~

Your C++ file will have to define its main loop function that will get called on
each frame:
~~~cpp
emscripten_set_main_loop(&MainLoop, 0, 1);
~~~
