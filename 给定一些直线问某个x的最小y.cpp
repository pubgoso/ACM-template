
struct Line {
	LL m, c;
public:
	bool operator<(Line l) {//find min
		if (m != l.m)return m > l.m;
		else return c > l.c;
	}
	/*
	bool operator<(Line l) {//find max
		if (m != l.m)return m < l.m;
		else return c < l.c;
	}
	*/
	bool check(Line L1, Line L2, Line L3) {//find min
		return 1ll * (L3.c - L1.c) * (L1.m - L2.m)
		       < 1ll * (L2.c - L1.c) * (L1.m - L3.m);
	}
	/*
	bool check(Line L1, Line L2, Line L3) {//find max
		return 1ll * (L3.c - L1.c) * (L1.m - L2.m)
	        <= 1ll * (L2.c - L1.c) * (L1.m - L3.m);
	}
	*/
} lines[N];
struct Convex_HULL_Trick {
	vector<Line> l;
	void add(Line newLine) {
		int n = l.size();
		while (n >= 2 && newLine.check(l[n - 2], l[n - 1], newLine)) {
			n--;
		}
		l.resize(n);
		l.push_back(newLine);
	}
	LL value(int in, int x) {
		return 1ll * l[in].m * x + l[in].c;
	}
	LL minQuery(int x) {
		if (l.empty())return LLONG_MAX;
		int low = 0, high = (int)l.size() - 2;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (value(mid, x) > value(mid + 1, x)) low = mid + 1;
			else high = mid - 1;
		}
		return value(low, x);
	}

	/*
	  LL maxQuery(int x) {
	    if (l.empty())return LLONG_MIN;
	    int low = 0, high = (int)l.size() - 2;
	    while (low <= high) {
	      int mid = (low + high) / 2;
	      if (value(mid, x) < value(mid + 1, x)) low = mid + 1;
	      else high = mid - 1;
	    }
	    return value(low, x);
	  }
	*/
} cht;
//sort(lines, lines + n);
//cht.add(lines[i]);
//cht.minQuery(pos)
