#ifndef BIGNUMBER_INTEGER_LIST_H
#define BIGNUMBER_INTEGER_LIST_H
#include "list.hpp"
namespace BigNumber {
class IntegerList final : public TinySTL::List<int> { // 大整数链表类
public:
	IntegerList();
	IntegerList(const IntegerList&);
	IntegerList& operator=(const IntegerList&);
	~IntegerList() override;
	void push_zero(size_t);		// 提供大整数的补0操作，往大整数的最高位前面进行补0操作
	void push_zero(int);
	void push_zero(long long);
	void pop_zero(int&);		// 大整数最低位的清0操作
	void pop_zero(long long&);
	void clean_zero();			// 大整数最高位的清0操作
	void shift(size_t);			// 提供大整数的移位操作 设形参为x且非负，该大整数左移x位，默认补0
	void shift(int);					
	void shift(long long);
};
} // namespace BigNumber
#endif // BIGNUMBER_INTEGER_LIST_H
