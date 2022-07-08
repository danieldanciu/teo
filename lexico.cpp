#include <algorithm>
#include <iostream>
#include <vector>
// std::ifstream fin("gama.in");
// std::ofstream fout("gama.out");
int find(const std::vector<int> &a, int start, int &k) {
    int min_idx = start;
    int idx = start + 1;
    for (; idx < std::min(int(a.size()), start + k + 1); ++idx) {
        if (a[idx] < a[min_idx]) {
            min_idx = idx;
        }
    }
    k -= (min_idx - start);
    return min_idx;
}

void move(std::vector<int> &a, int start, int end) {
    int aux = a[end];
    for (int i = end; i > start; i--) {
        a[i] = a[i - 1];
    }
    a[start] = aux;
}

int main() {
    int n, k;
    std::vector<int> a;
    std::cin >> n >> k;
    for (int index = 0; index < n; ++index) {
        int x;
        std::cin >> x;
        a.push_back(x);
    }
    for (int i = 0; i < n && k > 0; ++i) {
        int to_swap = find(a, i, k);
        move(a, i, to_swap);
    }
    for (int index = 0; index < n; ++index) {
        std::cout << a[index] << " ";
    }
    // fin.close();
    // fout.close();
    return 0;
}
