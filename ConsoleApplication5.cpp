#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>

#include <string>
#include <vector>
#include <map>
#include <set>

#include <queue>
#include <deque>
#include <cmath>

#include <algorithm>

using namespace std;
using ll = long long;
using db = double;
using ldb = long double;
using pll = pair <long long, long long>;
using pii = pair <int, int>;
#define rep(x) for(int rep_iter = 0; rep_iter < x; ++rep_iter)
#define all(x) (x).begin(), (x).end()
#define mp(x, y) make_pair(x, y)
#define print(x) for (auto element_of_smthng : x) cout << element_of_smthng << ' ';
//#define int ll
const ll INF = 2e18;


struct seg_tree {
	ll n;
	vector <ll> vec;
	vector <ll> t;
	vector <ll> modify;

	void gen(ll v, ll vl, ll vr) {
		if (vr - vl == 1) {
			t[v] = 0;
			return;
		}
		ll vm = (vl + vr) / 2;
		gen(2 * v, vl, vm);
		gen(2 * v + 1, vm, vr);
		t[v] = t[2 * v] + t[2 * v + 1];
	}

	seg_tree(vector<ll> a) {
		n = a.size();
		t.resize(4 * n);
		modify.resize(4 * n, 0);
		vec.assign(all(a));
		gen(1, 0, n);
	}


	void push(ll v, ll vl, ll vr) {
		t[v] += (vr - vl) * modify[v];

		if (vr - vl > 1) {
			modify[2 * v] += modify[v];
			modify[2 * v + 1] += modify[v];
		}
		modify[v] = 0;
	}


	ll get(ll v, ll vl, ll vr, ll ql, ll qr) {
		push(v, vl, vr);
		if (ql == vl && qr == vr)
			return t[v];
		ll vm = (vl + vr) / 2;
		if (qr <= vm)
			return get(2 * v, vl, vm, ql, qr);
		else if (ql >= vm)
			return get(2 * v + 1, vm, vr, ql, qr);
		return get(2 * v, vl, vm, ql, vm) + get(2 * v + 1, vm, vr, vm, qr);
	}


	void update(ll v, ll vl, ll vr, ll ql, ll qr, ll x) {
		push(v, vl, vr);
		if (ql == vl && qr == vr) {
			modify[v] += x;
			push(v, vl, vr);
			return;
		}
		ll vm = (vl + vr) / 2;
		if (qr <= vm)
			update(2 * v, vl, vm, ql, qr, x);
		else if (ql >= vm)
			update(2 * v + 1, vm, vr, ql, qr, x);
		else {
			update(2 * v, vl, vm, ql, vm, x);
			update(2 * v + 1, vm, vr, vm, qr, x);
		}
		t[v] = t[2 * v] + t[2 * v + 1];
	}
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed;
	cout.precision(8);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
}