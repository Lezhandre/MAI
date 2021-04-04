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
    double sum = f(a), prev_sum = 0;
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
        cout << "First derivative in point " << x << " : " << (Lagrange(X, Y, x + eps) - Lagrange(X, Y, x - eps)) / (2 * eps) << endl;
        cout << "Second derivative in point " << x << " : " << (Lagrange(X, Y, x + eps) + Lagrange(X, Y, x - eps) - 2 * Lagrange(X, Y, x)) * pow(eps, -2) << endl;
    } else {
        cout << endl << "Select method of integration:" << endl;
        cout << "1) Simpson" << endl;
        cout << "2) Trapezium" << endl;
        cout << "3) Left rectangle" << endl;
        cout << "4) Right rectangle" << endl;
        cin >> choice;
        if (!cin || choice == 0 || choice > 2) {
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
