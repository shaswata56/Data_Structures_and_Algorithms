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
    fast_io();
    //freopen64("input.txt", "r", stdin);
    time__("Runtime") {
        solve();
    }
    return 0;
}

#define MAX 100000000
ll lazy[MAX] = {0};

void build_tree(ll arr[], ll tree[], ll node, ll a, ll b)
{
    if(a > b) return;
    if(a == b) {
        tree[node] = arr[a];
        return;
    }
    build_tree(arr, tree, node*2, a, (a+b)/2);
    build_tree(arr, tree, node*2+1, 1+(a+b)/2, b);
    tree[node] = tree[node*2] + tree[node*2+1];
}


void update_tree(ll tree[], ll node, ll a, ll b, ll i, ll j, ll value)
{
    i--; j--;
    if(lazy[node] != 0) {
        tree[node] += lazy[node];
        if(a != b) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(a > b || a > j || b < i)
        return;
    if(a >= i && b <= j) {
        tree[node] += value;
        if(a != b) {
            lazy[node*2] += value;
            lazy[node*2+1] += value;
        }
        return;
    }
    update_tree(tree, node*2, a, (a+b)/2, i, j, value);
    update_tree(tree, 1+node*2, 1+(a+b)/2, b, i, j, value);
    tree[node] = tree[node*2] + tree[node*2+1];
}

ll query_tree(ll tree[], ll node, ll a, ll b, ll i, ll j)
{
    i--; j--;
    if(a > b || a > j || b < i) return 0;
    if(lazy[node] != 0) {
        tree[node] += lazy[node];
        if(a != b) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(a >= i && b <= j)
        return tree[node];
    ll sum = query_tree(tree, node*2, a, (a+b)/2, i, j) + query_tree(tree, 1+node*2, 1+(a+b)/2, b, i, j);
    return sum;
}

void solve() {
    ll t, i;
    scanf("%lld", &t);
    ll arr[t];
    ll tree[t * 4];
    tree[t * 4] = {0};
    forl(i, 0, t)
        scanf("%lld", &arr[i]);
    build_tree(arr, tree, 1, 0, t-1);
    update_tree(tree, 1, 0, t-1, l, l, r);
    query_tree(tree, 1, 0, t-1, l, r);
}
