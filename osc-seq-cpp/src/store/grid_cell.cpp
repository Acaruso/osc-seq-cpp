#include "grid_cell.hpp"

Grid_Cell::Grid_Cell()
    : toggled(false), probability(100), retrigger(1), has_meta(false)
{
    data.push_back({ "note", 48, 0, 100 });
    meta_target.row = -1;
    meta_target.col = -1;
}
