//
///  М3О-219Бк-19, Дуженко Михаил, 10-ый вариант
//
///  Руководство по использованию программы:
//  После запуска программы в консоли/терминале предлагается выбрать одну из задач:
//  численное вычисление производных первого и второго порядков или интеграла функции
//  f(x) = sin(x) / (x + 1) на отрезке от 0 до 1. Далее, в зависимости от сделанного выбора,
//  предлагается или ввести узлы и точку, в которой следует искать производные,
//  или выбрать метод численного интегрирования.
//
//  Ниже основного кода написаны комментарии с условиями из 10-ого варианта (ввод условия
//  предусмотрен только для задачи нахождения производных первого и второго порядка).
//

#include <valarray>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

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

double Derivative(valarray<double>& X, valarray<double>& Y, double x, unsigned degree) {
    unsigned size = X.size();
    vector <valarray<double>> SLAE(size, valarray<double>(size + 1));
    for (unsigned i = 0, j; i < size; ++i) {
        for (j = 0; j < size; ++j)
            SLAE[i][j] = pow(X[i], j);
        SLAE[i][j] = Y[i];
    }
    vector <double> coef = Gaus(SLAE);
    double ans = 0;
    for (unsigned i = degree, j; i < size; ++i){
        for (j = i; j + degree > i; --j)
            coef[i] *= j;
        ans += coef[i] * pow(x, i - degree);
    }
    return ans;
}

double f(double x){
    return sin(x) / (x + 1);
}

double SimpInt(double a, double b, double eps){
    double sum = f(a) + f(b), prev_sum = 0;
    double hlp_var = 0;
    unsigned n = 1, iter = 0;
    while (fabs(sum - 2 * prev_sum) > eps * (3 * n) / (b - a)){
        n <<= 1; ++iter;
        prev_sum = sum;
        sum -= 2 * hlp_var;
        hlp_var = 0;
        for (unsigned i = 1; i < n; i += 2)
            hlp_var += f(a + (b - a) * i / n);
        sum += 4 * hlp_var;
    }
    return sum * (b - a) / (3 * n);
}

double TrapInt(double a, double b, double eps){
    double sum = f(a) + f(b), prev_sum = 0;
    unsigned n = 1, iter = 0;
    while (fabs(sum - 2 * prev_sum) > eps * (2 * n) / (b - a)){
        n <<= 1; ++iter;
        prev_sum = sum;
        for (unsigned i = 1; i < n; i += 2)
            sum += 2 * f(a + (b - a) * i / n);
    }
    return sum * (b - a) / (2 * n);
}

double LeftRectInt(double a, double b, double eps){
    double sum = f(a), prev_sum = -1;
    unsigned n = 1, iter = 0;
    while (fabs(sum - 2 * prev_sum) > eps * n / (b - a)){
        n <<= 1; ++iter;
        prev_sum = sum;
        for (unsigned i = 1; i < n; i += 2)
            sum += f(a + (b - a) * i / n);
    }
    return sum * (b - a) / n;
}

double RightRectInt(double a, double b, double eps){
    double sum = f(b), prev_sum = 0;
    unsigned n = 1, iter = 0;
    while (fabs(sum - 2 * prev_sum) > eps * n / (b - a)){
        n <<= 1; ++iter;
        prev_sum = sum;
        for (unsigned i = 1; i < n; i += 2)
            sum += f(a + (b - a) * i / n);
    }
    return sum * (b - a) / n;
}

double MiddleRectInt(double a, double b, double eps){
    double sum = f((a + b) / 2), prev_sum = 0;
    unsigned n = 2, iter = 0;
    while (fabs(sum - 2 * prev_sum) > eps * n / (b - a)){
        n <<= 1; ++iter;
        prev_sum = sum;
        for (unsigned i = 1; i < n; i += 2)
            sum += f(a + (b - a) * i / n);
    }
    return sum * (b - a) / n;
}

int main() {
    unsigned choice;
    cout << endl << "Select problem: " << endl;
    cout << "1) Derivative" << endl;
    cout << "2) Integral" << endl;
    cin >> choice;
    if (!cin || choice == 0 || choice > 2) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    cout << endl;
    double eps = 1e-4;
    if (choice == 1) {
        unsigned size;
        cout << "Enter quantity of nodal values: ";
        cin >> size;
        if (!cin || size < 2) {
            cout << "Incorrect input" << endl;
            return 0;
        }
        valarray <double> X(size), Y(size);
        double x;
        cout << "Enter nodal values:" << endl;
        for (unsigned i = 0; i < size; ++i) {
            cin >> X[i] >> Y[i];
            if (!cin) {
                cout << "Incorrect input" << endl;
                return 0;
            }
        }
        cout << "Enter point where to calculate value of derivative: ";
        cin >> x;
        if (!cin) {
            cout << "Incorrect input" << endl;
            return 0;
        }
        cout << "First derivative in point " << x << " : " << Derivative(X, Y, x, 1) << endl;
        cout << "Second derivative in point " << x << " : " << Derivative(X, Y, x, 2) << endl;
    } else {
        cout << endl << "Select method of integration:" << endl;
        cout << "1) Simpson" << endl;
        cout << "2) Trapezium" << endl;
        cout << "3) Left rectangle" << endl;
        cout << "4) Right rectangle" << endl;
        cout << "5) Middle rectangle" << endl;
        cin >> choice;
        if (!cin) {
            cout << "Incorrect input" << endl;
            return 0;
        }
        cout << endl;
        switch (choice){
            case 1:
                cout << "Integral calculated with Simpson's method: " << SimpInt(0, 1, eps) << endl;
            break;
            case 2:
                cout << "Integral calculated with method of trapeziums: " << TrapInt(0, 1, eps) << endl;
            break;
            case 3:
                cout << "Integral calculated with method of left rectangles: " << LeftRectInt(0, 1, eps) << endl;
            break;
            case 4:
                cout << "Integral calculated with method of right rectangles: " << RightRectInt(0, 1, eps) << endl;
            break;
            case 5:
                cout << "Integral calculated with method of middle rectangles: " << MiddleRectInt(0, 1, eps) << endl;
            break;
            default:
                cout << "Incorrect input" << endl;
                return 0;
        }
    }
    return 0;
}

/*\ for derivative
 6
 0.180 5.61543
 0.186 5.46693
 0.192 5.32634
 0.198 5.19304
 0.204 5.06649
 0.210 4.94619
 // x* : 0.1875
\*/

/*\ for integral
 f(x) = sin(x) / (x + 1)
\*/
