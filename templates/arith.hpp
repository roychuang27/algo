template <class T>
T mul(T a, unsigned long long n) {
        T res = T(0);
        while (n > 0) {
                if (n & 1) {
                        res = res + a;
                }
                n >>= 1;
                a = a + a;
        }
        return res;
}
template <class T>
T pow(T a, unsigned long long n) {
        T res = T(1);
        while (n > 0) {
                if (n & 1) {
                        res = res * a;
                }
                n >>= 1;
                a = a * a;
        }
        return res;
}
