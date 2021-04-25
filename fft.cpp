#include<iostream>
#include<cstdio>
#include<cmath>
#include <cstring>
using namespace std;
const int MAXN = (1 << 21) + 10;
const double Pi = acos(-1.0);
struct complex {
	double x, y;
	complex (double xx = 0, double yy = 0) {x = xx, y = yy;}
} a[MAXN], b[MAXN];
complex operator + (complex a, complex b) { return complex(a.x + b.x , a.y + b.y);}
complex operator - (complex a, complex b) { return complex(a.x - b.x , a.y - b.y);}
complex operator * (complex a, complex b) { return complex(a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x);} //不懂的看复数的运算那部分
int N, M;
int l, r[MAXN];
int limit = 1;
void fast_fast_tle(complex *A, int type) {
	for (int i = 0; i < limit; i++)
		if (i < r[i]) swap(A[i], A[r[i]]); //求出要迭代的序列
	for (int mid = 1; mid < limit; mid <<= 1) { //待合并区间的长度的一半
		complex Wn( cos(Pi / mid) , type * sin(Pi / mid) ); //单位根
		for (int R = mid << 1, j = 0; j < limit; j += R) { //R是区间的长度，j表示前已经到哪个位置了
			complex w(1, 0); //幂
			for (int k = 0; k < mid; k++, w = w * Wn) { //枚举左半部分
				complex x = A[j + k], y = w * A[j + mid + k]; //蝴蝶效应
				A[j + k] = x + y;
				A[j + mid + k] = x - y;
			}
		}
	}
}
int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i <= N; i++) scanf("%lf", &a[i].x);
	for (int i = 0; i <= M; i++) scanf("%lf", &b[i].x);
	while (limit <= N + M) limit <<= 1, l++;
	for (int i = 0; i < limit; i++)
		r[i] = ( r[i >> 1] >> 1 ) | ( (i & 1) << (l - 1) ) ;
	fast_fast_tle(a, 1);
	fast_fast_tle(b, 1);
	for (int i = 0; i <= limit; i++) a[i] = a[i] * b[i];
	fast_fast_tle(a, -1);
	for (int i = 0; i <= N + M; i++) {
		printf("%d ", (int)(a[i].x / limit + 0.5));
	}
	return 0;
}