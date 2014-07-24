//試し割り
//O(√n)
bool is_prime(ll n) {
    if (n == 0 || n == 1) return false;
    for (ll i = 2; i*i <= n; i++) {
        if (n%i == 0) return false;
    }
    return true;
}

//約数の列挙O(√n)
vector<int> divisor(int n) {
	vector<int> res;
	for(int i = 1 ; i * i <= n ; i++) {
		if(n % i == 0) {
			res.push_back(i);
			if(i != n / i) res.push_back(n/i);
		}
	}
	return res;
}

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

