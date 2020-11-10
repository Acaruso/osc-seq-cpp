#pragma once
#include "../store/ui_state.hpp"
#include <SDL.h>

void input_system(Ui_State& ui_state);
void mouse_button_down(SDL_Event& event, Ui_State& ui_state);
void mouse_button_up(SDL_Event& event, Ui_State& ui_state);
void mouse_motion(SDL_Event& event, Ui_State& ui_state);
void keydown(SDL_Event& event, Ui_State& ui_state);
void keyup(SDL_Event& event, Ui_State& ui_state);
