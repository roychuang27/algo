#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

template <class K, class Compare = std::less<K>>
using ordered_set = __gnu_pbds::tree<K,
                                     __gnu_pbds::null_type,
                                     Compare,
                                     __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;

struct splitmix_hash { // https://codeforces.com/blog/entry/62393
        size_t operator()(uint64_t x) const {
                static const uint64_t R =
                        std::chrono::steady_clock::now().time_since_epoch().count();
                x += R + 0x9e3779b97f4a7c15;
                x = (x ^ x >> 30) * 0xbf58476d1ce4e5b9;
                x = (x ^ x >> 27) * 0x94d049bb133111eb;
                return x ^ x >> 31;
        }
};
