class DSU {
    public:
        int N;
        vector<int> root;
 
        DSU(int n): N(n), root(N) {
                for (int i = 0; i < N; i++) {
                        root[i] = i;
                }
        }
 
        bool same_component(int a, int b) {
                return find_root(a) == find_root(b);
        }
 
        int find_root(int x) {
                if (root[x] == x)
                        return x;
                root[x] = find_root(root[x]);
                return root[x];
        }
 
        void unite(int a, int b) {
                a = find_root(a);
                b = find_root(b);
                root[b] = a;
        }
};

