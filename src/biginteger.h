#ifndef BIGNUMBER_BIGINTEGER_H
#define BIGNUMBER_BIGINTEGER_H
#include "integerlist.h"
#include <iostream>
#include <iomanip>
#include <sstream>
namespace BigNumber {
class BigInteger {																// 大整数类
public:
	// 大正整数符号位 1——非负 0——负
	constexpr static int k_non_negative = 1;
	constexpr static int k_negative = 0;										
	constexpr static int k_num = 3;												// 大整数以3位为1组
	constexpr static int k_base = 1000;											// 大整数的基数
	constexpr static char k_split = ',';										// 大整数的分隔符
	BigInteger();
	BigInteger(int);															// 注意这里int代表的是BigInteger的符号，而不是BigInteger的数值
	BigInteger(const std::string&, bool = true);
	BigInteger(const BigInteger&);												// 拷贝构造函数
	BigInteger(const BigInteger&, int);											
	virtual ~BigInteger() = default;
	int sign() const;															// 返回大整数的符号
	size_t size() const;														// 返回大整数的长度
	bool empty() const;															// 判断大整数是否为空
	void clear();																// 大整数的清空操作
	void push_zero(size_t);
	void push_zero(int);
	void push_zero(long long);
	void clean_zero();
	void shift(size_t);
	void shift(int);
	void shift(long long);
	virtual void from_string(const std::string&, bool = true);					// std::string->BigInteger
	virtual std::string to_string(bool = true) const;							// BigInteger->std::string，bool isSplit表示字符串中是否出现分隔符
	virtual operator std::string() const;										// BigInteger->std::string，默认返回具有分割符的字符串
	// 大正整数的比较操作
	bool is_abs_greater(const BigInteger&) const;								
	bool is_abs_equal(const BigInteger&) const;
	bool is_abs_less(const BigInteger&) const;
	BigInteger abs_add(const BigInteger&, int = k_non_negative) const;			// 大正整数的加法操作
	BigInteger abs_sub(const BigInteger&, int = k_non_negative) const;			// 大正整数的减法操作
	BigInteger abs_mul(const BigInteger&, int = k_non_negative) const;			// 大正整数的乘法操作
	BigInteger abs_div(const BigInteger&, int = k_non_negative) const;			// 大正整数的除法操作
	BigInteger add(const BigInteger&, int = k_non_negative) const;
	BigInteger sub(const BigInteger&, int = k_non_negative) const;
	BigInteger mul(const BigInteger&) const;
	BigInteger div(const BigInteger&) const;
	// 重载> == < >= <= != + - * / >> << 操作
	friend bool operator>(const BigInteger&, const BigInteger&);
	friend bool operator==(const BigInteger&, const BigInteger&);
	friend bool operator<(const BigInteger&, const BigInteger&);
	friend bool operator>=(const BigInteger&, const BigInteger&);
	friend bool operator<=(const BigInteger&, const BigInteger&);
	friend bool operator!=(const BigInteger&, const BigInteger&);
	friend BigInteger operator+(const BigInteger&, const BigInteger&);
	friend BigInteger operator-(const BigInteger&, const BigInteger&);
	friend BigInteger operator*(const BigInteger&, const BigInteger&);
	friend BigInteger operator/(const BigInteger&, const BigInteger&);
	friend std::istream& operator>>(std::istream&, BigInteger&);
	friend std::ostream& operator<<(std::ostream&, const BigInteger&);

protected:
	int symbol;																	// 大正整数的符号
	IntegerList list;															// 大正整数的整数链表
};
} // namespace BigNumber
#endif // BIGNUMBER_BIGINTEGER_H
