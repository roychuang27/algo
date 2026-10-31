struct ZKW {
    vector<lli> t = vector<lli> (nodes_cnt_max * 2);
    int N;

    void init(int arr_size) {
        N = arr_size;
        for (int i = 0; i <= 2 * N + 1; i++) t[i] = 0;
    }

    void printdbg() {
        cerr << "You are trying to print something" << endl;
        int l = N, r = 2 * N - 1;
        while (l <= r) {
            for (int i = l; i <= r; i++) cerr << t[i] << ' ';
            cerr << endl;
            if (l % 2 == 1) l++;
            if (r % 2 == 0) r--;
            l /= 2;
            r /= 2;
        }
    }

    void build() {
        for (int i = N; i < 2 * N; i++) {
            t[i] = zkw_over_arr[i - N];
        }
        for (int i = N - 1; i >= 1; i--) {
            t[i] = max(t[i * 2], t[i * 2 + 1]);
        }
    }

    void modify(int idx, lli val) {
        zkw_over_arr[idx] = val;
        idx += N;
        t[idx] = val;
        idx /= 2;
        while (idx >= 1) {
            t[idx] = max(t[2 * idx], t[2 * idx + 1]);
            idx /= 2;
        }
    }

    lli query(int l, int r) {
        l += N;
        r += N;
        lli res = -1;
        while (l <= r) {
            if (l % 2 == 1) res = max(t[l++], res);
            if (r % 2 == 0) res = max(t[r--], res);
            l /= 2;
            r /= 2;
        }
        return res;
    }
} zkw;
