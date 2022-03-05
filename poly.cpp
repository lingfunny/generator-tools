#include <bits/stdc++.h>
#define LL long long
using namespace std;

struct P {
// 单个元
// f: 元名称
// c: 元次数
	int f, c;
	inline bool operator < (const P& rhs) const {
		/*
		* 次数优先
		*/
		if(c != rhs.c) return c < rhs.c;
		return f < rhs.f;
	}
	// 全等
	inline bool operator == (const P& rhs) const { return f==rhs.f&&c==rhs.c; }
};
inline bool equals(vector <P> a, vector <P> b) { sort(a.begin(), a.end()); sort(b.begin(), b.end()); return a==b; }
struct F {
	// 单整式
	// pre 系数
	int pre; vector <P> v;
	inline void Sort() { sort(v.begin(), v.end()); }
	inline F operator * (const F& rhs) const {
		// 整式相乘
		F r = {pre * rhs.pre, {}};
		map <int, int> mp;
		for(P x: v) mp[x.f] += x.c; for(P x: rhs.v) mp[x.f] += x.c;
		// 某个元的指数相加
		for(auto x: mp) r.v.push_back({x.first, x.second});
		r.Sort();
		return r;
	}
	inline F operator * (const int& rhs) const { return {pre * rhs, v}; }
	inline bool operator < (const F& rhs) const {
		int totx = 0, toty = 0, mxx = 0, mxy = 0;
		for(P x: v) totx += x.c, mxx = max(mxx, x.c);
		for(P x: rhs.v) toty += x.c, mxy = max(mxy, x.c);
		/*
		* 次数优先
		* 最高次次之
		* 未知量个数次之
		* 系数次之
		*/
		if(totx != toty) return totx < toty;
		if(mxx != mxy) return mxx < mxy;
		if(v.size() != rhs.v.size()) return v.size() > rhs.v.size();
		return pre < rhs.pre;
	}
	inline bool operator == (const F& rhs) const {
		// 若整式相等则相等
		vector <P> x = v, y = rhs.v;
		return equals(x, y);
	}
};
inline void merge(vector <F>& v) {
	sort(v.begin(), v.end());
	for(auto it = v.begin(); it != v.end();)
	if(next(it) != v.end()) {
		if(*next(it) == *it) {
			(*it).pre += (*next(it)).pre;
			v.erase(next(it));
		} else ++it;
	} else ++it;
	sort(v.begin(), v.end());
}
struct FF {
	// 多项式
	vector <F> vv;
	inline void Sort() { sort(vv.begin(), vv.end()); }
	inline FF operator * (const FF& rhs) const {
		FF r;
		// 卷积
		for(auto a: vv) for(auto b: rhs.vv) r.vv.push_back(a*b);
		merge(r.vv);
		return r;
	}
	inline FF operator + (const FF& rhs) const {
		FF r;
		for(auto a: vv) r.vv.push_back(a);
		for(auto a: rhs.vv) r.vv.push_back(a);
		// 暴力插入再合并
		merge(r.vv);
		return r;
	}
	inline FF operator * (const int& rhs) const {
		FF r = *this;
		for(auto it = r.vv.begin(); it != r.vv.end(); ++it)
		(*it) = (*it) * rhs;
		// 每个点暴力乘
		r.Sort();
		return r;
	}
	inline void output(int mode = 0) {
		Sort();
		for(auto it = vv.begin(); it != vv.end(); ++it) {
			F dxs = *it;
			int flg = 0, flgg = 0;
			if(abs(dxs.pre) > 1) printf("%d ", dxs.pre), flgg = 1; // 系数大于1 输出
			else {
				if(abs(dxs.pre) == 0) continue;
				printf("%c", dxs.pre < 0 ? '-' : ' ');	// 系数为±1，输出符号
			}
			for(P dx: dxs.v) {
				if(dx.f == 0) continue; // 特殊
				if(dx.c == 0) continue;
				// 输出了系数，加上乘号
				// if(!flg && flgg) printf("\\times "), flg = 1;
				if(mode == 0) {
					if(dx.c > 1) printf("f_{%d}^{%d} ", dx.f, dx.c);
					else printf("f_{%d} ", dx.f);	// 一次项不输出指数
				} else {
					#define BEGIN 'a'-1
					if(dx.c > 1) printf("%c^{%d} ", BEGIN+dx.f, dx.c);
					else printf("%c ", BEGIN+dx.f);	// 一次项不输出指数
					#undef BEGIN
				}
				flg = 1;
			}
			if(!flg && !flgg) printf("%d", dxs.pre);	// 如果没有整式，输出常数
			if(next(it) != vv.end() && ((next(it)->pre)>0)) printf(" + ");	// 如果不是最后一个，填上加号
		}
		puts("\\\\");	// 换行
	}
};

#define pre 0
#define f 0
#define c 0
const FF SaMpLe = {{
	{pre, { {f, c}, {f, c}, {f, c} }},
	{pre, { {f, c}, {f, c} }},
	{pre, { {f, c} }}
}};
#undef pre
#undef f
#undef c

inline void ScHsQnJj() {
	// 生成函数求逆卷积
	static const int n = 6, mxn = n+2;
	FF A[mxn], F[mxn];
	for(int i = 0; i <= n; ++i) F[i] = {{{1,{{i, 1}}}}};
	A[0] = {{{1, {{0, 1}}}}};
	for(int i = 1; i <= n; ++i) {
		FF ans;
		for(int j = 1; j <= i; ++j)
		ans = ans + (F[j] * A[i-j]);
		A[i] = ans * -1;
	}
	for(int i = 0; i <= n; ++i) A[i].output(1);
}
inline void TEST() {}

signed main() {
	puts("\\begin{array}{c}");
	TEST();
	puts("\\end{array}");
	return 0;
}