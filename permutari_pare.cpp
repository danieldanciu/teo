#include <iostream>
#include <vector>

int n, half_n;
std::vector<int> x(20), ap(20);

void print_solution() {
    for (int i = 0; i < half_n - 1; ++i) {
        std::cout << 2 * x[i] + 1 << " " << 2 * i + 2 << " ";
    }
    std::cout << 2 * x[half_n - 1] + 1; // scriem ultimul numar impar din permutare
    if (n % 2 == 0) { // daca este numar par, mai adaugam un n la final
        std::cout << n;
    }
    std::cout << std::endl;
}

void back(int k) {
    if (k == half_n) {
        print_solution();
        return;
    }
    // incercam pe rand toate valorile pentru pozitia k din permutare
    for (int i = 0; i < half_n; ++i) {
        if (ap[i] == 0) { // verificam daca valoarea i apare deja in permutare
            x[k] = i;
            ap[x[k]] = 1;
            back(k + 1);
            ap[x[k]] = 0; // cand ne intoarcem din recursivitate, trebuie sa resetam ap
        }
    }
}

int main() {
    std::cin >> n;
    half_n = (n + 1) / 2; // pana aici generam permutari
    back(0);
}
