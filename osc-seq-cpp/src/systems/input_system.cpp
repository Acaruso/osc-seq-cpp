#include "input_system.hpp"

#include <iostream>

void input_system(Ui_State& ui_state)
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            ui_state.quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouse_button_down(event, ui_state);
            break;
        case SDL_MOUSEBUTTONUP:
            mouse_button_up(event, ui_state);
            break;
        case SDL_MOUSEMOTION:
            mouse_motion(event, ui_state);
            break;
        case SDL_KEYDOWN:
            keydown(event, ui_state);
            break;
        case SDL_KEYUP:
            keyup(event, ui_state);
            break;
        }
    }

    if (ui_state.click) {
        ui_state.prev_drag_x = ui_state.drag_x;
        ui_state.prev_drag_y = ui_state.drag_y;
        ui_state.drag_x = ui_state.cx;
        ui_state.drag_y = ui_state.cy;
    }
}

void mouse_button_down(SDL_Event& event, Ui_State& ui_state)
{
    ui_state.click = true;
    ui_state.drag_x = ui_state.cx;
    ui_state.drag_y = ui_state.cy;
}

void mouse_button_up(SDL_Event& event, Ui_State& ui_state)
{
    ui_state.click = false;
    ui_state.cur_elt_id = "";
}

void mouse_motion(SDL_Event& event, Ui_State& ui_state)
{
    ui_state.cx = event.motion.x;
    ui_state.cy = event.motion.y;
}

void keydown(SDL_Event& event, Ui_State& ui_state)
{
    ui_state.keydown_event = true;

    switch (event.key.keysym.sym) {
    case SDLK_UP:
        ui_state.up = true;
        break;
    case SDLK_DOWN:
        ui_state.down = true;
        break;
    case SDLK_LEFT:
        ui_state.left = true;
        break;
    case SDLK_RIGHT:
        ui_state.right = true;
        break;
    case SDLK_w:
        ui_state.w = true;
        break;
    case SDLK_a:
        ui_state.a = true;
        break;
    case SDLK_s:
        ui_state.s = true;
        break;
    case SDLK_d:
        ui_state.d = true;
        break;
    case SDLK_e:
        ui_state.e = true;
        break;
    case SDLK_q:
        ui_state.q = true;
        break;
    case SDLK_c:
        ui_state.c = true;
        break;
    case SDLK_v:
        ui_state.v = true;
        break;
    case SDLK_r:
        ui_state.r = true;
        break;
    case SDLK_p:
        ui_state.p = true;
        break;
    case SDLK_x:
        ui_state.x = true;
        break;
    case SDLK_f:
        ui_state.f = true;
        break;
    case SDLK_SPACE:
        ui_state.space = true;
        break;
    case SDLK_LSHIFT:
        ui_state.lshift = true;
        break;
    case SDLK_LCTRL:
        ui_state.lctrl = true;
        break;
    case SDLK_TAB:
        ui_state.tab = true;
        break;
    case SDLK_1:
        ui_state.i1 = true;
        break;
    case SDLK_2:
        ui_state.i2 = true;
        break;
    case SDLK_3:
        ui_state.i3 = true;
        break;
    case SDLK_4:
        ui_state.i4 = true;
        break;
    case SDLK_5:
        ui_state.i5 = true;
        break;
    case SDLK_6:
        ui_state.i6 = true;
        break;
    case SDLK_ESCAPE:
        ui_state.esc = true;
        break;
    }
}

void keyup(SDL_Event& event, Ui_State& ui_state)
{
    switch (event.key.keysym.sym) {
    case SDLK_UP:
        ui_state.up = false;
        break;
    case SDLK_DOWN:
        ui_state.down = false;
        break;
    case SDLK_LEFT:
        ui_state.left = false;
        break;
    case SDLK_RIGHT:
        ui_state.right = false;
        break;
    case SDLK_w:
        ui_state.w = false;
        break;
    case SDLK_a:
        ui_state.a = false;
        break;
    case SDLK_s:
        ui_state.s = false;
        break;
    case SDLK_d:
        ui_state.d = false;
        break;
    case SDLK_e:
        ui_state.e = false;
        break;
    case SDLK_q:
        ui_state.q = false;
        break;
    case SDLK_c:
        ui_state.c = false;
        break;
    case SDLK_v:
        ui_state.v = false;
        break;
    case SDLK_r:
        ui_state.r = false;
        break;
    case SDLK_p:
        ui_state.p = false;
        break;
    case SDLK_x:
        ui_state.x = false;
        break;
    case SDLK_f:
        ui_state.f = false;
        break;
    case SDLK_SPACE:
        ui_state.space = false;
        break;
    case SDLK_LSHIFT:
        ui_state.lshift = false;
        break;
    case SDLK_LCTRL:
        ui_state.lctrl = false;
        break;
    case SDLK_TAB:
        ui_state.tab = false;
        break;
    case SDLK_1:
        ui_state.i1 = false;
        break;
    case SDLK_2:
        ui_state.i2 = false;
        break;
    case SDLK_3:
        ui_state.i3 = false;
        break;
    case SDLK_4:
        ui_state.i4 = false;
        break;
    case SDLK_5:
        ui_state.i5 = false;
        break;
    case SDLK_6:
        ui_state.i6 = false;
        break;
    case SDLK_ESCAPE:
        ui_state.esc = false;
        break;
    }
}
