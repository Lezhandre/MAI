//
///  М3О-219Бк-19, Дуженко Михаил, 10-ый вариант
//
///  Руководство по использованию программы:
//  После запуска программы в консоли/терминале предлагается выбрать одну из задач:
//  нахождение собственных векторов и значений матрицы или нахождение корня уравнения
//  x^2 + 4 * sin(x) = 0 на отрезке от -pi до -pi/2. Далее, в зависимости от сделанного выбора,
//  предлагается или ввести матрицу размера 3x3 или выбрать метод поиска корня.
//
///  Объяснение результатов вывода собственных значений и векторов:
//  Вывод собственных значений и векторов устроен следующим образом: в первой строке выводятся
//  собственные значения, далее идут строки с векторами, таким образом, что под каждым
//  собственным значением находится вектор соответсвующий данному значению.
//
//  Ниже основного кода написаны комментарии с условиями из 10-ого варианта (ввод условия
//  предусмотрен только для задачи нахождения собственных значений и векторов матрицы).
//

#include <iostream>
#include <vector>
#include <valarray>
#include <cmath>
#include <algorithm>

using namespace std;

double f(double x){
    return x*x + 4 * sin(x);
}

void IterMethod(double eps){
    //x^2 + 4 * sin(x) = 0 <= x = -sqrt(-4 * sin(x)), x < 0
    double x = -M_PI / 2;
    unsigned i;
    for (i = 0; f(x - eps) * f(x) > 0; ++i)
        x = -sqrt(-4 * sin(x));
    cout << "Quantity of iterations: " << i << endl;
    printf("Root of equation: %.2lf\n", x);
}

void BinSearch(double eps){
    double r = -M_PI / 2, l = -M_PI, m;
    unsigned i;
    for (i = 0; r - l > eps; ++i){
        m = (l + r) / 2;
        if (f(m) < 0)
            r = m;
        else
            l = m;
    }
    cout << "Quantity of iterations: " << i << endl;
    printf("Root of equation: %.2lf\n", (l + r) / 2);
}

void NewtonMethod(double eps){
    double x = -M_PI / 2;
    unsigned i;
    for (i = 0; f(x - eps) * f(x) > 0; ++i)
        x -= f(x) / (2 * x + 4 * cos(x));
    cout << "Quantity of iterations: " << i << endl;
    printf("Root of equation: %.2lf\n", x);
}

void RotationsMethod(double eps, vector<valarray<double>> matrix){
    double phi, max_elem;
    unsigned k, m, n;
    vector<valarray<double>> rot_matrix(3, valarray<double>(3)), inter_res(3, valarray<double>(3));
    vector<valarray<double>> vectors(3, valarray<double>(3));
    for (unsigned i = 0; i < 3; ++i){
        for (unsigned j = 0; j < 3; ++j){
            vectors[i][j] = (i == j);
        }
    }
    unsigned iter = 0;
    valarray<double> kostyl;
    do {
        max_elem = 0;
        for (unsigned i = 0; i < 3; ++i){
            for (unsigned j = i + 1; j < 3; ++j){
                if (fabs(max_elem) < fabs(matrix[i][j])) {
                    max_elem = matrix[i][j];
                    k = i;
                    m = j;
                }
            }
        }
        
        if (fabs(max_elem) < eps)
            break;
        
        phi = atan2(2 * matrix[k][m], matrix[k][k] - matrix[m][m]) / 2;
        rot_matrix[k][k] = cos(phi);
        rot_matrix[k][m] = sin(phi);
        rot_matrix[m][k] = -sin(phi);
        rot_matrix[m][m] = cos(phi);
        n = 3 - k - m;
        for (unsigned i = 0; i < 3; ++i){
            rot_matrix[n][i] = 0;
            rot_matrix[i][n] = 0;
        }
        rot_matrix[n][n] = 1;
        
        for (unsigned i = 0; i < 3; ++i){
            for (unsigned j = 0; j < 3; ++j){
                kostyl = {matrix[0][j], matrix[1][j], matrix[2][j]};
                inter_res[i][j] = (rot_matrix[i] * kostyl).sum();
            }
        }
        swap(rot_matrix[m][k], rot_matrix[k][m]);
        for (unsigned i = 0; i < 3; ++i){
            for (unsigned j = 0; j < 3; ++j){
                kostyl = {rot_matrix[0][j], rot_matrix[1][j], rot_matrix[2][j]};
                matrix[i][j] = (inter_res[i] * kostyl).sum();
            }
        }
        
        for (unsigned i = 0; i < 3; ++i){
            for (unsigned j = 0; j < 3; ++j){
                kostyl = {rot_matrix[0][j], rot_matrix[1][j], rot_matrix[2][j]};
                inter_res[i][j] = (vectors[i] * kostyl).sum();
            }
        }
        vectors = inter_res;
        ++iter;
    } while (true);
    
    cout << "Quantity of iterations: " << iter << endl;
    for (unsigned i = 0; i < 3; ++i)
        printf("%.2lf\t", matrix[i][i]);
    cout << endl;
    for (auto& arr: vectors){
        for (auto elem: arr){
            printf("%.2lf\t", elem);
        }
        cout << endl;
    }
}

int main(){
    unsigned choice;
    cout << "Choice problem:" << endl;
    cout << "1) Eigen vectors and values of matrix" << endl;
    cout << "2) Find root of equation x^2 + 4 * sin(x) = 0" << endl;
    cin >> choice;
    cout << endl;
    if (!cin || choice == 0 || choice > 2) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    
    if (choice == 1) {
        vector<valarray<double>> matrix(3);
        cout << "Enter matrix with size 3x3:" << endl;
        for (auto& arr: matrix){
            arr.resize(3);
            for (auto& elem: arr)
                cin >> elem;
        }
        cout << endl;
        RotationsMethod(0.01, matrix);
    } else {
        cout << "Choice method that find root of equation:" << endl;
        cout << "1) Iterations" << endl;
        cout << "2) Binary search" << endl;
        cout << "3) Newton" << endl;
        cin >> choice;
        cout << endl;
        if (!cin || choice == 0 || choice > 3) {
            cout << "Incorrect input" << endl;
            return 0;
        }
        
        switch (choice) {
            case 1:
                IterMethod(0.01);
                break;
            case 2:
                BinSearch(0.01);
                break;
            default:
                NewtonMethod(0.01);
                break;
        }
    }
    return 0;
}

/*\ 3'rd problem
 80 0 3
 0 40 0
 3 0 80
\*/

/*\ 4'th problem
 x^2 + 4 * sin(x) = 0
\*/
