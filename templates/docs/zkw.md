# Segment Trees (`zkw.hpp` & `zkw_lazy.hpp`)

Iterative segment trees adapted from the AtCoder Library (`Segtree` and `LazySegtree`), using C++20/23 class template argument deduction (CTAD) and `[[no_unique_address]]` callable members.

Both templates support:
- **Capturing lambdas** passed via constructor arguments (no `std::function` overhead).
- **Stateless lambdas and function pointers** via constructor arguments (zero extra memory via `[[no_unique_address]]`) or explicit `decltype(...)` type arguments.
- **Template-argument stateless lambdas** (`template <auto f>`) and **capturing lambdas** in `max_right` / `min_left`.

---

## `Segtree` (`zkw.hpp`)

```cpp
template <class S, class Op, class E>
struct Segtree;
```

### Algebraic Requirements
- `op(S a, S b) -> S` is associative: `op(op(a, b), c) == op(a, op(b, c))`.
- `e() -> S` is the identity element: `op(a, e()) == op(e(), a) == a`.

### Constructors & Deduction

| Form | Behavior |
| --- | --- |
| `Segtree(n, op, e)` | Length `n` initialized to `e()`. Deduces `S` from `e()`. |
| `Segtree(v, op, e)` | Built from `const vector<S> &v` in $O(n)$. Deduces `S` from `v`. |
| `Segtree(op, e)` | Empty tree (`n = 0`). Deduces `S` from `e()`. |
| `Segtree<S, Op, E>()` / `(n)` / `(v)` | Available when `Op` and `E` are `default_initializable` (e.g. stateless lambdas or functors). |

### Operations

All intervals are half-open `[l, r)` with `0 <= l <= r <= n`.

| Method | Complexity | Description |
| --- | --- | --- |
| `void set(int p, S x)` | $O(\log n)$ | Sets `a[p] = x`. |
| `S get(int p) const` | $O(1)$ | Returns `a[p]`. |
| `S prod(int l, int r) const` | $O(\log n)$ | Returns `op(a[l], ..., a[r - 1])`, or `e()` if `l == r`. |
| `S all_prod() const` | $O(1)$ | Returns `prod(0, n)`, or `e()` if `n == 0`. |
| `int max_right<f>(int l) const` | $O(\log n)$ | Largest `r` (`l <= r <= n`) with `f(prod(l, r)) == true` (`f` is a stateless callable/function). |
| `int max_right(int l, F f) const` | $O(\log n)$ | Same as above, accepting any runtime / capturing callable `f`. |
| `int min_left<f>(int r) const` | $O(\log n)$ | Smallest `l` (`0 <= l <= r`) with `f(prod(l, r)) == true` (`f` is a stateless callable/function). |
| `int min_left(int r, F f) const` | $O(\log n)$ | Same as above, accepting any runtime / capturing callable `f`. |

### Examples

```cpp
// Capturing lambda via constructor arguments (S deduced from e())
ll mod = 998244353;
Segtree seg(
        n,
        [mod](ll a, ll b) { return (a + b) % mod; },
        [] { return 0LL; });

// Built from an existing vector (S deduced from v)
vector<ll> a(n, 1);
Segtree seg2(
        a,
        [](ll x, ll y) { return x + y; },
        [] { return 0LL; });

// Explicit type with stateless lambdas (e.g. for struct members or containers)
auto op = [](ll x, ll y) { return max(x, y); };
auto e = [] { return -(1LL << 60); };
Segtree<ll, decltype(op), decltype(e)> seg3(n);

// Binary search on the tree
int r = seg2.max_right<[](const ll &x) { return x <= 10; }>(0);
ll limit = 7;
int l = seg2.min_left(n, [&](const ll &x) { return x < limit; });
```

---

## `LazySegtree` (`zkw_lazy.hpp`)

```cpp
template <class S,
          class Op,
          class E,
          class F,
          class Mapping,
          class Composition,
          class Id>
struct LazySegtree;
```

