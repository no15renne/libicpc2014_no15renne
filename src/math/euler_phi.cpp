//オイラー関数により互いに素な数の数がわかる。
//phi(m*n)=phi(m)*phi(n)
//phi(p)=p-1(pは素数)
int euler_phi (int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            for (; n % i == 0; n /= i);
        }
    }
    if (n != 1) res = res / n * (n - 1);
    return res;
}

vector<int> euler_phi_table (int N) {
    vector<int> phi(N);
    phi[0] = phi[1] = 0;
    for (int i = 2; i < N; i++) phi[i] = i;
    for (int i = 2; i < N; i++) {
        if (phi[i] == i) {
            for (int j = i; j < N; j += i) {
                phi[j] = phi[j] * (i-1) / i;
            }
        }
    }
    return phi;
}