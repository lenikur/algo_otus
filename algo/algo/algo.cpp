#include <iostream>
#include <chrono>
#include <array>

using value = std::int64_t;
template <int N> using storage = std::array<value, N>;

namespace tickets
{
   template <int N>
   constexpr storage<(N * 9) + 1> GetCombinations()
   {
      storage<(N * 9) + 1> total{};
      constexpr auto prevTotal = GetCombinations<N - 1>();

      for (int sum = 0; sum <= N * 9; ++sum)
      {
         for (int lastDigit = 0; lastDigit < 10; ++lastDigit)
         {
            if (sum - lastDigit >= 0 && (sum - lastDigit) < prevTotal.size())
            {
               total[sum] += prevTotal[sum - lastDigit];
            }
         }
      }

      return total;
   }

   template <>
   constexpr storage<10> GetCombinations<1>()
   {
      return { 1,1,1,1,1,1,1,1,1,1 };
   }

   template <int N>
   constexpr value GetResult()
   {
      value r{};
      constexpr auto res = GetCombinations<N>();
      for (const auto& val : res)
      {
         r += val * val;
      }

      return r;
   }
}

int main()
{
   constexpr int N = 10;
   const auto start = std::chrono::steady_clock::now();
   constexpr auto totalCombinationCount = tickets::GetResult<N>();
   const auto calculationTime = std::chrono::steady_clock::now() - start;

   std::cout << "N == " << N << "; combinations: " << totalCombinationCount
      << "; calculation time: " << calculationTime;
}
