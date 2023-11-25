#define X first
#define Y second
#include <bits/stdc++.h>
using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/118669
// dijkstra
// �� A���� B���� ���� �ִ� ����� ���ǰ� ���İ��� ���� ����� ���� �ƴ϶�, ���İ��� ���� �� �ִ����� �ٲ�
// �ִ� ����� ���ǰ� �ٲ� ���Ŀ��� ������ ���� ����� ������ ã���� �Ÿ��� Ȯ���� �� ����

int d[50005]; // d[i] : i�� ���������� intensity
vector<pair<int, int>> adj[50005]; //����(���, ��ȣ)
const int MX = 0x7f7f7f7f;
bool issummit[50005]; // issummit[i] : i�� ������ summit���� ����

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
        pq.push({ d[g],g }); // �켱���� ť�� (0,���Ա�) �߰�
    }

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop(); // cur.X : ��������� ���, cur.Y : ���� ���� ������ �ε���
        if (d[cur.Y] != cur.X) continue;
        for (auto nxt : adj[cur.Y]) { // nxt.X : ������ ���, nxt.Y : ������ �����ϴ� �ε���
            if (d[nxt.Y] <= max(d[cur.Y], nxt.X)) continue;
            d[nxt.Y] = max(d[cur.Y], nxt.X); // ����
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