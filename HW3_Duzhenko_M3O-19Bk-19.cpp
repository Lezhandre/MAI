//#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <valarray>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#undef min
#undef max

using namespace std;

vector <double> m;

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

double ApproxPolynom(valarray<double>& X, valarray<double>& Y, double x) {
    unsigned size = m.size();
    double ans = 0;
    for (unsigned i = size; i > 0; --i) {
        ans += pow(x, size - i) * m[i - 1];
    }
    return ans;
}

void DrawInterPol(valarray<double>& X, valarray<double>& Y, double(*f)(valarray<double>&, valarray<double>&, double)) {
    Sleep(1000);
    printf("\033[2J");
    double x_max, x_min, diap_x;
    double y_max, y_min, diap_y;
    double y, x;
    y_min = Y.min(); x_min = X.min();
    y_max = Y.max(); x_max = X.max();
    diap_x = (x_max - x_min) / 10;
    diap_y = (y_max - y_min) / 10;                             //диапазон делений для оY 
    y_max += diap_y; y_min -= diap_y;
    HDC hDC = GetDC(GetConsoleWindow());                       //настройка консоли для рисования 
    HPEN Pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));     //ручка для разметки 
    HPEN Pen1 = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));        //ручка для графика 
    HPEN Pen2 = CreatePen(PS_SOLID, 8, RGB(255, 0, 0));        //ручка для точек
    if (true) {
        HWND hwnd = GetConsoleWindow();
        RECT rect;
        //через прямоугольник rect описывается консолька 
        GetWindowRect(hwnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        SelectObject(hDC, Pen);
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
        //деления oX
        for (x = x_min; x < x_max; x += diap_x){
            MoveToEx(hDC, width * (x - x_min) / (x_max - x_min), height / 2 - height / 250 - 1, NULL);
            LineTo(hDC, width * (x - x_min) / (x_max - x_min), height / 2 + height / 250 + 1);
        }
        //деления oY
        for (y = y_min; y < y_max; y += diap_y){
            MoveToEx(hDC, width / 2 - width / 250 - 1, height * (y_max - y) / (y_max - y_min), NULL);
            LineTo(hDC, width / 2 + width / 250 + 1, height * (y_max - y) / (y_max - y_min));
        }
        //вывод графика и точек, по которому он строится
        SelectObject(hDC, Pen1);
        for (x = x_min; x < x_max; x += 1e-3){
            MoveToEx(hDC, width * (x - x_min) / (x_max - x_min), height * (y_max - f(X, Y, x)) / (y_max - y_min), NULL);
            LineTo(hDC, width * (x + 1e-3 - x_min) / (x_max - x_min), height * (y_max - f(X, Y, x + 1e-3)) / (y_max - y_min));
        }
        SelectObject(hDC, Pen2);
        for (unsigned i = 0; i < X.size(); ++i) {
            MoveToEx(hDC, width * (X[i] - x_min) / (x_max - x_min), height * (y_max - Y[i]) / (y_max - y_min), NULL);
            LineTo(hDC, width * (X[i] - x_min) / (x_max - x_min), height * (y_max - Y[i]) / (y_max - y_min));
        }
    }
    _getch();
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
    //double x;
   /** cout << "Enter point where is need to calculate value: ";
    cin >> x;
    if (!cin) {
        cout << "Incorrect input" << endl;
        return 0;
    } /**/

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
        DrawInterPol(X, Y, Lagrange);
        //cout << "Value in selected point calculated by Lagrange: " << ans << endl;
    }
    else if (choice == 2) {
        DrawInterPol(X, Y, Newton);
        //cout << "Value in selected point calculated by Newton: " << ans << endl;
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
        /*m.resize(6);
        m[0] = 0; m[5] = 0;
        m[1] = 267.15494791670392;
        m[2] = 249.71354166664284;
        m[3] = 216.14583333331728;
        m[4] = 260.41666666667624;*/
        DrawInterPol(X, Y, Splines);
        
        //cout << "Value in selected point calculated by splines: " << ans << endl;
        //vector <double> coef = {(m[l+1] - m[l]) / (6*h[l+1]), (X[l+1] * m[l] - X[l] * m[l+1]) / (2*h[l+1]), (pow(X[l], 2) * m[l+1] - pow(X[l+1], 2) * m[l]) / (2*h[l+1]) + (Y[l+1] - m[l+1] * h[l+1]*h[l+1] / 6 - (Y[l] - m[l] * h[l+1]*h[l+1] / 6)) / h[l+1], (pow(X[l+1], 3) * m[l] - pow(X[l], 3) * m[l+1]) / (6*h[l+1]) - (Y[l+1] - m[l+1] * h[l+1]*h[l+1] / 6) * X[l] / h[l+1] + (Y[l] - m[l] * h[l+1]*h[l+1] / 6) * X[l+1] / h[l+1]};
        //printf("Spline: (%.2lf) * x^3 + (%.2lf) * x^2 + (%.2lf) * x + (%.2lf)\n", coef[0], coef[1], coef[2], coef[3]);
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
        //printf("Approximation by quadratic polynom (%.2lf) * x^2 + (%.2lf) * x + (%.2lf)\n", coef[0], coef[1], coef[2]);
        //printf("Discrepancy of approximation: %.2lf\n", pow(coef[0] * X * X + coef[1] * X + coef[2] - Y, 2).sum());
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
        //printf("Approximation by line (%.2lf) * x + (%.2lf)\n", coef[0], coef[1]);
        //printf("Discrepancy of approximation: %.2lf\n", pow(coef[0] * X + coef[1] - Y, 2).sum());
    }
    DrawInterPol(X, Y, ApproxPolynom);
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
