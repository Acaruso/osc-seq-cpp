#pragma once

#include "../event_editor.hpp"
#include "../register.hpp"
#include "dropdown_entry.hpp"

#include <functional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

enum Subfield_Flags
{
    Is_Selectable   = (1 << 0),
    Can_Be_Mod_Dest = (1 << 1),
    Note_Subfield   = (1 << 2),
};

enum Field_Flags
{
    Is_Osc_Data     = (1 << 0),
    Delay_Field     = (1 << 1),
    Cond_Field      = (1 << 2),
    Mod_Field       = (1 << 3),
    Note_Field      = (1 << 4),
};

struct Display_Res
{
    std::string text;
    std::vector<std::pair<int, int>> subfield_idxs;
};

struct Int_Subfield
{
    std::string key;
    unsigned int flags;
    int data;
    int min;
    int max;
    int meta_mod;

    void update(int delta);
    void reset_meta_mods();
    std::string to_string();
    std::string get_display();
};

struct Subfield_Path
{
    std::string tab_key;
    std::string field_key;
    std::string subfield_key;
};

struct Options_Subfield
{
    std::string key;
    unsigned int flags;
    int selected;
    Subfield_Path subfield_path;
    std::vector<std::string> options;
    Dropdown_Entry dropdown_list;

    void update(int delta);
    void reset_meta_mods();
    std::string to_string();
    std::string get_display();
    std::string get_selected_option();
};

using Subfield = std::variant<Int_Subfield, Options_Subfield>;

struct Event_Field
{
    std::string key;
    unsigned int flags;
    std::vector<Subfield> subfields;

    Display_Res get_display();

    Subfield& get_selected_subfield(Event_Editor& ee);

    int get_num_selectable_subfields();

    std::string to_string();

    bool should_set_subfield_na(
        Subfield& subfield,
        std::string type_key,
        std::string const_key
    );

    template<typename T>
    T& get_subfield(std::string key)
    {
        auto get_key_v = [](auto& value) { return value.key; };
        for (auto& sf : subfields) {
            if (std::visit(get_key_v, sf) == key) {
                return std::get<T>(sf);
            }
        }
    }
};

unsigned int get_flags(Subfield& subfield);

bool has_dropdown(Subfield& subfield);

bool can_be_mod_dest(Subfield& subfield);

void update(Subfield& subfield, int delta);

std::string get_key(Subfield& subfield);

std::string get_note_display(int note_num);
