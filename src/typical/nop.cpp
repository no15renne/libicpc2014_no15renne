const int MAX_N = 1000;
const int MAX_M = 1000;
const int M = 1000;
int n,m;
int dp[MAX_N][MAX_M];

//dp[i][j]:iのj分割

void solve() {
	dp[0][0] = 1;
	for(int i = 1 ; i <= m ; i++) {
		for(int j = 0 ; j <= n ; j++) {
			if(j - i >= 0) {
				dp[i][j] = (dp[i-1][j] + dp[i][j-i]) % M;
			} else {
				dp[i][j] = dp[i-1][j];
			}
		}
	}
	cout << dp[m][n] << endl;
}
