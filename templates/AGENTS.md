# Notes for agents working on this repo

A personal competitive-programming template collection. There is no build
system: the `.hpp` files are fragments that get pasted into a single
`starter.cpp` translation unit at solve time, and `g.py` publishes them to
Helix snippets. Everything below is about keeping that paste flow working.

## Layout

| Path | What it is |
| --- | --- |
| `starter.cpp` | The snippet body: includes, `using namespace std`, `ll`/`ull`, `fir`/`all`/`rall`, `line`/`dbg`, `pow`, `chmin`/`chmax`, `array_fill`, `>>` overloads, `I`/`O`, `ITER`, and `single_testcase()` containing the `${1}` placeholder |
| `*.hpp` | Template fragments appended to `starter.cpp`, in the user's own 8-space style: `modint.hpp`, `fraction.hpp`, `matrix.hpp`, `matrix_mul.hpp`, `zkw.hpp`, `zkw_lazy.hpp`, `geometry.hpp`, `set_and_map.hpp`, `fenwick.hpp`, `dsu.hpp`, `dinic.hpp`, `aho_corasick.hpp` |
| `g.py` | Publishes `starter.cpp` as snippet `cp` and `modint`/`fraction`/`matrix`/`matrix_mul`/`zkw`/`zkw_lazy` as snippets named after their stem, into `$XDG_CONFIG_HOME/helix/snippets/cpp.json` |
| `tests/` | `run.py` plus `cases/*.cpp`; see below |
| `IO/` | Vendored fast-IO libraries, independent of the snippets |
| `sudoku.py` | Unrelated scratch script |

`g.py` with no arguments syncs the default set; passing filenames syncs those
instead (`./g.py geometry.hpp`), which is how the headers outside the default
list get published.

## How the fragments are used

The headers are only ever compiled *after* everything else in `starter.cpp`, so:

- `using namespace std;` is already in effect. Do not write `std::` in the
  fragments, with the exception of things that must be declared in `std`
  (there are none left — see below).
- Helpers from `starter.cpp` (`pow`, `chmin`, `ll`, `fir`, ...) are
  available to the fragments. There is no `square`/`SQ` helper: write
  `pow(x, 2)`.
- Use `ssize(c)` for container sizes, not an `SZ` macro — the codebase no
  longer defines one.
- order matters: a fragment may use anything defined above it, not below.

`starter.cpp` must keep the literal `${1}` inside `single_testcase()`; the
editor snippet parser expands it into the code cursor position.

## Conventions in this codebase

- 8-space indentation, no tabs, about 80 columns. `zkw.hpp` and
  `zkw_lazy.hpp` still carry ACL's 4-space layout from upstream — leave the
  existing bodies alone unless you are editing those lines anyway.
- Types that need to be printed define `string str() const` built on
  `ostringstream`: `Matrix`, `Fraction`, `StaticModint`, `Point`, `Circle`.
  The formatter specializations and `operator<<` overrides that used to exist
  were deliberately removed; do not re-add `std::formatter` or per-type
  stream operators without being asked.
- Input still uses stream operators (`pair`, `array`, `vector`, `StaticModint`,
  `Fraction`) because `str()` gives no replacement for reading.
- `I(a, b, ...)` reads every argument (`cin >> ... >> a`), `O(a, b, ...)`
  prints them space separated and ends the line. Both are variadic function
  templates, not macros, so argument lists containing commas are fine.
- `ITER<T>` wraps a container to print it space separated via `cout << ITER{v}`.
  It is the one deliberate exception to the `str()` rule: it exists as an
  ostream helper only and has no `str()`.
- Fragments spell out `long long`; the old `lli` alias does not exist.
- `line(...)` and `dbg(...)` are debugging aids, active only with
  `-DSHELTER` on a C++23 library with `<print>`; otherwise they expand to
  `39`. `dbg` formats through `println`/`forward_as_tuple`, so it accepts
  built-in types only — custom types have no formatter.

## Tests

```
python3 tests/run.py          # all cases, exits non-zero on failure
```

Each case in `tests/cases/*.cpp` is assembled exactly like a real solve: the
declared headers are injected just above `void single_testcase() {` and the
code replaces `${1}`. Case file format:

```
// std: c++23 c++17          standards to build with (default: c++23)
// mode: full                full (default) or prelude
// headers: modint.hpp       fragments appended to the file
// defines: SHELTER          macros defined while compiling
--- code
<code placed at ${1}, or after the prelude in `mode: prelude`>
--- out: c++23
<expected stdout; `--- out` alone applies to every standard>
--- err has
<substrings expected on stderr, ANSI stripped>
```

`mode: prelude` splices the code after everything above
`#if defined(SHELTER)`, so the case provides its own `main()`; it exists for
cases that cannot live inside `single_testcase()`.

Builds use `g++ -std=<std> -Wall -Wextra -O2`, GCC 16.2.1. Keep new code
warning-clean; temporaries live only in `tempfile` directories.

## Gotchas

- The git index stores these files under `templates/`, but the working tree
  root *is* that directory (`templates/` does not exist on disk). `git diff`
  therefore prints `templates/foo.hpp` for a file you edited as `foo.hpp`.
- The user edits files concurrently while you work. Re-read a file before
  editing it, and re-run the suite after changes; do not assume the state you
  saw earlier is current.
- A constructor whose mem-initializer names the class is a *delegating*
  constructor: `zkw.hpp`/`zkw_lazy.hpp` were broken for a while because the
  classes were renamed `segtree` → `Segtree` / `lazy_segtree` →
  `LazySegtree` (commit `fb35e05`) while the delegation target kept the old
  lowercase name.
