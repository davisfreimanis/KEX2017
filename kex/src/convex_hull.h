// Authors: Johannes Olegård <jolegard@kth.se> and
//          Johannes Olsson  <johanneo@kth.se>

#include <vector>
#include <algorithm>
#include <numeric>


//Cross-product of two points/vectors.
template<class AT, class AF, class BT, class BF>
typename impl::TypeJoin<AT,BT>::type
cross(const Point<AT,AF> &a, const Point<BT,BF> &b) {
    return a.x*b.y - a.y*b.x;
}n
// Convex hull of set of 2D-points.
// Return size of hull and write hull point indices to res
// in counterclockwise order.
//
// p: random-access iterator to the set of points.
// n: |p|
// res: iterator to write the hull indices to.
//
// Ref:
//  <https://en.wikipedia.org/wiki/Graham_scan>
template<class P, class I>
size_t convex_hull(P p, size_t n, I res) {
    std::vector<size_t> ss(1+n);
    std::iota(ss.begin()+1, ss.end(), 0);

    size_t num_points; // num (unique/relevant) points
    { // filter out duplicates to avoid issues
        std::sort(ss.begin()+1, ss.end(),
                [&] (size_t i, size_t j) {
                return (p[i].y < p[j].y
                        || (p[i].y == p[j].y
                            && p[i].x < p[j].x));
                });

        num_points = 1;
        for (size_t i = 0+2; i < n+1; ++i) {
            if (p[ss[i-1]] != p[ss[i]]) {
                ss[++num_points] = ss[i];
            }
        }
        ss.resize(1+num_points);
    }

    // the bottom-left-most point WILL be on the hull
    auto base = p[ss[1]];

    std::sort(ss.begin()+1, ss.end(),
            [&] (size_t i, size_t j) {
            auto d = cross(p[i]-base, p[j]-base);
            return (d > 0
                    || (d == 0
                        && ((p[i]-base).len2() < (p[j]-base).len2())));
            });

    ss[0] = ss[num_points];

    size_t k = 1;
    for (size_t i = 2; i < num_points + 1; ++i) {
        // while right turn or straight
        while (cross(p[ss[k]] - p[ss[k-1]], p[ss[i]] - p[ss[k]]) <= 0) {
            if (k > 1) {
                --k;
            } else if (i == num_points) {
                break;
            } else {
                ++i;
            }
        }
        ++k;
        std::swap(ss[k], ss[i]);
    }

    for (size_t i = 0+1; i < k + 1; ++i) {
        *res = ss[i];
        ++res;
    }
    return k;
}

int test() {
    return 3;
}