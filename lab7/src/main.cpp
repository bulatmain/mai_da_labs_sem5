#include <iostream>
#include <cinttypes>
#include <vector>
#include <string>

namespace lab {
    using u64 = uint64_t;
    template <class T>
    using vec = std::vector<T>;

    u64 countPalindromeSubsequences(std::string const& s) {
        u64 n = s.size();
        vec<vec<u64>> dp(n, vec<u64>(n, 0));
        
        for (u64 i = 0; i < n; i++) {
            dp[i][i] = 1;
        }

        for (u64 len = 2; len <= n; len++) {
            for (u64 i = 0; i <= n - len; i++) {
                u64 j = i + len - 1;

                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j] + dp[i][j - 1] + 1;
                } else {
                    dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
                }
            }
        }

        return dp[0][n - 1];
    }
}


int main() {
    std::string s;
    std::cin >> s;

    auto result = lab::countPalindromeSubsequences(s);
    std::cout << result << std::endl;

    return 0;
}
