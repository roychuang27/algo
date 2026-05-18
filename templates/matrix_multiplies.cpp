vector<vector<lli>> matrices_multiply(vector<vector<lli>>& A,
                                      vector<vector<lli>>& B) {
        if (SZ(A[0]) != SZ(B)) return {};
        vector<vector<lli>> res(SZ(A), vector<lli>(SZ(B[0]), 0LL));
        for (int i = 0; i < SZ(A); i++) {
                for (int j = 0; j < SZ(B[0]); j++) {
                        for (int k = 0; k < SZ(A[0]); k++) {
                                res[i][j] += A[i][k] * B[k][j];
                                if (res[i][j] >= MOD) res[i][j] %= MOD;
                        }
                }
        }
        return res;
}

vector<vector<lli>> matrix_fast_power(vector<vector<lli>>& A, lli power) {
        if (SZ(A) != SZ(A[0])) return {};
        vector<vector<lli>> res(SZ(A), vector<lli>(SZ(A[0]), 0LL));
        for (int i = 0; i < SZ(A); i++) res[i][i] = 1;
        while (power > 0) {
                if (power & 1) res = matrices_multiply(res, A);
                power >>= 1;
                A = matrices_multiply(A, A);
        }
        return res;
}
