//x^(2*i)を計算することで高速に計算　O(log n)
int mod_pow (int x, int n, int mod) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}