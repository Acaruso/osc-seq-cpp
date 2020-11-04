#include "app_db.hpp"
#include <stdio.h>

template <typename T>
void Table<T>::print() {
	printf("table print\n");
}

template <typename T>
void Table<T>::push(int entity_id, T new_row) {
	int idx = data.size();
	data.push_back(new_row);
	index[entity_id] = idx;
}

template <typename T>
void Table<T>::update(int entity_id, T row) {
    auto iter = index.find(entity_id);
    if (iter != index.end()) {
        int idx = iter->second;
        data[idx] = row;
    }
}

App_Db::App_Db() {
	next_entity_id = 0;

	Position_Rect pr;
	pr.position.x = 10;
	pr.position.y = 10;
	pr.rect.w = 10;
	pr.rect.h = 10;
	push_position_rect(pr);
}

void App_Db::push_position_rect(Position_Rect position_rect) {
	Position position;
	position.entity_id = next_entity_id;
	position.x = position_rect.position.x;
	position.y = position_rect.position.y;
	position_table.push(next_entity_id, position);

	Rect rect;
	rect.entity_id = next_entity_id;
	rect.w = position_rect.rect.w;
	rect.h = position_rect.rect.h;
	rect_table.push(next_entity_id, rect);

	++next_entity_id;
}

std::vector<Position_Rect> App_Db::get_position_rects() {
	// joining 2 tables, position and rect
	// iterate over all of 1st, join all of 2nd

	std::vector<Position_Rect> res;

	for (auto const& iter : position_table.index) {
		int entity_id = iter.first;
		int position_idx = iter.second;

		Position_Rect pr;
		pr.position = position_table.data[position_idx];

		auto rect_iter = rect_table.index.find(entity_id);
		if (rect_iter != rect_table.index.end()) {
			int rect_idx = rect_iter->second;
			pr.rect = rect_table.data[rect_idx];
			res.push_back(pr);
		}
	}

	return res;
}

void App_Db::update_position_rect(Position_Rect position_rect) {
    int entity_id = position_rect.position.entity_id;
    position_table.update(entity_id, position_rect.position);
    rect_table.update(entity_id, position_rect.rect);
}

void App_Db::print() {
	printf("app_db print\n");
}
