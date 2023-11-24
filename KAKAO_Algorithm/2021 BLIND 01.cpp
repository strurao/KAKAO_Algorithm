#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// https://school.programmers.co.kr/learn/courses/30/lessons/72410
// 별생각없이 erase()를 쓰면 O(n^2)에 수행한다. 이 문제에선 n이 최대 1000이라서 상관없겠지만!
// 새 배열에 복사하면 O(n)에 수행 가능하다.
// C++ string 의 경우 `=` 연산 시 Deep Copy 로, Shallow Copy 처럼 앞의 문자열에 영향을 끼치지 않는다.

string solution(string new_id) {
    string id1;
    for (auto c : new_id) id1 += tolower(c);

    string step2_filter = "0123456789abcdefghijklmnopqrstuvwxyz-_.";
    string id2;
    for (auto c : id1) {
        if (find(step2_filter.begin(), step2_filter.end(), c) != step2_filter.end())
            id2 += c;
    }

    string id3;
    for (auto c : id2) {
        if (c != '.') id3 += c;
        else {
            if (!id3.empty() && id3.back() == '.') continue;
            id3 += c;
        }
    }

    string id4;
    for (int i = 0; i < id3.size(); i++) {
        if ((i == 0 || i + 1 == id3.size()) && id3[i] == '.') continue;
        id4 += id3[i];
    }

    string id5 = id4;
    if (id5.empty()) id5 = "a";

    string id6 = id5.substr(0, 15);
    if (id6.back() == '.') id6.pop_back();

    string id7 = id6;
    while (id7.size() < 3) id7 += id7.back();

    return id7;
}