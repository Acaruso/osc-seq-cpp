#include "app_db.hpp"
#include <stdio.h>

template <typename T>
void Table<T>::print() {
	printf("table print\n");
}

template <typename T>
void Table<T>::push_back(T new_row) {
	data.push_back(new_row);
}

App_Db::App_Db() {
	Position position;
	position.x = 10;
	position.y = 10;
	position_table.data.push_back(position);

	Rect rect;
	rect.w = 10;
	rect.h = 10;
	rect_table.data.push_back(rect);

	print();

	//for (auto& elt : tables) {
	//	auto new_elt = static_cast<Table<Test_Table_Schema>*>(elt);
	//	new_elt->print();
	//}
}

std::vector<PositionRect> App_Db::getPositionRects() {
	std::vector<PositionRect> res;
	for (
		size_t i = 0; 
		i < position_table.data.size() && i < rect_table.data.size();
		i++
	) {
		PositionRect pr;
		pr.position = position_table.data[i];
		pr.rect = rect_table.data[i];
		res.push_back(pr);
	}
	return res;
}

void App_Db::print() {
	printf("app_db print\n");
}