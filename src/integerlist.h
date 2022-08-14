#ifndef BIGNUMBER_INTEGER_LIST_H
#define BIGNUMBER_INTEGER_LIST_H
#include "list.hpp"
namespace BigNumber {
class IntegerList final : public TinySTL::List<int> { // ������������
public:
	IntegerList();
	IntegerList(const IntegerList&);
	IntegerList& operator=(const IntegerList&);
	~IntegerList() override;
	void push_zero(size_t);		// �ṩ�������Ĳ�0�������������������λǰ����в�0����
	void push_zero(int);
	void push_zero(long long);
	void pop_zero(int&);		// ���������λ����0����
	void pop_zero(long long&);
	void clean_zero();			// ���������λ����0����
	void shift(size_t);			// �ṩ����������λ���� ���β�Ϊx�ҷǸ����ô���������xλ��Ĭ�ϲ�0
	void shift(int);					
	void shift(long long);
};
} // namespace BigNumber
#endif // BIGNUMBER_INTEGER_LIST_H
