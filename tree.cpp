#include <bits/stdc++.h>
using namespace std;
mt19937 myrand(time(0));
#define random(a, b) (myrand()%(b-a+1) + a)

void creatData(int n) {
	int *tree = new int [n];
	for (int i = 0; i < n; ++i) {
		tree[i] = i + 1;
	}
	int root = random(0, n - 1);
	swap(tree[root], tree[n - 1]);
	int nxt_idx = n - 2;
	queue<int> Que;
	cout << n << endl;
	cout << endl;
	Que.push(tree[n - 1]);
	while (!Que.empty()) {
		int now = Que.front();
		Que.pop();
		int cnt = random(1, 3);
		for (int i = 0; i < cnt; ++i) {
			int tmp_idx = random(0, nxt_idx); 
			swap(tree[tmp_idx], tree[nxt_idx]);
			cout << now << ' ' << tree[nxt_idx] << endl;
			Que.push(tree[nxt_idx]);
			nxt_idx--;
			if (nxt_idx == -1) break;
		}
		if (nxt_idx == -1) break;
	}
	for(int i = 1; i < n; ++i) printf("%d ", random(1, n-1));
}

int main()
{
	freopen(".in", "w", stdout);
	// creatData(1000, "creatTree1000.txt");
	// creatData(10000, "creatTree10000.txt");
	// creatData(100000, "creatTree100000.txt");
	// creatData(1000000, "creatTree1000000.txt");
	creatData(500000);
}
