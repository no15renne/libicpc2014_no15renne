int N, K;
int T[MAX_K], X[MAX_K], Y[MAX_K];

void solve () {
    init(N*3);
    int ans = 0;
    for (int i = 0; i < K; i++) {
        int t = T[i];
        int x = X[i] - 1, Y[i] - 1;
        
        // incorrect number
        if (x < 0 || N <= x || y < 0 || N <= y) {
            ans++;
            continue;
        }
        if (t == 1) {
            // x and y is same kind
            if (same(x, y+N) || same(x, y+2*N)) {
                ans++;
            } else {
                unite(x, y);
                unite(x+N, y+N);
                unite(x+N*2, y+N*2);
            }
        } else {
            // x eat y
            if (same(x, y) || same(x, y+2*N)) {
                ans++;
            } else {
                unite(x, y+N);
                unite(x+N, y+2*N);
                unite(x+2*N, y);
            }
        }
    }
    printf("%d\n",ans);
}
            }
