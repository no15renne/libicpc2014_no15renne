#define MAX_N 100000
int N;
int dat[2 * MAX_N - 1];
void init (int n) {
	N = 1;
	while (N < n) N *= 2;
	for (int i = 0; i < 2*N-1; i++) dat[i] = -INFI;
}
void update (int k, int a) {
	k += N - 1;
	dat[k] = a;
	while (k > 0) {
		k = (k - 1) / 2;
		dat[k] = max(dat[k*2+1], dat[k*2+2]);
	}
}
int query (int a, int b, int k, int l, int r) {
	if(r <= a | | b <= l){ return -INFI; }
	if(a <= l && r <= b){ return dat[k]; }
	int vl = query(a, b, k*2+1, l, (l+r)/2);
	int vr = query(a, b, k*2+2, (l+r)/2, r);
	return max(vl, vr); 
}
int query (int l, int r) { return query(l, r, 0, 0, N); }
