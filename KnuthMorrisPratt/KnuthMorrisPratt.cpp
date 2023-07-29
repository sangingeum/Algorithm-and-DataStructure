#include "KnuthMorrisPratt.hpp"

int KnuthMorrisPratt::findString(const std::string& text, const std::string& pattern) {
	int t = 0; // current text index
	int p = 0; // current pattern index
	int tSize = text.size(), pSize = pattern.size();
	auto skip = preprocess(pattern);
	while (t < tSize) {
		if (pattern[p] == text[t]) {
			p++; t++;
			if (p == pSize) {
				// Pattern found
				return t - p;
			}
		}
		else {
			p = skip[p];
			if (p < 0) {
				t++; p++;
			}
		}
	}
	// Pattern not found
	return -1;
}

std::vector<int> KnuthMorrisPratt::findStrings(const std::string& text, const std::string& pattern) {
	int t = 0; // current text index
	int p = 0; // current pattern index
	int tSize = text.size(), pSize = pattern.size();
	std::vector<int> found;
	auto skip = preprocess(pattern);
	while (t < tSize) {
		if (pattern[p] == text[t]) {
			p++; t++;
			if (p == pSize) {
				// Pattern found
				found.push_back(t - p);
				// Reset
				p = skip[p];
			}
		}
		else {
			p = skip[p];
			if (p < 0) {
				t++; p++;
			}
		}
	}
	return found;
}

std::vector<int> KnuthMorrisPratt::preprocess(const std::string& pattern) {
	size_t size = pattern.size();
	std::vector<int> skip(size + 1);
	skip[0] = -1;
	skip[1] = 0;
	size_t i = 1, prefixLen = 0;
	while (i < size) {
		if (pattern[i] == pattern[prefixLen]) {
			skip[++i] = ++prefixLen;
		}
		else if (prefixLen > 0) {
			prefixLen = skip[prefixLen];
		}
		else {
			skip[++i] = 0;
		}
	}
	return skip;
}