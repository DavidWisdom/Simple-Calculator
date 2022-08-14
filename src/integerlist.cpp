#include "integerlist.h"
namespace BigNumber {
IntegerList::IntegerList() {}

IntegerList::IntegerList(const IntegerList& list) : List<int>(list) {}


IntegerList& IntegerList::operator=(const IntegerList& list) {
	if (this != &list) {
		clear();
		copy(list.begin(), list.len);
	}
	return *this;
}

IntegerList::~IntegerList() {}

void IntegerList::push_zero(size_t num) {
	while (num--) {
		push_back(0);
	}
}

void IntegerList::push_zero(int num) {
	if (num <= 0) {
		return;
	}
	while (num--) {
		push_back(0);
	}
}

void IntegerList::push_zero(long long num) {
	if (num <= 0) {
		return;
	}
	while (num--) {
		push_back(0);
	}
}

void IntegerList::pop_zero(int& idx) {
	if (empty() || idx >= 0) {
		return;
	}
	while (!(empty() || front() || idx >= 0)) {
		pop_front();
		++idx;
	}
}

void IntegerList::pop_zero(long long& idx) {
	if (empty() || idx >= 0) {
		return;
	}
	while (!(empty() || idx >= 0 || front() != 0)) {
		pop_front();
		++idx;
	}
}

void IntegerList::clean_zero() {
	while (!(empty() || back())) {
		pop_back();
	}
}

void IntegerList::shift(size_t num) {
	while (num--) {
		push_front(0);
	}
}

void IntegerList::shift(int num) {
	if (num <= 0) {
		return;
	}
	while (num--) {
		push_front(0);
	}
}

void IntegerList::shift(long long num) {
	if (num <= 0) {
		return;
	}
	while (num--) {
		push_front(0);
	}
}

} // namespace BigNumber
