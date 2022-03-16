#include <cstdint>
#include <iostream>
#include <vector>
using i32 = std::int32_t;
using i64 = std::int64_t;
struct edge_t
{
    i32 t;
    i32 w;
};
struct result_t
{
    i64 costs;
    i64 bikes;
    i64 nodes;
};
struct data_t
{
    std::vector<std::vector<edge_t>> e;
    std::vector<i32> w;
    i32 k;
    bool input(std::istream &is)
    {
        i32 n, k_;
        if (!(is >> n >> k_))
            return false;
        k = k_;
        w.resize(n);
        e.clear();
        e.resize(n);
        for (auto &ww : w)
            is >> ww;
        for (i32 i = 1; i < n; ++i)
        {
            i32 f, t, w;
            is >> f >> t >> w;
            --f;
            --t;
            e[f].push_back(edge_t{t, w});
            e[t].push_back(edge_t{f, w});
        }
        return true;
    }
    result_t dfs(i32 cur, i32 dad)
    {
        result_t ans{0, w[cur], 1};
        for (auto next : e[cur])
        {
            if (next.t == dad)
                continue;
            auto ret = dfs(next.t, cur);
            ans.costs += std::abs(ret.nodes * k - ret.bikes) * next.w;
            ans.costs += ret.costs;
            ans.bikes += ret.bikes;
            ans.nodes += ret.nodes;
        }
        return ans;
    }
    void start(std::ostream &os)
    {
        auto ret = dfs(e.size() / 2, -1);
        os << ret.costs << '\n';
    }
};
int main()
{
    data_t d;
    while (d.input(std::cin))
    {
        d.start(std::cout);
        std::cout.flush();
    }
}
