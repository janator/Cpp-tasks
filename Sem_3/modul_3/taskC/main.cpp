#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

const long double INF = 1e9;
const long double x_border = 2e7;
const long double y_border = 3e8;
const long double z_border = x_border * y_border;
struct Dot {
    long double x = 0.0;
    long double y = 0.0;
    long double z = 0.0;
    Dot *prev = NULL;
    Dot *next = NULL;
    int number;

    // if prev->next != this
    bool Act() {
        if (prev->next != this) {
            prev->next = next->prev = this;
            return true;
        } else {
            prev->next = next;
            next->prev = prev;
            return false;
        }
    }
};

inline long double Turn(Dot *p, Dot *q, Dot *r) {
    if (!p || !q || !r) {
        return 1.0;
    }
    return (q->x - p->x) * (r->y - p->y) - (r->x - p->x) * (q->y - p->y);
}

inline long double Time(Dot *p, Dot *q, Dot *r) {
    if (!p || !q || !r) {
        return INF;
    }
    return ((q->x - p->x) * (r->z - p->z) - (r->x - p->x) * (q->z - p->z)) / Turn(p, q, r);
}

std::vector<Dot*> BuildDownHull(std::vector<Dot> &dots, int left, int right) {
    if (right - left == 1)
        return std::vector<Dot*> ();
    int middle = (right + left) / 2;
    std::vector<Dot*> down_hull;
    Dot *u, *v;

    //recursive on left and right sides
    std::vector<Dot*> recursion_parts[2] = {BuildDownHull(dots, left, middle), BuildDownHull(dots, middle, right)};

    //find initial bridge
    u = &dots[middle - 1], v = &dots[middle];
    for (; ;) {
        if (Turn(u, v, v->next) < 0) {
            v = v->next;
        } else if (Turn(u->prev, u, v) < 0) {
            u = u->prev;
        } else {
            break;
        }
    }

    // merge by tracking bridge uv over time
    int i = 0, j = 0, minl, k;
    long double oldt, newt;
    std::vector<long double> t(6, INF);
    for (oldt = -INF; ; oldt = newt) {
        if (i < recursion_parts[0].size()) {
            t[0] = Time(recursion_parts[0][i]->prev, recursion_parts[0][i], recursion_parts[0][i]->next);
        }
        if (j < recursion_parts[1].size()) {
            t[1] = Time(recursion_parts[1][j]->prev, recursion_parts[1][j], recursion_parts[1][j]->next);
        }
        t[2] = Time(u, v, v->next);
        t[3] = Time(u, v->prev, v);
        t[4] = Time(u->prev, u, v);
        t[5] = Time(u, u->next, v);
        for (newt = INF, k = 0; k < 6; ++k) {
            if (t[k] > oldt && t[k] < newt) {
                minl = k;
                newt = t[k];
            }
        }
        if (newt == INF)
            break;
        switch (minl) {
            case 0:
                if (recursion_parts[0][i]->x < u->x) {
                    down_hull.push_back(recursion_parts[0][i]);
                }
                recursion_parts[0][i]->Act();
                ++i;
                break;
            case 1:
                if (recursion_parts[1][j]->x > v->x) {
                    down_hull.push_back(recursion_parts[1][j]);
                }
                recursion_parts[1][j]->Act();
                ++j;
                break;
            case 2:
                down_hull.push_back(v);
                v = v->next;
                break;
            case 3:
                v = v->prev;
                down_hull.push_back(v);
                break;
            case 4:
                down_hull.push_back(u);
                u = u->prev;
                break;
            case 5:
                u = u->next;
                down_hull.push_back(u);
                break;
        }
    }
    // now go back in time to update pointers
    u->next = v;
    v->prev = u;
    for (i = down_hull.size() - 1; i >= 0; --i) {
        if (down_hull[i]->x <= u->x || down_hull[i]->x >= v->x) {
            down_hull[i]->Act();
            if (down_hull[i] == u)
                u = u->prev;
            if  (down_hull[i] == v)
                v = v->next;
        } else {
            u->next = down_hull[i];
            down_hull[i]->prev = u;
            v->prev = down_hull[i];
            down_hull[i]->next = v;
            if (down_hull[i]->x <= dots[middle - 1].x) {
                u = down_hull[i];
            } else {
                v = down_hull[i];
            }
        }
    }
    return down_hull;
}

