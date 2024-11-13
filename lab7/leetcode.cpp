#include <limits>
#include <vector>

using namespace std;

class Solution {
public:

    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        Inner solver(toppingCosts, baseCosts, target);
        return solver.solve();
    }

private:
    class Inner {
    private:
        int maxToppingCount = 2;
        vector<int>& toppingCosts;
        vector<int>& baseCosts;
        int target;
        int closest = std::numeric_limits<int>::max();

    public:
        Inner(vector<int>& toppingCosts, vector<int>& baseCosts, int target)
            : toppingCosts(toppingCosts), baseCosts(baseCosts), target(target) {}

        int solve() {
            for (auto base : baseCosts) {
                findForBase(base, 0);
            }
            return closest;
        }

        void findForBase(int cost, int topping) {
            if (cost >= target || topping >= toppingCosts.size()) {
                if (abs(cost - target) < abs(closest - target)) {
                    closest = cost;
                } else if (abs(cost - target) == abs(closest - target)) {
                    closest = min(cost, closest);
                }
            } else {
                for (int j = 0; j <= maxToppingCount; ++j) {
                    findForBase(cost + j*toppingCosts[topping], topping + 1);
                }
            }
        }

        int abs(int x) {
            return x < 0 ? -x : x;
        }

        int min(int a, int b) {
            return a < b ? a : b;
        }
        
    };

};


#include <iostream>

int main() {
    vector<int> baseCosts{1, 7};
    vector<int> toppicCosts{3, 4};
    int target = 10;

    Solution s;
    cout << s.closestCost(baseCosts, toppicCosts, target);


    return 0;
}