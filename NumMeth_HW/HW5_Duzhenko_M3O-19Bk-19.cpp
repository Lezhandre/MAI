//
///  М3О-219Бк-19, Дуженко Михаил, 10-ый вариант
//
///  Руководство по использованию программы:
//  После запуска программы в консоли/терминале предлагается ввести начальное условие Коши
//  в формате (x, y), а затем длину шага итерации и точность вычислений функции.
//  Далее нужно выбрать один из методов численного решения дифференциального уравнения
//  y' = cos(2 * x + y) + 1.5 * (x - y) : Эйлера, Кутте или Адамса.
//
///  Вывод результатов:
//  После всех введённых данных появляется окно во весь экран, в рабочей области которого
//  нарисован график по заданным методу и задаче.
//
//  Ниже основного кода написаны комментарии с условиями из 10-ого варианта.
//

#include <vector>
#include <valarray>
#include <cmath>
#include <cstdio>
#include <wchar.h>
#include <iostream>
#include <algorithm>
#include <windows.h>
#undef min
#undef max

using namespace std;

double Lagrange(valarray<double>& X, valarray<double>& Y, double x) {
    double tmp, ans = 0;
    unsigned size = X.size();
    for (unsigned i = 0; i < size; ++i) {
        tmp = Y[i];
        for (unsigned k = 0; k < size; ++k) {
            if (k == i) continue;
            tmp *= (x - X[k]) / (X[i] - X[k]);
        }
        ans += tmp;
    }
    return ans;
}

double f(double x, double y) {
    return cos(2 * x + y) + 1.5 * (x - y);
}

void Eiler(double x, double y, double step, double eps, double (*f)(double, double), vector<double>& X, vector<double>& Y) {
    double y2 = y;
    while (fabs(y - y2) < eps) {
        printf("y(%lg) = %lg\n", x, y);
        y2 += step * f(x, y2);
        y += step * f(x + step / 2, y + step / 2 * f(x, y));
        x += step;
        X.push_back(x);
        Y.push_back(y);
    }
}

void Kutte(double x, double y, double step, double eps, double (*f)(double, double), vector<double>& X, vector<double>& Y) {
    double K[4];
    double y2 = y;
    while (fabs(y - y2) < 7 * eps) {
        printf("y(%lg) = %lg\n", x, y);
        y2 += step * f(x + step, y2 + step / 2 * f(x, y2));
        K[0] = f(x, y);
        for (unsigned i = 1; i < 3; ++i)
            K[i] = f(x + step / 2, y + step / 2 * K[i - 1]);
        K[3] = f(x + step, y + step * K[2]);
        y += step / 6 * (K[0] + 2 * (K[1] + K[2]) + K[3]);
        x += step;
        X.push_back(x);
        Y.push_back(y);
    }
}

void Adams(double x, double y, double step, double eps, double (*f)(double, double), vector<double>& X, vector<double>& Y) {
    double y2 = y;
    while (fabs(y - y2) < 3 * eps) {
        printf("y(%lg) = %lg\n", x, y);
        y2 += step * f(x + step, y2 + step * f(x, y2));
        y += step / 2 * (f(x + step, y + step * f(x, y)) + f(x, y));
        x += step;
        X.push_back(x);
        Y.push_back(y);
    }
}

LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawPlot(HDC, unsigned, unsigned, double, double, double, double, double, double, valarray<double>&, valarray<double>&, double(*)(valarray<double>&, valarray<double>&, double));
void CreateWindowForPlot(valarray<double>& , valarray<double>& , double(*)(valarray<double>&, valarray<double>&, double));

int main() {
    unsigned choice;
    double start_x, start_y;
    double step;
    double eps;
    cout << "Enter initial condition Cauchy: ";
    cin >> start_x >> start_y;
    if (!cin) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    cout << "Enter length of step: ";
    cin >> step;
    if (!cin) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    cout << "Enter needed accuracy: ";
    cin >> eps;
    if (!cin) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    cout << endl << "Select method of solving differencial equation: " << endl;
    cout << "1) Eiler's method" << endl;
    cout << "2) Adams's method" << endl;
    cout << "3) Runge-Kutte's method" << endl;
    cin >> choice;
    if (!cin || choice == 0 || choice > 3) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    cout << endl;
    vector<double> X, Y;
    switch (choice){
    case 1:
        Eiler(start_x, start_y, step, eps, f, X, Y);
        break;
    case 2:
        Adams(start_x, start_y, step, eps, f, X, Y);
        break;
    case 3:
        Kutte(start_x, start_y, step, eps, f, X, Y);
        break;
    }
    valarray<double> X1(X.data(), X.size());
    valarray<double> Y1(Y.data(), Y.size());
    CreateWindowForPlot(X1, Y1, Lagrange);
    return 0;
}

