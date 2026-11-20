struct Barrett {
        using u32 = uint32_t;
        using u64 = uint64_t;
        using u128 = __uint128_t;
        constexpr explicit Barrett(u32 m = 1):
                m_(m),
                im_(0) {
                assert(m_ != 0);
                im_ = ~u64(0) / m_ + 1;
        }
        constexpr u32 umod() const {
                return m_;
        }
        u32 reduce(u64 z) const {
                u64 x = u64((u128(z) * im_) >> 64);
                u64 y = x * m_;
                return u32(z - y + (z < y ? m_ : 0));
        }
        u32 mul(u32 a, u32 b) const {
                return reduce(u64(a) * b);
        }
    private:
        u32 m_;
        u64 im_;
};
struct ModContext {
    private:
        Barrett bt_;
        uint32_t gen_ = 0;
    public:
        explicit ModContext(uint32_t m):
                bt_(m) {
        }
        ModContext(const ModContext &) = delete;
        ModContext &operator=(const ModContext &) = delete;
        ModContext(ModContext &&) = delete;
        ModContext &operator=(ModContext &&) = delete;
        uint32_t mod() const {
                return bt_.umod();
        }
        Barrett barrett() const {
                return bt_;
        }
        void set_mod(uint32_t m) {
                bt_ = Barrett(m);
                ++gen_;
        }
        struct mint {
                friend struct ModContext;
            private:
                using u32 = uint32_t;
                using u64 = uint64_t;
                using u128 = __uint128_t;
                const ModContext *ctx_;
                u32 v_;
                u32 gen_;
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                mint(const ModContext &ctx, T x):
                        ctx_(&ctx),
                        v_(from(ctx.bt_, x)),
                        gen_(ctx.gen_) {
                }
                mint with_raw(u32 v) const {
                        mint r = *this;
                        r.v_ = v;
                        return r;
                }
                template <class T>
                mint make(T x) const {
                        return mint(*ctx_, x);
                }
                void check() const {
                        assert(gen_ == ctx_->gen_ && "mint used after set_mod()");
                }
                void check([[maybe_unused]] const mint &b) const {
                        assert(ctx_ == b.ctx_ &&
                               "mints from different ModContexts");
                        assert(gen_ == ctx_->gen_ && b.gen_ == ctx_->gen_ &&
                               "mint used after set_mod()");
                }
                static u32 from_u64(const Barrett &bt, u64 x) {
                        u32 m = bt.umod();
                        if (x < m) {
                                return u32(x);
                        }
                        if (m == 1) {
                                return 0;
                        }
                        return bt.reduce(x);
                }
                template <class T>
                static u32 from(const Barrett &bt, T x) {
                        if constexpr (sizeof(T) > 8) {
                                u32 m = bt.umod();
                                if constexpr (std::is_signed_v<T>) {
                                        __int128 y = __int128(x) % __int128(m);
                                        return u32(y < 0 ? y + m : y);
                                } else {
                                        return u32(u128(x) % m);
                                }
                        } else if constexpr (std::is_signed_v<T>) {
                                if (x >= 0) {
                                        return from_u64(bt, u64(x));
                                }
                                u32 r = from_u64(bt,
                                                 u64(0) - u64(int64_t(x)));
                                return r ? bt.umod() - r : 0;
                        } else {
                                return from_u64(bt, u64(x));
                        }
                }
            public:
                u32 val() const {
                        check();
                        return v_;
                }
                u32 mod() const {
                        check();
                        return ctx_->mod();
                }
                mint &operator++() {
                        check();
                        u32 x = v_ + 1;
                        v_ = x == ctx_->bt_.umod() ? 0 : x;
                        return *this;
                }
                mint &operator--() {
                        check();
                        v_ = v_ ? v_ - 1 : ctx_->bt_.umod() - 1;
                        return *this;
                }
                mint operator++(int) {
                        mint x = *this;
                        ++*this;
                        return x;
                }
                mint operator--(int) {
                        mint x = *this;
                        --*this;
                        return x;
                }
                mint &operator+=(const mint &b) {
                        check(b);
                        u32 m = ctx_->bt_.umod(), r = m - b.v_;
                        v_ = v_ >= r ? v_ - r : v_ + b.v_;
                        return *this;
                }
                mint &operator-=(const mint &b) {
                        check(b);
                        u32 m = ctx_->bt_.umod();
                        u32 x = v_ - b.v_;
                        v_ = v_ < b.v_ ? x + m : x;
                        return *this;
                }
                mint &operator*=(const mint &b) {
                        check(b);
                        v_ = ctx_->bt_.mul(v_, b.v_);
                        return *this;
                }
                mint &operator/=(const mint &b) {
                        check(b);
                        return *this *= b.inv();
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                mint &operator+=(T b) {
                        return *this += make(b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                mint &operator-=(T b) {
                        return *this -= make(b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                mint &operator*=(T b) {
                        return *this *= make(b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                mint &operator/=(T b) {
                        return *this /= make(b);
                }
                mint pow(long long n) const {
                        check();
                        assert(n >= 0);
                        Barrett bt = ctx_->bt_;
                        u32 x = v_, r = bt.umod() > 1 ? 1u : 0u;
                        for (unsigned long long e = n; e; e >>= 1) {
                                if (e & 1) {
                                        r = bt.mul(r, x);
                                }
                                if (e > 1) {
                                        x = bt.mul(x, x);
                                }
                        }
                        return with_raw(r);
                }
                mint inv() const {
                        check();
                        u32 m = ctx_->bt_.umod(), a = v_, b = m;
                        int64_t u = 1, v = 0;
                        while (b) {
                                u32 q = a / b;
                                a -= q * b;
                                std::swap(a, b);
                                u -= int64_t(q) * v;
                                std::swap(u, v);
                        }
                        assert(a == 1);
                        return with_raw(u < 0 ? u32(u + int64_t(m)) :
                                                u32(u));
                }
                mint operator+() const {
                        check();
                        return *this;
                }
                mint operator-() const {
                        check();
                        return with_raw(v_ ? ctx_->bt_.umod() - v_ : 0);
                }
                friend mint operator+(mint a, const mint &b) {
                        return a += b;
                }
                friend mint operator-(mint a, const mint &b) {
                        return a -= b;
                }
                friend mint operator*(mint a, const mint &b) {
                        return a *= b;
                }
                friend mint operator/(mint a, const mint &b) {
                        return a /= b;
                }
                friend bool operator==(const mint &a, const mint &b) {
                        a.check(b);
                        return a.v_ == b.v_;
                }
                friend bool operator!=(const mint &a, const mint &b) {
                        return !(a == b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend mint operator+(const mint &a, T b) {
                        return a + a.make(b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend mint operator+(T a, const mint &b) {
                        return b.make(a) + b;
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend mint operator-(const mint &a, T b) {
                        return a - a.make(b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend mint operator-(T a, const mint &b) {
                        return b.make(a) - b;
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend mint operator*(const mint &a, T b) {
                        return a * a.make(b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend mint operator*(T a, const mint &b) {
                        return b.make(a) * b;
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend mint operator/(const mint &a, T b) {
                        return a / a.make(b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend mint operator/(T a, const mint &b) {
                        return b.make(a) / b;
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend bool operator==(const mint &a, T b) {
                        return a == a.make(b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend bool operator==(T a, const mint &b) {
                        return b.make(a) == b;
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend bool operator!=(const mint &a, T b) {
                        return !(a == b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend bool operator!=(T a, const mint &b) {
                        return !(a == b);
                }
                friend std::istream &operator>>(std::istream &is, mint &x) {
                        long long v;
                        if (is >> v) {
                                x = mint(*x.ctx_, v);
                        }
                        return is;
                }
                friend std::ostream &operator<<(std::ostream &os, const mint &x) {
                        return os << x.val();
                }
        };
        template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
        mint operator()(T x) const & {
                return mint(*this, x);
        }
        template <class T>
        mint operator()(T) const && = delete;
};
