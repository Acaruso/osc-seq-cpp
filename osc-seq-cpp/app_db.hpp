#pragma once
#include <vector>

struct Position {
	int x;
	int y;
};

struct Rect {
	int w;
	int h;
};

struct PositionRect {
	Position position;
	Rect rect;
};

template <typename T>
class Table {
public:
	std::vector<T> data;
	void print();
	void push_back(T new_row);
};

class App_Db {
public:
	std::vector<void*> tables;

	Table<Position> position_table;
	Table<Rect> rect_table;

	App_Db();
	void print();
	std::vector<PositionRect> getPositionRects();
};
