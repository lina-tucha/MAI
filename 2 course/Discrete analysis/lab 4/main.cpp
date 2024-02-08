#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>
#include <map>

std::vector<size_t> ZFunction(std::vector<std::uint32_t>& pattern) {
    size_t n = pattern.size(), l = 0, r = 0;
    std::vector<size_t> z(n);
    for (size_t i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && pattern[z[i]] == pattern[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
             r = i + z[i] - 1;
        }
    }
    return z;
}

std::vector<size_t> NFunction(std::vector<std::uint32_t>& pattern) {
    std::reverse(pattern.begin(), pattern.end());
    std::vector<size_t> z = ZFunction(pattern);
    std::vector<size_t> n(z.size());
    for (size_t i = 0; i < pattern.size(); ++i) {
        n[i] = z[pattern.size() - i - 1];
    }
    std::reverse(pattern.begin(), pattern.end());
    return n;
}

std::pair<std::vector<size_t>, std::vector<size_t>> LFunction(std::vector<std::uint32_t>& pattern) {
    std::vector<size_t> n = NFunction(pattern);
    std::vector<size_t> l(n.size());
    std::vector<size_t> L(pattern.size() + 1);
    size_t j = 0;
    for (size_t i = 0; i < pattern.size() - 1; ++i) {
        if (n[i] != 0) {
            j = pattern.size() - n[i];
            l[j] = i;
        }
        if (n[i] == i + 1) {
            L[pattern.size() - i - 1] = i + 1;
        } else {
            L[pattern.size() - i - 1] = L[pattern.size() - i];
        }
    }
    return std::pair<std::vector<size_t>, std::vector<size_t>>(l, L);
}


void BM(std::vector<std::pair<std::pair<size_t, size_t>, std::uint32_t>> const& text,
    std::vector<std::uint32_t>& pattern) {
    int n = pattern.size() - 1;
    std::vector<int> result;
    std::pair<std::vector<size_t>, std::vector<size_t>> l = LFunction(pattern);
    while (n < text.size()) {
        int i = pattern.size() - 1, j = n;
        while ((i >= 0) && (pattern[i] == text[j].second)) {
            --i;
            --j;
        }
        if (i == -1) {
            result.push_back(n - pattern.size() + 1);
            if (pattern.size() > 2) {
                n += pattern.size() - l.second[1];
            } else {
                ++n;
            }
        } else {
            int suffix = 1, k = 1;
            if (i == pattern.size() - 1) {
                suffix = 1;
            } else {
                if (l.first[i + 1] > 0) {
                    suffix = pattern.size() - l.first[i + 1] - 1;
                } else {
                    suffix = pattern.size() - l.second[i + 1];
                }
            }
            n += std::max(suffix, k);
        }
    }
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << text[result[i]].first.first << "," << text[result[i]].first.second << "\n";
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    std::vector<std::uint32_t> pattern;
    std::vector<std::pair<std::pair<size_t, size_t>, std::uint32_t>> text;
    char s;
    int row = 1, num = 1, space = 0;
    std::string p, t;
    while (true) {
        s = getchar();
        if (s == ' ') {
            if (!p.empty()) {
                pattern.push_back(static_cast<std::uint32_t>(std::stoi(p)));
            }
            p.clear();
        } else if (s == '\n' || s == EOF) {
            if (!p.empty()) {
                pattern.push_back(static_cast<std::uint32_t>(std::stoi(p)));
            }
            break;
        }
        else {
            p.push_back(s);
        }
    }
    while ((s = getchar()) != EOF) {
        if (s == ' ') {
            if (!t.empty()) {
                text.push_back({{row, num}, static_cast<std::uint32_t>(std::stoi(t))});
            }
            if (!space) {
                space = 1;
                ++num;
            }
            t.clear();
        } else if (s == '\n') {
            if (!t.empty()) {
                text.push_back({{row, num}, static_cast<std::uint32_t>(std::stoi(t))});
            }
            t.clear();
            space = 0;
            num = 1;
            ++row;
        } else {
            space = 0;
            t.push_back(s);
        }
    }
    BM(text, pattern);
    return 0;
}