void Rotate(std::vector<Dot> &dots, long double phi) {
    for (int i = 0; i < dots.size(); ++i) {
        long double t = dots[i].x * cos(phi) + dots[i].z * sin(phi);
        dots[i].z = -dots[i].x * sin(phi) + dots[i].z * cos(phi);
        dots[i].x = t;
        t = dots[i].z * cos(phi) + dots[i].y * sin(phi);
        dots[i].y = -dots[i].z * sin(phi) + dots[i].y * cos(phi);
        dots[i].z = t;
        t = dots[i].x * cos(phi) + dots[i].y * sin(phi);
        dots[i].y = -dots[i].x * sin(phi) + dots[i].y * cos(phi);
        dots[i].x = t;
    }
}

struct Plane {
    int first;
    int second;
    int third;
    Plane(int first, int second, int third) : first(first), second(second), third(third) {}
    void CycleShift() {
        if (third < first && third < second) {
            std::swap(second, third);
            std::swap(second, first);
        }if (second < first && third > second) {
            std::swap(first, second);
            std::swap(second, third);
        }
    }
};
bool operator<(const Plane& a, const Plane& b) {
    if (a.first < b.first) {
        return true;
    } else if (a.first > b.first) {
        return false;
    } else {
        if (a.second < b.second) {
            return true;
        } else if (a.second > b.second) {
            return false;
        } else {
            return a.third < b.third;
        }
    }
}
void BuildConvexHull(std::vector<Dot> &dots, std::vector<Plane> &convex_hull) {

    std::vector<Dot*> down_hull = BuildDownHull(dots, 0, dots.size());
    for (Dot* dot : down_hull) {
        Plane plane(dot->prev->number, dot->number, dot->next->number);
        // counterclockwise relative to normal
        if (!dot->Act())
            std::swap(plane.first, plane.second);
        plane.CycleShift();
        convex_hull.push_back(plane);
    }
    // now build upper hull, all z -> -z
    for (int i = 0; i < dots.size(); ++i) {
        dots[i].next = NULL;
        dots[i].prev = NULL;
        dots[i].z *= -1;
    }
    std::vector<Dot*> upper_hull = BuildDownHull(dots, 0, dots.size());
    for (Dot* dot : upper_hull) {
        Plane plane(dot->prev->number, dot->number, dot->next->number);
        // counterclockwise relative to normal
        if (dot->Act())
            std::swap(plane.first, plane.second);
        plane.CycleShift();
        convex_hull.push_back(plane);
    }

}

int main() {
    int test_number;
    std::cin >> test_number;
    for (int i = 0; i < test_number; ++i) {
        int n;
        std::cin >> n;
        std::vector<Dot> dots(n+2);
        for (int i = 0; i < n; ++i) {
            std::cin >> dots[i].x >> dots[i].y;
            dots[i].z = dots[i].x * dots[i].x + dots[i].y * dots[i].y;
            dots[i].number = i;
        }
        dots[n].x = -2e7, dots[n].y = 3e8, dots[n].z = 2e7 * 3e8, dots[n].number = -1;
        dots[n+1].x = 2e7, dots[n+1].y = -3e8, dots[n+1].z = 2e7 * 3e8, dots[n+1].number = -2;
        std::vector<Plane> convex_hull;
        Rotate(dots, 0.01);
        std::sort(dots.begin(), dots.end(), [](Dot &a, Dot&b) {return a.x < b.x;});
        BuildConvexHull(dots, convex_hull);
        std::sort(convex_hull.begin(), convex_hull.end());
        std::cout << convex_hull.size() << std::endl;
        for (Plane plane : convex_hull) {
            std::cout << 3 << " " << plane.first << " " << plane.second << " " << plane.third << std::endl;
        }
    }
    return 0;
}