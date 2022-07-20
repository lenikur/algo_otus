#include <array>
#include <iostream>
#include <vector>
#include <numeric>
#include <random>

#include <benchmark/benchmark.h>

namespace
{

template<typename T>
void BubbleSort(T& storage)
{
   if (storage.size() <= 1)
   {
      return;
   }

   for (size_t i = 0; i < storage.size() - 1; ++i)
   {
      for (size_t j = 1; j < storage.size() - i; ++j)
      {
         if (storage[j - 1] > storage[j])
         {
            std::swap(storage[j - 1], storage[j]);
         }
      }
   }
}

template<typename T>
void InsertionSort(T& storage)
{
   if (storage.size() <= 1)
   {
      return;
   }

   for (size_t i = 1; i < storage.size(); ++i)
   {
      for (size_t j = i; j > 0; --j)
      {
         if (storage[j - 1] > storage[j])
         {
            std::swap(storage[j - 1], storage[j]);
         }
         else
         {
            break;
         }
      }
   }
}

template <typename T>
void ShellSort(T& storage)
{
   for (size_t gap = storage.size() / 2; gap > 1; gap /= 2)
   {
      for (size_t i = 0; i + gap < storage.size(); i += gap)
      {
         if (storage[i] > storage[i + gap])
         {
            std::swap(storage[i], storage[i + gap]);
         }
      }
   }

   InsertionSort(storage);
}

template <typename T>
concept Container = requires(T t) 
{
   { t.empty() } -> std::convertible_to<bool>;
};

template <typename T>
requires Container<T>
std::ostream& operator<<(std::ostream& stream, const T& storage) 
{
   for (const auto& item : storage)
   {
      std::cout << item << "; ";
   }

   return stream;
}

template <typename T>
void Shuffle(T& storage)
{
   std::shuffle(begin(storage), end(storage), std::default_random_engine{});
//   std::cout << "shuffled: " << storage << std::endl;
}

}

class SortingFixture : public benchmark::Fixture 
{
public:
   void SetUp(const ::benchmark::State& state) 
   {
      _storage = std::vector<int>(state.range(0));
      std::iota(begin(_storage), end(_storage), 0);
      Shuffle(_storage);
   }

   void TearDown(const ::benchmark::State& state) 
   {
      _storage.clear();
   }

   std::vector<int> _storage;
};

BENCHMARK_DEFINE_F(SortingFixture, Insertion)(benchmark::State& state)
{
   for (auto _ : state)
   {
      InsertionSort(_storage);
   }
}

BENCHMARK_DEFINE_F(SortingFixture, Bubble)(benchmark::State& state) 
{
   for (auto _ : state)
   {
      BubbleSort(_storage);
   }
}

BENCHMARK_DEFINE_F(SortingFixture, Shell)(benchmark::State& state)
{
   for (auto _ : state)
   {
      ShellSort(_storage);
   }
}

static constexpr std::array itemsCount{ 100, 1000, 10'000 };

BENCHMARK_REGISTER_F(SortingFixture, Bubble)
   ->Arg(itemsCount[0])
   ->Arg(itemsCount[1])
   ->Arg(itemsCount[2]);

BENCHMARK_REGISTER_F(SortingFixture, Insertion)
   ->Arg(itemsCount[0])
   ->Arg(itemsCount[1])
   ->Arg(itemsCount[2]);

BENCHMARK_REGISTER_F(SortingFixture, Shell)
   ->Arg(itemsCount[0])
   ->Arg(itemsCount[1])
   ->Arg(itemsCount[2]);

BENCHMARK_MAIN();
