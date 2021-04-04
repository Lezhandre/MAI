#ifndef GYPFUN
#define GYPFUN

#include <cmath>
#include <iostream>

class GypFun{
private:
    double x;
public:
    GypFun(double val) : x(val){}
    void PutArg(double);
    double Sh();
    double Ch();
    double Th();
    double Cth();
    double Sch();
    double Csh();
    double Ash();
    double Ach();
    double Ath();
    double Acth();
    double Asch();
    double Acsh();
    void PrintSh(double, double, double);
    void PrintCh(double, double, double);
    void PrintSch(double, double, double);
    void PrintCsh(double, double, double);
    void PrintTh(double, double, double);
    void PrintCth(double, double, double);
    void PrintAsh(double, double, double);
    void PrintAch(double, double, double);
    void PrintAsch(double, double, double);
    void PrintAcsh(double, double, double);
    void PrintAth(double, double, double);
    void PrintActh(double, double, double);
};

void GypFun::PutArg(double val){
    x = val;
}

double GypFun::Ch(){
    return cosh(x);
}

double GypFun::Sh(){
    return sinh(x);
}

double GypFun::Th(){
    return tanh(x);
}

double GypFun::Cth(){
    if (tanh(x) == 0)
        return NAN;
    return 1 / tanh(x);
}

double GypFun::Sch(){
    return 1 / cosh(x);
}

double GypFun::Csh(){
    return 1 / sinh(x);
}

double GypFun::Ach(){
    return acosh(x);
}

double GypFun::Ash(){
    return asinh(x);
}

double GypFun::Ath(){
    return atanh(x);
}

double GypFun::Acth(){
    if (x == 0)
        return 0;
    return atanh(1 / x);
}

double GypFun::Asch(){
    return acosh(1 / x);
}

double GypFun::Acsh(){
    return asinh(1 / x);
}

void GypFun::PrintSh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Sh:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% .2lf\t", sinh(a + step * i));
    std::cout << std::endl;
}

void GypFun::PrintCh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Ch:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% .2lf\t", cosh(a + step * i));
    std::cout << std::endl;
}

void GypFun::PrintTh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Th:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% .2lf\t", tanh(a + step * i));
    std::cout << std::endl;
}

void GypFun::PrintCth(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Cth:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% .2lf\t", 1 / tanh(a + step * i));
    std::cout << std::endl;
}

void GypFun::PrintSch(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Sch:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% .2lf\t", 1 / cosh(a + step * i));
    std::cout << std::endl;
}

void GypFun::PrintCsh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Csh:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% .2lf\t", 1 / sinh(a + step * i));
    std::cout << std::endl;
}

void GypFun::PrintAsh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Ash:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% .2lf\t", asinh(a + step * i));
    std::cout << std::endl;
}

void GypFun::PrintAch(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Ach:\t";
    for (unsigned i = 0; i <= n; ++i){
        printf("% .2lf\t", acosh(a + step * i));
    }
    std::cout << std::endl;
}

void GypFun::PrintAth(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Ath:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% .2lf\t", atanh(a + step * i));
    std::cout << std::endl;
}

void GypFun::PrintActh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Acth:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% .2lf\t", atanh(1 / (a + step * i)));
    std::cout << std::endl;
}

void GypFun::PrintAsch(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Asch:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% 2.1lg\t", 1, cosh(1 / (a + step * i)));
    std::cout << std::endl;
}

void GypFun::PrintAcsh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Acsh:\t";
    for (unsigned i = 0; i <= n; ++i)
        printf("% 2.1lg\t", 1, sinh(1 / (a + step * i)));
    std::cout << std::endl;
}

#endif //GYPFUN