#include <iostream>

#include "Rational.h"

int main()
{
    int cases;

    scanf("%d", &cases);

    for (int i = 0; i < cases; ++i) {
        long long int x1, y1, x2, y2;
        char op;

        scanf("%lld %lld %c %lld %lld", &x1, &y1, &op, &x2, &y2);

        Rational<long long> a(x1, y1), b(x2, y2), c(0, 0);

        switch (op) {
        case '+':
            c = a + b;
            break;

        case '-':
            c = a - b;
            break;

        case '*':
            c = a * b;
            break;

        case '/':
            c = a / b;
            break;
        }

        printf("%lld / %lld\n", c.num(), c.den());
    }
}
