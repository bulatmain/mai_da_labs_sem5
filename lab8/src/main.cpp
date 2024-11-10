#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cassert>

namespace lab {
    using u32 = uint32_t;
    using u64 = uint64_t;
    template <class T>
    using vec = std::vector<T>;

    u32 const INF = std::numeric_limits<u32>::max();

    const double EPS = 1E-9;

    double fabs(double const& x) {
        return x < 0 ? -x : x;
    }

    u32 compute_rank(vec<vec<double>> A) {
        u64 n = A.size();
        u64 m = A[0].size();

        u32 rank = 0;
        vec<char> row_selected(n, 0);
        for (u64 i = 0; i < m; ++i) {
            u64 j;
            for (j = 0; j < n; ++j) {
                if (!row_selected[j] && fabs(A[j][i]) > EPS)
                    break;
            }

            if (j != n) {
                ++rank;
                row_selected[j] = 1;
                for (u64 p = i + 1; p < m; ++p) {
                    A[j][p] /= A[j][i];
                }
                for (u64 k = 0; k < n; ++k) {
                    if (k != j && fabs(A[k][i]) > EPS) {
                        for (u64 p = i + 1; p < m; ++p)
                            A[k][p] -= A[j][p] * A[k][i];
                    }
                }
            }
        }
        return rank;
    }
}

using namespace lab;

int main() {
    u32 M, N;
    std::cin >> M >> N;

    if (M < N) {
        std::cout << -1 << std::endl;
        return 0;
    }

    vec<vec<double>> matrix(M, vec<double>(N, 0));
    vec<u32> costs(M);

    for (u32 i = 0; i < M; ++i) {
        for (u32 j = 0; j < N; ++j) {
            std::cin >> matrix[i][j];
        }
        std::cin >> costs[i];
    }

    if (compute_rank(matrix) != N) {
        std::cout << -1 << std::endl;
    } else {
        for (u32 i = 0; i < M; ++i) {
            std::cout << i + 1 << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}