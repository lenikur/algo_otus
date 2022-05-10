#include <iostream>
#include <vector>
#include <chrono>

using value = std::int64_t;
using storage = std::vector<value>;

namespace tickets
{
   storage GetCombinations(int N)
   {
      if (N == 1)
      {
         return storage(10, 1);
      }

      storage total((N * 9) + 1, 0);
      storage prevTotal = GetCombinations(N - 1);

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

   value GetResult(int N)
   {
      value r{};
      const auto res = GetCombinations(N);
      for (const auto& val : res)
      {
         r += val * val;
      }

      return r;
   }
}

int main()
{
   const int N = 10;
   const auto start = std::chrono::steady_clock::now();
   const auto totalCombinationCount = tickets::GetResult(N);
   const auto calculationTime = std::chrono::steady_clock::now() - start;

   std::cout << "N == " << N << "; combinations: " << totalCombinationCount
      << "; calculation time: " << calculationTime;
}
