#include <bits/stdc++.h>
using namespace std;

// 플로이드
int d[205][205];
int INF = 1e8 + 10;
int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    for (int i = 1; i <= n; i++) fill(d[i], d[i] + 1 + n, INF);
    for (auto v : fares) {
        d[v[0]][v[1]] = v[2];
        d[v[1]][v[0]] = v[2];
    }
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    int answer = INF;
    for (int mid = 1; mid <= n; mid++)
        answer = min(answer, d[s][mid] + d[mid][a] + d[mid][b]);
    return answer;
}


////////////////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;

// 다익스트라
using pii = pair<int, int>;
int d[3][205];
int INF = 1e8 + 10;
vector<pii> adj[205];

void dijkstra(int st, int idx) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    fill(d[idx], d[idx] + 201, INF);
    d[idx][st] = 0;
    pq.push({ d[idx][st], st });
    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int dist = cur.first, i = cur.second;
        if (d[idx][i] != dist) continue;
        for (auto nxt : adj[i]) {
            int cost = nxt.first, ni = nxt.second;
            if (d[idx][ni] > dist + cost) {
                d[idx][ni] = dist + cost;
                pq.push({ d[idx][ni], ni });
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    for (auto v : fares) {
        adj[v[0]].push_back({ v[2], v[1] });
        adj[v[1]].push_back({ v[2], v[0] });
    }
    dijkstra(s, 0);
    dijkstra(a, 1);
    dijkstra(b, 2);
    int answer = INF;
    for (int mid = 1; mid <= n; mid++)
        answer = min(answer, d[0][mid] + d[1][mid] + d[2][mid]);
    return answer;
}
