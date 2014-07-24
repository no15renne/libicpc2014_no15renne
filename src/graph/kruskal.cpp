/* union find */
int par[MAX_UNI_N]; // root
int rank[MAX_UNI_N]; // depth of tree

// 要素数nで初期化
void init_union_find(int n) {
    for (int i=0;i<n; i++) {
        par[i] = i;
        rank[i] = 0;
    }
}

// 木の根を求める
int find(int x) {
    if (par[x] == x) {
        return x;
    } else {
        return par[x] = find(par[x]);
    }
}

// xとyの属する集合を併合
void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if(x==y) return;

    if(rank[x] < rank[y]) {
        par[x] = y;
    } else {
        par[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
}

// xとyが同じ集合に属するか否か
bool same(int x, int y) {
    return find(x) == find(y);
}


/* kruskal */
struct edge { int u, v, cost; };

bool comp(const edge& e1, const edge& e2) {
    return e1.cost < e2.cost;
}

edge es[MAX_E];
int V, E; // 頂点数と辺数

int kruskal() {
    sort(es, es + E, comp); // edge.cost が小さい順にソートする
    init_union_find(V); // Union-Findの初期化
    int res = 0;
    for (int i=0;i<E;i++) {
        edge e = es[i];
        if (!same(e.u, e.v)) {
            unite(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}