### Algebraic Requirements
- `(S, op, e)` is a monoid.
- `id() -> F` is the identity mapping: `mapping(id(), x) == x`.
- `mapping(F f, S x) -> S` distributes over `op`: `mapping(f, op(x, y)) == op(mapping(f, x), mapping(f, y))`.
- `composition(F f, F g) -> F` applies `g` first, then `f`: `mapping(composition(f, g), x) == mapping(f, mapping(g, x))`.

### Constructors & Deduction

| Form | Behavior |
| --- | --- |
| `LazySegtree(n, op, e, mapping, composition, id)` | Length `n` initialized to `e()`. Deduces `S` from `e()` and `F` from `id()`. |
| `LazySegtree(v, op, e, mapping, composition, id)` | Built from `const vector<S> &v` in $O(n)$. Deduces `S` from `v` and `F` from `id()`. |
| `LazySegtree(op, e, mapping, composition, id)` | Empty tree (`n = 0`). Deduces `S` from `e()` and `F` from `id()`. |
| `LazySegtree<S, Op, E, F, Mapping, Composition, Id>()` / `(n)` / `(v)` | Available when all 5 callables are `default_initializable`. |

### Operations

All intervals are half-open `[l, r)` with `0 <= l <= r <= n`.

| Method | Complexity | Description |
| --- | --- | --- |
| `void set(int p, S x)` | $O(\log n)$ | Sets `a[p] = x`. |
| `S get(int p)` | $O(\log n)$ | Returns `a[p]`. |
| `S prod(int l, int r)` | $O(\log n)$ | Returns `op(a[l], ..., a[r - 1])`, or `e()` if `l == r`. |
| `S all_prod()` | $O(1)$ | Returns `prod(0, n)`, or `e()` if `n == 0`. |
| `void apply(int p, F f)` | $O(\log n)$ | Sets `a[p] = mapping(f, a[p])`. |
| `void apply(int l, int r, F f)` | $O(\log n)$ | Applies `mapping(f, a[i])` for every `i` in `[l, r)`. |
| `int max_right<g>(int l)` / `(int l, G g)` | $O(\log n)$ | Largest `r` (`l <= r <= n`) with `g(prod(l, r)) == true`. |
| `int min_left<g>(int r)` / `(int r, G g)` | $O(\log n)$ | Smallest `l` (`0 <= l <= r`) with `g(prod(l, r)) == true`. |

### Example

```cpp
// Range add + range sum modulo runtime `mod`
struct Node {
        ll sum;
        int len;
};
ll mod = 998244353;

LazySegtree lseg(
        vector<Node>(n, Node{0, 1}),
        [mod](const Node &a, const Node &b) {
                return Node{(a.sum + b.sum) % mod, a.len + b.len};
        },
        [] { return Node{0, 0}; },
        [mod](ll f, const Node &x) {
                return Node{(x.sum + f * x.len) % mod, x.len};
        },
        [mod](ll f, ll g) { return (f + g) % mod; },
        [] { return 0LL; });

lseg.apply(0, 4, 5);
ll total = lseg.prod(0, n).sum;
```

---

## Notes & Gotchas

- **Monotonicity of `max_right` / `min_left`**: `f(e())` must be `true` (checked by `assert`), and the predicate must be monotonic over prefixes from `l` (for `max_right`) or suffixes ending at `r` (for `min_left`). Modular sums that wrap around are generally *not* monotonic.
- **Reassigning trees with capturing lambdas**: C++ closure types with captures are copy-constructible (if their captures are) but have a deleted copy-assignment operator. Construct a new variable or wrap in `optional` if you need to rebind one.
- **`const` on `Segtree` callables**: `prod`, `max_right`, and `min_left` on `Segtree` are `const`-qualified, so `op` and `e` must be `const`-invocable (non-`mutable` lambdas).
- **Template predicates vs. runtime predicates**: Use `max_right<[](const S &x) { ... }>(l)` for stateless lambdas/functions, and `max_right(l, [&](const S &x) { ... })` whenever the predicate captures local variables.
