// Reference : atcoder library
template <class S,
          class Op,
          class E,
          class F,
          class Mapping,
          class Composition,
          class Id>
struct LazySegtree {
    public:
        LazySegtree()
                requires default_initializable<Op> && default_initializable<E> &&
                         default_initializable<Mapping> &&
                         default_initializable<Composition> &&
                         default_initializable<Id>:
                LazySegtree(0, Op{}, E{}, Mapping{}, Composition{}, Id{}) {
        }
        explicit LazySegtree(int n)
                requires default_initializable<Op> && default_initializable<E> &&
                         default_initializable<Mapping> &&
                         default_initializable<Composition> &&
                         default_initializable<Id>:
                LazySegtree(n, Op{}, E{}, Mapping{}, Composition{}, Id{}) {
        }
        explicit LazySegtree(const vector<S> &v)
                requires default_initializable<Op> && default_initializable<E> &&
                         default_initializable<Mapping> &&
                         default_initializable<Composition> &&
                         default_initializable<Id>:
                LazySegtree(v, Op{}, E{}, Mapping{}, Composition{}, Id{}) {
        }
        LazySegtree(Op op_,
                    E e_,
                    Mapping mapping_,
                    Composition composition_,
                    Id id_):
                LazySegtree(0,
                            move(op_),
                            move(e_),
                            move(mapping_),
                            move(composition_),
                            move(id_)) {
        }
        LazySegtree(int n,
                    Op op_,
                    E e_,
                    Mapping mapping_,
                    Composition composition_,
                    Id id_):
                _n(n),
                op(move(op_)),
                e(move(e_)),
                mapping(move(mapping_)),
                composition(move(composition_)),
                id(move(id_)) {
                size = 1;
                log = 0;
                while (size < _n) {
                        size <<= 1;
                        log++;
                }
                d = vector<S>(2 * size, e());
                lz = vector<F>(size, id());
        }
        LazySegtree(const vector<S> &v,
                    Op op_,
                    E e_,
                    Mapping mapping_,
                    Composition composition_,
                    Id id_):
                LazySegtree(int(v.size()),
                            move(op_),
                            move(e_),
                            move(mapping_),
                            move(composition_),
                            move(id_)) {
                for (int i = 0; i < _n; i++) {
                        d[size + i] = v[i];
                }
                for (int i = size - 1; i >= 1; i--) {
                        update(i);
                }
        }

        void set(int p, S x) {
                assert(0 <= p && p < _n);
                p += size;
                for (int i = log; i >= 1; i--) {
                        push(p >> i);
                }
                d[p] = x;
                for (int i = 1; i <= log; i++) {
                        update(p >> i);
                }
        }

        S get(int p) {
                assert(0 <= p && p < _n);
                p += size;
                for (int i = log; i >= 1; i--) {
                        push(p >> i);
                }
                return d[p];
        }

        S prod(int l, int r) {
                assert(0 <= l && l <= r && r <= _n);
                if (l == r) {
                        return e();
                }

                l += size;
                r += size;

                for (int i = log; i >= 1; i--) {
                        if (((l >> i) << i) != l) {
                                push(l >> i);
                        }
                        if (((r >> i) << i) != r) {
                                push((r - 1) >> i);
                        }
                }

                S sml = e(), smr = e();
                while (l < r) {
                        if (l & 1) {
                                sml = op(sml, d[l++]);
                        }
                        if (r & 1) {
                                smr = op(d[--r], smr);
                        }
                        l >>= 1;
                        r >>= 1;
                }

                return op(sml, smr);
        }

        S all_prod() {
                return d[1];
        }

        void apply(int p, F f) {
                assert(0 <= p && p < _n);
                p += size;
                for (int i = log; i >= 1; i--) {
                        push(p >> i);
                }
                d[p] = mapping(f, d[p]);
                for (int i = 1; i <= log; i++) {
                        update(p >> i);
                }
        }

