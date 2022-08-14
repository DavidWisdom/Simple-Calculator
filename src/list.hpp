#ifndef BIGNUMBER_LIST_HPP
#define BIGNUMBER_LIST_HPP
#include "node.hpp"
#include <cassert>
namespace TinySTL {
template <typename T>
class List {					
public:
	List();
	List(const List<T>&);												// �������캯�������ⷢ��ǳ����
	List& operator=(const List<T>&);									// 
	virtual ~List();													// ����������
	void init();														// ����ĳ�ʶ������
	bool empty() const;													// �ж������Ƿ�Ϊ�ղ���
	void clear();														// �������ղ���
	void copy(const Node<T>*, size_t);									// ʵ������Ŀ�������
	void copy(const Node<T>*, int);										// ʵ������Ŀ�������
	Node<T>* insert(Node<T>*, const T&);								// ����Ĳ���������ڸ����Ľ�������в���
	Node<T>* insert(const T&, Node<T>*);								// ����Ĳ���������ڸ����Ľ��ǰ����в���
	void remove(const Node<T>*);										// �Ƴ����
	void push_front(const T&);											// �������ͷ���ǰ�����push����
	void push_back(const T&);											// �������β���������push����
	void pop_front();													// �������ͷ������pop����
	void pop_back();													// �������β������pop����
	Node<T>* begin() const;												// ���������ͷ���
	Node<T>* end() const;												// ���������βָ��
	Node<T>* rbegin() const;											// ���������β���
	Node<T>* rend() const;												// ���������ͷָ��
	T front() const;													// ��������ͷ���洢����ֵ
	T back() const;														// ��������β���洢����ֵ
	size_t size() const;												// ��������ĳ���
	T& operator[](size_t) const;										// ����[]�����
	T& operator[](int) const;											// ����[]�����

protected:
	Node<T>* head;														// �����ͷָ��
	Node<T>* rear;														// �����βָ��
	size_t len;															// ����ĳ���
};
} // namespace TinySTL
namespace TinySTL {
template <typename T>
List<T>::List() : head(new Node<T>), rear(new Node<T>), len(0) {
	head->next = rear;
	rear->prev = head;
}

template <typename T>
List<T>::List(const List<T>& list) : head(new Node<T>), rear(new Node<T>), len(0) {
	head->next = rear;
	rear->prev = head;
	copy(list.begin(), list.len);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& list) {
	if (this != &list) {
		clear();
		copy(list.begin(), list.len);
	}
	return *this;
}

template <class T>
List<T>::~List() {
	clear();
	// ������� 
	delete head;
	head = nullptr;
	delete rear;
	rear = nullptr;
	// �ͷ�ͷָ���βָ�룬����Ϊnullptr
}

template <typename T>
void List<T>::init() {
	// ����ĳ�ʼ������
	head = new Node<T>;
	rear = new Node<T>;
	head->next = rear;
	rear->prev = head;
	len = 0;
}

template <typename T>
bool List<T>::empty() const {
	// ������пղ���
	return len == 0;
}

template <typename T>
void List<T>::clear() {
	// �������ղ���
	while (len > 0) {
		remove(head->next);
		// �������еĽ��һһ����remove����
	}
}

template <typename T>
void List<T>::copy(const Node<T>* node, size_t num) {
	while (num--) {
		push_back(node->data);
		node = node->next;
	}
	// ʵ������Ŀ����������Ը�������ÿ������е�����һһ���п���
}

template <typename T>
void List<T>::copy(const Node<T>* node, int num) {
	assert(num >= 0);
	while (num--) {
		push_back(node->data);
		node = node->next;
	}
	// ʵ������Ŀ����������Ը�������ÿ������е�����һһ���п���
}

template <typename T>
Node<T>* List<T>::insert(Node<T>* node, const T& elem) {
	++len;
	return node->insert_as_prev(elem);
}

template <typename T>
Node<T>* List<T>::insert(const T& elem, Node<T>* node) {
	++len;
	return node->insert_as_next(elem);
}

template <typename T>
void List<T>::remove(const Node<T>* node) {
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete node;
	node = nullptr;
	// node delete�����Ϊnullptr
	--len;
	// �Ƴ�������㲢��������-1
}

template <typename T>
void List<T>::push_front(const T& elem) {
	++len;
	head->insert_as_next(elem);
	// ��headָ��֮����в��룬ͬʱ������+1
}

template <typename T>
void List<T>::push_back(const T& elem) {
	++len;
	rear->insert_as_prev(elem);
	// ��rearָ��֮����в��룬ͬʱ������+1
}

template <typename T>
void List<T>::pop_front() {
	assert(len > 0);
	// �����ȴ���0ʱ������������pop_front()�������������Ϊ�Ƿ�����
	remove(head->next);
}

template <typename T>
void List<T>::pop_back() {
	assert(len > 0);
	// �����ȴ���0ʱ������������pop_back()�������������Ϊ�Ƿ�����
	remove(rear->prev);
}

template <typename T>
Node<T>* List<T>::begin() const {
	return head->next;
}

template <typename T>
Node<T>* List<T>::end() const {
	return rear;
}

template <typename T>
Node<T>* List<T>::rbegin() const {
	return rear->prev;
}

template <typename T>
Node<T>* List<T>::rend() const {
	return head;
}

template <typename T>
T List<T>::front() const {
	return head->next->data;
}

template <typename T>
T List<T>::back() const {
	return rear->prev->data;
}

template <typename T>
size_t List<T>::size() const {
	return len;
}

template <typename T>
T& List<T>::operator[](size_t n) const {					// ʱ�临�Ӷ�ΪO(n)
	assert(n < len);
	//��ֹ����Խ����Ϊ����֤nС������ĳ���
	Node<T>* node = head->next;
	while (n-- > 0) {
		node = node->next;
	}
	return node->data;
}

template <typename T>
T& List<T>::operator[](int n) const {						// ʱ�临�Ӷ�ΪO(n)
	assert(n >= 0 && n < len);
	//��ֹ����Խ����Ϊ����֤nС������ĳ���
	Node<T>* node = head->next;
	while (n-- > 0) {
		node = node->next;
	}
	return node->data;
}
} //namespace TinySTL
#endif // BIGNUMBER_LIST_HPP
