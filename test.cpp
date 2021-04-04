#include <iostream>
#include "gypfun.hpp"
#include <cmath>

int main(){
    using namespace std;
    GypFun F(2.3), G(1.7), E(4);
    cout << F.Ch() << "^2 - " << F.Sh() << "^2 = " << pow(F.Ch(), 2) - pow(F.Sh(), 2) << endl; 
    cout << F.Th() << " * " << F.Cth() << " = " << F.Th() * F.Cth() << endl;
    cout << E.Ch() << " = " << F.Ch() * G.Ch() - F.Sh() * G.Sh();
    cout << endl;
    
    cout << '\t';
    for (unsigned i = 0; i <= 20; ++i)
        printf("% .2lf\t", -1 + i * 0.1);
    cout << endl;
    F.PrintSh(-1, 1, 0.1);
    F.PrintCh(-1, 1, 0.1);
    F.PrintTh(-1, 1, 0.1);
    F.PrintCth(-1, 1, 0.1);
    F.PrintSch(-1, 1, 0.1);
    F.PrintCsh(-1, 1, 0.1);
    cout << endl;

    cout << '\t';
    for (unsigned i = 0; i <= 20; ++i)
        printf("% .2lf\t", -1 + i * 0.1);
    cout << endl;
    F.PrintAsh(-1, 1, 0.1);
    F.PrintAch(-1, 1, 0.1);
    F.PrintAth(-1, 1, 0.1);
    F.PrintActh(-1, 1, 0.1);
    F.PrintAsch(-1, 1, 0.1);
    F.PrintAcsh(-1, 1, 0.1);
    return 0;
}