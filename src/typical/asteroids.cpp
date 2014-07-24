int N, K;
int R[MAX_K], C[MAX_K];
void solve () {
    V = N * 2;
    for (int i = 0; i < K; i++) {
        add_edge(R[i] - 1, N + C[i] - 1);
    }
    printf("%d\n", bipartite_matching());
}
