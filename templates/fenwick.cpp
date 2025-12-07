class Fenwick {
        public:
        const int capacity = 2e5;
        vector<lli> b;
        
        Fenwick() {
                b = vector<lli> (capacity + 10, 0);
        }
        
        int lowbit(int x) {
                return x & -x;
        }
        
        void modify(int idx, int delta) {
                for (int pos = idx; pos <= capacity; pos += lowbit(pos)) {
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

