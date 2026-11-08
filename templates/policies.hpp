#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template <class Key>
using ordered_set = __gnu_pbds::tree<Key,
                                     __gnu_pbds::null_type,
                                     std::less<Key>,
                                     __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;

template <class Key, class Val>
using ordered_map = __gnu_pbds::tree<Key,
                                     Val,
                                     std::less<Key>,
                                     __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;

// https://codeforces.com/blog/entry/62393
struct custom_hash {
        static uint64_t splitmix64(uint64_t x) {
                x += 0x9e3779b97f4a7c15;
                x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
                x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
                return x ^ (x >> 31);
        }

        size_t operator()(uint64_t x) const {
                static const uint64_t FIXED_RANDOM =
                        chrono::steady_clock::now().time_since_epoch().count();
                return splitmix64(x + FIXED_RANDOM);
        }
};

template <class Key, class Val, class Hash = std::hash<Key>>
using hashmap = __gnu_pbds::gp_hash_table<Key, Val, Hash>;
