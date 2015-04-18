#include <vector>
#include <iostream>

using namespace std;

#define Int int

Int cross_product(const pair<Int, Int> &x, const pair<Int, Int> &y, const pair<Int, Int> &z)
{
    return (y.first - x.first) * (z.second - x.second) -
           (z.first - x.first) * (y.second - x.second);
}


int pointinpoly(Int x0, Int y0, vector<pair<Int, Int> > poly)
{
    pair<Int, Int> p = make_pair(x0, y0);
    if (poly.size() <= 0)
        return false;
    else if (poly.size() == 1) {
        if (p == poly[0])
            return 2;
        return 0;
    } else if (poly.size() == 2) {
        if (p.first <= std::max(poly[0].first, poly[1].first) &&
            p.first >= std::min(poly[0].first, poly[1].first) &&
            p.second >= std::min(poly[0].second, poly[1].second) &&
            p.second <= std::max(poly[0].second, poly[1].second) &&
            0 == cross_product(poly[0], poly[1], p))
            return 2;
        return 0;
    }


    bool inside = false;
    bool on = false;

    int num_points = poly.size();
    pair<Int, Int> p1 = poly[0];
    int count = 0;
    for (int i = 1; i <= num_points; ++i) {
        pair<Int, Int> &p2 = poly[i % num_points];
        if (p2 == p1)
            continue; //ignore duplicate consecutives

        int cross_prod = cross_prod = cross_product(p, p1, p2);
        if (p1.second < p2.second)
            cross_prod = cross_prod = cross_product(p, p1, p2);
        else
            cross_prod = cross_product(p, p2, p1);
        if (p.second >= std::min(p1.second, p2.second) && p.second <= std::max(p1.second, p2.second) &&
            p.first <= std::max(p1.first, p2.first)) { // && p.first>=std::min(p1.first, p2.first))
            if (cross_prod == 0 && p.first >= std::min(p1.first, p2.first))
                on = true;
            if (cross_prod > 0 && p.second != std::min(p1.second, p2.second))
                inside = !inside;
        }
        p1 = p2;
    }
    if (on)
        return 2;
    return inside;
}

int main()
{
    int num_points;
    int a, b;

    pair<Int, Int> p1 = make_pair(5, 5);
    pair<Int, Int> p2 = make_pair(10, 0);
    pair<Int, Int> p3 = make_pair(0, 10);

    while (scanf("%d", &num_points) && num_points > 0) {
        vector<pair<Int, Int> > poly;
        for (int i = 0; i < num_points; ++i) {
            scanf("%d %d", &a, &b);
            poly.push_back(make_pair(a, b));
        }
        int queries;
        scanf("%d", &queries);
        for (int i = 0; i < queries; ++i) {
            scanf("%d %d", &a, &b);
            int pnt = pointinpoly(a, b, poly);
            if (pnt == 1) {
                printf("in\n");
            } else if (pnt == 2) {
                printf("on\n");
            } else {
                printf("out\n");
            }
        }
    }

    return 0;
}

