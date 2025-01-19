#include "Integral.h"



double simpsonRule(FuncPointer f, double a, double b, int n){
    double h = (b-a)/n;
    double sum = f(a) + f(b);

    for(int i = 1; i < n; i++){
        if (i % 2 == 0) {
            sum += 2 * f(a + i*h);
        } else {
            sum += 4 * f(a + i*h);
        }
    }
    return (h/3)*sum;
}