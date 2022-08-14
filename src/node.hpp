#ifndef BIGNUMBER_NODE_HPP
#define BIGNUMBER_NODE_HPP
namespace TinySTL {
template <typename T>
class Node final { // ����� 
public:
	explicit Node(T = T(), Node<T>* = nullptr, Node<T>* = nullptr);
	Node* insert_as_prev(const T&); // �ڵ�ǰ���֮ǰ����
	Node* insert_as_next(const T&); // �ڵ�ǰ���֮�����
	T data;							// �洢����ֵ
	Node* prev;						// ǰһ�����
	Node* next;						// ��һ�����
};
} //namespace TinySTL
namespace TinySTL {
template <typename T>
Node<T>::Node(const T elem, Node<T>* pred, Node<T>* succ) : data(elem), prev(pred), next(succ) {}

template <typename T>
Node<T>* Node<T>::insert_as_prev(const T& elem) {							// �ڵ�ǰ���֮ǰ����
	Node<T>* node = new Node<T>(elem, prev, this);
	prev->next = node;
	prev = node;
	return node;
}

template <typename T>
Node<T>* Node<T>::insert_as_next(const T& elem) {							// �ڵ�ǰ���֮�����
	Node<T>* node = new Node<T>(elem, this, next);
	next->prev = node;
	next = node;
	return node;
}
} //namespace TinySTL
#endif // BIGNUMBER_NODE_HPP
