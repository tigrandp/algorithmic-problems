#include <cstdio>
#include <cmath>

constexpr int kMaxN = 1007;
constexpr double kMaxC = 7;
constexpr double kEps = 1e-7;
double PI = std::acos(-1.0);

int n;

struct Point {
  Point() : x(0), y(0), r(0), phi(0) {}
  Point(double x_, double y_)
    : x(x_), y(y_), r(std::hypot(x, y)), phi(std::atan2(y_, x_)) {}

  void Rotate(double thetta) {
    phi -= thetta;
    x = r * std::cos(phi);
    y = r * std::sin(phi);
  }

  void Set(double r_, double phi_) {
    r = r_;
    phi = phi_;
    x = r * std::cos(phi);
    y = r * std::sin(phi);
  }

  Point operator-(const Point& lhs) const {
    return Point(x - lhs.x, y - lhs.y);
  }

  Point operator+(const Point& lhs) const {
    return Point(x + lhs.x, y + lhs.y);
  }

  Point operator*(double alpha) const {
    return Point(x * alpha, y * alpha);
  }

  void Print() {
    printf("%lf %lf\n", x, y);
  }

  void Debug() const {
    fprintf(stderr, "Dec=(%.3lf, %.3lf) Polar=(%.3lf, %.3lf)\n", x, y, r, phi);
  }

  double x, y;
  double r, phi;
} points[kMaxN];

double Det(double A11, double A12, double A21, double A22) {
  return A11 * A22 - A12 * A21;
}

struct Line {
  Line() : a(0.0), b(0.0), c(0.0) {}
  Line(const Point& lhs, const Point& rhs) : p(lhs), q(rhs) {
    a = p.y - q.y;
    b = q.x - p.x;
    c = -a * p.x - b * p.y;
  }

  bool Intersect(const Line& o, Point& inter_point) const {
    double det = Det(a, b, o.a, o.b);
    if (std::fabs(det) <= kEps) return false;

    double X1 = Det(-c, b, -o.c, o.b) / det;
    double Y1 = Det(a, -c, o.a, -o.c) / det;

    double min_x = std::min(o.p.x, o.q.x);
    double max_x = std::max(o.p.x, o.q.x);

    double min_y = std::min(o.p.y, o.q.y);
    double max_y = std::max(o.p.y, o.q.y);

    if (X1 < min_x - kEps || X1 > max_x + kEps) return false;
    if (Y1 < min_y - kEps || Y1 > max_y + kEps) return false;

    inter_point = Point(X1, Y1);

    return true;
  }

  Point p, q;
  double a, b, c;
};

double Area(const Point& a, const Point& b, const Point& c) {
  return std::fabs((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) * 0.5;
}

int main() {
  // freopen("debug.out", "w", stdout);
  int test_cases; scanf("%d", &test_cases);

  while (test_cases--) {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
      double x, y;
      scanf("%lf%lf", &x, &y);
      points[i] = Point(x, y);
    }

    // Move the first point to the origin.
    for (int i = 1; i < n; ++i) {
      points[i] = points[i] - points[0];
    }
    points[0] = Point(0, 0);

    // Rotate the polygon so that the first segment lies on x-axis.
    double thetta = points[1].phi;
    for (int i = 1; i < n; ++i)
      points[i].Rotate(thetta);

    // Find the location of the camera.
    Point mid = points[0] + (points[1] - points[0]) * 0.5;

    // Find the vectors at which camera observes. 
    Point pos_v; pos_v.Set(kMaxC, PI / 4);
    Point neg_v; neg_v.Set(kMaxC, 3 * PI / 4);
    Line l_pos(mid, mid + pos_v);
    Line l_neg(mid, mid + neg_v);

    // Find intersection with the polygon from both sides.
    Point pos_intersect;
    int pos_seg_b = 0, pos_seg_e = 0;

    Point neg_intersect;
    int neg_seg_b = 0, neg_seg_e = 0;
    for (int i = 1; i < n; ++i) {
      int curr = i, next = (i + 1) % n;

      Point result;
      if (l_pos.Intersect(Line(points[curr], points[next]), result)) {
        pos_seg_b = curr;
        pos_seg_e = next;
        pos_intersect = result;
      }
      if (l_neg.Intersect(Line(points[curr], points[next]), result)) {
        neg_seg_b = curr;
        neg_seg_e = next;
        neg_intersect = result;
      }
    }

    // fprintf(stderr, "Positive intersection: %d %d\n", pos_seg_b, pos_seg_e); pos_intersect.Debug();
    // fprintf(stderr, "Negative intersection: %d %d\n", neg_seg_b, neg_seg_e); neg_intersect.Debug();

    // Now we have everything to calculate the area under the surveilance.
    double surveilance_area = 0.0;
    
    if (pos_seg_b == neg_seg_b && pos_seg_e == neg_seg_e) {
      surveilance_area += Area(mid, pos_intersect, neg_intersect);
    } else {
      surveilance_area = Area(mid, pos_intersect, points[pos_seg_e]) +
                         Area(mid, neg_intersect, points[neg_seg_b]);
      for (int i = pos_seg_e; i < neg_seg_b; ++i) {
        surveilance_area += Area(mid, points[i], points[(i + 1) % n]);
      }
    }

    double total_area = 0.0;
    for (int i = 1; i <= n; ++i) {
      total_area += Area(mid, points[i % n], points[(i + 1) % n]);
    }

    printf("%.7lf\n", surveilance_area / total_area);
    // fprintf(stderr, "Answer: %.7lf\n", surveilance_area / total_area);
  }

  return 0;
}
