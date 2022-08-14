#ifndef BIGNUMBER_LIST_HPP
#define BIGNUMBER_LIST_HPP
#include "node.hpp"
#include <cassert>
namespace TinySTL {
template <typename T>
class List {					
public:
	List();
	List(const List<T>&);												// 拷贝构造函数，避免发生浅拷贝
	List& operator=(const List<T>&);									// 
	virtual ~List();													// 虚析构函数
	void init();														// 链表的初识化操作
	bool empty() const;													// 判断链表是否为空操作
	void clear();														// 链表的清空操作
	void copy(const Node<T>*, size_t);									// 实现链表的拷贝操作
	void copy(const Node<T>*, int);										// 实现链表的拷贝操作
	Node<T>* insert(Node<T>*, const T&);								// 链表的插入操作，在给定的结点后面进行插入
	Node<T>* insert(const T&, Node<T>*);								// 链表的插入操作，在给定的结点前面进行插入
	void remove(const Node<T>*);										// 移除结点
	void push_front(const T&);											// 往链表的头结点前面进行push操作
	void push_back(const T&);											// 往链表的尾结点后面进行push操作
	void pop_front();													// 对链表的头结点进行pop操作
	void pop_back();													// 对链表的尾结点进行pop操作
	Node<T>* begin() const;												// 返回链表的头结点
	Node<T>* end() const;												// 返回链表的尾指针
	Node<T>* rbegin() const;											// 返回链表的尾结点
	Node<T>* rend() const;												// 返回链表的头指针
	T front() const;													// 返回链表头结点存储的数值
	T back() const;														// 返回链表尾结点存储的数值
	size_t size() const;												// 返回链表的长度
	T& operator[](size_t) const;										// 重载[]运算符
	T& operator[](int) const;											// 重载[]运算符

protected:
	Node<T>* head;														// 链表的头指针
	Node<T>* rear;														// 链表的尾指针
	size_t len;															// 链表的长度
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
	// 清空链表 
	delete head;
	head = nullptr;
	delete rear;
	rear = nullptr;
	// 释放头指针和尾指针，并置为nullptr
}

template <typename T>
void List<T>::init() {
	// 链表的初始化操作
	head = new Node<T>;
	rear = new Node<T>;
	head->next = rear;
	rear->prev = head;
	len = 0;
}

template <typename T>
bool List<T>::empty() const {
	// 链表的判空操作
	return len == 0;
}

template <typename T>
void List<T>::clear() {
	// 链表的清空操作
	while (len > 0) {
		remove(head->next);
		// 对链表中的结点一一进行remove操作
	}
}

template <typename T>
void List<T>::copy(const Node<T>* node, size_t num) {
	while (num--) {
		push_back(node->data);
		node = node->next;
	}
	// 实现链表的拷贝操作，对给定链表每个结点中的内容一一进行拷贝
}

template <typename T>
void List<T>::copy(const Node<T>* node, int num) {
	assert(num >= 0);
	while (num--) {
		push_back(node->data);
		node = node->next;
	}
	// 实现链表的拷贝操作，对给定链表每个结点中的内容一一进行拷贝
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
	// node delete完后置为nullptr
	--len;
	// 移除给定结点并且链表长度-1
}

template <typename T>
void List<T>::push_front(const T& elem) {
	++len;
	head->insert_as_next(elem);
	// 在head指针之后进行插入，同时链表长度+1
}

template <typename T>
void List<T>::push_back(const T& elem) {
	++len;
	rear->insert_as_prev(elem);
	// 在rear指针之后进行插入，同时链表长度+1
}

template <typename T>
void List<T>::pop_front() {
	assert(len > 0);
	// 链表长度大于0时才能正常运行pop_front()操作，其余情况为非法操作
	remove(head->next);
}

template <typename T>
void List<T>::pop_back() {
	assert(len > 0);
	// 链表长度大于0时才能正常运行pop_back()操作，其余情况为非法操作
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
T& List<T>::operator[](size_t n) const {					// 时间复杂度为O(n)
	assert(n < len);
	//防止链表越界行为，保证n小于链表的长度
	Node<T>* node = head->next;
	while (n-- > 0) {
		node = node->next;
	}
	return node->data;
}

template <typename T>
T& List<T>::operator[](int n) const {						// 时间复杂度为O(n)
	assert(n >= 0 && n < len);
	//防止链表越界行为，保证n小于链表的长度
	Node<T>* node = head->next;
	while (n-- > 0) {
		node = node->next;
	}
	return node->data;
}
} //namespace TinySTL
#endif // BIGNUMBER_LIST_HPP
