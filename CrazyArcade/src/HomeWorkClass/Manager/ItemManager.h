#pragma once
#include "HomeWorkClass/Obj/Item/Item.h"

class ItemManager
{
public:
	bool init();
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();

	void collision();
	void push_Item(shared_ptr<Item> item);
	void erase_Item(shared_ptr<Item> item);
	auto& GetItems() { return items; }

public:
	vector<shared_ptr<Item>> items;

private:
	DECLARE_SINGLE(ItemManager)
};

