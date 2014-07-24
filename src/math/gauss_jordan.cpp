typedef vector<double> Array;
typedef vector<Array> Matrix;
Array gauss_jordan (const Matrix &A, const Array &b) {
    int n = A.size();
    Matrix B(n, Array(n + 1));
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) B[i][j] = A[i][j];
    for (int i = 0; i < n; i++) B[i][n] = b[i];

    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i; j < n; j++) {
            if (abs(B[i][j]) > abs(B[pivot][i])) pivot = j;
        }
        swap(B[i], B[pivot]);
        //no answer
        if (abs(B[i][i]) < EPS) return Array();

        for (int j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                for (int k = i + 1; k <= n; k++) B[j][k] -= B[j][i] * B[i][k];
            }
        }
    }
    Array x(n);
    for (int i = 0; i < n; i++) x[i] = B[i][n];
    return x;
}