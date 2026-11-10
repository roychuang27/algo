class Fenwick {
    public:
        int N;
        vector<long long> b;

        Fenwick(int _n):
                N(_n),
                b(N + 1, 0) {
        }

        int lowbit(int x) {
                return x & -x;
        }

        void modify(int idx, int delta) {
                idx++;
                for (int pos = idx; pos <= N; pos += lowbit(pos)) {
                        b[pos] += delta;
                }
        }

        long long query(int idx) {
                idx++;
                long long res = 0;
                for (int pos = idx; pos >= 1; pos -= lowbit(pos)) {
                        res += b[pos];
                }
                return res;
        }
};
