#include "grid.hpp"

Grid_Cell::Grid_Cell() : toggled(false) {
}

Grid::Grid() {}

Grid::Grid(int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        std::vector<Grid_Cell> v;
        for (int k = 0; k < numCols; k++) {
            v.push_back(Grid_Cell());
        }
        data.push_back(v);
    }
}
