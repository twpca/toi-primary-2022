#include <algorithm>
#include <iostream>
#include <random>
template <class DIST>
std::vector<int> random_add(int n, int sum, std::mt19937 &rng, DIST dist)
{
    std::vector<int> a(n);
    for (int i = 0; i < sum; ++i)
    {
        a.at(dist(rng))++;
    }
    return a;
}

std::vector<int> gen_weight(int n, int k, std::mt19937 &rng,
                            std::string weight_type)
{
    if (weight_type == "large_one")
    {
        auto dist = std::uniform_int_distribution<int>(0, n - 1);
        auto res = random_add(n, n * k, rng, dist);
        int sum = 0;
        for (auto &x : res)
        {
            if (x >= k)
            {
                sum += x - k;
                x = k;
            }
        }
        res[dist(rng)] += sum;
        return res;
    }
    else if (weight_type == "random_uniform")
    {
        return random_add(n, n * k, rng,
                          std::uniform_int_distribution<int>(0, n - 1));
    }
    else if (weight_type == "random_normal")
    {
        return random_add(n, n * k, rng,
                          [n](std::mt19937 &r)
                          {
                              auto ndist =
                                  std::normal_distribution<double>(0, n);

                              while (true)
                              {
                                  auto x = std::abs(ndist(r));
                                  int t = std::round(x);
                                  if (t < n)
                                  {
                                      return t;
                                  }
                              }
                          });
    }
    else
    {
        throw std::invalid_argument("weight_type: " + weight_type);
    }
}

auto gen_tree(int n, std::mt19937 &rng, std::string tree_type)
{
    std::vector<std::pair<int, int>> e;
    if (n <= 0)
        return e;
    if (tree_type == "line")
    {
        int step;
        if (n < 4)
        {
            step = 1;
        }
        else if (n < 2048)
        {
            step = 2;
        }
        else
        {
            step = 1025;
        }
        while (true)
        {
            if (std::gcd(step, n) == 1)
                break;
            ++step;
        }
        for (int i = 1; i < n; ++i)
        {
            e.push_back({i, (i + step) % n});
        }
    }
    else if (tree_type == "star")
    {
        int c = std::uniform_int_distribution<int>(0, n - 1)(rng);
        e.resize(n);
        for (int i = 0; i < n; ++i)
        {
            e[i] = {i, c};
        }
        e[c] = e.back();
        e.pop_back();
    }
    else if (tree_type == "random")
    {
        e.resize(n);
        for (int i = 1; i < n; ++i)
        {
            e[i] = {i, std::uniform_int_distribution<int>(0, i - 1)(rng)};
        }
        e.front() = e.back();
        e.pop_back();
    }
    else
    {
        throw std::invalid_argument("tree_type: " + tree_type);
    }
    for (auto &ee : e)
    {
        if (rng() % 2)
        {
            std::swap(ee.first, ee.second);
        }
    }
    std::shuffle(e.begin(), e.end(), rng);
    return e;
}

void gen(int argc, char *argv[], std::ostream &os)
{
    int seed = std::atoi(argv[1]);
    int n_min = std::atoi(argv[2]);
    int n_max = std::atoi(argv[3]);
    int k_min = std::atoi(argv[4]);
    int k_max = std::atoi(argv[5]);
    int d_min = std::atoi(argv[6]);
    int d_max = std::atoi(argv[7]);
    auto tree_type = std::string(argv[8]);
    auto weight_type = std::string(argv[9]);
    std::mt19937 rng(seed);
    int n = std::uniform_int_distribution<int>(n_min, n_max)(rng);
    int k = std::uniform_int_distribution<int>(k_min, k_max)(rng);
    os << n << ' ' << k << '\n';
    {
        auto w = gen_weight(n, k, rng, weight_type);
        for (int i = 0; i < n; ++i)
        {
            os << w[i] << (i == n - 1 ? '\n' : ' ');
        }
    }
    {
        auto tree = gen_tree(n, rng, tree_type);
        auto dist = std::uniform_int_distribution<int>(d_min, d_max);
        for (auto e : tree)
        {
            os << e.first + 1 << ' ' << e.second + 1 << ' ' << dist(rng)
               << '\n';
        }
    }
}

int main(int argc, char *argv[]) { gen(argc, argv, std::cout); }