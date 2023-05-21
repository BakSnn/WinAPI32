#include <windows.h>
#include <cmath>

const int N_MAX = 11;
int x[N_MAX], y[N_MAX], R[N_MAX];
int V[N_MAX], W[N_MAX], t[N_MAX];
float a[N_MAX];
int n = 0, timer = 0, f = 0;
int m = -1;
int isAnim;
int X, Y;
float pi = 3.14;
HDC hDC;
PAINTSTRUCT ps;
RECT rect;
BOOL isAnimating = false;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch (Message) {

	case WM_DESTROY: {
		PostQuitMessage(0);
		KillTimer(hwnd, 1);
		break;
	}
	case WM_PAINT: {
		hDC = BeginPaint(hwnd, &ps);
		HPEN hP1, hP2;
		hP1 = CreatePen(PS_SOLID, 1, RGB(148, 0, 211));
		hP2 = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));

		for (int i = 0; i < n + 1; i++) {
			if (W[i] == 1) {
				SelectObject(hDC, hP2);
			}
			else {
				SelectObject(hDC, hP1);
			}
			if (V[i] == 1) {
				if (t[i] == 1) {
					MoveToEx(hDC, x[i] - R[i] * sin(a[i]), y[i] - R[i] * cos(a[i]), NULL);
					LineTo(hDC, x[i] - R[i] * cos(pi / 6 + a[i]), y[i] + R[i] * sin(pi / 6 + a[i]));
					LineTo(hDC, x[i] + R[i] * cos(pi / 6 - a[i]), y[i] - R[i] * sin(a[i] - pi / 6));
					LineTo(hDC, x[i] - R[i] * sin(a[i]), y[i] - R[i] * cos(a[i]));
				}
				if (t[i] == 2) {
					MoveToEx(hDC, x[i] - R[i] * sin(a[i]), y[i] - R[i] * cos(a[i]), NULL);
					LineTo(hDC, x[i] - R[i] * cos(a[i]), y[i] + R[i] * sin(a[i]));
					LineTo(hDC, x[i] + R[i] * sin(a[i]), y[i] + R[i] * cos(a[i]));
					LineTo(hDC, x[i] + R[i] * cos(a[i]), y[i] - R[i] * sin(a[i]));
					LineTo(hDC, x[i] - R[i] * sin(a[i]), y[i] - R[i] * cos(a[i]));
				}
				if (t[i] == 3) {
					MoveToEx(hDC, x[i] - R[i] * cos(pi / 4 - a[i]), y[i] - R[i] * cos(pi / 4 + a[i]), NULL);
					LineTo(hDC, x[i] - R[i] * cos(pi / 4 + a[i]), y[i] + R[i] * sin(pi / 4 + a[i]));
					LineTo(hDC, x[i] + R[i] * cos(pi / 4 - a[i]), y[i] - R[i] * sin(a[i] - pi / 4));
					LineTo(hDC, x[i] + R[i] * cos(pi / 4 + a[i]), y[i] - R[i] * sin(pi / 4 + a[i]));
					LineTo(hDC, x[i] - R[i] * cos(pi / 4 - a[i]), y[i] - R[i] * cos(pi / 4 + a[i]));
				}
			}
		}
		EndPaint(hwnd, &ps);
		break;
	}

	case WM_KEYDOWN: {
		if (wParam == VK_F5) {

			if (timer == 0)
			{
				isAnimating = true;
				SetTimer(hwnd, 1, 100, NULL);
				timer = 1;
				OutputDebugStringW(L"Анимация включена \n");
			}
			else
			{
				isAnimating = false;
				KillTimer(hwnd, 1);
				timer = 0;
				OutputDebugStringW(L"Анимация выключена \n");
			}
		}
		if (!isAnimating) {
			if (wParam == VK_F1) {
				if (n < N_MAX - 1) {
					n++;
					m = n - 1;
					x[m] = 100;
					y[m] = 100;
					R[m] = 50;
					V[m] = 1;
					t[m] = 1;
					a[m] = 0;
					for (int j = 0; j <= n; j++) {
						if (W[j] != 0) W[j] = 0;
					}
					W[m] = 1;
				}
				OutputDebugStringW(L"Треугольник \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}
			if (wParam == VK_F2) {
				if (n < N_MAX - 1) {
					n++;
					m = n - 1;
					x[m] = 200;
					y[m] = 200;
					R[m] = 50;
					V[m] = 1;
					t[m] = 2;
					a[m] = 0;
					for (int j = 0; j <= n; j++) {
						if (W[j] != 0) W[j] = 0;
					}
					W[m] = 1;
				}
				OutputDebugStringW(L"Ромб \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}
			if (wParam == VK_F3) {
				if (n < N_MAX - 1) {
					n++;
					m = n - 1;
					x[m] = 300;
					y[m] = 300;
					R[m] = 50;
					V[m] = 1;
					t[m] = 3;
					a[m] = 0;
					for (int j = 0; j <= n; j++) {
						if (W[j] != 0) W[j] = 0;
					}
					W[m] = 1;
				}
				OutputDebugStringW(L"Квадрат \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}
			if (wParam == VK_LEFT) {
				W[m] = 0;
				if (m > 0) {
					m--;
				}
				else {
					m = n - 1;
				}
				W[m] = 1;
				OutputDebugStringW(L"Переключение фигуры влево \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}
			if (wParam == VK_RIGHT) {
				W[m] = 0;
				if (m < n - 1) {
					m++;
				}
				else {
					m = 0;
				}
				W[m] = 1;
				OutputDebugStringW(L"Переключение фигуры вправо \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}
			if (wParam == VK_UP) {
				R[m] += 5;
				OutputDebugStringW(L"Увеличение фигуры \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}
			if (wParam == VK_DOWN) {
				R[m] -= 5;
				OutputDebugStringW(L"Уменьшение фигуры \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}
			if (wParam == VK_F8) {
				a[m] += pi / 12;
				OutputDebugStringW(L"Поворот влево \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}
			if (wParam == VK_F9) {
				a[m] -= pi / 12;
				OutputDebugStringW(L"Поворот вправо \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}
			if (wParam == VK_SPACE) {
				if (f == 0)
					f = 1;
				else
					f = 0;
				OutputDebugStringW(L"Пробел нажат \n");
				GetClientRect(hwnd, &rect);
				InvalidateRect(hwnd, &rect, -1);
				UpdateWindow(hwnd);
			}

			if (wParam == VK_DELETE) {
				if (n >= 1) {
					x[m] = y[m] = R[m] = V[m] = t[m] = W[m] = 0;
					if (m != n) {
						for (int z = m + 1; z <= n - 1; z++) {
							x[z - 1] = x[z];
							y[z - 1] = y[z];
							R[z - 1] = R[z];
							V[z - 1] = V[z];
							t[z - 1] = t[z];
							W[z - 1] = W[z];
							a[z - 1] = a[z];
						}
					}

					if (m != 0) m--;
					n--;
					W[m] = 1;
					GetClientRect(hwnd, &rect);
					InvalidateRect(hwnd, &rect, -1);
					UpdateWindow(hwnd);
				}
			}
			break;
		}
		else {
			return 0;
		}
	}
	case WM_LBUTTONDOWN: {
		if (!isAnimating) {
			X = LOWORD(lParam);
			Y = HIWORD(lParam);

			x[m] = X;
			y[m] = Y;
			OutputDebugStringW(L"ЛКМ нажата \n");
			GetClientRect(hwnd, &rect);
			InvalidateRect(hwnd, &rect, -1);
			UpdateWindow(hwnd);

			break;
		}
	}
	case WM_RBUTTONDOWN: {
		if (!isAnimating) {
			X = LOWORD(lParam);
			Y = HIWORD(lParam);

			if (f == 0) {
				a[m] = -a[m];
				if (X >= x[m]) {
					x[m] = X + X - x[m];
				}
				else {
					x[m] = X - (x[m] - X);
				}
			}
			else {
				a[m] = -a[m] + pi;
				if (Y >= y[m]) {
					y[m] = Y + Y - y[m];
				}
				else {
					y[m] = Y - (y[m] - Y);
				}
			}
			OutputDebugStringW(L"ПКМ нажата \n");
			GetClientRect(hwnd, &rect);
			InvalidateRect(hwnd, &rect, -1);
			UpdateWindow(hwnd);
			break;
		}
	}

	case WM_TIMER: {
		isAnimating = false;
		float r[N_MAX] = { 0.0 };

		for (int i = 0; i < n; i++) {
			if (i != m) {
				float dx = x[m] - x[i];
				float dy = y[m] - y[i];
				float distance = sqrt(dx * dx + dy * dy);
				a[i] -= pi / 50;
				x[i] = x[m] + cos(a[i]) * distance;
				y[i] = y[m] + sin(a[i]) * distance;
			}
			else {
				a[i] += pi / 55;
				x[i] = x[i] + cos(a[i]) * r[i]; // r[i] чтобы задатьь радиус окружности фигур
				y[i] = y[i] + sin(a[i]) * r[i];
			}
			MSG msg;
			while (PeekMessage(&msg, NULL, WM_KEYFIRST, WM_KEYLAST, PM_REMOVE)) {}

		}
		isAnimating = true;
		GetClientRect(hwnd, &rect);
		InvalidateRect(hwnd, &rect, -1);
		UpdateWindow(hwnd);
		break;
	}
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;
	memset(&wc, 0, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = L"WindowClass";
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"WindowClass", L"Caption", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		640,
		480,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
