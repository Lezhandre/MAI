#include <vector>
#include <valarray>
#include <cmath>
#include <iostream>

using namespace std;

valarray <double> Gaus(vector <valarray<double>> a){
    unsigned n = a.size();
    valarray <double> ans(n);
    double coef;
    for (unsigned i = 0; i < n; ++i){
		unsigned j;
		for (j = i; j < n && a[j][i] == 0; ++j);
		if (j == n) {
			cout << "System has no solution or their quantity is infinity" << endl;
			exit(0);
		}
		if (i != j)
			swap(a[j], a[i]);
        for (j = 0; j < n; ++j){
            if (j == i) continue;
            coef = a[j][i] / a[i][i];
			a[j] -= a[i] * coef;
        }
	}
	for (unsigned i = 0; i < n; ++i)
        ans[i] =  a[i][n] / a[i][i];
    return ans;
}

int main(int argc, char** argv){
    valarray <double> coef;
    unsigned size, choice;
    cout << "Enter quantity of nodal values: ";
    cin >> size;
    if (!cin) {
        cout << "Incorrect input" << endl;
        return 0;
    }
    valarray <double> X(size), Y(size);
    cout << "Enter nodal values:" << endl;
	for (unsigned i = 0; i < size; ++i){
		cin >> X[i] >> Y[i];
        if (!cin) {
            cout << "Incorrect input" << endl;
            return 0;
        }
    }
    double x;
    cout << "Enter point where is need to calculate value: ";
    cin >> x;
    if (!cin) {
        cout << "Incorrect input" << endl;
        return 0;
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
        for (unsigned i = 0; i < size; ++i){
            tmp = Y[i];
            for (unsigned k = 0; k < size; ++k){
                if (k == i) continue;
                tmp *= (x - X[k]) / (X[i] - X[k]);
            }
            ans += tmp;
        }
        cout << "Value in selected point calculated by Lagrange: " << ans << endl;
    } else if (choice == 2) {
        tmp = 1;
        vector <double> dy(size);
        for (unsigned i = 0; i < size; ++i)
            dy[i] = Y[i];
        for (unsigned i = 0; i < size; ++i){
            ans += dy[0] * tmp;
            tmp *= x - X[i];
            for (unsigned j = 0; j + i < size - 1; ++j)
                dy[j] = (dy[j + 1] - dy[j]) / (X[j + i + 1] - X[j]);
        }
        cout << "Value in selected point calculated by Newton: " << ans << endl;
    } else {
        vector <double> h(size), P(size), Q(size), m(size);
        for (unsigned i = 1; i < size; ++i)
            h[i] = X[i] - X[i-1];
        P[1] = 0; Q[1] = 0;
        for (unsigned i = 1; i + 1 < size; ++i){
            P[i + 1] = - h[i+1] / (2 * (h[i] + h[i+1]) + P[i] * h[i]);
            tmp = (Y[i+1] - Y[i]) / h[i+1] + (Y[i] - Y[i-1]) / h[i];
            Q[i + 1] = (6 * tmp - h[i] * Q[i]) / (2 * (h[i] + h[i+1]) + P[i] * h[i]);
        }
        m[size - 1] = 0; m[0] = 0;
        for (unsigned i = size - 1; i > 0; --i)
            m[i - 1] = P[i] * m[i] + Q[i];

        unsigned l = 0, r = size - 1;
        while (r - l > 1){
            unsigned m = (l + r) / 2;
            if (X[m] > x)
                r = m;
            else
                l = m;
        }
        ans = m[l+1] * pow(x - X[l], 3) / (6*h[l+1]) + m[l] * pow(X[l+1] - x, 3) / (6*h[l+1]) + (Y[l+1] - m[l+1] * h[l+1]*h[l+1] / 6) * (x - X[l]) / h[l+1] + (Y[l] - m[l] * h[l+1]*h[l+1] / 6) * (X[l+1] - x) / h[l+1];
        cout << "Value in selected point calculated by splines: " << ans << endl;
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
        vector <valarray<double>> SLAE(3, valarray<double> (4));
        for (unsigned i = 0, j; i < 3; ++i){
            for (j = 0; j < 3; ++j){
                SLAE[i][j] = pow(X, 4 - (i + j)).sum();
            }
            SLAE[i][j] = (pow(X, 2 - i) * Y).sum();
        }
        coef = Gaus(SLAE);
        printf("Approximation by quadratic polynom (%.2lf) * x^2 + (%.2lf) * x + (%.2lf)\n", coef[0], coef[1], coef[2]);
        printf("Discrepancy of approximation: %.2lf\n", pow(coef[0] * X*X + coef[1] * X + coef[2] - Y, 2).sum());
    }
    else {
        vector <valarray<double>> SLAE(2, valarray<double> (3));
        for (unsigned i = 0, j; i < 2; ++i){
            for (j = 0; j < 2; ++j){
                SLAE[i][j] = pow(X, 2 - (i + j)).sum();
            }
            SLAE[i][j] = (pow(X, 1 - i) * Y).sum();
        }
        coef = Gaus(SLAE);
        printf("Approximation by line (%.2lf) * x + (%.2lf)\n", coef[0], coef[1]);
        printf("Discrepancy of approximation: %.2lf\n", pow(coef[0] * X + coef[1] - Y, 2).sum());
    }
}

/*\ interpolation
 6
 0.180 5.61543
 0.186 5.46693
 0.192 5.32634
 0.198 5.19304
 0.204 5.06649
 0.210 4.94619
 0.1875
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