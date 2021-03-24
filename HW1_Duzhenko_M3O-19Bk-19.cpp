//
///  Дуженко Михаил, М3О-219Бк-19, 10-ый вариант
//
///  Руководство по использованию программы:
//  Для начала нужно ввести количество неизвестных (size), потом нужно ввести матрицу,
//  состоящую из size x (size + 1) элементов, которая будет представляться как коэффициенты в СЛАУ.
//  Далее предложится на выбор один из 4-ёх алгоритмов решения СЛАУ, при вводе цифры которого
//  СЛАУ будет решена данным методом.
//
///  Ограничения в работе программы:
//  Метод Гаусса, в принципе, сам напишет возникшую ошибку при решении СЛАУ
//  Метод итераций и Зейделя работают, только при условии, что диагональные элементы имеют
//  большие коэффициенты (по модулю они должны быть больше суммы модулей остальных коэффициентах
//  при других элементах)
//  Метод прогонки используется только для 3-ёх-диагональных матриц
//
//  Вводимые данные в программу для 10-ого варианта находятся в комментариях
//  под основным кодом программы
//

#include <iostream>
#include <vector>
#include <valarray>
#include <algorithm>

using namespace std;

void Gaus(vector <valarray<double>> a){
    unsigned n = a.size();
    double coef;
    for (unsigned i = 0; i < n; ++i){
		unsigned j;
		for (j = i; j < n && a[j][i] == 0; ++j);
		if (j == n) {
			cout << "System has no solution or their quantity is infinity" << endl;
			exit(0);
		}
		else if (i != j)
			swap(a[j], a[i]);
        for (j = 0; j < i; ++j){
            coef = a[j][i] / a[i][i];
			a[j] -= a[i] * coef;
        }
        for (j = i + 1; j < n; ++j){
            coef = a[j][i] / a[i][i];
            a[j] -= a[i] * coef;
        }
	}
	for (unsigned i = 0; i < n; ++i)
        printf("x_%u = %.2lf\n", i + 1, a[i][n] / a[i][i]);
}

void SimpIterMethod(vector <valarray<double>> a, double eps)
{
    unsigned size = a.size();
    double norma = 0;
    vector<double> x(size);
    valarray<double> x0(size+1);
    vector<double> e(size);
    
    for (unsigned i = 0, j; i < size; ++i){
        norma = -a[i][i];
        a[i][size] *= -1;
        a[i][i] = 0;
        a[i] /= norma;
    }
    for (unsigned i = 0; i < size; i++)
        x0[i] = a[i][size];
    x0[size] = 1;
    int ctr = 0;
    do {
        for (unsigned i = 0; i < size; i++){
            x[i] = (a[i] * x0).sum();
            e[i] = fabs(x[i] - x0[i]);
        }
        norma = 0;
        for (unsigned i = 0; i < size; i++){
            norma = max(norma, e[i]);
            x0[i] = x[i];
        }
        ++ctr;
    } while (norma > eps);
    cout << endl << "Quantity of iterations: " << ctr << endl;
    for (int i = 0; i < size; i++)
        printf("x_%u = %.2lf\n", i + 1, x[i]);
}

void Zeidel(vector<valarray<double>> a, double eps){
    unsigned size = a.size();
    double norma = 0;
    vector<double> x(size);
    valarray<double> x0(size+1);
    valarray<double> e(size);
    
    for (unsigned i = 0; i < size; ++i){
        norma = -a[i][i];
        a[i][size] *= -1;
        a[i][i] = 0;
        a[i] /= norma;
    }
    for (unsigned i = 0; i < size; i++)
        x0[i] = a[i][size];
    x0[size] = 1;
    int ctr = 0;
    do {
        for (unsigned i = 0; i < size; i++){
            x[i] = (a[i] * x0).sum();
            e[i] = fabs(x[i] - x0[i]);
            x0[i] = x[i];
        }
        norma = (e*e).sum();
        ++ctr;
    } while (norma > eps);
    cout << endl << "Quantity of iterations: " << ctr << endl;
    for (int i = 0; i < size; i++)
        printf("x_%u = %.2lf\n", i + 1, x[i]);
}

void Runthrough(vector <valarray<double>> matrix)
{
    unsigned size = matrix.size();
    vector <double> p(size+1), q(size+1);
    p[0] = 0;
    q[0] = 0;
    unsigned step = 0;
    double a = 0, b, c;
    for (unsigned i = 0; i < size; ++i){
        if (i != 0)
            a = matrix[i][i-1];
        b = matrix[i][i];
        c = matrix[i][i+1];
        if (i + 1 == size)
            c = 0;
        p[i+1] = -c / (b + a * p[i]);
        q[i+1] = (matrix[i][size] - a * q[i]) / (b + a * p[i]);
    }
    vector<double> x(size);
    x[size-1] = q[size];
    for (unsigned i = size - 1; i > 0; --i){
        x[i - 1] = q[i] + p[i] * x[i];
    }
    for (unsigned i = 0; i < size; ++i)
        printf("x_%u = %.2lf\n", i + 1, x[i]);
}

int main()
{
	unsigned size;
	cout << "Enter size: "; cin >> size;
	vector<valarray<double>> coef(size);
	for (int i = 0; i < size; i++)
		coef[i].resize(size + 1);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size + 1; j++)
            cin >> coef[i][j];
    
    unsigned choice;
    cout << endl << "Choice method:" << endl;
    cout << "1) Gaus's" << endl;
    cout << "2) Iterations" << endl;
    cout << "3) Zeidel's" << endl;
    cout << "4) Run-through" << endl;
    cin >> choice;
    if (!cin || choice == 0 || choice > 4) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    
    switch (choice) {
        case 1:
            cout << endl;
            Gaus(coef);
            break;
        case 2:
            SimpIterMethod(coef, 0.01);
            break;
        case 3:
            Zeidel(coef, 0.01);
            break;
        default:
            cout << endl;
            Runthrough(coef);
            break;
    }
    return 0;
}

/*\ 1'st problem
 3
 1.12   -0.43   0.14    -0.17
 -0.07  1.34    0.72    0.62
 1.18   -0.08   -2.25   1.12
\*/

/*\ 2'nd problem
 4
 5  -1  0  0  9
 -1  7 -2  0  5
 0   2 11 -4 15
 0   0 -1  5 10
\*/
