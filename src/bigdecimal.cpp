#include "bigdecimal.h"
namespace BigNumber {
BigDecimal::BigDecimal() : exp(0) {}

BigDecimal::BigDecimal(const std::string& str, bool isUsingDelimiter) : exp(0) {
	from_string(str, isUsingDelimiter);
}

BigDecimal::BigDecimal(const BigInteger& bigInteger, const long long idx) : BigInteger(bigInteger), exp(idx) {}

BigDecimal::BigDecimal(const BigDecimal& bigDecimal) : BigInteger(bigDecimal), exp(bigDecimal.exp) {}

BigDecimal::BigDecimal(const BigDecimal& bigDecimal, int sgn) : exp(bigDecimal.exp) {
	symbol = sgn;
	list = bigDecimal.list;
}

BigDecimal BigDecimal::abs(const BigDecimal& bigDecimal) {
	if (bigDecimal.empty()) {
		return {};											// 当大实数为空时，返回0
	}
	return { bigDecimal, k_non_negative };				// 当大实数不为空时，
}

std::string BigDecimal::round(size_t num) const {
	std::string tmp = *this;
	size_t pos = tmp.find(k_dot);							// 寻找当前大实数小数点的位置
	if (pos != std::string::npos) {								// 如果大实数小数点的位置不为空
		if (num == 0) {											// 当num为0时，表示只保留大实数的整数部分
			return tmp.substr(0, pos);				
		}
		size_t end = tmp.size() - 1;							
		if (end - pos <= num) {
			return tmp;
		}
		return tmp.substr(0, pos + num + 1);
	}
	return tmp;
}

void BigDecimal::pop_zero() {
	list.pop_zero(exp);
}

void BigDecimal::from_string(const std::string& str, const bool isUsingDelimiter) {
	size_t begin = 0;
	size_t pos = str.find(k_dot);
	if (pos != std::string::npos)
	{
		const size_t tmp = pos;
		int sgn = k_non_negative;
		if (str[0] == '-') {
			sgn = k_negative;
			++begin;
			--pos;
		}
		const std::string integer = str.substr(begin, pos);
		BigInteger::from_string(integer);
		std::string decimal = str.substr(tmp + 1);
		if (decimal.size() % 3 != 0) {
			while (decimal.size() % 3) {
				decimal.push_back('0');
			}
		}
		BigInteger bigInteger;
		bigInteger.from_string(decimal, false);
		shift(decimal.size() / 3);
		const BigInteger res = abs_add(bigInteger, sgn);
		*this = BigDecimal(res, -(static_cast<long long>(decimal.size() / 3)));
	}
	else {
		BigInteger::from_string(str, isUsingDelimiter);
		exp = 0;
	}
}

std::string BigDecimal::to_string(bool isSplit) const {
	if (list.empty()) {
		return "0";
	}
	if (exp < 0) {
		std::string temp = BigInteger::to_string(false);
		const long long offset = std::max(0ll, (long long)(temp.size()) + exp * k_num);
		std::string mantissa = temp.substr(offset);
		if (size_t(-exp) >= list.size()) {
			mantissa = std::string(-exp * k_num - mantissa.size(), '0') + mantissa;
		}
		while (mantissa[mantissa.size() - 1] == '0') {
			mantissa.erase(mantissa.size() - 1);
		}
		return BigInteger(temp.substr(0, offset), false).to_string(isSplit) + k_dot + mantissa;
	}
	return BigInteger::to_string(isSplit);
}

BigDecimal::operator std::string() const {
	return to_string();
}

bool BigDecimal::is_abs_greater(const BigDecimal& bigDecimal) const {
	BigDecimal bigDecimal1 = *this;
	BigDecimal bigDecimal2 = bigDecimal;
	const long long len = bigDecimal1.exp < bigDecimal2.exp ? bigDecimal1.exp : bigDecimal2.exp;
	bigDecimal1.shift(bigDecimal1.exp - len);
	bigDecimal2.shift(bigDecimal2.exp - len);
	return bigDecimal1.BigInteger::is_abs_greater(bigDecimal2);
}


bool BigDecimal::is_abs_equal(const BigDecimal& bigDecimal) const {
	BigDecimal bigDecimal1 = *this;
	BigDecimal bigDecimal2 = bigDecimal;
	const long long len = bigDecimal1.exp < bigDecimal2.exp ? bigDecimal1.exp : bigDecimal2.exp;
	bigDecimal1.shift(bigDecimal1.exp - len);
	bigDecimal2.shift(bigDecimal2.exp - len);
	return bigDecimal1.BigInteger::is_abs_equal(bigDecimal2);
}

bool BigDecimal::is_abs_less(const BigDecimal& bigDecimal) const {
	BigDecimal bigDecimal1 = *this;
	BigDecimal bigDecimal2 = bigDecimal;
	const long long len = bigDecimal1.exp < bigDecimal2.exp ? bigDecimal1.exp : bigDecimal2.exp;
	bigDecimal1.shift(bigDecimal1.exp - len);
	bigDecimal2.shift(bigDecimal2.exp - len);
	return bigDecimal1.BigInteger::is_abs_less(bigDecimal2);
}

BigDecimal BigDecimal::add(const BigDecimal& bigDecimal) const {
	BigDecimal bigDecimal1 = *this;
	BigDecimal bigDecimal2 = bigDecimal;
	const long long len = bigDecimal1.exp < bigDecimal2.exp ? bigDecimal1.exp : bigDecimal2.exp;
	bigDecimal1.list.shift(bigDecimal1.exp - len);
	bigDecimal2.list.shift(bigDecimal2.exp - len);
	BigDecimal res(bigDecimal1.BigInteger::add(bigDecimal2, bigDecimal2.symbol), len);
	res.pop_zero();
	return res;
}

BigDecimal BigDecimal::sub(const BigDecimal& bigDecimal) const {
	BigDecimal bigDecimal1 = *this;
	BigDecimal bigDecimal2 = bigDecimal;
	const long long len = bigDecimal1.exp < bigDecimal2.exp ? bigDecimal1.exp : bigDecimal2.exp;
	bigDecimal1.list.shift(bigDecimal1.exp - len);
	bigDecimal2.list.shift(bigDecimal2.exp - len);
	BigDecimal res(bigDecimal1.BigInteger::sub(bigDecimal2, bigDecimal2.symbol), len);
	res.pop_zero();
	return res;
}

BigDecimal BigDecimal::mul(const BigDecimal& bigDecimal) const {
	BigDecimal res(BigInteger::mul(bigDecimal), exp + bigDecimal.exp);
	res.pop_zero();
	return res;
}

BigDecimal BigDecimal::div(const BigDecimal& bigDecimal) const {
	if (bigDecimal == BigDecimal("0"))
	{
		throw std::out_of_range("Divisor cannot be zero!");
	}
	if (*this == BigDecimal("0"))
	{
		return BigDecimal("0");
	}
	BigDecimal bigDecimal1 = *this;
	const BigDecimal& bigDecimal2 = bigDecimal;
	const long long len = bigDecimal1.exp - bigDecimal2.exp;
	if (len > k_digit) {
		BigDecimal res(BigInteger::div(bigDecimal), exp - bigDecimal.exp);
		res.pop_zero();
		return res;
	}
	bigDecimal1.shift(k_digit - len);
	BigDecimal res(bigDecimal1.BigInteger::div(bigDecimal2), bigDecimal1.exp - k_digit + len - bigDecimal2.exp);
	res.pop_zero();
	return res;
}

bool operator>(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return bigDecimal1.is_abs_greater(bigDecimal2);
}

bool operator==(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return bigDecimal1.is_abs_equal(bigDecimal2);
}

bool operator<(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return bigDecimal1.is_abs_less(bigDecimal2);
}

bool operator>=(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return !(bigDecimal1 < bigDecimal2);
}

bool operator<=(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return !(bigDecimal1 > bigDecimal2);
}

bool operator!=(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return !(bigDecimal1 == bigDecimal2);
}

BigDecimal operator+(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return bigDecimal1.add(bigDecimal2);
}

BigDecimal operator-(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return bigDecimal1.sub(bigDecimal2);
}

BigDecimal operator*(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return bigDecimal1.mul(bigDecimal2);
}

BigDecimal operator/(const BigDecimal& bigDecimal1, const BigDecimal& bigDecimal2) {
	return bigDecimal1.div(bigDecimal2);
}

std::istream& operator>>(std::istream& input, BigDecimal& bigDecimal) {
	std::string res;
	input >> res;
	bigDecimal.from_string(res);
	return input;
}

std::ostream& operator<<(std::ostream& output, const BigDecimal& bigDecimal) {
	output << bigDecimal.to_string();
	return output;
}
} //namespace BigNumber
