#pragma once
#include <vector>
#include <map>
#include <tuple>
#include <string>

struct Position {
	int entity_id;
	int x;
	int y;
};

struct Rect {
	int entity_id;
	int w;
	int h;
};

struct Position_Rect {
	Position position;
	Rect rect;
};

template <typename T>
class Table {
public:
	std::vector<T> data;
	std::map<int, int> index;
	void print();
	void push(int entity_id, T new_row);
    void update(int entity_id, T new_row);
};

class App_Db {
public:
	int next_entity_id;
	Table<Position> position_table;
	Table<Rect> rect_table;

	App_Db();
	void print();

	void push_position_rect(Position_Rect position_rect);
	std::vector<Position_Rect> get_position_rects();
	void update_position_rect(Position_Rect position_rect);
};
