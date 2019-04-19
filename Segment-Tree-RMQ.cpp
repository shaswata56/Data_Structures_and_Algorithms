/*
                              _                             _        _____   __
                             | |                           | |      | ____| / /
                          ___| |__   __ _ _____      ____ _| |_ __ _| |__  / /_
                         / __| '_ \ / _` / __\ \ /\ / / _` | __/ _` |___ \| '_ \
                         \__ \ | | | (_| \__ \\ V  V / (_| | || (_| |___) | (_) |
                         |___/_| |_|\__,_|___/ \_/\_/ \__,_|\__\__,_|____/ \___/

*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define forl(i,k,n)  for(i = k; i < n; ++i)
#define forg(i,k,n)  for(i = k; i >= n; --i)
#define forle(i,k,n)  for(i = k; i <= n; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) for( auto blockTime = make_pair(chrono::high_resolution_clock::now(), true); blockTime.second; debug("%s: %ld ms\n", d, chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - blockTime.first).count()), blockTime.second = false)
#define endl "\n"
typedef unsigned long long ull;
typedef long double ld;
const int INF = (int) 1e9;
inline ll countSetBit(ll i) { i = i - ((i >> 1) & 0x55555555); i = (i & 0x33333333) + ((i >> 2) & 0x33333333); i = (i + (i >> 4)) & 0x0f0f0f0f; i = i + (i >> 8); i = i + (i >> 16); return i & 0x3f; }
inline void set_bit(ll &n, ll b) { n |= 1 << b; }
inline void unset_bit(ll &n, ll b) { n &= ~(1 << b); }
inline void toggle_bit(ll &n, ll b) { n ^= 1 << b; }
inline void swap(ll &arr, ll &b) { arr ^= b; b ^= arr; arr ^= b; }
inline int digitContain(ll arr) { return (ll) (floor(log10(arr)) + 1); }
inline bool isPoweroftwo(ll x) { return x && (!(x&(x-1))); }
inline ll ipow(ll base, ull exp) { ll result = 1; while (exp) { if (exp & 1) result *= base; exp >>= 1; if (!exp) break; base *= base; } return result; }
inline ll msd(ll n) { return ipow(10, (long double) (log10(n) - floor(log10(n)))); }
inline void fast_io() { std::ios_base::sync_with_stdio(false); cin.tie(nullptr); }
void solve();

int main()
{
    //fast_io();
    //freopen64("input.txt", "r", stdin);
    time__("Runtime") {
        solve();
    }
    return 0;
}

int getMid(int s, int e) 
{ 
	return s + (e - s) / 2;
} 

int getRangeMax(int* st, int ss, int se, int qs, int qe, int index) 
{ 
	if (qs <= ss && qe >= se) 
		return st[index]; 
	if (se < qs || ss > qe) 
		return 0; 
	int mid = getMid(ss, se); 
	return max(getRangeMax(st, ss, mid, qs, qe, 2 * index + 1), getRangeMax(st, mid + 1, se, qs, qe, 2 * index + 2)); 
} 

int rangeMax(int* st, int n, int qs, int qe) 
{ 
	if (qs < 0 || qe > n - 1 || qs > qe) {
		return -1; 
	} 

	return getRangeMax(st, 0, n - 1, qs, qe, 0); 
} 

int constructSTree(int arr[], int ss, int se, int* st, int si) 
{ 
	if (ss == se) { 
		st[si] = arr[ss]; 
		return arr[ss]; 
	} 
	int mid = getMid(ss, se); 
	st[si] = max(constructSTree(arr, ss, mid, st, si * 2 + 1), constructSTree(arr, mid + 1, se, st, si * 2 + 2)); 
	return st[si]; 
} 

int* build_Stree(int arr[], int n) 
{ 
	int x = (int)(ceil(log2(n))); 
	int max_size = 2 * (int)pow(2, x) - 1; 
	int* st = new int[max_size]; 
	constructSTree(arr, 0, n - 1, st, 0); 
	return st; 
} 

int maxOccur(int st[], int arr[], int n, int qs, int qe) 
{ 
	int maxOcc;
	if (arr[qs] == arr[qe]) 
		maxOcc = (qe - qs + 1); 
	else { 
		int leftmost_same = 0, righmost_same = 0; 
		while (qs > 0 && qs <= qe && arr[qs] == arr[qs - 1]) { 
			qs++; 
			leftmost_same++; 
		} 
		while (qe >= qs && qe < n - 1 && arr[qe] == arr[qe + 1]) { 
			qe--; 
			righmost_same++; 
		} 
		maxOcc = max({leftmost_same, righmost_same, rangeMax(st, n, qs, qe)}); 
	} 
	return maxOcc; 
} 

void solve()
{
	int N, Q, i, j;
	scanf("%d", &N);
	if(N == 0) return;
	int arr[N];
	scanf("%d", &Q);
	forl(i, 0, N)
		scanf("%d", &arr[i]);
	int freq_arr[N + 1]; 
	unordered_map<int, int> cnt; 
	forl(i, 0, N) 
		cnt[arr[i]]++; 
	forl(i, 0, N) 
		freq_arr[i] = cnt[arr[i]]; 
	int* STree = build_Stree(freq_arr, N); 
	while(Q--){
		scanf("%d %d", &i, &j);
		printf("%d\n", maxOccur(STree, arr, N, --i, --j));
	}
	solve();
}
