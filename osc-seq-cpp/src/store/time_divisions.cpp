#include "time_divisions.hpp"

Time_Divisions get_time_divisions(int bpm) {
    Time_Divisions td;

    td.n4 = 6000 / bpm;
    td.n8 = td.n4 / 2;
    td.n16 = td.n4 / 4;
    td.n2 = td.n4 * 2;
    td.n1 = td.n4 * 4;

    td.n12 = td.n4 / 3;
    td.n6 = td.n12 * 2;
    td.n3 = td.n6 * 2;

    return td;
}
