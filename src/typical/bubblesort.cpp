typedef long long ll;
int n, a[MAX_N];
void solve () {
    ll ans = 0;
    for (int j = 0; j < n; j++) {
        ans += j - sum(a[j]);
        add(a[j], i);
    }
    printf("%lld\n", ans);
}
