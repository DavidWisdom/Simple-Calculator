#ifndef BIGNUMBER_BIGDECIMAL_H
#define BIGNUMBER_BIGDECIMAL_H
#include "biginteger.h"
#include <algorithm>
namespace BigNumber {
class BigDecimal final : public BigInteger {							// ��ʵ����
public:
	BigDecimal();														// �޲ι��캯��
	BigDecimal(const std::string&, bool = true);						// �ṩ�ַ���std::string->��ʵ��BigDecimal����������bool isSplit��ʾ�ַ������Ƿ��зָ���
	BigDecimal(const BigInteger&, long long = 0);						// �ṩ������BigInteger->��ʵ��BigDecimal����������idx��ʾ����
	BigDecimal(const BigDecimal&);										// �������캯�� ����ǳ����
	BigDecimal(const BigDecimal&, int sgn);								// sgn��ʾBigDecimal�ķ���
	static BigDecimal abs(const BigDecimal&);							// ��̬��Ա����abs�������ʵ��BigDecimal�ľ���ֵ
	std::string round(size_t num = k_digit) const;						// num ΪҪ������С����λ�� round(size_t)Ϊ����С�����λ�Ĳ���
	void pop_zero();													// С��ĩβ���ֵ���0����
	void from_string(const std::string&, bool = true) override;			// �ṩstd::string->BigDecimal����, 
	std::string to_string(bool = true) const override;					// �ṩBigDecimal->std::string������ͬ������bool isSplitҲ�Ǳ�ʾ�ַ������Ƿ��зָ���
	operator std::string() const override;								// �ṩstd::string->BigDecimal����
	bool is_abs_greater(const BigDecimal&) const;						// �жϵ�ǰ��ʵ���ľ���ֵ�Ƿ���ڸ����Ĵ�ʵ��
	bool is_abs_equal(const BigDecimal&) const;							// �жϵ�ǰ��ʵ���ľ���ֵ�Ƿ���ڸ����Ĵ�ʵ��
	bool is_abs_less(const BigDecimal&) const;							// �жϵ�ǰ��ʵ���ľ���ֵ�Ƿ�С�ڸ����Ĵ�ʵ��
	BigDecimal add(const BigDecimal&) const;							// ��ʵ���ӷ�
	BigDecimal sub(const BigDecimal&) const;							// ��ʵ������
	BigDecimal mul(const BigDecimal&) const;							// ��ʵ���˷�
	BigDecimal div(const BigDecimal&) const;							// ��ʵ������
	// ����> == < >= <= != + - * / >> << ����
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
	constexpr static char k_dot = '.';									// С����
	constexpr static long long k_digit = 10LL;							// Ҫ������λ��
	long long exp;														// ����
};
} // namespace BigNumber
#endif // BIGNUMBER_BIGDECIMAL_H