// главная функция обработки сообщений
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void CreateWindowForPlot(valarray<double>& X, valarray<double>& Y, double(*f)(valarray<double>&, valarray<double>&, double)) {
    double x_max, x_min, diap_x;
    double y_max, y_min, diap_y;
    y_min = Y.min(); x_min = X.min();
    y_max = Y.max(); x_max = X.max();
    diap_x = (x_max - x_min) / 10;     //диапазон делений для oX
    diap_y = (y_max - y_min) / 9;      //диапазон делений для оY
    x_max += diap_x / 2; x_min -= diap_x / 2;
    y_max += diap_y; y_min -= diap_y;
    //Получаем хендл приложения, потребуется при создании класса окна и самого окна.
    HINSTANCE histance = GetModuleHandleW(NULL);

    //Создаем класс окна
    WNDCLASSEX wclass = { 0 };
    wclass.cbSize = sizeof(WNDCLASSEX);
    wclass.style = CS_HREDRAW | CS_VREDRAW;
    wclass.lpfnWndProc = WndProc;
    wclass.hInstance = histance;
    wclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wclass.lpszClassName = L"MYCLASS";
    //Регистрируем класс окна.
    RegisterClassEx(&wclass);

    //Создаем окно
    HWND window = CreateWindowExW(
        0,
        L"MYCLASS",                         //Имя класса
        L"Рисование графика",               //Заголовок окна
        WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,  //Тип окна (становится максимального размера и есть кнопки)
        50, 50,                             //Координаты окна (учитываются при свёртывании)
        500, 250,                           //Ширина окна (учитываются при свёртывании)
        0,                                  //Ссылка на родительское окно (отсутствует)
        0,                                  //Хендл меню (отсутсвует)
        histance,                           //Хендл приложения
        0
    );
    //настройка окна для рисования
    HDC hDC = GetDC(window);
    //SetPolyFillMode(hDC, WINDING);
    SelectObject(hDC, GetStockObject(BLACK_BRUSH));

    //Показываем окно, если этого не сделать окно не будет отображено
    ShowWindow(window, SW_SHOW);
    //Обновляем окно
    UpdateWindow(window);
    RECT rect;
    //через прямоугольник rect описывается поле для рисования в окне
    GetClientRect(window, &rect);           //определние размеров рабочей области для рисования
    int width = rect.right - rect.left;     //определение ширины области
    int height = rect.bottom - rect.top;    //определение высоты области
    DrawPlot(hDC, width, height, x_max, x_min, y_max, y_min, diap_x, diap_y, X, Y, f);

    //Запускаем цикл обработки сообщений окна
    MSG msg = { 0 };
    while (GetMessage(&msg, 0, 0, 0)) {     //обработка изменения разрешения окна
        DispatchMessage(&msg);              //Передаем сообщения для обработки в "главную функцию обработки сообщений"
        GetClientRect(window, &rect);
        if (width != rect.right - rect.left || height != rect.bottom - rect.top) {
            width = rect.right - rect.left;
            height = rect.bottom - rect.top;
            DrawPlot(hDC, width, height, x_max, x_min, y_max, y_min, diap_x, diap_y, X, Y, f);
        }
    }
    UnregisterClass(L"MYCLASS", histance);
}

void DrawPlot(HDC hDC, unsigned width, unsigned height, double x_max, double x_min, double y_max, double y_min, double diap_x, double diap_y, valarray<double>& X, valarray<double>& Y, double(*f)(valarray<double>&, valarray<double>&, double)) {
    HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));        //ручка для разметки 
    HPEN Pen1 = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));     //ручка для графика 
    HPEN Pen2 = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));     //ручка для точек
    double y, x;
    wchar_t strtmp[20] = { 0 };
    SelectObject(hDC, Pen);
    //деления oX
    for (x = x_min + diap_x; x < x_max - diap_x / 2; x += diap_x) {
        MoveToEx(hDC, width * (x - x_min) / (x_max - x_min), height / 2 + 5, NULL);
        LineTo(hDC, width * (x - x_min) / (x_max - x_min), height / 2 - 5);
        swprintf(strtmp, 20, L"%.3lf", x);
        TextOutW(hDC, width * (x - x_min) / (x_max - x_min), height / 2 + 5, strtmp, wcslen(strtmp));
    }
    //деления oY
    for (y = y_min + diap_y; y < y_max - diap_y / 2; y += diap_y) {
        MoveToEx(hDC, width / 2 + 5, height * (y_max - y) / (y_max - y_min), NULL);
        LineTo(hDC, width / 2 - 5, height * (y_max - y) / (y_max - y_min));
        swprintf(strtmp, 20, L"%.4lf", y);
        TextOutW(hDC, width / 2 + 5, height * (y_max - y) / (y_max - y_min), strtmp, wcslen(strtmp));
    }
    //оси координат
    MoveToEx(hDC, 0, height / 2, NULL);
    LineTo(hDC, width, height / 2);
    MoveToEx(hDC, width / 2, height, NULL);
    LineTo(hDC, width / 2, 0);
    //стрелка oY
    POINT oY[3] = { {width / 2 + 5, 10}, {width / 2, 0}, {width / 2 - 5, 10} };
    Polygon(hDC, oY, 3);
    //стрелка оХ
    POINT oX[3] = { {width - 10, height / 2 - 5}, {width, height / 2}, {width - 10, height / 2 + 5} };
    Polygon(hDC, oX, 3);
    //вывод точек и графика, строящегося по данным точкам
    SelectObject(hDC, Pen1);
    diap_x /= width / 10;
    MoveToEx(hDC, 0, height * (y_max - f(X, Y, x_min)) / (y_max - y_min), NULL);
    for (x = x_min; x < x_max; x += diap_x)
        LineTo(hDC, width * (x + diap_x - x_min) / (x_max - x_min), height * (y_max - f(X, Y, x + diap_x)) / (y_max - y_min));
    SelectObject(hDC, Pen2);
    for (unsigned i = 0; i < X.size(); ++i) {
        MoveToEx(hDC, width * (X[i] - x_min) / (x_max - x_min), height * (y_max - Y[i]) / (y_max - y_min), NULL);
        LineTo(hDC, width * (X[i] - x_min) / (x_max - x_min), height * (y_max - Y[i]) / (y_max - y_min));
    }
    DeleteObject(Pen);
    DeleteObject(Pen1);
    DeleteObject(Pen2);
}