        void apply(int l, int r, F f) {
                assert(0 <= l && l <= r && r <= _n);
                if (l == r) {
                        return;
                }

                l += size;
                r += size;

                for (int i = log; i >= 1; i--) {
                        if (((l >> i) << i) != l) {
                                push(l >> i);
                        }
                        if (((r >> i) << i) != r) {
                                push((r - 1) >> i);
                        }
                }

                {
                        int l2 = l, r2 = r;
                        while (l < r) {
                                if (l & 1) {
                                        all_apply(l++, f);
                                }
                                if (r & 1) {
                                        all_apply(--r, f);
                                }
                                l >>= 1;
                                r >>= 1;
                        }
                        l = l2;
                        r = r2;
                }

                for (int i = 1; i <= log; i++) {
                        if (((l >> i) << i) != l) {
                                update(l >> i);
                        }
                        if (((r >> i) << i) != r) {
                                update((r - 1) >> i);
                        }
                }
        }

        template <auto g>
        int max_right(int l) {
                return max_right(l, [](const S &x) { return g(x); });
        }
        template <class G>
        int max_right(int l, G g) {
                assert(0 <= l && l <= _n);
                assert(g(e()));
                if (l == _n) {
                        return _n;
                }
                l += size;
                for (int i = log; i >= 1; i--) {
                        push(l >> i);
                }
                S sm = e();
                do {
                        while (l % 2 == 0) {
                                l >>= 1;
                        }
                        if (!g(op(sm, d[l]))) {
                                while (l < size) {
                                        push(l);
                                        l = (2 * l);
                                        if (g(op(sm, d[l]))) {
                                                sm = op(sm, d[l]);
                                                l++;
                                        }
                                }
                                return l - size;
                        }
                        sm = op(sm, d[l]);
                        l++;
                } while ((l & -l) != l);
                return _n;
        }

        template <auto g>
        int min_left(int r) {
                return min_left(r, [](const S &x) { return g(x); });
        }
        template <class G>
        int min_left(int r, G g) {
                assert(0 <= r && r <= _n);
                assert(g(e()));
                if (r == 0) {
                        return 0;
                }
                r += size;
                for (int i = log; i >= 1; i--) {
                        push((r - 1) >> i);
                }
                S sm = e();
                do {
                        r--;
                        while (r > 1 && (r % 2)) {
                                r >>= 1;
                        }
                        if (!g(op(d[r], sm))) {
                                while (r < size) {
                                        push(r);
                                        r = (2 * r + 1);
                                        if (g(op(d[r], sm))) {
                                                sm = op(d[r], sm);
                                                r--;
                                        }
                                }
                                return r + 1 - size;
                        }
                        sm = op(d[r], sm);
                } while ((r & -r) != r);
                return 0;
        }

    private:
        int _n, size, log;
        vector<S> d;
        vector<F> lz;
        [[no_unique_address]] Op op;
        [[no_unique_address]] E e;
        [[no_unique_address]] Mapping mapping;
        [[no_unique_address]] Composition composition;
        [[no_unique_address]] Id id;

        void update(int k) {
                d[k] = op(d[2 * k], d[2 * k + 1]);
        }
        void all_apply(int k, F f) {
                d[k] = mapping(f, d[k]);
                if (k < size) {
                        lz[k] = composition(f, lz[k]);
                }
        }
        void push(int k) {
                all_apply(2 * k, lz[k]);
                all_apply(2 * k + 1, lz[k]);
                lz[k] = id();
        }
};

template <class Op, class E, class Mapping, class Composition, class Id>
LazySegtree(Op, E, Mapping, Composition, Id)
        -> LazySegtree<remove_cvref_t<invoke_result_t<E &>>,
                       Op,
                       E,
                       remove_cvref_t<invoke_result_t<Id &>>,
                       Mapping,
                       Composition,
                       Id>;
template <class Op, class E, class Mapping, class Composition, class Id>
LazySegtree(int, Op, E, Mapping, Composition, Id)
        -> LazySegtree<remove_cvref_t<invoke_result_t<E &>>,
                       Op,
                       E,
                       remove_cvref_t<invoke_result_t<Id &>>,
                       Mapping,
                       Composition,
                       Id>;
template <class S, class Op, class E, class Mapping, class Composition, class Id>
LazySegtree(const vector<S> &, Op, E, Mapping, Composition, Id)
        -> LazySegtree<S,
                       Op,
                       E,
                       remove_cvref_t<invoke_result_t<Id &>>,
                       Mapping,
                       Composition,
                       Id>;
