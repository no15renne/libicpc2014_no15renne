typedef double Number;
typedef vector<Number> Array;
typedef vector<Array> Matrix;
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

struct LUinfo {
  vector<Number> value;
  vector<int> index;
};
//LU•ª‰ð(O(n^3))
LUinfo LU_decomposition(Matrix A) {
  const int N = A.size();
  LUinfo data;
  for (int i = 0; i < N; ++i) {
    int pivot = i;
    for (int j = i+1; j < N; ++j)
      if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    swap(A[pivot], A[i]);
    data.index.push_back(pivot);
    for(int j = i+1; j < N; ++j) {
      A[j][i] /= A[i][i];
      for(int k = i+1; k < N; ++k)
        A[j][k] -= A[i][k] * A[j][i];
      data.value.push_back(A[j][i]);
    }
  }
  for(int i = N-1; i >= 0; --i) {
    for(int j = i+1; j < N; ++j)
      data.value.push_back(A[i][j]);
    data.value.push_back(A[i][i]);
  }
  return data;
}
//data*x = b‚ð‰ð‚­O(n^2)
Matrix LU_backsubstitution(const LUinfo &data, Matrix b) {
  const int N = b.size();
  int k = 0;
  for (int i = 0; i < N; ++i){
    swap(b[data.index[i]][0], b[i][0]);
    for(int j = i+1; j < N; ++j)
      b[j][0] -= b[i][0] * data.value[k++];
  }
  for (int i = N-1; i >= 0; --i) {
    for (int j = i+1; j < N; ++j)
      b[i][0] -= b[j][0] * data.value[k++];
    b[i][0] /= data.value[k++];
  }
  return b;
}
