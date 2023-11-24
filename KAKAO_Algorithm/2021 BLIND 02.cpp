#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/72411
// 나만 이 문제 이해가 어려웠나? 싶었는데, 문제 설명이 복잡해서 다들 이해하기까지 오래 걸렸다고 한다.
// 코스 메뉴 조합을 추출하자!
// 단품 메뉴가 N개일 때 (2^N-1) 개의 메뉴 조합이 존재, 2진법을 이용해 목록을 얻을 수 있다.
// C,D,E -> C,D,E,CD,CE,DC,CDE

map<string, int> freq[11];
vector<string> solution(vector<string> orders, vector<int> course) {
    // 1) 코스 메뉴 조합 추출
    for (auto order : orders) {
        sort(order.begin(), order.end()); // O(nlogn)
        for (int i = 1; i < (1 << order.size()); i++) { // 2진법
            string menu;
            int tmp = i;
            for (int j = 0; j < order.size(); j++) {
                if (tmp % 2) menu += order[j];
                tmp /= 2;
            }
            freq[menu.size()][menu]++;
        }
    }
    // 2) 코스요리 메뉴 계산
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