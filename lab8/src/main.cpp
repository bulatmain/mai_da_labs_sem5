#include <iostream>
#include <vector>
#include <algorithm>

class Solver {

public:
    Solver() {
        readInput();
    }

    void solve() {
        for (int i = 0; i < n; ++i) {
            int index = findRow(matrix, i);
            if (index == -1) {
                std::cout << "-1" << std::endl;
                return;
            }

            std::swap(matrix[i], matrix[index]);
            res.push_back(matrix[i][n + 1]);
            substractRows(matrix, i);
        }

        std::sort(res.begin(), res.end());
        for (int i = 0; i < res.size(); ++i) {
            std::cout << res[i] + 1;
            if (i == res.size() - 1) {
                std::cout << std::endl;
            } else {
                std::cout << " ";
            }
        }

    }

private:
    const int MAX_NUM = 50;
    int m, n;

    std::vector<int> res;
    std::vector<std::vector<double>> matrix;
                            

    void readInput() {    
        std::cin >> m >> n;

        matrix.assign(m, std::vector<double> (n + 2));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n + 1; ++j) {
                std::cin >> matrix[i][j];
            }
            matrix[i][n + 1] = i;
        }
    }

    int findRow(std::vector<std::vector<double>>& v, int t) {
        int minPrice = MAX_NUM + 1;
        int index = -1;
        for (int i = t; i < m; ++i) {
            if ((v[i][t] != 0.0) && (v[i][n] < minPrice)) {
                index = i;
                minPrice = v[i][n];
            }
        }
        return index;
    }

    void substractRows(std::vector<std::vector<double>>& v, int t) {
        for (int i = t + 1; i < m; ++i) {
            double coeff = v[i][t] / v[t][t];
            for (int j = t; j < n; ++j) {
                v[i][j] -= v[t][j] * coeff;
            }
        }
    }

};



int main() {
    Solver solver;

    solver.solve();

    return 0;
}