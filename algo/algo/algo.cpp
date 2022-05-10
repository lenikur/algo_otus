#include <iostream>
#include <chrono>
#include <array>

// Happy tickets combinations count calculation algorithm;
// Complexity: O(N^2 * 100)
// Compilation time calculation (0ns in runtime)

using value = std::int64_t;
template <int N> using storage = std::array<value, N>;

namespace tickets
{
   template <int N>
   consteval storage<(N * 9) + 1> GetCombinations()
   {
      storage<(N * 9) + 1> total{};
      auto prevTotal = GetCombinations<N - 1>();

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
   consteval storage<10> GetCombinations<1>()
   {
      return { 1,1,1,1,1,1,1,1,1,1 };
   }

   template <int N>
   consteval value GetResult()
   {
      value r{};
      auto res = GetCombinations<N>();
      for (const auto& val : res)
      {
         r += val * val;
      }

      return r;
   }

   template <>
   consteval value GetResult<0>()
   {
      return 0;
   }
}

// correct results (for CalculateAndTesting)
constexpr storage<11> combinations =
{ 0, 10, 670, 55252 , 4816030, 432457640, 39581170420, 3671331273480, 343900019857310, 32458256583753952, 3081918923741896840 };

template <int N>
consteval value CalculateAndTest()
{
   static_assert(combinations[N] == tickets::GetResult<N>());
   return tickets::GetResult<N>();
}

consteval storage<11> CalculateAll()
{
   std::array<value, 11> results;

   results[0] = CalculateAndTest<0>();
   results[1] = CalculateAndTest<1>();
   results[2] = CalculateAndTest<2>();
   results[3] = CalculateAndTest<3>();
   results[4] = CalculateAndTest<4>();
   results[5] = CalculateAndTest<5>();
   results[6] = CalculateAndTest<6>();
   results[7] = CalculateAndTest<7>();
   results[8] = CalculateAndTest<8>();
   results[9] = CalculateAndTest<9>();
   results[10] = CalculateAndTest<10>();

   return results;
}

int main()
{
   const auto start = std::chrono::steady_clock::now();
   constexpr storage<11> results = CalculateAll();
   const auto calculationTime = std::chrono::steady_clock::now() - start;

   int i{};
   for (const auto& val : results)
   {
      std::cout << "N == " << i << (i > 9 ? "; " : ";  ") << "combinations: " << val << std::endl;
      ++i;
   }

   std::cout << "\nTotal calculation time: " << calculationTime;
   std::cout << "\nNo shock, please.. it is a compile time calculation";
}
