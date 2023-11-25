#define X first
#define Y second
#include <bits/stdc++.h>
using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/118669
// dijkstra
// 단 A에서 B까지 가는 최단 경로의 정의가 거쳐가는 간선 비용의 합이 아니라, 거쳐가는 간선 중 최댓값으로 바뀜
// 최단 경로의 정의가 바뀐 이후에도 여전히 가장 가까운 정점을 찾으면 거리를 확정할 수 있음

int d[50005]; // d[i] : i번 지점까지의 intensity
vector<pair<int, int>> adj[50005]; //간선(비용, 번호)
const int MX = 0x7f7f7f7f;
bool issummit[50005]; // issummit[i] : i번 지점이 summit인지 여부

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    for (auto summit : summits)
        issummit[summit] = true;
    for (auto path : paths) {
        int u = path[0];
        int v = path[1];
        int w = path[2];
        adj[u].push_back({ w,v });
        adj[v].push_back({ w,u });
    }
    fill(d, d + n + 1, MX);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (auto g : gates) {
        d[g] = 0;
        pq.push({ d[g],g }); // 우선순위 큐에 (0,출입구) 추가
    }

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop(); // cur.X : 현재까지의 비용, cur.Y : 현재 보는 정점의 인덱스
        if (d[cur.Y] != cur.X) continue;
        for (auto nxt : adj[cur.Y]) { // nxt.X : 간선의 비용, nxt.Y : 간선이 연결하는 인덱스
            if (d[nxt.Y] <= max(d[cur.Y], nxt.X)) continue;
            d[nxt.Y] = max(d[cur.Y], nxt.X); // 갱신
            if (!issummit[nxt.Y])
                pq.push({ d[nxt.Y], nxt.Y });
        }
    }
    int ans = summits[0];
    for (auto summit : summits) {
        if (d[summit] < d[ans]) ans = summit;
        else if (d[summit] == d[ans] && summit < ans) ans = summit;
    }
    return vector<int>({ ans, d[ans] });
}