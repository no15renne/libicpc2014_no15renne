#define MAX_E 1000
#define MAX_V 1000
struct edge {int from, to, cost; };
edge es[MAX_E];
int d[MAX_V];
void bellman_ford(int s) {
    for (int i = 0; i < MAX_V; i++) d[i] = INF;
    d[s] = 0;
    while (true) {
        bool update = false;
        for (int i = 0; i < MAX_E; i++) {
            edge e = es[i];
            if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if (!update) break;
    }
}

