#include "../../segmentintersection.h"
#include <cstdio>
#include <cmath>

using namespace std;

// just to avoid -0.0 in output
inline double adjustZeroes(double &d) {
    if (fabs(d) < 0.00000001)
        return 0.0;
    else
        return d;
}

int main()
{
    int cases;
    scanf("%d", &cases);
    for (int i = 0; i < cases; ++i)
    {
        double x1, y1, x2, y2, x3, y3, x4, y4;
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
        auto res = segmentIntersection(Line({{x1, y1}, {x2, y2}}), Line({{x3, y3}, {x4, y4}}));
        if (res.result_type == NONE)
            printf("none\n");
        else if (res.result_type == SINGLE_POINT)
            printf("%.2f %.2f\n", adjustZeroes(res.p1.first), adjustZeroes(res.p1.second));
        else {
            printf("%.2f %.2f %.2f %.2f\n", adjustZeroes(res.p1.first), adjustZeroes(res.p1.second), adjustZeroes(res.p2.first), adjustZeroes(res.p2.second));
        }
    }
}
