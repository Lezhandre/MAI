#include <vector>
#include <valarray>
#include <cmath>
#include <cstdio>
#include <wchar.h>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <string>
#undef min
#undef max

using namespace std;

vector <double> m;
unsigned l;
double eps;

vector <double> Gaus(vector <valarray<double>> a) {
    unsigned n = a.size();
    vector <double> ans(n);
    double coef;
    for (unsigned i = 0; i < n; ++i) {
        unsigned j;
        for (j = i; j < n && a[j][i] == 0; ++j);
        if (j == n) {
            cout << "System has no solution or their quantity is infinity" << endl;
            exit(0);
        }
        if (i != j)
            swap(a[j], a[i]);
        for (j = 0; j < n; ++j) {
            if (j == i) continue;
            coef = a[j][i] / a[i][i];
            a[j] -= a[i] * coef;
        }
    }
    for (unsigned i = 0; i < n; ++i)
        ans[i] = a[i][n] / a[i][i];
    return ans;
}

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

double Newton(valarray<double>& X, valarray<double>& Y, double x) {
    double tmp = 1, ans = 0;
    unsigned size = X.size();
    vector <double> dy(size);
    for (unsigned i = 0; i < size; ++i)
        dy[i] = Y[i];
    for (unsigned i = 0; i < size; ++i) {
        ans += dy[0] * tmp;
        tmp *= x - X[i];
        for (unsigned j = 0; j + i < size - 1; ++j)
            dy[j] = (dy[j + 1] - dy[j]) / (X[j + i + 1] - X[j]);
    }
    return ans;
}

double Splines(valarray<double>& X, valarray<double>& Y, double x) {
    unsigned l = 0, r = X.size() - 1;
    while (r - l > 1) {
        unsigned m = (l + r) / 2;
        if (X[m] > x)
            r = m;
        else
            l = m;
    }
    return (m[l + 1] * pow(x - X[l], 3) + m[l] * pow(X[l + 1] - x, 3)) / (6 * (X[l + 1] - X[l])) + (Y[l + 1] - m[l + 1] * pow((X[l + 1] - X[l]), 2) / 6) * (x - X[l]) / (X[l + 1] - X[l]) + (Y[l] - m[l] * pow((X[l + 1] - X[l]), 2) / 6) * (X[l + 1] - x) / (X[l + 1] - X[l]);
}

double Spline(valarray<double>& X, valarray<double>& Y, double x) {
    return (m[l + 1] * pow(x - X[l], 3) + m[l] * pow(X[l + 1] - x, 3)) / (6 * (X[l + 1] - X[l])) + (Y[l + 1] - m[l + 1] * pow((X[l + 1] - X[l]), 2) / 6) * (x - X[l]) / (X[l + 1] - X[l]) + (Y[l] - m[l] * pow((X[l + 1] - X[l]), 2) / 6) * (X[l + 1] - x) / (X[l + 1] - X[l]);
}

double ApproxPolynom(valarray<double>& X, valarray<double>& Y, double x) {
    unsigned size = m.size();
    double ans = 0;
    for (unsigned i = size; i > 0; --i)
        ans += pow(x, size - i) * m[i - 1];
    return ans;
}

void DrawPlot(HDC hDC, unsigned width, unsigned height, double x_max, double x_min, double y_max, double y_min, double diap_x, double diap_y, valarray<double>& X, valarray<double>& Y, double(*f)(valarray<double>&, valarray<double>&, double)) {
    HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));        //ручка для разметки 
    HPEN Pen1 = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));     //ручка для графика 
    HPEN Pen2 = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));     //ручка для точек
    double y, x;
    wchar_t strtmp[20] = {0};
    SelectObject(hDC, Pen);
    //деления oX
    for (x = x_min + diap_x; x < x_max; x += diap_x) {
        MoveToEx(hDC, width * (x - x_min) / (x_max - x_min), height / 2 - height / 250 - 1, NULL);
        LineTo(hDC, width * (x - x_min) / (x_max - x_min), height / 2 + height / 250 + 1);
        swprintf(strtmp, 20, L"%.3lf", x);
        TextOutW(hDC, width * (x - x_min) / (x_max - x_min), height / 2 + height / 250, strtmp, wcslen(strtmp));
    }
    //деления oY
    for (y = y_min + diap_y; y < y_max; y += diap_y) {
        MoveToEx(hDC, width / 2 - width / 250 - 1, height * (y_max - y) / (y_max - y_min), NULL);
        LineTo(hDC, width / 2 + width / 250 + 1, height * (y_max - y) / (y_max - y_min));
        swprintf(strtmp, 20, L"%.4lf", y);
        TextOutW(hDC, width / 2 + width / 250, height * (y_max - y) / (y_max - y_min), strtmp, wcslen(strtmp));
    }
    //оси координат 
    MoveToEx(hDC, 0, height / 2, NULL);
    LineTo(hDC, width, height / 2);
    MoveToEx(hDC, width / 2, height, NULL);
    LineTo(hDC, width / 2, 0);
    //стрелка oY 
    MoveToEx(hDC, width / 2, 0, NULL);
    LineTo(hDC, width / 2 + 10, 10);
    MoveToEx(hDC, width / 2 - 10, 10, NULL);
    LineTo(hDC, width / 2, 0);
    //стрелка оХ 
    MoveToEx(hDC, width - 10, height / 2 - 10, NULL);
    LineTo(hDC, width, height / 2);
    MoveToEx(hDC, width, height / 2, NULL);
    LineTo(hDC, width - 10, height / 2 + 10);
    //вывод точек и графика, строящегося по данным точкам
    SelectObject(hDC, Pen1);
    diap_x /= 100;
    for (x = x_min; x < x_max; x += diap_x) {
        MoveToEx(hDC, width * (x - x_min) / (x_max - x_min), height * (y_max - f(X, Y, x)) / (y_max - y_min), NULL);
        LineTo(hDC, width * (x + diap_x - x_min) / (x_max - x_min), height * (y_max - f(X, Y, x + diap_x)) / (y_max - y_min));
    }
    SelectObject(hDC, Pen2);
    for (unsigned i = 0; i < X.size(); ++i) {
        MoveToEx(hDC, width * (X[i] - x_min) / (x_max - x_min), height * (y_max - Y[i]) / (y_max - y_min), NULL);
        LineTo(hDC, width * (X[i] - x_min) / (x_max - x_min), height * (y_max - Y[i]) / (y_max - y_min));
    }
}

LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
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

    //Создаем класс окна.
    WNDCLASSEX wclass = { 0 };                                  //Обнуляем структуру с самого начала, так как заполнять будем не все поля.
    wclass.cbSize = sizeof(WNDCLASSEX);                         //По размеру структуры Windows определит, какая версия API была использована.
    wclass.style = CS_HREDRAW | CS_VREDRAW;                     //Говорим окну перерисовываться при изменении размеров окна.
    wclass.lpfnWndProc = WndProc;                               //Указываем функцию обработки сообщений.
    wclass.hInstance = histance;                                //Указываем хендл приложения.
    wclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //GetStockObject возвращает хендл на белую кисточку, для фона окна
    wclass.lpszClassName = L"MYCLASS";                          //Имя данного класса, должно быть уникальным, иначе, если класс с таким именем уже зарегестрирован, то в регистрации будет отказано.
    //Регистрируем класс окна.
    RegisterClassEx(&wclass);

    //Создаем окно.
    HWND window = CreateWindowExW(
        0,
        L"MYCLASS",                         //Имя класса
        L"Рисование графика",               //Заголовок окна
        WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,  //Тип окна, влияет на отображение системного меню, кнопок в верхнем правом углу и т.п.
        50, 50,                             //Координаты окна (не нужно)
        320, 240,                           //Ширина окна (не нужно)
        0,                                  //Ссылка на родительское окно (отсутствует)
        0,                                  //Хендл меню (отсутсвует)
        histance,                           //Хендл приложения
        0
    );
    HDC hDC = GetDC(window);                //настройка окна для рисования 

    //Показываем окно, если этого не сделать окно не будет отображено.
    ShowWindow(window, SW_SHOW);
    //Обновляем окно.
    UpdateWindow(window);
    RECT rect;
    //через прямоугольник rect описывается поле для рисования в окне
    GetClientRect(window, &rect);           //определние размеров рабочей области для рисования
    int width = rect.right - rect.left;     //определение ширины области
    int height = rect.bottom - rect.top;    //определение высоты области
    DrawPlot(hDC, width, height, x_max, x_min, y_max, y_min, diap_x, diap_y, X, Y, f);

    //Запускаем цикл обработки сообщений окна.
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

vector <double> CalcCoef(unsigned size, valarray<double>& X, valarray<double>& Y, double(*f)(valarray<double>&, valarray<double>&, double)) {
    vector <valarray<double>> SLAE(size, valarray<double>(size + 1));
    for (unsigned i = 0, j; i < size; ++i) {
        for (j = 0; j < size; ++j)
            SLAE[i][j] = pow(i, j);
        SLAE[i][j] = f(X, Y, i);
    }
    return Gaus(SLAE);
}

