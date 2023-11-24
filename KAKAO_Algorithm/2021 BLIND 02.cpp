#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/72411
// ���� �� ���� ���ذ� �������? �;��µ�, ���� ������ �����ؼ� �ٵ� �����ϱ���� ���� �ɷȴٰ� �Ѵ�.
// �ڽ� �޴� ������ ��������!
// ��ǰ �޴��� N���� �� (2^N-1) ���� �޴� ������ ����, 2������ �̿��� ����� ���� �� �ִ�.
// C,D,E -> C,D,E,CD,CE,DC,CDE

map<string, int> freq[11];
vector<string> solution(vector<string> orders, vector<int> course) {
    // 1) �ڽ� �޴� ���� ����
    for (auto order : orders) {
        sort(order.begin(), order.end()); // O(nlogn)
        for (int i = 1; i < (1 << order.size()); i++) { // 2����
            string menu;
            int tmp = i;
            for (int j = 0; j < order.size(); j++) {
                if (tmp % 2) menu += order[j];
                tmp /= 2;
            }
            freq[menu.size()][menu]++;
        }
    }
    // 2) �ڽ��丮 �޴� ���
    vector<string> answer;
    for (auto i : course) {
        int mxfreq = 0;
        for (auto p : freq[i])
            mxfreq = max(mxfreq, p.second);
        if (mxfreq < 2) continue;
        for (auto p : freq[i]) {
            if (p.second == mxfreq) answer.push_back(p.first);
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}