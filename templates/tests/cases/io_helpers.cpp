// I reads every argument, O prints them space separated and ends the line.
--- code
        istringstream in("3 1 2 3\nend\n");
        cin.rdbuf(in.rdbuf());
        int n;
        I(n);
        vector<int> v(n);
        I(v);
        string s;
        I(s);
        O(n, v.size(), v[2], s);
        O(v[0] + v[1]);
        O();
        O("end");
--- out
3 3 3 end
3

end
