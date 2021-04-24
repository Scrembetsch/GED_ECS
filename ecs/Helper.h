#pragma once

#include <vector>
#include <algorithm>

namespace Helper
{
	template<typename D, typename T>
	bool find(const std::vector<D>& vec, const T& item)
	{
		return std::find(vec.begin(), vec.end(), item) != vec.end();
	}
}
