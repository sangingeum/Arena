#pragma once
#include <cstdint>
#include <type_traits>

enum class CollisionFilter : uint16_t {
	all = 0x0001,
	notAllocated2 = 0x0002,
	notAllocated3 = 0x0004,
	notAllocated4 = 0x0008,

	notAllocated5 = 0x0010,
	notAllocated6 = 0x0020,
	notAllocated7 = 0x0040,
	notAllocated8 = 0x0080,

	notAllocated9 = 0x0100,
	notAllocated10 = 0x0200,
	notAllocated11 = 0x0400,
	notAllocated12 = 0x0800,

	notAllocated13 = 0x1000,
	notAllocated14 = 0x2000,
	notAllocated15 = 0x4000,
	notAllocated16 = 0x8000
};


class CollisionFilterHelper
{
public:
	template<class Filter>
	static uint16_t createFilter(Filter category) {
		static_assert(std::is_same<decltype(category), CollisionFilter>::value, "category must be CollisionFilter");
		return static_cast<uint16_t>(category);
	}
	template<class Filter, class... Args>
	static uint16_t createFilter(Filter category, Args... categories) {
		static_assert(std::is_same<decltype(category), CollisionFilter>::value, "category must be CollisionFilter");
		return static_cast<uint16_t>(category) + createFilter(categories...);
	}
};

