#include<bits/stdc++.h>
using namespace std;

#define MAX 100000000
long long lazy[MAX] = {0};

void build_tree(long long arr[], long long tree[], long long node, long long a, long long b)
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


void update_tree(long long tree[], long long node, long long a, long long b, long long i, long long j, long long value)
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

long long query_tree(long long tree[], long long node, long long a, long long b, long long i, long long j)
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
    long long sum = query_tree(tree, node*2, a, (a+b)/2, i, j) + query_tree(tree, 1+node*2, 1+(a+b)/2, b, i, j);
    return sum;
}

int main() {
    long long t;
    scanf("%lld", &t);
    long long arr[t];
    long long tree[t * 4];
    tree[t * 4] = {0};
    for(long long i = 0; i < t; i++)
        scanf("%lld", &arr[i]);
    build_tree(arr, tree, 1, 0, t-1);
    update_tree(tree, 1, 0, t-1, l, l, r);
    query_tree(tree, 1, 0, t-1, l, r);
    return 0;
}
