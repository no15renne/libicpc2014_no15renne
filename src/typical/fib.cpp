void solve () {
    mat A(2, vec(2));
    A[0][0] = 1; A[0][1] = 1;
    A[1][0] = 1; A[1][1] = 0;
    A = pow(A,N);
    printf("%d\n", A[1][0]);
}
