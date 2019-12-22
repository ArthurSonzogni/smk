std::function<void()> main_loop;
void MainLoop() {
  main_loop();
}

void ExecuteMainLoop(smk::Window& window, std::function<void()> loop) {
  main_loop = loop;
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(&MainLoop, 0, 1);
#else
  while (!window.input().IsKeyPressed(GLFW_KEY_ESCAPE)) {
    MainLoop();
    window.LimitFrameRate(60.0f);
  }
#endif
}
