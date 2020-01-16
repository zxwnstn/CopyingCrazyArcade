#include "Etc/stdafx.h"
#include "CharacterManager.h"
DEFINITION_SINGLE(CharacterManager)

CharacterManager::CharacterManager()
{
}


CharacterManager::~CharacterManager()
{
}

bool CharacterManager::init()
{
	auto player = make_shared<Player>();
	auto enemy = make_shared<Enemy>();

	characters.push_back(player);
	characters.push_back(enemy);

	return true;
}

void CharacterManager::update(float deltaTime)
{
	for (auto&e : characters)
		e->update(deltaTime);
}

void CharacterManager::render(HDC hdc)
{
	for (auto&e : characters)
		e->render(hdc);
}

void CharacterManager::debugRender(HDC hdc)
{
	for (auto&e : characters)
		e->debugRender(hdc);
}


void CharacterManager::release()
{
}

void CharacterManager::collision()
{
}
