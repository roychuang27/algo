template <class UInt = uint32_t>
struct Barrett {
        static_assert(std::is_integral_v<UInt> && std::is_unsigned_v<UInt> &&
                      sizeof(UInt) <= 4);

        using u64 = uint64_t;
        using u128 = __uint128_t;
        explicit Barrett(UInt m = 1):
                m_(m) {
                assert(m_ != 0);
                im_ = ~u64(0) / m_ + 1;
        }
        UInt umod() const {
                return m_;
        }
        UInt mul(UInt a, UInt b) const {
                assert(a < m_ && b < m_);
                u64 z = u64(a) * b;
                u64 x = u64((u128(z) * im_) >> 64);
                u64 y = x * m_;
                return UInt(z - y + (z < y ? m_ : 0));
        }

    private:
        UInt m_;
        u64 im_{};
};
struct ModContext {
    private:
        Barrett<> bt_;

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
        void set_mod(uint32_t m) {
                bt_ = Barrett<>(m);
        }
        struct mint {
                friend struct ModContext;

            private:
                const ModContext *ctx_;
                mutable uint32_t v_;
                uint32_t m() const {
                        return ctx_->mod();
                }
                // Normalize and update the stored representative.
                uint32_t norm() const {
                        return v_ %= m();
                }
                void check(const mint &b) const {
                        assert(ctx_ == b.ctx_);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                mint(const ModContext &ctx, T x):
                        ctx_(&ctx) {
                        if constexpr (std::is_signed_v<T>) {
                                int64_t y = int64_t(x) % int64_t(m());
                                if (y < 0) {
                                        y += m();
                                }
                                v_ = uint32_t(y);
                        } else {
                                v_ = uint32_t(uint64_t(x) % m());
                        }
                }

            public:
                uint32_t val() const {
                        return norm();
                }
                uint32_t mod() const {
                        return m();
                }
                mint &operator++() {
                        uint32_t x = norm() + 1;
                        v_ = x == m() ? 0 : x;
                        return *this;
                }
                mint &operator--() {
                        uint32_t x = norm();
                        v_ = x ? x - 1 : m() - 1;
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
                        uint64_t x = uint64_t(norm()) + b.norm();
                        if (x >= m()) {
                                x -= m();
                        }
                        v_ = uint32_t(x);
                        return *this;
                }
                mint &operator-=(const mint &b) {
                        check(b);
                        uint32_t x = norm(), y = b.norm(), mod = m();
                        v_ = x >= y ? x - y : uint32_t(uint64_t(x) + mod - y);
                        return *this;
                }
                mint &operator*=(const mint &b) {
                        check(b);
                        v_ = ctx_->bt_.mul(norm(), b.norm());
                        return *this;
                }
                mint &operator/=(const mint &b) {
                        check(b);
                        return *this *= b.inv();
                }
                mint pow(long long n) const {
                        assert(n >= 0);
                        mint x = *this, r(*ctx_, 1);
                        x.norm();
                        for (; n; n >>= 1, x *= x) {
                                if (n & 1) {
                                        r *= x;
                                }
                        }
                        return r;
                }
                mint inv() const {
                        int64_t a = norm(), b = m(), u = 1, v = 0;
                        while (b) {
                                int64_t q = a / b;
                                a -= q * b;
                                std::swap(a, b);
                                u -= q * v;
                                std::swap(u, v);
                        }
                        assert(a == 1);
                        return mint(*ctx_, u);
                }
                mint operator+() const {
                        mint x = *this;
                        x.norm();
                        return x;
                }
                mint operator-() const {
                        uint32_t x = norm();
                        return mint(*ctx_, x ? m() - x : 0);
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
                        return a.norm() == b.norm();
                }
                friend bool operator!=(const mint &a, const mint &b) {
                        return !(a == b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend bool operator==(const mint &a, T b) {
                        return a == mint(*a.ctx_, b);
                }
                template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
                friend bool operator==(T a, const mint &b) {
                        return mint(*b.ctx_, a) == b;
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
                        int64_t v;
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
