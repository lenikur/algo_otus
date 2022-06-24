#include <iostream>
#include <vector>
#include <numeric>
#include <random>

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
   std::cout << "shuffled: " << storage << std::endl;
}

}

int main()
{
   std::vector<int> storage(50);
   std::iota(begin(storage), end(storage), 0);
   std::cout << "original: " << storage << std::endl << std::endl;

   Shuffle(storage);
   BubbleSort(storage);
   std::cout << "Bubble sort: " << storage << std::endl << std::endl;

   Shuffle(storage);
   InsertionSort(storage);
   std::cout << "Insertion sort: " << storage << std::endl << std::endl;

   Shuffle(storage);
   ShellSort(storage);
   std::cout << "Shell sort: " << storage << std::endl;
}
