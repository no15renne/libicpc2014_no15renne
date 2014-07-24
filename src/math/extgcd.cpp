//ax+by=1となる整数x,yを求める場合に使える。
int extgcd (int a, int b, int x, int y) {
    int d = a;
    if (b != 0) {
        d = extgcd(b, a%b, y, x);
        y -= (a / b) *x;
    } else {
        x = 1;
        y = 0;
    }
    return d;
}