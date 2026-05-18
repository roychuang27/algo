class Fenwick {
    public:
        int N;
        vector<lli> b;
        
        Fenwick(int _n) : N(_n), b(N + 1, 0) {}
        
        int lowbit(int x) {
                return x & -x;
        }
        
        void modify(int idx, int delta) {
                for (int pos = idx; pos <= N; pos += lowbit(pos)) {
                        b[pos] += delta;
                }
        }
        
        lli query(int idx) {
                lli res = 0;
                for (int pos = idx; pos >= 1; pos -= lowbit(pos)) {
                        res += b[pos];
                }
                return res;
        }
};
