#include "grid_cell.hpp"

Target::Target() {}

Target::Target(int row, int col) : row(row), col(col) {}

Grid_Cell_Data::Grid_Cell_Data() {}

Grid_Cell_Data::Grid_Cell_Data(
    std::string key,
    int value,
    int min,
    int max,
    unsigned int options
) : key(key), value(value), min(min), max(max), options(options) {}

Grid_Cell::Grid_Cell()
: toggled(false)
{
    data.push_back({ "probability", 100, 0, 101, Op_Int });
    data.push_back({ "retrigger", 1, 1, 17, Op_Int });
    data.push_back({ "note", 48, 0, 101, Op_Int | Op_Osc_Data });

    // data.push_back({ "note", 48, 0, 100 });
    // meta_target.row = -1;
    // meta_target.col = -1;
}
