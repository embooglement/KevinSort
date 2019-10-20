/*
 * kevin_sort.h
 *
 */

#ifndef _KEVIN_SORT_H_
#define _KEVIN_SORT_H_

#include <algorithm>
#include <iterator>
#include <thread>
#include <random>
#include <vector>
#include <utility>
#include <chrono>
#include <mutex>

class debug_duration : std::chrono::milliseconds
{
public:
	constexpr debug_duration(rep value) : std::chrono::milliseconds(value) { }
	static constexpr debug_duration min() { return debug_duration(1); }
	static constexpr debug_duration max() { return debug_duration(100); }
};

template <typename Duration, typename ForwardIter>
void kevin_sort(ForwardIter begin_iter, ForwardIter end_iter)
{
	typedef Duration duration;
	
	auto time = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine engine(static_cast<std::default_random_engine::result_type>(time));
	std::uniform_int_distribution<typename duration::rep> distribution(duration::zero().count(), duration::max().count());

	while (!std::is_sorted(begin_iter, end_iter))
	{
		std::vector<std::thread> threads;
		std::vector<typename std::iterator_traits<ForwardIter>::value_type> temp;
		std::mutex m;
		
		for (auto it = begin_iter; it != end_iter; ++it)
		{
			threads.emplace_back(
				[=, &temp, &distribution, &m]() mutable {
					auto ms = distribution(engine);
					std::this_thread::sleep_for(duration(ms));
					std::lock_guard<std::mutex> lock(m);
					temp.push_back(*it);
				}
			);
		}
		
		std::for_each(std::begin(threads), std::end(threads), [](std::thread& t) { t.join(); });
		std::move(std::begin(temp), std::end(temp), begin_iter);
	}
};

template <typename ForwardIter>
void kevin_sort(ForwardIter begin_iter, ForwardIter end_iter)
{
	kevin_sort<std::chrono::milliseconds, ForwardIter>(begin_iter, end_iter);
};

#endif
