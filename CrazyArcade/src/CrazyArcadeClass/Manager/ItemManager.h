#pragma once
#include "CrazyArcadeClass/Obj/Item/Item.h"

class ItemManager{
public:
	//interface
	bool init();
	void update(float deltaTime);
	void render(HDC hdc);
	void debugRender(HDC hdc);
	void release();

public:
	//getter
	auto& GetItems() { return items; }

public:
	vector<shared_ptr<Item>> items;

private:
	DECLARE_SINGLE(ItemManager)
};

