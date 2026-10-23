#if __cplusplus >= 202302L

#include <concepts>
#include <format>
#include <iostream>
#include <print>
#include <ranges>
#include <string>

#define RED_BOLD "\033[1;31m"
#define WHITE_NORMAL "\033[0m"

template <class T>
concept _R = std::ranges::input_range<T> &&
             !std::convertible_to<T, std::string_view>;
template <class T>
concept _M = _R<T> && (_R<std::ranges::range_reference_t<T> > || requires {
                     requires _R<typename T::key_type> ||
                             _R<typename T::mapped_type>;
             });

std::string _P(const auto &x, std::string p = "") {
        using T = std::remove_cvref_t<decltype(x)>;
        if constexpr (_M<T>) {
                if (!std::ranges::empty(x)) {
                        constexpr bool b = requires {
                                typename T::key_type;
                        };
                        std::string s, q = p + "  ";
                        for (auto &&e : x) {
                                if constexpr (requires {
                                                      typename T::mapped_type;
                                              }) {
                                        s += (s.empty() ? "" : ",\n" + q) +
                                             _P(e.first, q) + ": " +
                                             _P(e.second, q);
                                } else {
                                        s += (s.empty() ? "" : ",\n" + q) +
                                             _P(e, q);
                                }
                        }
                        return (b ? "{\n" : "[\n") + q + s + "\n" + p +
                               (b ? "}" : "]");
                }
        }
        return std::format("{}", x);
}

#define dbg(...)                                                              \
        ([](auto &&...a) {                                                    \
                std::string K[sizeof...(a)];                                  \
                size_t i = 0, j = 0, d = 0, w = 0;                            \
                for (char c : #__VA_ARGS__)                                   \
                        if (c == ',' && !d)                                   \
                                i += i + 1 < sizeof...(a);                    \
                        else if (d += (c == '(' || c == '[' || c == '{') -    \
                                      (c == ')' || c == ']' || c == '}');     \
                                 c && (c != ' ' || K[i].size()))              \
                                w += (K[i] += c).size() > w;                  \
                std::println(stderr, RED_BOLD "#{}" WHITE_NORMAL, __LINE__);  \
                (std::println(stderr, RED_BOLD "{:<{}} | {}" WHITE_NORMAL,    \
                              K[j++], w, _P(a, std::string(w, ' ') + " | ")), \
                 ...);                                                        \
        }(__VA_ARGS__))

#define log(msg)                                                      \
        std::println(stderr, "{}#{}\n{}{}", RED_BOLD, __LINE__, #msg, \
                     WHITE_NORMAL)

#else

#define dbg(...) 39
#define log(...) 39

#endif
