class FFT {
public:
  struct Point {
      double x, y;
  };

  Point pointPlus(Point a, Point b) {
      a.x += b.x;
      a.y += b.y;
      return a;
  }

  Point pointMinus(Point a, Point b) {
      a.x -= b.x;
      a.y -= b.y;
      return a;
  }

  Point pointMultiple(Point a, Point b) {
      Point c;
      c.x = a.x * b.x - a.y * b.y;
      c.y = a.x * b.y + a.y * b.x;
      return c;
  }

  Point pointMultipleDouble(Point a, double k) {
      a.x *= k;
      a.y *= k;
      return a;
  }

  Point pointPolar(double r, double t) {
      Point a;
      a.x = r * cos(t);
      a.y = r * sin(t);
      return a;
  } /* r * exp(i * t), i = sqrt(-1) */

  static Point pointGenerator(double x, double y) {
      Point res;
      res.x = x;
      res.y = y;
      return res;
  }   /* x + i * y *

  /* Fast Fourier Transform */
  /* n = size of a = a power of 2, theta = 2 * PI / n */
  /* for inverse fft, theta = -2 * PI / n */
  void calcDFT(int n, double theta, vector<Point>& a) {

      for(int m = n; m >= 2; m /= 2) {
          int mh = m / 2;
          rep(i, mh) {
              Point w = pointPolar(1, i * theta);
              for(int j = i; j < n; j += m) {
                  int k = j + mh;
                  Point x = pointMinus(a[j], a[k]);
                  a[j] = pointPlus(a[j], a[k]);
                  a[k] = pointMultiple(w, x);
              }
          }
          theta *= 2;
      }

      int i = 0;
      FOR(j, 1, n - 2) {
          for(int k = n / 2; k > (i ^= k); k /= 2);
          if(j < i) {
              Point tmp = a[i];
              a[i] = a[j];
              a[j] = tmp;
          }
      }
  }

  vector<Point> iDFT(int N, vector<Point>& P, vector<Point>& Q) {
      vector<Point> R(N, pointGenerator(0, 0));
      double invN = 1.0 / N;
      double theta = 2 * PI * invN;

      // P and Q are polynomials of M (<= N / 2) degree
      // R is polynomial of N degree contains the multiplication result of P and Q
      calcDFT(N, theta, P);
      calcDFT(N, theta, Q);
      rep(i, N) {
          R[i] = pointMultiple(P[i], Q[i]);
      }
      calcDFT(N, -1.0 * theta, R);

      rep(i, N) {
          R[i].x *= invN;
      }

      return R;
  }
};

/*
Example:
FFT fft;
vector<FFT::Point> P(65536, FFT::pointGenerator(0, 0)), Q(65536, FFT::pointGenerator(0, 0));
P[0].x = 2, P[1].x = 3, P[2].x = 4; // 2 + 3x + 4x^2
Q[0].x = 5, Q[1].x = 7; // 5 + 7x
vector<FFT::Point> R = fft.iDFT(65536, P, Q); // 10 + 29x + 41x^2 + 28x^3

*/
