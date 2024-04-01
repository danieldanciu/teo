#include <cassert>
#include <fstream>

std::ifstream fin("artifact.in");
std::ofstream fout("artifact.out");

struct digit {
  bool first = false;
  bool occ = false;
  int64_t coef = 0;
} ap[27];

uint32_t n, m, nr;
char unique[27];
uint64_t ans = 0, p[16];
int64_t sum = 0;
bool f[10];

void update_coefficient(std::string s, uint32_t pos, uint32_t size, bool sub) {
  auto c = p[size - pos - 1];
  if (!sub)
    ap[s[pos] - 'A'].coef += c;
  else
    ap[s[pos] - 'A'].coef -= c;
}

void read() {
  fin >> n >> m;
  for (int i = 0; i < n + m; ++i) {
    std::string s;
    fin >> s;
    if (s.length() > 1) {
      ap[s[0] - 'A'].first = true;
    }
    int size = s.size();
    for (int j = 0; j < size; ++j) {
      if (!ap[s[j] - 'A'].occ) {
        ap[s[j] - 'A'].occ = true;
        unique[nr++] = s[j];
      }
      update_coefficient(s, j, size, i>=n);
    }
  }
}

void back(uint32_t k) {
  if (k == nr) {
    if (sum == 0)
      ++ans;
    return;
  }
  for (uint32_t i = (ap[unique[k]-'A'].first ? 1 : 0); i < 10; ++i)
    if (!f[i]) {
      f[i] = true;
      sum += i * ap[unique[k] - 'A'].coef;
      back(k + 1);
      sum -= i * ap[unique[k] - 'A'].coef;
      f[i] = false;
    }
}

int main() {
  p[0] = 1;
  for (int i = 1; i < 16; ++i) {
    p[i] = p[i - 1] * 10;
  }
  read();
  back(0);
  fout << ans;
  return 0;
}
