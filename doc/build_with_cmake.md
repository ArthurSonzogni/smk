# Depend on SMK and its dependencies
~~~bash
mkdir third_party
git submodule add --depth=1 git@github.com:arthursonzogni/smk third_party/smk
git submodule add --depth=1 git@github.com:aseprite/freetype2 third_party/freetype2
git submodule add --depth=1 git@github.com:ddiakopoulos/libnyquist third_party/libnyquist
git submodule add --depth=1 git@github.com:g-truc/glm third_party/glm
git submodule add --depth=1 git@github.com:glfw/glfw third_party/glfw
git submodule add --depth=1 git@github.com:kcat/openal-soft third_party/openal
git submodule add --depth=1 git@github.com:omniavinco/glew-cmake third_party/glew
~~~

# Write a CMakeLists.txt
~~~cmake
~~~

# Build for desktop
~~~
~~~

# Build for the Web
~~~
mkdir build_webassembly
emconfigure cmake ..
make -j
~~~
