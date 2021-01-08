#include "store.hpp"

#include <stdlib.h>

#include <iostream>
#include <sstream>

#include "../sdl/sdl_wrapper.hpp"

Store::Store()
{
	Init_Sdl_Res init_sdl_res = init_sdl();

	window = init_sdl_res.window;
	window_surface = init_sdl_res.window_surface;
	window_renderer = init_sdl_res.window_renderer;

    seq_grid = Seq_Grid{16, 1, 16, 40, 40};

    pattern_grid = Pattern_Grid{2, 8, 20, 20};

    registers.push_back({ "$0", 0, 8 });
    registers.push_back({ "$1", 0, 8 });

    default_cell = Grid_Cell{};

    copied_cell = Grid_Cell{};

    copied_pattern = Grid<Grid_Cell>{};

    bpm = 120;
    clock = 0;
    blink_clock = 0;
    PPQ = 96;
    time_divisions = get_time_divisions(bpm);

    transport_mode = Pause;

    event_editor = { 0, 0, 0, 0, std::vector<int>(), 0, Event_Editor_Mode::Normal };
    for (int i = 0; i < 10; i++) {
        event_editor.selected_dropdown_rows.push_back(0);
    }

    Image_Set arrow_up;
    arrow_up.image = load_image("image/arrow-up.png", window_renderer);
    arrow_up.image_hot = load_image("image/arrow-up-hot.png", window_renderer);
    arrow_up.image_active = load_image("image/arrow-up-active.png", window_renderer);

    Image_Set arrow_down;
    arrow_down.image = load_image("image/arrow-down.png", window_renderer);
    arrow_down.image_hot = load_image("image/arrow-down-hot.png", window_renderer);
    arrow_down.image_active = load_image("image/arrow-down-active.png", window_renderer);

    Image_Set button_green;
    button_green.image = load_image("image/button-darkgreen-1.png", window_renderer);
    button_green.image_hot = load_image("image/button-darkgreen-2.png", window_renderer);
    button_green.image_active = load_image("image/button-darkgreen-3.png", window_renderer);
    button_green.image_toggled = load_image("image/button-darkgreen-4.png", window_renderer);

    Image_Set button_orange;
    button_orange.image = load_image("image/button-orange-1.png", window_renderer);
    button_orange.image_hot = load_image("image/button-orange-2.png", window_renderer);
    button_orange.image_active = load_image("image/button-orange-3.png", window_renderer);
    button_orange.image_toggled = load_image("image/button-orange-4.png", window_renderer);

    Image_Set button_pink;
    button_pink.image = load_image("image/button-pink-1.png", window_renderer);
    button_pink.image_hot = load_image("image/button-pink-2.png", window_renderer);
    button_pink.image_active = load_image("image/button-pink-3.png", window_renderer);
    button_pink.image_toggled = load_image("image/button-pink-4.png", window_renderer);

    Image_Set button_red;
    button_red.image = load_image("image/button-red-1.png", window_renderer);
    button_red.image_hot = load_image("image/button-red-2.png", window_renderer);
    button_red.image_active = load_image("image/button-red-3.png", window_renderer);
    button_red.image_toggled = load_image("image/button-red-4.png", window_renderer);

    Image_Set button_small;
    button_small.image = load_image("image/button-small-1.png", window_renderer);
    button_small.image_toggled = load_image("image/button-small-3.png", window_renderer);

    Image_Set button_selection;
    button_selection.image = load_image("image/button-selection.png", window_renderer);

    Image_Set button_selection_green;
    button_selection_green.image = load_image("image/button-selection-green.png", window_renderer);

    Image_Set button_plus;
    button_plus.image = load_image("image/button-plus-1.png", window_renderer);
    button_plus.image_hot = load_image("image/button-plus-2.png", window_renderer);
    button_plus.image_active = load_image("image/button-plus-3.png", window_renderer);

    Image_Set button_minus;
    button_minus.image = load_image("image/button-minus-1.png", window_renderer);
    button_minus.image_hot = load_image("image/button-minus-2.png", window_renderer);
    button_minus.image_active = load_image("image/button-minus-3.png", window_renderer);

    Image_Set select_event_editor;
    select_event_editor.image = load_image("image/select-event-editor.png", window_renderer);

    Image_Set select_underline;
    select_underline.image = load_image("image/select-underline.png", window_renderer);

    Image_Set select_vertical_left;
    select_vertical_left.image = load_image("image/select-vertical-left.png", window_renderer);

    Image_Set select_vertical_right;
    select_vertical_right.image = load_image("image/select-vertical-right.png", window_renderer);

    Image_Set button_xs;
    button_xs.image = load_image("image/button-xs-1.png", window_renderer);
    button_xs.image_hot = load_image("image/button-xs-3.png", window_renderer);
    button_xs.image_active = load_image("image/button-xs-3.png", window_renderer);
    button_xs.image_toggled = load_image("image/button-xs-2.png", window_renderer);

    Image_Set button_xs_blink;
    button_xs_blink.image = load_image("image/button-xs-4.png", window_renderer);

    Image_Set button_mute;
    button_mute.image = load_image("image/button-mute-1.png", window_renderer);
    button_mute.image_hot = load_image("image/button-mute-2.png", window_renderer);
    button_mute.image_active = load_image("image/button-mute-3.png", window_renderer);
    button_mute.image_toggled = load_image("image/button-mute-3.png", window_renderer);

    Image_Set button_load_save;
    button_load_save.image = load_image("image/button-load-save-1.png", window_renderer);
    button_load_save.image_hot = load_image("image/button-load-save-2.png", window_renderer);
    button_load_save.image_active = load_image("image/button-load-save-2.png", window_renderer);

    images["arrow-up"] = arrow_up;
    images["arrow-down"] = arrow_down;
    images["button-green"] = button_green;
    images["button-orange"] = button_orange;
    images["button-pink"] = button_pink;
    images["button-red"] = button_red;
    images["button-small"] = button_small;
    images["button-selection"] = button_selection;
    images["button-selection-green"] = button_selection_green;
    images["button-plus"] = button_plus;
    images["button-minus"] = button_minus;
    images["select-event-editor"] = select_event_editor;
    images["select-underline"] = select_underline;
    images["select-vertical-left"] = select_vertical_left;
    images["select-vertical-right"] = select_vertical_right;
    images["button-xs"] = button_xs;
    images["button-xs-blink"] = button_xs_blink;
    images["button-mute"] = button_mute;
    images["button-load-save"] = button_load_save;

    font_size = 16;     // font height
    font_width = 9;
    line_height = 20;   // height of line -> font + whitespace

    fonts["dos"] = FC_CreateFont();

    FC_LoadFont(
        fonts["dos"],
        window_renderer,
        "image/Perfect-DOS-VGA-437.ttf",
        font_size,
        FC_MakeColor(0, 0, 0, 255),
        TTF_STYLE_NORMAL
    );

    fonts["dos-white"] = FC_CreateFont();

    FC_LoadFont(
        fonts["dos-white"],
        window_renderer,
        "image/Perfect-DOS-VGA-437.ttf",
        font_size,
        FC_MakeColor(255, 255, 255, 255),
        TTF_STYLE_NORMAL
    );
}
