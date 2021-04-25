int dp[N + 33][21];
void RMQ() {


	for (int i = 1; i <= n; i++) dp[i][0] = i;
	for (int i = 1; (1 << i) <= n; i++) {
		for (int j = 1; j + (1 << i) - 1 <= N; j++) {
			dp[j][i] = a[dp[j][i - 1]] >= a[dp[j + (1 << (i - 1))][i - 1]] ?
			           dp[j][i - 1] : dp[j + (1 << (i - 1))][i - 1];
		}
	}
}
int lg[N + 3];
void init() {
	lg[0] = -1;
	for (int i = 1; i < N; i++)lg[i] = lg[i >> 1] + 1;
}
int get(int L, int R) {
	int k = lg[R - L + 1];
	int Mid = (a[dp[L][k]] >= a[dp[R - (1 << k) + 1][k]] ? dp[L][k] : dp[R - (1 << k) + 1][k]); //最大值下标
	return Mid;
}