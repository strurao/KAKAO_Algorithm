//////////////////floyd//////////////////////

#include <bits/stdc++.h>
using namespace std;

int d[205][205]; // 그래프 표현
int INF = 1e8 + 10;

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    for (int i = 1; i <= n; i++) 
        fill(d[i], d[i] + 1 + n, INF); // 최단 거리 테이블을 모두 무한으로 초기화

    // 각 간선에 대한 정보를 입력받아, 그 값으로 초기화
    // fares 배열의 각 행은 [c, d, f] 형태 
    // c지점과 d지점 사이의 예상 택시요금이 f원이라는 뜻
    for (auto v : fares) { 
        d[v[0]][v[1]] = v[2];
        d[v[1]][v[0]] = v[2];
    }

    for (int i = 1; i <= n; i++) d[i][i] = 0; // 자기 자신에서 자기 자신으로 가는 비용은 0으로 초기화

    for (int k = 1; k <= n; k++) // 거쳐가는 노드 k
        for (int i = 1; i <= n; i++) 
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    int answer = INF;

    for (int mid = 1; mid <= n; mid++)
        answer = min(answer, d[s][mid] + d[mid][a] + d[mid][b]);

    return answer;
}


//////////////////dijkstra//////////////////////

#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
vector<pii> adj[205]; // 각 노드에 연결되어 있는 노드에 대한 정보를 담는 배열
int d[3][205]; // 최단 거리 테이블
int INF = 1e8 + 10; 

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
                d[idx][ni] = dist + cost; // 갱신
                pq.push({ d[idx][ni], ni });
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    // fares 배열의 각 행은 [c, d, f] 형태 
    // c지점과 d지점 사이의 예상 택시요금이 f원이라는 뜻
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
