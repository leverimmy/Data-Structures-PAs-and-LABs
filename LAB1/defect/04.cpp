#include <iostream>
#include <string>

using namespace std;
string a;

void play(int rank) {
    int left = rank;
    int right = rank;
    char color = a.at(rank);

    while (left > 0 && a.at(left) == color) --left;
    while (right < a.size() && a.at(right) == color) ++right;

    int size = right - left;
    if (size >= 3) {
        a.erase(left, size);

        if (left >= 0 && left < a.size()) {
            play(left);
        }
    }
}

int main() {
    freopen("04.in", "r", stdin);
    freopen("04.out", "w", stdout);
    getline(cin, a);
    int m = 0;
    cin >> m;

    int rank; char color;
    for(int i = 0; i < m; ++i) {
        cin >> rank >> color;
        a.insert(a.cbegin() + min(rank, (int)a.size()), color);
        play(rank);
    }
    
    cout << a << endl;

    return 0;
}