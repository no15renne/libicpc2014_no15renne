//エラトステネスの篩
//O(N log log N)
//N未満の素数テーブルを求める。
vector<int> eratosthenes (int n) {
    vector<int> primes(n);
    primes[0] = primes[1] = 0;
    for (int i = 2; i < n; i++) primes[i] = i;
    for (int i = 2; i < n; i++)
        if (primes[i]) 
            for (int j = i<<1; j < n; j += i) 
                primes[j] = 0;
    vector<int>::iterator it = remove(primes.begin(), primes.end(), 0);
    primes.erase(it, primes.end());
    return primes;
}