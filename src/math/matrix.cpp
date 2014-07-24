const int MOD = 10000;

Matrix Mul (Matrix A, Matrix B) {
    int M = A.size(), N = B[0].size();
    assert(A[0].size() == B.size());
    int K = A[0].size();
    Matrix C(M, Vector(N, 0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}


Matrix Pow (Matrix A, long long n) {
    assert(A.size() == A[0].size());
    int N = A.size();
    if (n == 0) {
        for (int i = 0; i < N; i++) 
            for (int j = 0; j < N; j++) 
                A[i][j] = i==j;
        return A;
    }
    else 
        return n % 2 == 0 ? Pow(Mul(A, A), n/2) : Mul(A, Pow(A, n-1));
}
int Rank (Matrix A) {
    int M = A.size(), N = A[0].size();
    int r = 0;
    for (int i = 0; i < N && r < M; i++) {
        int pivot = r;
        for (int j = r + 1; j < M; j++) 
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        swap(A[pivot], A[r]);
        if (abs(A[r][i]) < EPS) continue;
        for (int k = N-1; k >= i; k--) {
            A[r][k] /= A[r][i];
        }
        for (int j = r + 1; j < M; j++) {
            double tmp = A[j][i];
            for (int k = i; k < N; k++) {
                A[j][k] -= A[r][k] * tmp;
                //A[j][k] = static_cast<int>(round(A[j][k] + MOD)) % MOD;
            }
        }
        r++;
    }
    return r;
}

