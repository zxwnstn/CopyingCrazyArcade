#include "Etc/stdafx.h"
#include "Scene.h"


HRESULT Scene::init()
{
	IMAGEMANAGER->addImage("배경", "../Common_Images/사나.bmp", WINSIZEX, WINSIZEY);
	return S_OK;
}

void Scene::release()
{
	//IMAGEMANAGER->deleteImage("배경");
}

void Scene::update(float deltaTime)
{
	
}

void Scene::render()
{
	IMAGEMANAGER->render("배경", getMemDC());
}

Scene::Scene()
{
}


Scene::~Scene()
{
}
