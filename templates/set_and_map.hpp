#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

using namespace __gnu_pbds;
template <class K>
using ordered_set =
        tree<K, null_type, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

struct splitmix_hash { // https://codeforces.com/blog/entry/62393
        size_t operator()(uint64_t x) const {
                static const uint64_t R =
                        chrono::steady_clock::now().time_since_epoch().count();
                x += R + 0x9e3779b97f4a7c15;
                x = (x ^ x >> 30) * 0xbf58476d1ce4e5b9;
                x = (x ^ x >> 27) * 0x94d049bb133111eb;
                return x ^ x >> 31;
        }
};
