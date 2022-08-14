#ifndef BIGNUMBER_NODE_HPP
#define BIGNUMBER_NODE_HPP
namespace TinySTL {
template <typename T>
class Node final { // 结点类 
public:
	explicit Node(T = T(), Node<T>* = nullptr, Node<T>* = nullptr);
	Node* insert_as_prev(const T&); // 在当前结点之前插入
	Node* insert_as_next(const T&); // 在当前结点之后插入
	T data;							// 存储的数值
	Node* prev;						// 前一个结点
	Node* next;						// 后一个结点
};
} //namespace TinySTL
namespace TinySTL {
template <typename T>
Node<T>::Node(const T elem, Node<T>* pred, Node<T>* succ) : data(elem), prev(pred), next(succ) {}

template <typename T>
Node<T>* Node<T>::insert_as_prev(const T& elem) {							// 在当前结点之前插入
	Node<T>* node = new Node<T>(elem, prev, this);
	prev->next = node;
	prev = node;
	return node;
}

template <typename T>
Node<T>* Node<T>::insert_as_next(const T& elem) {							// 在当前结点之后插入
	Node<T>* node = new Node<T>(elem, this, next);
	next->prev = node;
	next = node;
	return node;
}
} //namespace TinySTL
#endif // BIGNUMBER_NODE_HPP
