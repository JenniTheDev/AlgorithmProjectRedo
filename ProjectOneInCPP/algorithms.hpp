///////////////////////////////////////////////////////////////////////////////
// algorithms.hpp
//
// Definitions for three algorithms:
//
// find_dip
// longest_balanced_span
// telegraph_style
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <optional>
#include <string>
#include <vector>
#include <cctype>
#include <regex>
#include <ctype.h>
#include <algorithm>

namespace algorithms {
	std::vector<int>::const_iterator find_dip(const std::vector<int>& values) {
		if (values.size() < 3) {
			return values.end();
			std::cout << "less then 3, returning" << std::endl;
		}

		std::vector<int>::const_iterator dipIterator;
		std::vector<int>::const_iterator dipStart = values.end();

		for (dipIterator = values.begin(); dipIterator != values.end(); dipIterator++) {
			if (*dipIterator == *(dipIterator + 2) && *dipIterator > *(dipIterator + 1)) {
				dipStart = dipIterator;
			}
		}
		return dipStart;
	}

	class span {
	private:
		std::vector<int>::const_iterator begin_, end_;

	public:

		// Create a span from two iterators. Both iterators must refer to the same
		// vector. begin must come before end.

		span(std::vector<int>::const_iterator begin,
			std::vector<int>::const_iterator end)
			: begin_(begin), end_(end) {
			assert(begin < end);
		}

		// Equality tests, two spans are equal when each of their iterators are equal.
		bool operator== (const span& rhs) const {
			return (begin_ == rhs.begin_) && (end_ == rhs.end_);
		}

		// Accessors.
		const std::vector<int>::const_iterator& begin() const { return begin_; }
		const std::vector<int>::const_iterator& end() const { return end_; }

		// Compute the number of elements in the span.
		size_t size() const { return end_ - begin_; }
	};

	std::optional<span> longest_balanced_span(const std::vector<int>& values) {
		std::optional<span> bestSpan;
		int total;
		std::vector<int>::const_iterator s, e;

		for (int i = 0; i < values.size(); i++) {
			total = values[i];
			for (int j = i + 1; j <= values.size(); j++) {
				if (total == 0) {
					if (bestSpan == std::nullopt || bestSpan->size() <= j - i) {
						s = values.begin() + i;
						e = values.begin() + j;
						bestSpan = span(s, e);
					}
				}
				total += values[j];
			}
		}
		return bestSpan;
	}

	std::string telegraph_style(const std::string& s) {
		std::string outgoing = s;
		//const std::string removePattern = "[^0-9A-Z\\s]"; // replace anything that's not a letter, digit, space with a period
		//std::regex removeRgx (removePattern);

		const std::string punctuationPattern = "[!\\?;]"; // replace punctuation
		std::regex removePunct(punctuationPattern);

		const std::string otherSymbols = "[^0-9a-zA-Z\\s\\.]";
		std::regex removeSymb(otherSymbols);

		const std::string manySpaces = "[' ']{2,}";
		std::regex removeSpaces(manySpaces);

		const std::string lineReturns = "[\\n\\t\\r]";
		std::regex removeLineRe(lineReturns);

		// works dont touch
		std::for_each(outgoing.begin(), outgoing.end(), [](char& c) {
			c = ::toupper(c);
			});

		outgoing = std::regex_replace(outgoing, removePunct, ".");
		outgoing = std::regex_replace(outgoing, removeSymb, "");

		// remove multiple spaces
		outgoing = std::regex_replace(outgoing, removeSpaces, " ");
		outgoing = std::regex_replace(outgoing, removeLineRe, "");

		// Is working
		if (outgoing.length() < 5 || outgoing.substr(outgoing.length() - 5, outgoing.length()) != "STOP.") {
			outgoing.append("STOP.");
		}

		return outgoing;
	}
}