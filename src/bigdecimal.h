#ifndef BIGNUMBER_BIGDECIMAL_H
#define BIGNUMBER_BIGDECIMAL_H
#include "biginteger.h"
#include <algorithm>
namespace BigNumber {
class BigDecimal final : public BigInteger {							// 大实数类
public:
	BigDecimal();														// 无参构造函数
	BigDecimal(const std::string&, bool = true);						// 提供字符串std::string->大实数BigDecimal操作，其中bool isSplit表示字符串中是否有分隔符
	BigDecimal(const BigInteger&, long long = 0);						// 提供大整数BigInteger->大实数BigDecimal操作，其中idx表示阶码
	BigDecimal(const BigDecimal&);										// 拷贝构造函数 避免浅拷贝
	BigDecimal(const BigDecimal&, int sgn);								// sgn表示BigDecimal的符号
	static BigDecimal abs(const BigDecimal&);							// 静态成员函数abs，计算大实数BigDecimal的绝对值
	std::string round(size_t num = k_digit) const;						// num 为要保留的小数的位数 round(size_t)为保留小数点后几位的操作
	void pop_zero();													// 小数末尾部分的清0操作
	void from_string(const std::string&, bool = true) override;			// 提供std::string->BigDecimal操作, 
	std::string to_string(bool = true) const override;					// 提供BigDecimal->std::string操作，同样这里bool isSplit也是表示字符串中是否有分隔符
	operator std::string() const override;								// 提供std::string->BigDecimal操作
	bool is_abs_greater(const BigDecimal&) const;						// 判断当前大实数的绝对值是否大于给定的大实数
	bool is_abs_equal(const BigDecimal&) const;							// 判断当前大实数的绝对值是否等于给定的大实数
	bool is_abs_less(const BigDecimal&) const;							// 判断当前大实数的绝对值是否小于给定的大实数
	BigDecimal add(const BigDecimal&) const;							// 大实数加法
	BigDecimal sub(const BigDecimal&) const;							// 大实数减法
	BigDecimal mul(const BigDecimal&) const;							// 大实数乘法
	BigDecimal div(const BigDecimal&) const;							// 大实数除法
	// 重载> == < >= <= != + - * / >> << 操作
	friend bool operator>(const BigDecimal&, const BigDecimal&);		
	friend bool operator==(const BigDecimal&, const BigDecimal&);
	friend bool operator<(const BigDecimal&, const BigDecimal&);
	friend bool operator>=(const BigDecimal&, const BigDecimal&);
	friend bool operator<=(const BigDecimal&, const BigDecimal&);
	friend bool operator!=(const BigDecimal&, const BigDecimal&);
	friend BigDecimal operator+(const BigDecimal&, const BigDecimal&);
	friend BigDecimal operator-(const BigDecimal&, const BigDecimal&);
	friend BigDecimal operator*(const BigDecimal&, const BigDecimal&);
	friend BigDecimal operator/(const BigDecimal&, const BigDecimal&);
	friend std::istream& operator>>(std::istream&, BigDecimal&);
	friend std::ostream& operator<<(std::ostream&, const BigDecimal&);

protected:
	constexpr static char k_dot = '.';									// 小数点
	constexpr static long long k_digit = 10LL;							// 要保留的位数
	long long exp;														// 阶码
};
} // namespace BigNumber
#endif // BIGNUMBER_BIGDECIMAL_H
