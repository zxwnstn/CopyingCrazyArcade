#include "Etc/stdafx.h"
#include "CharacterManager.h"
#include "CrazyArcadeClass/Obj/Character/Player.h"
#include "CrazyArcadeClass/Obj/Character/Enemy.h"
#include "CrazyArcadeClass/Manager/ItemManager.h"
#include "Manager/SoundManager.h"

DEFINITION_SINGLE(CharacterManager)

CharacterManager::CharacterManager()
{
}
CharacterManager::~CharacterManager()
{
	release();
}

bool CharacterManager::init()
{
	//TODO : add other
	auto player = make_shared<Player>(0, 0);
	player->init(CharacterType::Bazzi);

	//auto enemy1 = make_shared<Enemy>(14, 10);
	//enemy1->init(CharacterType::Bazzi);

	characters.push_back(player);
	//characters.push_back(enemy1);
	return true;
}
void CharacterManager::update(float deltaTime)
{
	for (auto&e : characters)
		e->update(deltaTime);
	collision();
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
	characters.clear();
}

void CharacterManager::collision()
{
	collisionItem();
	collisionCharacter();
}
void CharacterManager::collisionItem()
{
	auto& items = GET_SINGLE(ItemManager)->GetItems();
	for (auto character = characters.begin(); character != characters.end(); ++character) {
		for (auto item = items.begin(); item != items.end(); ) {
			if (isRectRectCollision((*item)->getCollisionRect(), (*character)->getOtherCollisionRect())) {
				GET_SINGLE(SoundManager)->playSound("아이템얻기", 4);
				switch ((*item)->getType())
				{
				case ItemType::ItemRangeUp:
					(*character)->bombRangeUp();
					break;
				case ItemType::ItemSpeedUp:
					(*character)->speedUp();
					break;
				case ItemType::ItemBombLimitUp:
					(*character)->bombLimitUp();
					break;
				/*case ItemType::ItemKick:
					(*character)->getUsableItem(ItemType::ItemKick);
					break;
				case ItemType::ItemDart:
					(*character)->getUsableItem(ItemType::ItemDart);
					break;*/
				case ItemType::ItemNone:
					break;
				}
				item = items.erase(item);
			}
			else item++;
		}
	}
}
void CharacterManager::collisionCharacter()
{
	for (int i = 0; i < characters.size() - 1; ++i) {
		for (int j = 1; j < characters.size(); ++j) {
			if (characters[j]->getState() == CharacterState::CharacterInBalloon) {
				if (isRectRectCollision(characters[i]->getBlockCollisionRect(), characters[j]->getOtherCollisionRect())) {
					characters[j]->fallDown();
				}
			}
		}
	}
}