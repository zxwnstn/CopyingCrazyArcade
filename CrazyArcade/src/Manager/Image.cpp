#include "Etc/stdafx.h"
#include "Image.h"

//for alpha blending library
#pragma comment(lib, "msimg32.lib")

Image::Image()
	: _imageInfo(NULL), _isTrans(false), _transColor(RGB(0, 0, 0))
{
}


Image::~Image()
{
	SAFE_DELETE(_imageInfo);
}

HRESULT Image::init(int width, int height)
{
	if (_imageInfo != nullptr) {
		release();
	}

	//image settup
	HDC hdc = GetDC(m_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit1 = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//blend settup
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;
	
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit1 = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	if (_imageInfo->hBit == NULL) {
		release();
		return E_FAIL;
	}
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL)
		return E_FAIL;
	if (_imageInfo != NULL)
		release();
	for (int i = 0; i < 255; ++i) {
		if (fileName[i] == NULL) {
			break;
		}
		_fileName[i] = fileName[i];
	}
	HDC hdc = GetDC(m_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit1 = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//blend settup
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit1 = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	int len = strlen(fileName);
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL) {
		release();
		return E_FAIL;
	}
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL)
		return E_FAIL;
	if (_imageInfo != NULL)
		release();
	for (int i = 0; i < 255; ++i) {
		if (fileName[i] == NULL) {
			break;
		}
		_fileName[i] = fileName[i];
	}

	HDC hdc = GetDC(m_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit1 = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->currentFrameY = frameY - 1;
	_imageInfo->FrameWidth = width / frameX;
	_imageInfo->FrameHeight = height / frameY;
	_imageInfo->currentFrameX = frameX;
	_imageInfo->currentFrameY = frameY;

	//blend settup
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit1 = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	int len = strlen(fileName);
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL) {
		release();
		return E_FAIL;
	}
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL)
		return E_FAIL;
	if (_imageInfo != NULL)
		release();
	for (int i = 0; i < 255; ++i) {
		if (fileName[i] == NULL) {
			break;
		}
		_fileName[i] = fileName[i];
	}

	HDC hdc = GetDC(m_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit1 = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->currentFrameY = frameY - 1;
	_imageInfo->FrameWidth = width / frameX;
	_imageInfo->FrameHeight = height / frameY;
	_imageInfo->currentFrameX = frameX;
	_imageInfo->currentFrameY = frameY;

	//blend settup
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit1 = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	int len = strlen(fileName);
	strcpy_s(_fileName, len + 1, fileName);
	_isTrans = isTrans;
	_transColor = transColor;

	if (_imageInfo->hBit == NULL) {
		release();
		return E_FAIL;
	}
	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}


void Image::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

void Image::release()
{
	if (_imageInfo) {
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit1);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}
}

void Image::render(HDC hdc)
{
	if (_isTrans) {
		//비트맵을 불러올때, 특정색상을 제외하고 복사하는 함수
		GdiTransparentBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC,
							   0, 0, _imageInfo->width, _imageInfo->height, _transColor);
	}
	else {
		//SRCCOPY : 가로세로를 재정의해서 복사하겟다.
		//DC간 데이터를 고속 복사
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, 
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) {
		GdiTransparentBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, 
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
	}
	else {
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, 
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//dest는 memdc에 그릴 좌표 src는 이미지를 가져올 좌표
void Image::render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight)
{
	if (_isTrans) {
		GdiTransparentBlt(hdc, destX, destY, srcWidth, srcHeight, 
			_imageInfo->hMemDC, srcX, srcY, srcWidth, srcHeight, _transColor);
	}
	else {
		BitBlt(hdc, destX, destY, srcWidth, srcHeight, 
			_imageInfo->hMemDC, srcX, srcY, SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans) {
		GdiTransparentBlt(hdc, destX, destY, _imageInfo->FrameWidth, _imageInfo->FrameHeight, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->FrameWidth, _imageInfo->currentFrameY * _imageInfo->FrameHeight, 
			_imageInfo->FrameWidth, _imageInfo->FrameHeight, _transColor);
	}
	else {
		BitBlt(hdc, destX, destY, _imageInfo->FrameWidth, _imageInfo->FrameHeight, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->FrameWidth, _imageInfo->currentFrameY * _imageInfo->FrameHeight, SRCCOPY);
	}
}

void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (_isTrans) {
		GdiTransparentBlt(hdc, destX, destY, _imageInfo->FrameWidth, _imageInfo->FrameHeight, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->FrameWidth, _imageInfo->currentFrameY * _imageInfo->FrameHeight,
			_imageInfo->FrameWidth, _imageInfo->FrameHeight, _transColor);
	}
	else {
		BitBlt(hdc, destX, destY, _imageInfo->FrameWidth, _imageInfo->FrameHeight, _imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->FrameWidth, _imageInfo->currentFrameY * _imageInfo->FrameHeight, SRCCOPY);
	}
}

void Image::loopRender(HDC hdc, LPRECT drawArea, int offsetX, int offsetY)
{
	//보정
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	RECT rcSour;

	int sourWidth;
	int sourHeight;

	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 loop
	for (int y = 0; y < drawAreaH; y += sourHeight) {
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//영역 이탈
		if (y + sourHeight > drawAreaH) {
			//넘어간 그림의 값만큼 바텀을 올려준다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;
		//가로 loop
		for (int x = 0; x < drawAreaW; x += sourWidth) {
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;
			//영역 이탈
			if (x + sourWidth > drawAreaW) {
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

void Image::loopAlphaRender(HDC hdc, LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//보정
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	RECT rcSour;

	int sourWidth;
	int sourHeight;

	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 loop
	for (int y = 0; y < drawAreaH; y += sourHeight) {
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//영역 이탈
		if (y + sourHeight > drawAreaH) {
			//넘어간 그림의 값만큼 바텀을 올려준다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;
		//가로 loop
		for (int x = 0; x < drawAreaW; x += sourWidth) {
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;
			//영역 이탈
			if (x + sourWidth > drawAreaW) {
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top, alpha);
		}
	}
}

//알파렌더 - 투명값 먹이기 범위 0 - 25
void Image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (_isTrans) {
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, 
			hdc, 0, 0, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else {
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (_isTrans) {
		BitBlt(_blendImage->hMemDC, destX, destY, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, destX, destY, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else {
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (_isTrans) {
		BitBlt(_blendImage->hMemDC, destX, destY, sourWidth, sourHeight,
			hdc, sourX, sourY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, destX, destY, _imageInfo->width, _imageInfo->height,
			hdc, sourX, sourY, sourWidth, sourHeight, _transColor);

		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	} 
	else {
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}
