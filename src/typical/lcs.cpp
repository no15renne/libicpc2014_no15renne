const int MAX_N = 10000;
const int MAX_M = 10000;
int n,m; //文字列の長さ
char s[MAX_N],t[MAX_M];
int dp[MAX_N + 1][MAX_M + 1]; 

void solve() {
	for(int i =  0 ; i < n ; i++) {
		for(int j = 0 ; j < m ; j++) {
 			if(s[i] == s[j]) {
				dp[i + 1][j + 1] = dp[i][j] + 1;
			} else {
				dp[i + 1][j + 1] = max(dp[i + 1][j],dp[i][j + 1]);
			}
		}
	}
	cout << dp[n][m] << endl;
}

