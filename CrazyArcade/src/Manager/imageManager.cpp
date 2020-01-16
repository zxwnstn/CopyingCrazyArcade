#include "Etc/stdafx.h"
#include "imageManager.h"

imageManager::imageManager()
{
}

imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	deleteAll();
}

Image * imageManager::addImage(string strKey, int width, int height)
{
	Image* img = findImage(strKey);
	if (img) 
		return img;

	img = new Image;

	if (FAILED(img->init(width, height))) {
		SAFE_DELETE(img);
		return NULL;
	}

	//이미지를 이미지 목록에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * imageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transCollor)
{
	Image* img = findImage(strKey);
	if (img)
		return img;

	img = new Image;

	if (FAILED(img->init(fileName, width, height, isTrans, transCollor))) {
		SAFE_DELETE(img);
		return NULL;
	}

	//이미지를 이미지 목록에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * imageManager::addImage(string strKey, const char * fileName, int x, int y, int width, int height, bool isTrans, COLORREF transCollor)
{
	Image* img = findImage(strKey);
	if (img)
		return img;

	img = new Image;

	if (FAILED(img->init(fileName, x, y, width, height, 1, 1, isTrans, RGB(255, 0, 255)))) {
		SAFE_DELETE(img);
		return NULL;
	}

	//이미지를 이미지 목록에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transCollor)
{
	Image* img = findImage(strKey);
	if (img)
		return img;

	img = new Image;

	if (FAILED(img->init(fileName,width, height, frameX, frameY, isTrans, transCollor))) {
		SAFE_DELETE(img);
		return NULL;
	}

	//이미지를 이미지 목록에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}

Image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transCollor)
{
	Image* img = findImage(strKey);
	if (img)
		return img;

	img = new Image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transCollor))) {
		SAFE_DELETE(img);
		return NULL;
	}

	//이미지를 이미지 목록에 추가
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


Image * imageManager::findImage(string strkey)
{
	mapImageIter key = _mImageList.find(strkey);
	if (key != _mImageList.end())
		return key->second;
	return nullptr;
}

bool imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);
	if (key != _mImageList.end()) {
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);
		return true;
	}
	return false;
}

bool imageManager::deleteAll()
{
	mapImageIter it = _mImageList.begin();

	for (it; it != _mImageList.end();) {
		if (it->second != NULL) {
			SAFE_DELETE(it->second);
			it = _mImageList.erase(it);
		}
		else ++it;
	}
	_mImageList.clear();
	return true;
}

void imageManager::render(string strKey, HDC hdc)
{
	Image* img = findImage(strKey);
	if (img)
		img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = findImage(strKey);
	if (img)
		img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	Image* img = findImage(strKey);
	if (img)
		img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	Image* img = findImage(strKey);
	if (img)
		img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	Image* img = findImage(strKey);
	if (img) 
		img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	Image* img = findImage(strKey);
	if (img) 
		img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	Image* img = findImage(strKey);
	if (img)
		img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}
