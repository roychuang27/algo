enum TagType { ADD, SET, NONE };
 
struct Tag {
        TagType type = NONE;
        lli val = 0;
};
 
struct LazySegTree {
        const int N;
        vector<lli> t;
        vector<Tag> tag;
 
        void build(int id, int l, int r, const vector<lli> &vec) {
                if (l == r) {
                        t[id] = vec[l];
                } else {
                        int m = (l + r) / 2;
                        build(2*id, l, m, vec);
                        build(2*id+1, m+1, r, vec);
                        t[id] = t[2*id] + t[2*id+1];
                }
        }
 
        void apply(int id, int len, const Tag &x) {
                if (x.type == ADD) {
                        if (tag[id].type != SET) {
                                tag[id] = Tag{ADD, tag[id].val + x.val};
                        } else {
                                tag[id] = Tag{SET, tag[id].val + x.val};
                        }
                        t[id] += x.val * len;
                } else if (x.type == SET) {
                        t[id] = x.val * len;
                        tag[id] = x;
                }
        }
 
        void push_down(int id, int l, int r) {
                int m = (l + r) / 2;
                apply(2*id, m-l+1, tag[id]);
                apply(2*id+1, r-m, tag[id]);
                tag[id] = Tag();
        }
 
        void range_update(int id, int l, int r, int ql, int qr, const Tag &x) {
                if (qr < l or ql > r) return;
                if (ql <= l and r <= qr) {
                        apply(id, r-l+1, x);
                } else {
                        push_down(id, l, r);
                        int m = (l + r) / 2;
                        range_update(2*id, l, m, ql, qr, x);
                        range_update(2*id+1, m+1, r, ql, qr, x);
                        t[id] = t[2*id] + t[2*id+1];
                }
        }
 
        lli query_range_sum(int id, int l, int r, int ql, int qr) {
                if (qr < l or ql > r) return 0;
                if (l >= ql and r <= qr) return t[id];
                push_down(id, l, r);
                int m = (l + r) / 2;
                return query_range_sum(2*id, l, m, ql, qr) + query_range_sum(2*id+1, m+1, r, ql, qr);
        }
 
        LazySegTree(const vector<lli> &vec) : N(SZ(vec)), t(4*N), tag(4*N) {
                build(1, 0, N-1, vec);
        }
};
