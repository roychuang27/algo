// ordered_set keeps order statistics, splitmix_hash plugs into unordered_map.
// headers: set_and_map.hpp
--- code
        ordered_set<int> s;
        for (int x : {5, 1, 3, 1, 3}) {
                s.insert(x);
        }
        cout << s.size() << ' ' << *s.find_by_order(1) << ' ' << s.order_of_key(3)
             << '\n';
        unordered_map<long long, int, splitmix_hash> h;
        h[1] = 2;
        cout << h[1] << ' ' << h.contains(2) << '\n';
--- out
3 3 1
2 0
