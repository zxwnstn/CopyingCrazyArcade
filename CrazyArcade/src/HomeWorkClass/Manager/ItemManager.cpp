#include "Etc/stdafx.h"
#include "ItemManager.h"
#include "HomeWorkClass/HomeWorkType.h"
#include "HomeWorkClass/Manager/BombManager.h"
DEFINITION_SINGLE(ItemManager)

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

bool ItemManager::init()
{

	return true;
}

void ItemManager::update(float deltaTime)
{
	for (auto& e : items)
		e->update(deltaTime);
	collision();
}

void ItemManager::render(HDC hdc)
{
	for (auto& e : items)
		e->render(hdc);
}

void ItemManager::debugRender(HDC hdc)
{
	for (auto& e : items)
		e->debugRender(hdc);
}

void ItemManager::release()
{
	items.clear();
}

void ItemManager::collision()
{
	auto& booms = GET_SINGLE(BombManager)->GetBooms();
	for (auto& e : booms) {
		for (auto it = items.begin(); it != items.end(); ) {
			if (isRectRectCollision(e->getRect(), (*it)->getRect())) {
				it = items.erase(it);
			}
			else ++it;
		}
	}
}

void ItemManager::push_Item(shared_ptr<Item> item)
{
	items.push_back(item);
}

void ItemManager::erase_Item(shared_ptr<Item> item)
{
	for (auto it = items.begin(); it != items.end(); ++it)
		if (*it == item) 
			items.erase(it);
}