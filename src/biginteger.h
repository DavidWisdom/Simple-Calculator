#ifndef BIGNUMBER_BIGINTEGER_H
#define BIGNUMBER_BIGINTEGER_H
#include "integerlist.h"
#include <iostream>
#include <iomanip>
#include <sstream>
namespace BigNumber {
class BigInteger {																// ��������
public:
	// ������������λ 1�����Ǹ� 0������
	constexpr static int k_non_negative = 1;
	constexpr static int k_negative = 0;										
	constexpr static int k_num = 3;												// ��������3λΪ1��
	constexpr static int k_base = 1000;											// �������Ļ���
	constexpr static char k_split = ',';										// �������ķָ���
	BigInteger();
	BigInteger(int);															// ע������int�������BigInteger�ķ��ţ�������BigInteger����ֵ
	BigInteger(const std::string&, bool = true);
	BigInteger(const BigInteger&);												// �������캯��
	BigInteger(const BigInteger&, int);											
	virtual ~BigInteger() = default;
	int sign() const;															// ���ش������ķ���
	size_t size() const;														// ���ش������ĳ���
	bool empty() const;															// �жϴ������Ƿ�Ϊ��
	void clear();																// ����������ղ���
	void push_zero(size_t);
	void push_zero(int);
	void push_zero(long long);
	void clean_zero();
	void shift(size_t);
	void shift(int);
	void shift(long long);
	virtual void from_string(const std::string&, bool = true);					// std::string->BigInteger
	virtual std::string to_string(bool = true) const;							// BigInteger->std::string��bool isSplit��ʾ�ַ������Ƿ���ַָ���
	virtual operator std::string() const;										// BigInteger->std::string��Ĭ�Ϸ��ؾ��зָ�����ַ���
	// ���������ıȽϲ���
	bool is_abs_greater(const BigInteger&) const;								
	bool is_abs_equal(const BigInteger&) const;
	bool is_abs_less(const BigInteger&) const;
	BigInteger abs_add(const BigInteger&, int = k_non_negative) const;			// ���������ļӷ�����
	BigInteger abs_sub(const BigInteger&, int = k_non_negative) const;			// ���������ļ�������
	BigInteger abs_mul(const BigInteger&, int = k_non_negative) const;			// ���������ĳ˷�����
	BigInteger abs_div(const BigInteger&, int = k_non_negative) const;			// ���������ĳ�������
	BigInteger add(const BigInteger&, int = k_non_negative) const;
	BigInteger sub(const BigInteger&, int = k_non_negative) const;
	BigInteger mul(const BigInteger&) const;
	BigInteger div(const BigInteger&) const;
	// ����> == < >= <= != + - * / >> << ����
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
	int symbol;																	// ���������ķ���
	IntegerList list;															// ������������������
};
} // namespace BigNumber
#endif // BIGNUMBER_BIGINTEGER_H
