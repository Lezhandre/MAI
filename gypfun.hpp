#ifndef GYPFUN
#define GYPFUN

#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

class GypFun{
private:
    class Result{
    private:
        double res;
    public:
        Result(double new_r = 0) : res(new_r) {};
        friend std::ostream& operator << (std::ostream&, Result);
    };
    double x;
public:
    GypFun() {};
    GypFun(double val) : x(val){}
    void PutArg(double);
    Result Sh();
    Result Ch();
    Result Th();
    Result Cth();
    Result Sch();
    Result Csh();
    Result Ash();
    Result Ach();
    Result Ath();
    Result Acth();
    Result Asch();
    Result Acsh();
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
    friend std::ostream& operator << (std::ostream&, Result);
};

void GypFun::PutArg(double val){
    x = val;
}

GypFun::Result GypFun::Ch(){
    return cosh(x);
}

GypFun::Result GypFun::Sh(){
    return sinh(x);
}

GypFun::Result GypFun::Th(){
    return tanh(x);
}

GypFun::Result GypFun::Cth(){
    return 1 / tanh(x);
}

GypFun::Result GypFun::Sch(){
    return 1 / cosh(x);
}

GypFun::Result GypFun::Csh(){
    return 1 / sinh(x);
}

GypFun::Result GypFun::Ach(){
    return acosh(x);
}

GypFun::Result GypFun::Ash(){
    return asinh(x);
}

GypFun::Result GypFun::Ath(){
    return atanh(x);
}

GypFun::Result GypFun::Acth(){
    return atanh(1 / x);
}

GypFun::Result GypFun::Asch(){
    return acosh(1 / x);
}

GypFun::Result GypFun::Acsh(){
    return asinh(1 / x);
}

std::ostream& operator << (std::ostream& out, GypFun::Result res){
    if (isnan(res.res) || isinf(res.res))
        printf(" NaN");
    else
        printf("% .2lf", res.res);
    return out;
}

void GypFun::PrintSh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Sh:\t\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Sh() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintCh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Ch:\t\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Ch() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintTh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Th:\t\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Th() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintCth(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Cth:\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Cth() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintSch(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Sch:\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Sch() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintCsh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Csh:\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Csh() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintAsh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Ash:\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Ash() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintAch(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Ach:\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Ach() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintAth(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Ath:\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Ath() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintActh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Acth:\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Acth() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintAsch(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Asch:\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Asch() << '\t';
    }
    std::cout << std::endl;
}

void GypFun::PrintAcsh(double a, double b, double step){
    unsigned n = (b - a) / step;
    std::cout << "Acsh:\t";
    for (unsigned i = 0; i <= n; ++i){
        x = a + step * i;
        std::cout << Acsh() << '\t';
    }
    std::cout << std::endl;
}

#endif //GYPFUN
