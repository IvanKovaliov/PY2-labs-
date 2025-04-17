#include <windows.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

// Прототипы функций
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void lab1_arrayProcessing();
void lab2_stringProcessing();
void lab3_graphPlotting(HWND);
void lab4_structProcessing();
void lab5_fileProcessing();
void lab6_dynamicMemory();
void lab7_sortAndSearch();
void lab8_recursion();
void lab9_classes();
void setRussianLocale();

// Структура для лабораторной 4
struct Student {
    string name;
    int group;
    double averageScore;
};

// Класс для лабораторной 9
class Book {
private:
    string title;
    string author;
    int year;
public:
    Book(string t = "", string a = "", int y = 0) : title(t), author(a), year(y) {}
    void display() {
        cout << "Название: " << title << ", Автор: " << author << ", Год: " << year << "\n";
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
    setRussianLocale();

    // Создание класса окна
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, 
        LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_SIZEALL), 
        CreateSolidBrush(RGB(192, 192, 192)), NULL, L"LabWindowClass", NULL };
    RegisterClassEx(&wc);

    // Создание меню
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

    // Создание окна
    HWND hwnd = CreateWindow(L"LabWindowClass", L"Лабораторные работы", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, hMenu, hInstance, NULL);

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
        case ID_LAB1: lab1_arrayProcessing(); break;
        case ID_LAB2: lab2_stringProcessing(); break;
        case ID_LAB3: lab3_graphPlotting(hwnd); break;
        case ID_LAB4: lab4_structProcessing(); break;
        case ID_LAB5: lab5_fileProcessing(); break;
        case ID_LAB6: lab6_dynamicMemory(); break;
        case ID_LAB7: lab7_sortAndSearch(); break;
        case ID_LAB8: lab8_recursion(); break;
        case ID_LAB9: lab9_classes(); break;
        case ID_EXIT: DestroyWindow(hwnd); break;
        }
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
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

void setRussianLocale() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void lab1_arrayProcessing() {
    cout << "Лабораторная работа 1: Обработка массивов\n";
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    if (n <= 0) {
        cout << "Некорректный размер!\n";
        return;
    }
    vector<int> arr(n);
    cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    cout << "Отсортированный массив:\n";
    for (vector<int>::iterator it = arr.begin(); it != arr.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\nНажмите Enter для возврата в меню...\n";
    cin.ignore();
    cin.get();
}

void lab2_stringProcessing() {
    cout << "Лабораторная работа 2: Обработка строк\n";
    string str;
    cout << "Введите строку: ";
    cin.ignore();
    getline(cin, str);
    int wordCount = 0;
    bool inWord = false;
    for (unsigned int i = 0; i < str.length(); ++i) {
        if (isspace(str[i])) {
            inWord = false;
        } else if (!inWord) {
            inWord = true;
            wordCount++;
        }
    }
    cout << "Количество слов в строке: " << wordCount << "\n";
    cout << "Нажмите Enter для возврата в меню...\n";
    cin.get();
}

void lab3_graphPlotting(HWND hwnd) {
    cout << "Лабораторная работа 3: Построение графика f(x) = 30*sin(5-3x)\n";
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
    cout << "График построен. Нажмите Enter для возврата в меню...\n";
    cin.ignore();
    cin.get();
}

void lab4_structProcessing() {
    cout << "Лабораторная работа 4: Работа со структурами\n";
    vector<Student> students;
    int n;
    cout << "Введите количество студентов: ";
    cin >> n;
    if (n <= 0) {
        cout << "Некорректное количество!\n";
        return;
    }
    cin.ignore();
    for (int i = 0; i < n; i++) {
        Student s;
        cout << "Имя студента: ";
        getline(cin, s.name);
        cout << "Группа: ";
        cin >> s.group;
        cout << "Средний балл: ";
        cin >> s.averageScore;
        cin.ignore();
        students.push_back(s);
    }
    cout << "Список студентов:\n";
    for (vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
        cout << "Имя: " << it->name << ", Группа: " << it->group << ", Средний балл: " << it->averageScore << "\n";
    }
    cout << "Нажмите Enter для возврата в меню...\n";
    cin.get();
}

void lab5_fileProcessing() {
    cout << "Лабораторная работа 5: Работа с файлами\n";
    ofstream outFile("output.txt");
    if (!outFile) {
        cout << "Ошибка создания файла!\n";
        return;
    }
    outFile << "Пример записи в файл.\n";
    outFile.close();
    
    ifstream inFile("output.txt");
    if (!inFile) {
        cout << "Ошибка чтения файла!\n";
        return;
    }
    string line;
    cout << "Содержимое файла:\n";
    while (getline(inFile, line)) {
        cout << line << "\n";
    }
    inFile.close();
    cout << "Нажмите Enter для возврата в меню...\n";
    cin.ignore();
    cin.get();
}

void lab6_dynamicMemory() {
    cout << "Лабораторная работа 6: Динамическая память\n";
    int rows, cols;
    cout << "Введите количество строк и столбцов матрицы: ";
    cin >> rows >> cols;
    if (rows <= 0 || cols <= 0) {
        cout << "Некорректные размеры!\n";
        return;
    }
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    cout << "Случайная матрица:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    cout << "Нажмите Enter для возврата в меню...\n";
    cin.ignore();
    cin.get();
}

void lab7_sortAndSearch() {
    cout << "Лабораторная работа 7: Сортировка и поиск\n";
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    if (n <= 0) {
        cout << "Некорректный размер!\n";
        return;
    }
    vector<int> arr(n);
    cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    cout << "Отсортированный массив:\n";
    for (vector<int>::iterator it = arr.begin(); it != arr.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\nВведите число для поиска: ";
    int target;
    cin >> target;
    vector<int>::iterator it = lower_bound(arr.begin(), arr.end(), target);
    if (it != arr.end() && *it == target) {
        cout << "Число найдено на позиции: " << (it - arr.begin()) << "\n";
    } else {
        cout << "Число не найдено.\n";
    }
    cout << "Нажмите Enter для возврата в меню...\n";
    cin.ignore();
    cin.get();
}

void lab8_recursion() {
    cout << "Лабораторная работа 8: Рекурсия\n";
    cout << "Введите число для вычисления факториала: ";
    int n;
    cin >> n;
    if (n < 0) {
        cout << "Факториал не определен для отрицательных чисел!\n";
        return;
    }
    long long factorial(int n);
    cout << "Факториал " << n << " = " << factorial(n) << "\n";
    cout << "Нажмите Enter для возврата в меню...\n";
    cin.ignore();
    cin.get();
}

long long factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

void lab9_classes() {
    cout << "Лабораторная работа 9: Классы\n";
    vector<Book> books;
    int n;
    cout << "Введите количество книг: ";
    cin >> n;
    if (n <= 0) {
        cout << "Некорректное количество!\n";
        return;
    }
    cin.ignore();
    for (int i = 0; i < n; i++) {
        string title, author;
        int year;
        cout << "Название книги: ";
        getline(cin, title);
        cout << "Автор: ";
        getline(cin, author);
        cout << "Год издания: ";
        cin >> year;
        cin.ignore();
        books.push_back(Book(title, author, year));
    }
    cout << "Список книг:\n";
    for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
        it->display();
    }
    cout << "Нажмите Enter для возврата в меню...\n";
    cin.get();
}