int main() {
    unsigned size, choice;
    cout << "Enter quantity of nodal values: ";
    cin >> size;
    if (!cin || size < 1) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    valarray <double> X(size), Y(size);
    cout << "Enter nodal values:" << endl;
    for (unsigned i = 0; i < size; ++i) {
        cin >> X[i] >> Y[i];
        if (!cin) {
            cout << "Incorrect input" << endl;
            return 0;
        }
    }

    cout << endl << "Select problem: " << endl;
    cout << "1) Interpolation" << endl;
    cout << "2) Approximation" << endl;
    cin >> choice;
    if (!cin || choice == 0 || choice > 2) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    double ans = 0, tmp;
    if (choice == 2) goto CHOICE_OF_APPR_METHOD;

    cout << endl << "Select method of interpolation" << endl;
    cout << "1) By Lagrange's polynom" << endl;
    cout << "2) By Newton's polynom" << endl;
    cout << "3) By splines" << endl;
    cin >> choice;
    if (!cin || choice == 0 || choice > 3) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    cout << endl;

    if (choice == 1) {
        CreateWindowForPlot(X, Y, Lagrange);
        m = CalcCoef(size, X, Y, Lagrange);
        for (unsigned i = 0; i < size; ++i) {
            cout << "(" << m[i] << ")";
            if (i > 0)
                cout << " * x";
            if (i > 1)
                cout << "^" << i;
            if (i + 1 < size) cout << " + ";
        }
        cout << endl;
    }
    else if (choice == 2) {
        CreateWindowForPlot(X, Y, Newton);
        m = CalcCoef(size, X, Y, Newton);
        for (unsigned i = 0; i < size; ++i) {
            cout << "(" << m[i] << ")";
            if (i > 0)
                cout << " * x";
            if (i > 1)
                cout << "^" << i;
            if (i + 1 < size) cout << " + ";
        }
        cout << endl;
    }
    else {
        vector <double> h(size), P(size), Q(size);
        m.resize(size);
        for (unsigned i = 1; i < size; ++i)
            h[i] = X[i] - X[i - 1];
        P[1] = 0; Q[1] = 0;
        for (unsigned i = 1; i + 1 < size; ++i) {
            P[i + 1] = -h[i + 1] / (2 * (h[i] + h[i + 1]) + P[i] * h[i]);
            tmp = (Y[i + 1] - Y[i]) / h[i + 1] - (Y[i] - Y[i - 1]) / h[i];
            Q[i + 1] = (6 * tmp - h[i] * Q[i]) / (2 * (h[i] + h[i + 1]) + P[i] * h[i]);
        }
        m[size - 1] = 0; m[0] = 0;
        for (unsigned i = size - 1; i > 0; --i)
            m[i - 1] = P[i] * m[i] + Q[i];
        CreateWindowForPlot(X, Y, Splines);
        vector<double> coef;
        for (l = 0; l + 1 < size; ++l) {
            coef = CalcCoef(4, X, Y, Spline);
            cout << "Spline " << l + 1 << " : ";
            for (unsigned j = 0; j < 4; ++j) {
                cout << "(" << coef[j] << ")";
                if (j > 0)
                    cout << " * x";
                if (j > 1)
                    cout << "^" << j;
                if (j + 1 < 4) cout << " + ";
            }
            cout << endl;
        }
    }
    if (choice == 1 || choice == 2) {
        m = CalcCoef(size, X, Y, Lagrange);
        eps = ApproxPolynom(X, Y, 0.1875);
        m = CalcCoef(size, X, Y, Newton);
        eps -= ApproxPolynom(X, Y, 0.1875);
        cout << endl << "Accuracy in point " << 0.1875 << " : " << fabs(eps) << endl;
    }
    return 0;

    CHOICE_OF_APPR_METHOD:
    cout << endl << "Select method of approximation:" << endl;
    cout << "1) By quadratic polinom" << endl;
    cout << "2) By line" << endl;
    cin >> choice;
    if (!cin || choice == 0 || choice > 2) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    cout << endl;

    if (choice == 1) {
        vector <valarray<double>> SLAE(3, valarray<double>(4));
        for (unsigned i = 0, j; i < 3; ++i) {
            for (j = 0; j < 3; ++j) {
                SLAE[i][j] = pow(X, 4 - (i + j)).sum();
            }
            SLAE[i][j] = (pow(X, 2 - i) * Y).sum();
        }
        m = Gaus(SLAE);
    }
    else {
        vector <valarray<double>> SLAE(2, valarray<double>(3));
        for (unsigned i = 0, j; i < 2; ++i) {
            for (j = 0; j < 2; ++j) {
                SLAE[i][j] = pow(X, 2 - (i + j)).sum();
            }
            SLAE[i][j] = (pow(X, 1 - i) * Y).sum();
        }
        m = Gaus(SLAE);
    }
    CreateWindowForPlot(X, Y, ApproxPolynom);
    for (unsigned i = 0; i < 4 - choice; ++i) {
        cout << "(" << m[i] << ")";
        if (3 - choice - i > 0)
            cout << " * x";
        if (3 - choice - i > 1)
            cout << "^" << 3 - choice - i;
        if (i + 1 + choice < 4)
            cout << " + ";
    }
    cout << endl;
    return 0;
}

/*\ interpolation
 6
 0.180 5.61543
 0.186 5.46693
 0.192 5.32634
 0.198 5.19304
 0.204 5.06649
 0.210 4.94619
 //0.1875
\*/

/*\ approximation
 11
 0    2.2
 0.12 2.0
 0.19 2.2
 0.35 3.2
 0.4  2.6
 0.45 3.8
 0.62 4.5
 0.71 5.2
 0.84 5.8
 0.91 7.0
 1.0  8.0
\*/
