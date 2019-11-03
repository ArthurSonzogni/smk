std::function<void()> main_loop;
void MainLoop() {
  main_loop();
}

void ExecuteMainLoop(std::function<void()> loop) {
  main_loop = loop;
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(&MainLoop, 0, 1);
#else
  while (!screen.input().IsKeyPressed(GLFW_KEY_ESCAPE))
    MainLoop()
#endif
}

void LimitFrameRate(smk::Screen& screen) {
#ifdef __EMSCRIPTEN__
#else
  screen.LimitFrameRate(60.0f);
#endif
}
