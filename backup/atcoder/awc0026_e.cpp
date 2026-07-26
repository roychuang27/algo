#include <deque>
#include <functional>
#include <iostream>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.begin(), x.end()

using namespace std;
using lli = long long int;

void solution() {
        int N, K; cin >> N >> K;
        vector<int> A(N); for (int &x : A) cin >> x;
        const function cnt_pairs_diff_leq_k = [&](int k)->lli {
                if (k < 0) return 0;
                deque<int> max_MQ, min_MQ;
                int l = 0;
                lli res = 0;
                for (int r = 0; r < N; r++) {
                        while (not max_MQ.empty() and A[max_MQ.end()[-1]] <= A[r])
                                max_MQ.pop_back();
                        max_MQ.push_back(r);

                        while (not min_MQ.empty() and A[min_MQ.end()[-1]] >= A[r])
                                min_MQ.pop_back();
                        min_MQ.push_back(r);

                        while (A[max_MQ[0]] - A[min_MQ[0]] > k) {
                                l++;
                                if (max_MQ[0] < l) max_MQ.pop_front();
                                if (min_MQ[0] < l) min_MQ.pop_front();
                        }

                        res += (r - l + 1);
                }

                return res;
        };

        cout << cnt_pairs_diff_leq_k(K) - cnt_pairs_diff_leq_k(K-1) << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
