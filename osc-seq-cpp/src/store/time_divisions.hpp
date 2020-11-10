#pragma once

struct Time_Divisions {
    int n4;
    int n8;
    int n16;
    int n2;
    int n1;
    int n12;
    int n6;
    int n3;
};

Time_Divisions get_time_divisions(int bpm);
