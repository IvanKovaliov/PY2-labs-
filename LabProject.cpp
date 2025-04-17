#include <windows.h>
#include <commctrl.h>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#include "resource.h"

using namespace std;

// Прототипы функций
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Lab1DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Lab2DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Lab4DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Lab5DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Lab6DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Lab7DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Lab8DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Lab9DlgProc(HWND, UINT, WPARAM, LPARAM);
void lab3_graphPlotting(HWND);

// Структура для лабораторной 4
struct Student {
    wstring name;
    int group;
    double averageScore;
};

// Класс для лабораторной 9
class Book {
public:
    wstring title;
    wstring author;
    int year;
    Book(wstring t = L"", wstring a = L"", int y = 0) : title(t), author(a), year(y) {}
    wstring display() {
        wstringstream ss;
        ss << L"Название: " << title << L", Автор: " << author << L", Год: " << year;
        return ss.str();
    }
};

// Глобальные переменные
HINSTANCE hInst;
const int WINDOW_WIDTH = 450;
const int WINDOW_HEIGHT = 200;

// Идентификаторы меню
#define ID_LAB1 40001
#define ID_LAB2 40002
#define ID_LAB3 40003
#define ID_LAB4 40004
#define ID_LAB5 40005
#define ID_LAB6 40006
#define ID_LAB7 40007
#define ID_LAB8 40008
#define ID_LAB9 40009
#define ID_EXIT 40010

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;
    InitCommonControls(); // Инициализация общих элементов управления

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, 
        LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_SIZEALL), 
        CreateSolidBrush(RGB(192, 192, 192)), NULL, L"LabWindowClass", NULL };
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Ошибка регистрации класса окна!", L"Ошибка", MB_OK | MB_ICONERROR);
        return 1;
    }

    HMENU hMenu = CreateMenu();
    HMENU hSubMenu = CreatePopupMenu();
    AppendMenu(hSubMenu, MF_STRING, ID_LAB1, L"Лаб. 1: Массивы");
    AppendMenu(hSubMenu, MF_STRING, ID_LAB2, L"Лаб. 2: Строки");
    AppendMenu(hSubMenu, MF_STRING, ID_LAB3, L"Лаб. 3: График");
    AppendMenu(hSubMenu, MF_STRING, ID_LAB4, L"Лаб. 4: Структуры");
    AppendMenu(hSubMenu, MF_STRING, ID_LAB5, L"Лаб. 5: Файлы");
    AppendMenu(hSubMenu, MF_STRING, ID_LAB6, L"Лаб. 6: Динамическая память");
    AppendMenu(hSubMenu, MF_STRING, ID_LAB7, L"Лаб. 7: Сортировка и поиск");
    AppendMenu(hSubMenu, MF_STRING, ID_LAB8, L"Лаб. 8: Рекурсия");
    AppendMenu(hSubMenu, MF_STRING, ID_LAB9, L"Лаб. 9: Классы");
    AppendMenu(hSubMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hSubMenu, MF_STRING, ID_EXIT, L"Выход");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Лабораторные работы");

    HWND hwnd = CreateWindow(L"LabWindowClass", L"Лабораторные работы", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, hMenu, hInstance, NULL);
    if (!hwnd) {
        MessageBox(NULL, L"Ошибка создания окна!", L"Ошибка", MB_OK | MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_LAB1:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, Lab1DlgProc);
            break;
        case ID_LAB2:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, Lab2DlgProc);
            break;
        case ID_LAB3:
            lab3_graphPlotting(hwnd);
            break;
        case ID_LAB4:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hwnd, Lab4DlgProc);
            break;
        case ID_LAB5:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hwnd, Lab5DlgProc);
            break;
        case ID_LAB6:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6), hwnd, Lab6DlgProc);
            break;
        case ID_LAB7:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG7), hwnd, Lab7DlgProc);
            break;
        case ID_LAB8:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG8), hwnd, Lab8DlgProc);
            break;
        case ID_LAB9:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG9), hwnd, Lab9DlgProc);
            break;
        case ID_EXIT:
            DestroyWindow(hwnd);
            break;
        }
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        GetClientRect(hwnd, &rect);
        FillRect(hdc, &rect, CreateSolidBrush(RGB(192, 192, 192)));
        EndPaint(hwnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Диалоговые процедуры
BOOL CALLBACK Lab1DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    static vector<int> arr;
    switch (msg) {
    case WM_INITDIALOG:
        arr.clear();
        SetDlgItemText(hwndDlg, IDC_INPUT, L"");
        SetDlgItemText(hwndDlg, IDC_OUTPUT, L"");
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_EXECUTE: {
            WCHAR buffer[256];
            GetDlgItemText(hwndDlg, IDC_INPUT, buffer, 256);
            wstringstream ss(buffer);
            arr.clear();
            int num;
            while (ss >> num) {
                arr.push_back(num);
            }
            if (arr.empty()) {
                MessageBox(hwndDlg, L"Введите хотя бы одно число!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            sort(arr.begin(), arr.end());
            wstringstream out;
            for (vector<int>::iterator it = arr.begin(); it != arr.end(); ++it) {
                out << *it << L" ";
            }
            SetDlgItemText(hwndDlg, IDC_OUTPUT, out.str().c_str());
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

BOOL CALLBACK Lab2DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_INITDIALOG:
        SetDlgItemText(hwndDlg, IDC_INPUT, L"");
        SetDlgItemText(hwndDlg, IDC_OUTPUT, L"");
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_EXECUTE: {
            WCHAR buffer[256];
            GetDlgItemText(hwndDlg, IDC_INPUT, buffer, 256);
            wstring str(buffer);
            if (str.empty()) {
                MessageBox(hwndDlg, L"Введите строку!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            int wordCount = 0;
            bool inWord = false;
            for (unsigned int i = 0; i < str.length(); ++i) {
                if (iswspace(str[i])) {
                    inWord = false;
                } else if (!inWord) {
                    inWord = true;
                    wordCount++;
                }
            }
            wstringstream out;
            out << L"Количество слов: " << wordCount;
            SetDlgItemText(hwndDlg, IDC_OUTPUT, out.str().c_str());
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

void lab3_graphPlotting(HWND hwnd) {
    InvalidateRect(hwnd, NULL, TRUE);
    UpdateWindow(hwnd);
    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    SelectObject(hdc, hPen);

    int centerX = WINDOW_WIDTH / 2;
    int centerY = WINDOW_HEIGHT / 2;
    double scaleX = 50.0;
    double scaleY = 50.0;

    MoveToEx(hdc, 0, centerY, NULL);
    LineTo(hdc, WINDOW_WIDTH, centerY);
    MoveToEx(hdc, centerX, 0, NULL);
    LineTo(hdc, centerX, WINDOW_HEIGHT);

    for (int px = 0; px < WINDOW_WIDTH; px++) {
        double x = (px - centerX) / scaleX;
        double y = 30 * sin(5 - 3 * x);
        int py = centerY - (int)(y * scaleY / 30);
        if (px == 0) {
            MoveToEx(hdc, px, py, NULL);
        } else {
            LineTo(hdc, px, py);
        }
    }

    DeleteObject(hPen);
    ReleaseDC(hwnd, hdc);
    MessageBox(hwnd, L"График построен. Нажмите OK для возврата.", L"Лаб. 3", MB_OK | MB_ICONINFORMATION);
}

BOOL CALLBACK Lab4DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    static vector<Student> students;
    switch (msg) {
    case WM_INITDIALOG:
        students.clear();
        SendDlgItemMessage(hwndDlg, IDC_LIST, LB_RESETCONTENT, 0, 0);
        SetDlgItemText(hwndDlg, IDC_NAME, L"");
        SetDlgItemText(hwndDlg, IDC_GROUP, L"");
        SetDlgItemText(hwndDlg, IDC_SCORE, L"");
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_EXECUTE: {
            WCHAR name[100], group[10], score[10];
            GetDlgItemText(hwndDlg, IDC_NAME, name, 100);
            GetDlgItemText(hwndDlg, IDC_GROUP, group, 10);
            GetDlgItemText(hwndDlg, IDC_SCORE, score, 10);
            if (wcslen(name) == 0) {
                MessageBox(hwndDlg, L"Введите имя студента!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            int g;
            double s;
            wstringstream ss1(group), ss2(score);
            if (!(ss1 >> g) || g <= 0) {
                MessageBox(hwndDlg, L"Введите корректный номер группы!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            if (!(ss2 >> s) || s < 0 || s > 100) {
                MessageBox(hwndDlg, L"Введите балл от 0 до 100!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            Student student = { name, g, s };
            students.push_back(student);
            wstringstream out;
            out << L"Имя: " << name << L", Группа: " << g << L", Балл: " << s;
            SendDlgItemMessage(hwndDlg, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)out.str().c_str());
            SetDlgItemText(hwndDlg, IDC_NAME, L"");
            SetDlgItemText(hwndDlg, IDC_GROUP, L"");
            SetDlgItemText(hwndDlg, IDC_SCORE, L"");
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

BOOL CALLBACK Lab5DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_INITDIALOG:
        SetDlgItemText(hwndDlg, IDC_INPUT, L"Пример записи в файл.");
        SetDlgItemText(hwndDlg, IDC_OUTPUT, L"");
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_EXECUTE: {
            WCHAR buffer[256];
            GetDlgItemText(hwndDlg, IDC_INPUT, buffer, 256);
            wstring input(buffer);
            ofstream outFile("output.txt");
            if (!outFile) {
                MessageBox(hwndDlg, L"Ошибка создания файла!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            string narrowInput(input.begin(), input.end());
            outFile << narrowInput;
            outFile.close();

            ifstream inFile("output.txt");
            if (!inFile) {
                MessageBox(hwndDlg, L"Ошибка чтения файла!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            string line, content;
            while (getline(inFile, line)) {
                content += line + "\n";
            }
            inFile.close();
            wstring wideContent(content.begin(), content.end());
            SetDlgItemText(hwndDlg, IDC_OUTPUT, wideContent.c_str());
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

BOOL CALLBACK Lab6DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_INITDIALOG:
        SetDlgItemText(hwndDlg, IDC_INPUT, L"");
        SetDlgItemText(hwndDlg, IDC_OUTPUT, L"");
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_EXECUTE: {
            WCHAR buffer[256];
            GetDlgItemText(hwndDlg, IDC_INPUT, buffer, 256);
            wstringstream ss(buffer);
            int rows, cols;
            if (!(ss >> rows >> cols) || rows <= 0 || cols <= 0) {
                MessageBox(hwndDlg, L"Введите два положительных числа (строки столбцы)!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            int** matrix = new int*[rows];
            for (int i = 0; i < rows; i++) {
                matrix[i] = new int[cols];
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] = rand() % 100;
                }
            }
            wstringstream out;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    out << matrix[i][j] << L"\t";
                }
                out << L"\n";
            }
            for (int i = 0; i < rows; i++) {
                delete[] matrix[i];
            }
            delete[] matrix;
            SetDlgItemText(hwndDlg, IDC_OUTPUT, out.str().c_str());
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

BOOL CALLBACK Lab7DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    static vector<int> arr;
    switch (msg) {
    case WM_INITDIALOG:
        arr.clear();
        SetDlgItemText(hwndDlg, IDC_INPUT, L"");
        SetDlgItemText(hwndDlg, IDC_AUTHOR, L"");
        SetDlgItemText(hwndDlg, IDC_OUTPUT, L"");
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_EXECUTE: {
            WCHAR buffer[256];
            GetDlgItemText(hwndDlg, IDC_INPUT, buffer, 256);
            wstringstream ss(buffer);
            arr.clear();
            int num;
            while (ss >> num) {
                arr.push_back(num);
            }
            if (arr.empty()) {
                MessageBox(hwndDlg, L"Введите массив!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            int target;
            WCHAR targetBuf[10];
            GetDlgItemText(hwndDlg, IDC_AUTHOR, targetBuf, 10);
            wstringstream ssTarget(targetBuf);
            if (!(ssTarget >> target)) {
                MessageBox(hwndDlg, L"Введите число для поиска!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            sort(arr.begin(), arr.end());
            wstringstream out;
            out << L"Отсортированный массив: ";
            for (vector<int>::iterator it = arr.begin(); it != arr.end(); ++it) {
                out << *it << L" ";
            }
            vector<int>::iterator it = lower_bound(arr.begin(), arr.end(), target);
            if (it != arr.end() && *it == target) {
                out << L"\nЧисло " << target << L" найдено на позиции: " << (it - arr.begin());
            } else {
                out << L"\nЧисло " << target << L" не найдено.";
            }
            SetDlgItemText(hwndDlg, IDC_OUTPUT, out.str().c_str());
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

BOOL CALLBACK Lab8DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_INITDIALOG:
        SetDlgItemText(hwndDlg, IDC_INPUT, L"");
        SetDlgItemText(hwndDlg, IDC_OUTPUT, L"");
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_EXECUTE: {
            WCHAR buffer[256];
            GetDlgItemText(hwndDlg, IDC_INPUT, buffer, 256);
            wstringstream ss(buffer);
            int n;
            if (!(ss >> n) || n < 0) {
                MessageBox(hwndDlg, L"Введите неотрицательное число!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            long long factorial(int n);
            wstringstream out;
            out << L"Факториал " << n << L" = " << factorial(n);
            SetDlgItemText(hwndDlg, IDC_OUTPUT, out.str().c_str());
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

BOOL CALLBACK Lab9DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam) {
    static vector<Book> books;
    switch (msg) {
    case WM_INITDIALOG:
        books.clear();
        SendDlgItemMessage(hwndDlg, IDC_LIST, LB_RESETCONTENT, 0, 0);
        SetDlgItemText(hwndDlg, IDC_TITLE, L"");
        SetDlgItemText(hwndDlg, IDC_AUTHOR, L"");
        SetDlgItemText(hwndDlg, IDC_YEAR, L"");
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_EXECUTE: {
            WCHAR title[100], author[100], year[10];
            GetDlgItemText(hwndDlg, IDC_TITLE, title, 100);
            GetDlgItemText(hwndDlg, IDC_AUTHOR, author, 100);
            GetDlgItemText(hwndDlg, IDC_YEAR, year, 10);
            if (wcslen(title) == 0 || wcslen(author) == 0) {
                MessageBox(hwndDlg, L"Введите название и автора!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            int y;
            wstringstream ss(year);
            if (!(ss >> y) || y < 0) {
                MessageBox(hwndDlg, L"Введите корректный год!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            Book book(title, author, y);
            books.push_back(book);
            SendDlgItemMessage(hwndDlg, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)book.display().c_str());
            SetDlgItemText(hwndDlg, IDC_TITLE WCHAR title[100], author[100], year[10];
            GetDlgItemText(hwndDlg, IDC_TITLE, title, 100);
            GetDlgItemText(hwndDlg, IDC_AUTHOR, author, 100);
            GetDlgItemText(hwndDlg, IDC_YEAR, year, 10);
            if (wcslen(title) == 0 || wcslen(author) == 0) {
                MessageBox(hwndDlg, L"Введите название и автора!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            int y;
            wstringstream ss(year);
            if (!(ss >> y) || y < 0) {
                MessageBox(hwndDlg, L"Введите корректный год!", L"Ошибка", MB_OK | MB_ICONERROR);
                return TRUE;
            }
            Book book(title, author, y);
            books.push_back(book);
            SendDlgItemMessage(hwndDlg, IDC_LIST, LB_ADDSTRING, 0, (LPARAM)book.display().c_str());
            SetDlgItemText(hwndDlg, IDC_TITLE, L"");
            SetDlgItemText(hwndDlg, IDC_AUTHOR, L"");
            SetDlgItemText(hwndDlg, IDC_YEAR, L"");
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}
