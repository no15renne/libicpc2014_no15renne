//パスカルの三角系を用いて動的計画法で求まる。
ll mem[50][50] = {0};
ll comb(int n, int k) {
    if (k == 0 | | k == n) return 1;
    if (mem[n][k])  return mem[n][k];
    return mem[n][k] = comb(n - 1, k - 1) + comb(n-1, k);
}
//又は
for (int i = 0; i <= n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) {
        C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }
}