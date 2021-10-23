#include <iostream>
#include <vector>

const long long int INF = 10000000001;

struct edge {
    int a;
    int b;
    long long int cost;
};

int main() {
    std::ios::sync_with_stdio(false);
    int n = 0, m = 0, start, finish;
    std::cin >> n >> m >> start >> finish;
    
    std::vector<long long int> d(n, INF);
    std::vector<edge> ed(m);
    d[start - 1] = 0;
    int a, b;
    
    for(int i = 0; i < m; ++i) {
        std::cin >> a >> b >> ed[i].cost;
        ed[i].a = a - 1;
        ed[i].b = b - 1;
    }

    for(int j = 0; j < n - 1; ++j) {
        bool flag = false;
        for(int i = 0; i < m; ++i) {
            if(d[ed[i].a] < INF) {
                if(d[ed[i].b] > d[ed[i].a] + ed[i].cost) {
                    d[ed[i].b] = d[ed[i].a] + ed[i].cost;
                    flag = true;
                }
            }
        }
        if(!flag) break;
    }

    if(d[finish - 1] == INF) {
        std::cout << "No solution\n";
    } else {
        std::cout << d[finish - 1] << '\n';
    }
    return 0;
}