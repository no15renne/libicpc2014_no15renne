typedef vector<double> Vector;
typedef vector<Vector> Matrix;

Vector GaussJordan (Matrix A, const Vector &y) {
    assert(A[0].size() == y.size());
    int N = A.size();
    for (int i = 0; i < N; i++) A[i].push_back(y[i]);
    for (int i = 0; i < N; i++) {
        int pivot = i;
        for (int j = i; j < N; j++) {
            if (abs(A[i][j]) > abs(A[pivot][i])) pivot = j;
        }
        swap(A[i], A[pivot]);
        //no answer
        if (abs(A[i][i]) < EPS) return Vector();
        for (int j = i + 1; j <= N; j++) A[i][j] /= A[i][i];
        for (int j = 0; j < N; j++) {
            if (i != j) {
                for (int k = i + 1; k <= N; k++) A[j][k] -= A[j][i] * A[i][k];
            }
        }
    }
    Vector x(N);
    for (int i = 0; i < N; i++) x[i] = A[i][N];
    return x;
}
