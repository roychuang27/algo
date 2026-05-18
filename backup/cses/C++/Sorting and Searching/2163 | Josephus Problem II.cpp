#include <iostream>
#include <vector>
using namespace std;

struct Fenwick {
    int n;
    vector<int> fenw;
    Fenwick(int n): n(n), fenw(n+1, 0) {}
    
    // Initialize with values (here all ones)
    void init(const vector<int>& arr) {
        for (int i = 0; i < n; i++) {
            fenw[i+1] = arr[i];
        }
        for (int i = 1; i <= n; i++) {
            int j = i + (i & -i);
            if (j <= n) fenw[j] += fenw[i];
        }
    }
    
    // Update position i (1-indexed) with delta
    void update(int i, int delta) {
        for(; i <= n; i += i & -i)
            fenw[i] += delta;
    }
    
    // Return prefix sum up to index i (1-indexed)
    int sum(int i) {
        int res = 0;
        for(; i > 0; i -= i & -i)
            res += fenw[i];
        return res;
    }
    
    // Find the smallest index such that the prefix sum is >= k
    int find(int k) {
        int idx = 0;
        // bitMask should be high enough so that (1 << bitMask) >= n
        for (int bitMask = 1 << 18; bitMask; bitMask >>= 1) {
            int nextIdx = idx + bitMask;
            if (nextIdx <= n && fenw[nextIdx] < k) {
                k -= fenw[nextIdx];
                idx = nextIdx;
            }
        }
        return idx + 1;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long k;
    cin >> n >> k;
    
    // Build initial array: every child is present (value 1)
    vector<int> arr(n, 1);
    Fenwick fenw(n);
    fenw.init(arr);
    
    // currentRank tracks the position (0-indexed among remaining children) 
    // where counting will start for the next removal.
    long long currentRank = 0;
    int rem = n;
    
    // For each removal, calculate the position to remove using modular arithmetic.
    for (int i = 0; i < n; i++) {
        // Determine the removal position (0-indexed) among remaining children
        currentRank = (currentRank + k) % rem;
        // Convert to 1-indexed rank for BIT operations
        int removalRank = currentRank + 1;
        // Find the actual child position (1-indexed) in the original numbering
        int pos = fenw.find(removalRank);
        cout << pos << " ";
        // Mark this child as removed
        fenw.update(pos, -1);
        rem--;
        // currentRank remains as is because after removal, the next child occupies the same rank.
        if (currentRank >= rem) currentRank = 0;
    }
    
    cout << "\n";
    return 0;
}