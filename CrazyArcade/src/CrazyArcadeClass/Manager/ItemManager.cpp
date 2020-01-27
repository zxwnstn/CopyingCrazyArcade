#include "Etc/stdafx.h"
#include "ItemManager.h"
#include "BombManager.h"
DEFINITION_SINGLE(ItemManager)

ItemManager::ItemManager()
{
}
ItemManager::~ItemManager()
{
	release();
}

bool ItemManager::init()
{
	return true;
}
void ItemManager::update(float deltaTime)
{
	for (auto& e : items)
		e->update(deltaTime);
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