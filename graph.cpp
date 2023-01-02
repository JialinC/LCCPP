#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int MAX_V = 1000;
const int MAX_M = 1000;
const int MAX_N = 1000;
const int MAX_E = 1000;
const int MAX_R = 1000;
typedef pair<int, int> P;
double INF = numeric_limits<double>::infinity();
// graph representation

vector<int> G[MAX_V];
// property on edge
// struct edge {int to, cost;};
// vector<edge> G[MAX_V];

int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    for (int i = 0; i < E; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        G[s].push_back(t);
    }
    return 0;
}

struct vertex {
    vector<vertex*> edge;
};
vertex GG[MAX_V];

int main(){
    int V, E;
    scanf("%d %d", &V, &E);
    for (int i = 0; i < E; i++){
        int s, t;
        scanf("%d %d", &s, &t);
        GG[s].edge.push_back(&GG[t]);
        // G[t].edge.push_back(&G[s]);
    }
}

// 2 devide graph
vector<int> G[MAX_V];
int V;
int color[MAX_V];
bool dfs (int v, int c){
    color[v] = c;
    for (int i = 0; i < G[v].size(); i++){
        if(color[G[v][i]] == c) return false;
        if(color[G[v][i]] == 0 && !dfs(G[v][i], -c)) return false;
    }
    return true;
}

void solve () {
    for (int i = 0; i < V; i++){
        if (color[i] == 0) {
            if (!dfs(i, 1)){
                printf("No\n");
                return;
            }
        }
    }
    printf("Yes\n");
}

// single source shortest path
// Bellman-Ford O(|V|x|E|)
struct edge {int from, to, cost;};

edge es[MAX_E];
int d[MAX_V];
int V, E;

void shortest_path(int s){
    for (int i = 0; i < V; i++) d[i] = INF;
    d[s] = 0;
    while (true) {
        bool update = false;
        for (int i = 0; i < E; i++) {
            edge e = es[i];
            if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if (!update) break;
    }
}

//check negative cycle
bool find_negative_loop(){
    memset (d, 0, sizeof(d));

    for(int i = 0; i < V; i++){
        for(int j = 0; j < E; j++){
            edge e = es[j];
            if (d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                if (i == V - 1) return true;
            }
        }
    }
    return false;
}

// Dijkstra
int cost[MAX_V][MAX_V];
int d[MAX_V];
bool used[MAX_V];
int V;

void dijkstra(int s){
    fill(d, d + V, INF);
    fill(used, used + V, false);
    d[s] = 0;

    while(true) {
        int v = -1;
        for (int u = 0; u < V; u++){
            if (!used[u] && (v == -1 || d[u] < d[v])) v = u;
        }

        if (v == -1) break;
        used[v] = true;

        for (int u = 0; u < V; u++){
            d[u] = min(d[u], d[v] + cost[v][u]);
        }
    }
}

// Floyd-Warshall O(|V|^3) can handle negative edge, for negative cycle check d[i][i] is negative

int dd[MAX_V][MAX_V]; // d[i][i] = 0
int V;

void warshall_floyd() {
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++) dd[i][j] = min(dd[i][j], dd[i][k] + dd[k][j]);
            // k = 0, i = 0, j = 0
            // d[0][0] =  min(dd[0][0], dd[0][0] + dd[0][0])

            // k = 0, i = 0, j = 1
            // d[0][1] =  min(dd[0][1], dd[0][0] + dd[0][1])

            // k = 0, i = 1, j = 0
            // d[1][0] =  min(dd[1][0], dd[1][0] + dd[0][0])

            // k = 0, i = 1, j = 1
            // d[1][1] =  min(dd[1][1], dd[1][0] + dd[0][1])

            // k = 1, i = 0, j = 0
            // d[0][0] =  min(dd[0][0], dd[0][1] + dd[1][0])

            // k = 1, i = 0, j = 1
            // d[0][1] =  min(dd[0][1], dd[0][1] + dd[1][1])

            // k = 1, i = 1, j = 0
            // d[1][0] =  min(dd[1][0], dd[1][1] + dd[1][0])

            // k = 1, i = 1, j = 1
            // d[1][1] =  min(dd[1][1], dd[1][1] + dd[1][1])
}

// path recovery O(|V|)
int pre[MAX_V];

void dijkstra(int s){
    fill(d, d + V, INF);
    fill(used, used + V, false);
    fill(pre, pre + V, -1);
    d[s] = 0; // starting point

    while(true) {
        int v = -1;
        for (int u = 0; u < V; u++){
            if (!used[u] && (v == -1 || d[u] < d[v])) v = u;
        }

        if (v == -1) break;
        used[v] = true;

        for (int u = 0; u < V; v++){
            if (d[u] > d[v] + cost[v][u]){
                d[u] = d[v] + cost[v][u];
                pre[u] = v;
            }
        }
    }
}

vector<int> get_path(int t) {
    vector<int> path;
    for (; t != -1; t = pre[t]) path.push_back(t);
    reverse(path.begin(), path.end());
    return path;
}

// minimum spanning tree
// Prim O(|V|^2) or O(|E|log|V|)
int cost[MAX_V][MAX_V];
int mincost[MAX_V]; // from already discovered
bool used[MAX_V];
int V;

int prim() {
    // initialization
    for (int i = 0; i < V; ++i){
        mincost[i] = INF;
        used[i] = false;
    }
    mincost[0] = 0;
    int res = 0;

    while(true) {
        int v = -1;

        for (int u = 0; u < V; u++) {
            if (!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
        }

        if(v == -1) break;
        used[v] = true;
        res += mincost[v];

        for (int u = 0; u < V; u++){
            mincost[u] = min(mincost[u], cost[v][u]);
        }
    }
    return res;
}


// Kruskal use union-find
struct edge { int u, v, cost;};

bool comp(const edge& e1, const edge& e2){
    return e1.cost < e2.cost;
}

edge es[MAX_E];
int V, E;

int kruskal() {
    sort(es, es + E, comp);
    init_union_find(V);
    int res = 0;
    for (int i = 0; i < E; i++){
        edge e = es[i];
        if (!same(e.u, e.v)) {
            unite(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}

// second shortest path
int N, R;
vector<edge> G[MAX_N];

int dist[MAX_N];
int dist2[MAX_N];

void solve() {
    priority_queue<P, vector<P>, greater<P>> que;
    fill(dist, dist + N, INF);
    fill(dist2, dist2 + N, INF);
    dist[0] = 0;
    que.push(P(0, 0));

    while (!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.second, d = p.first;
        if (dist2[v] < d) continue;
        for (int i = 0; i < G[v].size(); i++){
            edge &e = G[v][i];
            int d2 = d + e.cost;
            if (dist[e.to] > d2){
                swap(dist[e.to], d2);
                que.push(P(dist[e.to], e.to));
            }
            if (dist2[e.to] > d2 && dist[e.to] < d2){
                dist2[e.to] = d2;
                que.push(P(dist2[e.to], e.to));
            }
        }
    }
    printf("%d\n", dist2[N - 1]);
}

int N, M, R;
int x[MAX_R], y[MAX_R], d[MAX_R];

void solve(){
    V = N + M;
    E = R;
    for (int i = 0; i < R; i++){
        es[i] = (edge){x[i], N + y[i], -d[i]};
    }
    printf("%d\n", 10000 * (N + M) + kruskal());
}



