#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
using i32 = std::int32_t;
using i64 = std::int64_t;
struct self_explode_int32_t
{
    int64_t value;
    self_explode_int32_t(int32_t x) : value(x) {}
    auto &operator+=(const self_explode_int32_t &other)
    {
        value += other.value;
        assert(-0x8000'0000LL <= value && value <= 0x7fff'ffff);
        return value;
    }
    auto operator*(const self_explode_int32_t &other) -> self_explode_int32_t
    {
        auto new_value = value * other.value;
        assert(-0x8000'0000LL <= new_value && new_value <= 0x7fff'ffff);
        return new_value;
    }
    auto operator-(const self_explode_int32_t &other) -> self_explode_int32_t
    {
        auto new_value = value - other.value;
        assert(-0x8000'0000LL <= new_value && new_value <= 0x7fff'ffff);
        return new_value;
    }
    auto abs() const -> self_explode_int32_t
    {
        auto new_value = value < 0 ? -value : value;
        assert(-0x8000'0000LL <= new_value && new_value <= 0x7fff'ffff);
        return new_value;
    }
};
struct edge_t
{
    i32 t;
    i32 w;
};
struct result_t
{
    self_explode_int32_t costs;
    self_explode_int32_t bikes;
    self_explode_int32_t nodes;
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
            ans.costs += (ret.nodes * k - ret.bikes).abs() * next.w;
            ans.costs += ret.costs;
            ans.bikes += ret.bikes;
            ans.nodes += ret.nodes;
        }
        return ans;
    }
    void start(std::ostream &os)
    {
        auto ret = dfs(e.size() / 2, -1);
        os << ret.costs.value << '\n';
    }
};
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    data_t d;
    while (d.input(std::cin))
    {
        d.start(std::cout);
        std::cout.flush();
    }
}
