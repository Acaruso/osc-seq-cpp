#include "grid_cell.hpp"
#include "../util.hpp"

Target::Target() {}

Target::Target(int row, int col) : row(row), col(col) {}

Grid_Cell_Data::Grid_Cell_Data() {}

Grid_Cell_Data::Grid_Cell_Data(
    std::string key,
    int int_value,
    int min,
    int max,
    unsigned int options
) : key(key), int_value(int_value), min(min), max(max), options(options) {}

void Grid_Cell_Data::increment()
{
    if (options & Op_Int) {
        int_value = clamp(int_value + 1, min, max);
    }
}

void Grid_Cell_Data::decrement()
{
    if (options & Op_Int) {
        int_value = clamp(int_value - 1, min, max);
    }
}

std::string Grid_Cell_Data::get_value_str()
{
    if (options & Op_Int) {
        return std::to_string(int_value);
    }
}

Grid_Cell::Grid_Cell()
: toggled(false), has_meta(false)
{
    data.push_back({ "probability", 100, 0, 101, Op_Int });
    data.push_back({ "retrigger", 1, 1, 17, Op_Int });
    data.push_back({ "note", 48, 0, 101, Op_Int | Op_Osc_Data });

    meta_data.push_back({ "num targets", 0, 0, 10, Op_Int });

    // data.push_back({ "note", 48, 0, 100 });

    // meta_target.row = -1;
    // meta_target.col = -1;
}
