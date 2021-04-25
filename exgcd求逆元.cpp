struct INV {
	LL exgcd(LL a, LL b, LL &x, LL &y) {
		if (b == 0) {
			x = 1;
			y = 0;
			return a;
		}
		LL g, t;
		g = exgcd(b, a % b, x, y);
		t = x;
		x = y;
		y = t - a / b * y;
		return g;
	}
	LL inv(LL a, LL p) {
		LL g, x, y;
		g = exgcd(a, p, x, y);
		return g == 1 ? (x + p) % p : -1;
	}
};