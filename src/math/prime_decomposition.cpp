//素因数分解
//firstに値
//secondに数
//O(√n)
vector< pair<int,int> > prime_decomposition (int n) {
    vector< pair<int,int> > res;
    for (int i = 2; i*i <= n; i++) {
        if (n % i != 0) continue;
        res.push_back(make_pair(i, 0));
        while (n % i == 0) {
            res.back().second++;
            n /= i;
        }
    }
    if (n != 1) res.push_back(make_pair(n, 1));
    return res;
}
