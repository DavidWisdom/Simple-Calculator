#include "biginteger.h"
namespace BigNumber {
BigInteger::BigInteger() : symbol(k_non_negative) {}

BigInteger::BigInteger(int sgn) : symbol(sgn) {}

BigInteger::BigInteger(const std::string& str, bool isSplit) : symbol(k_non_negative) {
	from_string(str, isSplit);
}

BigInteger::BigInteger(const BigInteger& bigInteger) : symbol(bigInteger.symbol) {
	list = bigInteger.list;
}

BigInteger::BigInteger(const BigInteger& bigInteger, int sgn)  : symbol(sgn) {
	list = bigInteger.list;
}

int BigInteger::sign() const {
	return symbol;
}

size_t BigInteger::size() const {
	return list.size();
}

bool BigInteger::empty() const {
	return list.empty();
}

void BigInteger::clear() {
	list.clear();
}

void BigInteger::push_zero(size_t num) {
	list.push_zero(num);
}

void BigInteger::push_zero(int num) {
	list.push_zero(num);
}

void BigInteger::push_zero(long long num) {
	list.push_zero(num);
}

void BigInteger::clean_zero() {
	list.clean_zero();
	if (list.empty()) {
		symbol = 1; // TODO:理论上来讲，应该不会出现-0的情况，这里代码也许不需要特判
	}
}
void BigInteger::from_string(const std::string& str, bool isUsingDelimiter) {
	if (str.empty()) {
		return;
	}
	long long begin = 0;
	auto end = static_cast<long long>(str.size());
	if (str[0] == '-') {
		symbol = k_negative;
		++begin;
	}
	while (end > begin) {
		const long long start = (begin > end - static_cast<long long>(k_num) ? begin : (end - static_cast<long long>(k_num)));
		int val = 0;
		for (long long i = 0; i < end - start; ++i)
		{
			if (!(str[start + i] >= '0' && str[start + i] <= '9'))
			{
				assert(false);
			}
			val = val * 10 + (str[start + i] - '0');
		}
		list.push_back(val);
		end -= static_cast<long long>(k_num) + isUsingDelimiter;
	}
	// 字符串转为大整数
}

std::string BigInteger::to_string(bool isSplit) const {
	if (list.empty()) {
		return "0";
	}
	std::stringstream output;
	if (!symbol) {
		output << '-';
	}
	for (auto it = list.rbegin(); it != list.rend(); it = it->prev) {
		if (it == list.rbegin()) {
			output << it->data;
		}
		else {
			output << std::setw(k_num) << std::setfill('0') << it->data;
		}
		if (isSplit && it != list.begin()) {
			output << k_split;
		}
	}
	std::string res;
	output >> res;
	return res;
	// 大整数转字符串
}

BigInteger::operator std::string() const {
	return to_string();
}

void BigInteger::shift(int num) {
	list.shift(num);
}

void BigInteger::shift(size_t num) {
	list.shift(num);
}

void BigInteger::shift(long long num) {																// 大整数的移位操作——这里是左移操作
	list.shift(num);
}

bool BigInteger::is_abs_greater(const BigInteger& bigInteger) const {
	if (empty()) {
		return false;
	}																								// 当第一个数为0时返回false
	if (bigInteger.empty()) {
		return true;
	}																								// 当第二个数为0时返回true
	//assert(list.back()); //
	//assert(bigInteger.list.back());
	if (size() != bigInteger.size()) {
		return size() > bigInteger.size();
	}
	auto it1 = list.rbegin();
	auto it2 = bigInteger.list.rbegin();
	for (size_t i = 1; i <= size(); ++i, it1 = it1->prev, it2 = it2->prev) {
		if (it1->data != it2->data) {
			return it1->data > it2->data;
		}
	}
	return false;
}

bool BigInteger::is_abs_equal(const BigInteger& bigInteger) const {									// 判断两个大整数是否相等
	if (empty() && bigInteger.empty()) {
		return true;																				// 如果为空
	}
	if (empty() || bigInteger.empty()) {
		return false;
	}
	//assert(list.back());
	//assert(bigInteger.list.back());
	if (size() != bigInteger.size()) {
		return false;
	}																								// 当大整数的长度不相等时返回false
	auto it1 = list.rbegin();
	auto it2 = bigInteger.list.rbegin();
	for (size_t i = 1; i <= size(); ++i, it1 = it1->prev, it2 = it2->prev) {
		if (it1->data != it2->data) {
			return false;																			// 当大整数数位上的数字不同时返回false
		}
	}
	return true;
}

bool BigInteger::is_abs_less(const BigInteger& bigInteger) const {
	if (bigInteger.empty()) {
		return false;
	}
	if (empty()) {
		return true;
	}
	//assert(list.back());
	//assert(bigInteger.list.back());
	if (size() != bigInteger.size()) {
		return size() < bigInteger.size();
	}																								
	auto it1 = list.rbegin();
	auto it2 = bigInteger.list.rbegin();
	for (size_t i = 1; i <= size(); ++i, it1 = it1->prev, it2 = it2->prev) {
		if (it1->data != it2->data) {
			return it1->data < it2->data;
		}
	}
	return false;
}

BigInteger BigInteger::abs_add(const BigInteger& bigInteger, int sgn) const {
	if (empty()) {
		return BigInteger{ bigInteger, sgn };
	}
	if (bigInteger.empty()) {
		return BigInteger{ *this, sgn };
	}
	BigInteger res(sgn);
	const size_t len = (size() > bigInteger.size() ? size() : bigInteger.size()) + 1;
	res.push_zero(len);
	auto iter = res.list.begin();
	auto it1 = list.begin();
	auto it2 = bigInteger.list.begin();
	for (size_t i = 1; i < len; ++i) {
		const int val1 = (it1 == list.end() ? 0 : it1->data);
		const int val2 = (it2 == bigInteger.list.end() ? 0 : it2->data);
		iter->data += val1 + val2;
		iter->next->data = iter->data / k_base;
		iter->data = iter->data % k_base;
		it1 = (it1 == list.end() ? list.end() : it1->next);
		it2 = (it2 == bigInteger.list.end() ? bigInteger.list.end() : it2->next);
		iter = iter->next;
	}
	res.clean_zero();
	return res;
}

BigInteger BigInteger::abs_sub(const BigInteger& bigInteger, int sgn) const {
	assert(!is_abs_less(bigInteger));
	if (bigInteger.empty()) {
		return { *this, sgn };
	}
	BigInteger res(sgn);
	res.push_zero(size() + 1);
	auto iter = res.list.begin();
	auto it1 = list.begin();
	auto it2 = bigInteger.list.begin();
	for (size_t i = 1; i <= size(); ++i) {
		const int val1 = it1->data;
		const int val2 = (it2 == bigInteger.list.end() ? 0 : it2->data);
		iter->data += val1 - val2;
		while (iter->data < 0) {
			iter->data += k_base;
			iter->next->data -= 1;
		}
		it1 = it1->next;
		it2 = (it2 == bigInteger.list.end() ? bigInteger.list.end() : it2->next);
		iter = iter->next;
	}
	res.clean_zero();
	return res;
}

BigInteger BigInteger::abs_mul(const BigInteger& bigInteger, int sgn) const {
	if (empty() || bigInteger.empty()) {
		return {};
	}
	BigInteger res(sgn);
	auto it1 = list.begin();
	for (size_t i = 1; i <= size(); ++i) {
		auto it2 = bigInteger.list.begin();
		BigInteger temp;
		temp.push_zero(bigInteger.size() + 1);
		auto iter = temp.list.begin();
		for (size_t j = 1; j <= bigInteger.size(); ++j) {
			iter->data += it1->data * it2->data;
			iter->next->data = iter->data / k_base;
			iter->data = iter->data % k_base;
			it2 = it2->next;
			iter = iter->next;
		}
		temp.shift(i - 1);
		temp.clean_zero();
		res = res.abs_add(temp, sgn);
		it1 = it1->next;
	}
	return res;
}

BigInteger BigInteger::abs_div(const BigInteger& bigInteger, int sgn) const {
	BigInteger bigInteger1 = *this;
	BigInteger bigInteger2 = bigInteger;
	BigInteger res(sgn);
	if (bigInteger2.empty()) {
		throw std::out_of_range("Divisor cannot be zero!");
	}
	if (bigInteger1.empty()) {
		return res;
	}
	//assert(bigInteger1.list.back());
	//assert(bigInteger2.list.back());
	if (bigInteger1.is_abs_less(bigInteger2)) {
		return res;
	}
	const size_t num = bigInteger1.size() - bigInteger2.size();
	BigInteger temp;
	bigInteger2.shift(num);
	int val = 0;
	while (!bigInteger1.is_abs_less(bigInteger2)) {
		bigInteger1 = bigInteger1.abs_sub(bigInteger2, sgn);
		++val;
	}
	temp.list.push_back(val);
	temp.shift(num);
	res = res.abs_add(temp, sgn);
	for (size_t cnt = 1; cnt <= num; ++cnt) {
		BigInteger temp2;
		bigInteger2.list.pop_front();
		int val2 = 0;
		while (!bigInteger1.is_abs_less(bigInteger2)) {
			bigInteger1 = bigInteger1.abs_sub(bigInteger2, sgn);
			++val2;
		}
		temp2.list.push_back(val2);
		temp2.shift(num - cnt);
		res = res.abs_add(temp2, sgn);
	}
	return res;
}

BigInteger BigInteger::add(const BigInteger& bigInteger, int sgn) const {
	if (symbol == k_non_negative) {
		if (sgn == k_non_negative) {
			return abs_add(bigInteger);
		}
		return sub(bigInteger, k_non_negative);
	}
	if (sgn == k_non_negative) {
		return bigInteger.sub(*this, k_non_negative);
	}
	return abs_add(bigInteger, k_negative);
}

BigInteger BigInteger::sub(const BigInteger& bigInteger, int sgn) const {
	if (symbol == k_non_negative) {
		if (sgn == k_non_negative) {
			if (!is_abs_less(bigInteger)) {
				return abs_sub(bigInteger);
			}
			return bigInteger.abs_sub(*this, k_negative);
		}
		return abs_add(bigInteger);
	}
	if (sgn == k_non_negative) {
		return abs_add(bigInteger, k_negative);
	}
	return BigInteger(bigInteger, k_non_negative).sub(*this, k_non_negative);
	//TODO: 还有待优化
}

BigInteger BigInteger::mul(const BigInteger& bigInteger) const {
	if (!(sign() ^ bigInteger.sign())) {
		return abs_mul(bigInteger);
	}
	return abs_mul(bigInteger, k_negative);
}

BigInteger BigInteger::div(const BigInteger& bigInteger) const {
	if (!(sign() ^ bigInteger.sign())) {
		return abs_div(bigInteger);
	}
	return abs_div(bigInteger, k_negative);
}

bool operator>(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	if (bigInteger1.sign() > bigInteger2.sign()) {
		return true;
	}
	return bigInteger1.is_abs_greater(bigInteger2);
}

bool operator==(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	return (bigInteger1.sign() == bigInteger2.sign()) && (bigInteger1.is_abs_equal(bigInteger2));
}

bool operator<(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	if (bigInteger1.sign() < bigInteger2.sign()) {
		return true;
	}
	return bigInteger1.is_abs_less(bigInteger2);
}

bool operator>=(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	return !(bigInteger1 < bigInteger2);
}

bool operator<=(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	return !(bigInteger1 > bigInteger2);
}

bool operator!=(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	return !(bigInteger1 == bigInteger2);
}

BigInteger operator+(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	return bigInteger1.add(bigInteger2, bigInteger2.symbol);
}

BigInteger operator-(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	return bigInteger1.sub(bigInteger2, bigInteger2.symbol);
}

BigInteger operator*(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	return bigInteger1.mul(bigInteger2);
}

BigInteger operator/(const BigInteger& bigInteger1, const BigInteger& bigInteger2) {
	return bigInteger1.div(bigInteger2);
}

std::istream& operator>>(std::istream& input, BigInteger& bigInteger) {
	std::string res;
	input >> res;
	bigInteger.from_string(res);
	return input;
}

std::ostream& operator<<(std::ostream& output, const BigInteger& bigInteger) {
	output << bigInteger.to_string();
	return output;
}
} // namespace BigNumber
