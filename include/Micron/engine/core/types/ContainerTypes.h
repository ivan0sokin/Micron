#ifndef _MICRON_CORE_CONTAINER_MATHTYPES_H
#define _MICRON_CORE_CONTAINER_MATHTYPES_H

#include <vector>
#include <list>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <bitset>
#include <span>
#include <optional>
#include <string>
#include <string_view>

#include <concepts>

#include <fmt/core.h>

#include <boost/lexical_cast.hpp>

#include "BasicTypes.h"

namespace Micron
{
	template <typename T> using Vector = std::vector<T>;
	template <typename T> using List = std::list<T>;
	template <typename T, USize S> using Array = std::array<T, S>;
	template <typename T> using Deque = std::deque<T>;
	template <typename T> using Queue = std::queue<T>;
	template <typename T> using Stack = std::stack<T>;
	template <typename KT, typename T> using HashMap = std::map<KT, T>;
	template <typename KT, typename T> using UnorderedHashMap = std::unordered_map<KT, T>;
	template <typename T> using HashSet = std::set<T>;
	template <typename T> using UnorderedHashSet = std::unordered_set<T>;
	template <USize S> using BitSet = std::bitset<S>;
	template <typename T, USize Extent> using Span = std::span<T, Extent>;
	template <typename T> using Optional = std::optional<T>;

	using MultibyteString = std::string;
	using MultibyteStringView = std::string_view;

	using UnicodeString = std::wstring;
	using UnicodeStringView = std::wstring_view;

	static Array<MultibyteString, 2> const boolAsString = { "False", "True" };
	inline MultibyteString ToString(Bool value) noexcept { return boolAsString[static_cast<USize>(value)]; }

	template <std::integral Integral> inline MultibyteString ToString(Integral value) noexcept { return fmt::format("{}", value); }
	template <std::floating_point FloatingPoint> inline MultibyteString ToString(FloatingPoint value) noexcept { return fmt::format("{}", value); }

	template <std::integral Integral> inline Integral FromString(MultibyteString const& string) noexcept { return boost::lexical_cast<Integral>(string); }
	template <std::floating_point FloatingPoint> inline FloatingPoint FromString(MultibyteString const& string) noexcept { return boost::lexical_cast<FloatingPoint>(string); }
}

#endif