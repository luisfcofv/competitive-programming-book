import java.util.*;

class Pollardsrho {
  public static long mulmod(long a, long b, long c) { // returns (a * b) % c, and minimize overflow
    long x = 0, y = a % c;
    while (b > 0) {
      if (b % 2 == 1) x = (x + y) % c;
      y = (y * 2) % c;
      b /= 2;
    }
    return x % c;
  }

  public static long abs_val(long a) { return a >= 0 ? a : -a; }

  public static long gcd(long a, long b) { return b == 0 ? a : gcd(b, a % b); } // standard gcd

  public static long pollard_rho(long n) {
    int i = 0, k = 2;
    long x = 3, y = 3;            // random seed = 3, other values possible
    while (true) {
      i++;
      x = (mulmod(x, x, n) + n - 1) % n;             // generating function
      long d = gcd(abs_val(y - x), n);                   // the key insight
      if (d != 1 && d != n) return d;       // found one non-trivial factor
      if (i == k) { y = x; k *= 2; }
    }
  }

  public static void main(String[] args) {
    long n = 2063512844981574047L; // we assume that n is not a large prime
    long ans = pollard_rho(n);      // break n into two non trivial factors
    if (ans > n / ans) ans = n / ans;        // make ans the smaller factor
    System.out.println(ans + " " + (n / ans)); // should be: 1112041493 1855607779
  }
}
