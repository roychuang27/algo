// credit to: cot orz
#include <unistd.h>
struct fastIO {
    static constexpr unsigned Ibuf_size = 1 << 16, Obuf_size = 1 << 16;
    static constexpr array<char, 200> digit_table = []() {
        array<char, 200> ret{};
        for (int i = 0; i < 100; i++) {
            int x = i;
            for (int t = 2; t--; ) {
                ret[i * 2 + t] = (x % 10) ^ 48;
                x /= 10;
            }
        }
        return ret;
    }();
    static constexpr array<unsigned, 5> ten_pow = []() {
        array<unsigned, 5> ret{};
        ret[0] = 1;
        for (int i = 1; i < 5; i++) ret[i] = ret[i - 1] * 10;
        return ret;
    }();
    char Ibuf[Ibuf_size], Obuf[Obuf_size], num_buf[32], Ic, not_eof;
    unsigned Il, Ir, Or;
    explicit operator bool() const
    { return not_eof; }
    fastIO() : Il(), Ir(), Or(), Ic(), not_eof(1) {}
    ~fastIO() { flush(); }
    char get_char() {
        if (Il == Ir) Ir = (Il = 0) + read(0, Ibuf, Ibuf_size);
        if (Ir == 0) return (not_eof = 0);
        return Ibuf[Il++];
    }
    void skip_space() {
        while (isspace(Ic = get_char()));
    }
    void flush() {
        write(1, Obuf, Or);
        Or = 0;
    }
    fastIO& operator>>(char& c) {
        skip_space();
        c = Ic;
        return *this;
    }
    template <class Int, typename = enable_if_t<is_integral_v<Int>>>
    fastIO& operator>>(Int& x) {
        skip_space();
        bool neg = (Ic == '-');
        if (neg) Ic = get_char();
        Int ret{};
        if (isdigit(Ic)) {
            ret = Ic & 15;
            while (isdigit(Ic = get_char()))
                ret = ret * 10 + (Ic & 15);
        }
        x = neg ? -ret : ret;
        return *this;
    }
    fastIO& operator>>(string& str) {
        skip_space();
        if (Ic != 0) {
            str.clear();
            do {
                str.push_back(Ic);
            } while (!isspace(Ic = get_char()) && Ic);
        }
        return *this;
    }
    fastIO& operator<<(char c) {
        if (Or == Obuf_size) flush();
        Obuf[Or++] = c;
        return *this;
    }
    template <class Int, typename = enable_if_t<is_integral_v<Int>>>
    fastIO& operator<<(Int x) {
        make_unsigned_t<Int> y = x;
        if constexpr (is_signed_v<Int>) {
            if (x < 0) {
                y = -x;
                (*this) << '-';
            }
        }
        int __i = 32;
        do {
            *(short*)&num_buf[__i - 2] = *(const short*)&digit_table[(y % 100) * 2];
            __i -= 1 + (y >= 10);
        } while (y /= 100);
        if (Or + 32 - __i >= Obuf_size) flush();
        for (; __i < 32; ) Obuf[Or++] = num_buf[__i++];
        return *this;
    }
 
    fastIO& operator<<(string_view sv) {
        if (Or + size(sv) >= Obuf_size) {
            flush();
            write(1, data(sv), size(sv));
        }
        else {
            copy(begin(sv), end(sv), &Obuf[Or]);
            Or += size(sv);
        }
        return *this;
    }
} IO;
#define cin IO
#define cout IO
