# Multidimensional Matrix (`matrix.hpp` & `matrix_mul.hpp`)

Flat row-major $D$-dimensional array (`Matrix`) with C++23 multidimensional subscripting (`m[i, j, k]`), optional automatic dimension count, braced-initializer support (`{}` / `{a, b}`), and 2D matrix multiplication / binary exponentiation (`matrix_mul.hpp`).

---

## `Matrix` (`matrix.hpp`)

```cpp
template <class T, size_t D = 0>
struct Matrix;
```

- When `D == 0` (default, i.e. `Matrix<T>`), the number of dimensions is determined automatically from the constructor arguments and stored in `vector<size_t> s` (up to 16 dimensions).
- When `D > 0` (e.g. `Matrix<T, 2>`), the rank is fixed at compile time and stored in `array<size_t, D> s` with zero extra heap allocation for shape metadata.
- Elements are stored contiguously in row-major order in `vector<T> a`.

### Constructors & Deduction

| Form | Resulting Type | Behavior |
| --- | --- | --- |
| `Matrix<T>()` / `Matrix<T, D>()` | `Matrix<T, 0>` / `Matrix<T, D>` | Default empty matrix (`a` is empty). |
| `Matrix<T>(d0, ..., d_{k-1}, val)` | `Matrix<T, 0>` | $k$-dimensional matrix (`1 <= k <= 16`) filled with `val`. `val` is non-deduced `const T &`, so `{}` and braced initializers like `{1, 2}` work directly. |
| `Matrix<T, D>(d0, ..., d_{D-1})` | `Matrix<T, D>` | Fixed $D$-dimensional matrix initialized to `T{}`. |
| `Matrix<T, D>(d0, ..., d_{D-1}, val)` | `Matrix<T, D>` | Fixed $D$-dimensional matrix filled with `val` (supports `{}` and braced initializers). |
| `Matrix(d0, ..., d_{k-1}, val)` | `Matrix<decltype(val), k>` | CTAD (`k >= 1`): deduces both element type `T` and compile-time rank `k`. |

Dimension arguments are converted through an internal `Dim` wrapper accepting any integral type, asserting `x >= 0` for signed integers, avoiding narrowing errors under brace-init (`Matrix<int>{n, m, {}}`), and rejecting accidental `{}` in dimension positions.

### Members & Operations

| Member | Complexity | Description |
| --- | --- | --- |
| `s` | — | Shape container (`vector<size_t>` for `D == 0`, `array<size_t, D>` for `D > 0`). |
| `a` | — | Underlying flat row-major `vector<T>`. |
| `size_t pos(I... i) const` | $O(D)$ | Computes the flat index for `(i...)`. Checks arity (`static_assert` for `D > 0`, `assert` for `D == 0`) and bounds (`in_range<size_t>(i) && size_t(i) < s[d]`). |
| `at(I... i)` / `at(I... i) const` | $O(D)$ | Returns `a[pos(i...)]` via `decltype(auto)` (supports `Matrix<bool>` proxy references). |
| `operator[](I... i)` / `const` | $O(D)$ | Same as `at(i...)`, using C++23 multidimensional subscripting `mat[i, j, k]`. |
| `string str() const` | $O(\prod s_i)$ | Formats nested `[...]` output via `ostringstream` (`"[]"` when `s` is empty). |

### Examples

```cpp
// Automatic dimension count with {} for default value
Matrix<int> dp(n, m, k, {});
dp[0, 1, 2] = 7;

// Automatic dimension count with explicit or braced fill values
Matrix<int> dist(n, m, -1);
Matrix<pair<int, int>> grid(n, m, {0, 0});
Matrix<Matrix<int>> nested(2, 2, {3, 4, {}});

// Fixed compile-time rank (fill value optional, {} also supported)
Matrix<int, 2> fixed(n, m);
Matrix<int, 3> fixed_zero(1, 2, 3, {});

// CTAD deduces both T and compile-time D
Matrix mat(1, 2, 3, 0LL); // Matrix<long long, 3>
```

---

## 2D Multiplication (`matrix_mul.hpp`)

All functions in `matrix_mul.hpp` require `D == 0 || D == 2` and work on both `Matrix<T>` (asserting `s.size() == 2` at runtime) and `Matrix<T, 2>`.

| Function | Complexity | Description |
| --- | --- | --- |
| `operator*(const Matrix<T, D> &a, const Matrix<T, D> &b)` | $O(nmk)$ | Matrix product of an $n \times m$ and an $m \times k$ matrix. Asserts `a.s.size() == 2 && b.s.size() == 2 && a.s[1] == b.s[0]`. |
| `operator*=(Matrix<T, D> &a, const Matrix<T, D> &b)` | $O(nmk)$ | Assigns `a = a * b`. |
| `mat_pow(Matrix<T, D> a, uint64_t n)` | $O(m^3 \log n)$ | Computes $a^n$ for a square $m \times m$ matrix (`a.s[0] == a.s[1]`), starting from the identity with `T{}` off-diagonal and `T{1}` on the diagonal. |

### Example

```cpp
// 10th Fibonacci number using automatic-rank Matrix<ll>
Matrix<ll> fib(2, 2, {});
fib[0, 0] = fib[0, 1] = fib[1, 0] = 1;
ll f10 = mat_pow(fib, 10)[0, 1]; // 55

// Same with fixed-rank Matrix<ll, 2>
Matrix<ll, 2> fib2(2, 2);
fib2[0, 0] = fib2[0, 1] = fib2[1, 0] = 1;
ll f10_2 = mat_pow(fib2, 10)[0, 1]; // 55
```

---

## Notes & Gotchas

- **Last argument is always the fill value for `Matrix<T>`**: When `D == 0`, the final argument is always `const T &v` so dimensions and values are never ambiguous for integral `T`. Pass `{}` for default initialization (`Matrix<int> m(2, 3, {})`); writing `Matrix<int> m(2, 3)` constructs a **1D** matrix of length `2` filled with `3`.
- **Rank limit for `Matrix<T>`**: Automatic-rank constructors are generated for up to 16 dimensions (`make_index_sequence<D ? D : 16>` in `matrix.hpp`). Explicit `Matrix<T, D>` and CTAD `Matrix(...)` have no fixed upper limit.
- **Matching `D` in `matrix_mul.hpp`**: `operator*` and `operator*=` expect both operands to have the same `D` (either both `Matrix<T>` or both `Matrix<T, 2>`).
- **Non-default-constructible `T`**: Supported by both `Matrix<T>` and `Matrix<T, D>` whenever an explicit fill value is passed (including braced constructor arguments like `Matrix<Foo>(2, 3, {42})`).
