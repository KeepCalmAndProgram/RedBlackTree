#ifndef  RedBlackTree_h
#define  RedBlackTree_h
#include <math.h>


enum class node_color : char
{
	R, B
};

template<class T>
class Node {

public:
	T data;
	Node<T>* father;
	Node<T>* left_son;
	Node<T>* right_son;
	node_color color;

	int index;

	Node() {

	}
	Node(const T& value_data) {
		this->data = value_data;
	}
	~Node() {

	}

private:

};



template<class T1>
class RedBlackTree {

public:
	Node<T1>* root;
	int tree_size;

	Node<T1>* search_for_item(const T1& data);

	void add_item(const T1& data);

	int inorder(Node<T1>* aNode);
	void inorder();

	int postorder(Node<T1>* aNode);
	void postorder();

	int preorder(Node<T1>* aNode);
	void preorder();

	int tree_height(Node<T1>* aNode);
	void tree_height();

	int display_tree(Node<T1>* aNode, int max_number_of_displayed_items = 3);
	void display_tree();

	int left_rotation(Node<T1>* father);
	int right_rotation(Node<T1>* father);

	int remove_all_nodes(Node<T1>* aNode);
	void remove_all_nodes();


private:

};

template<class T>
inline int RedBlackTree<T>::right_rotation(Node<T>* father)
{
	Node<T>* element_second = father->left_son;
	father->left_son = element_second->right_son;

	if (element_second->right_son != NULL) {
		element_second->right_son->father = father;
	}

	if (element_second != NULL) {
		element_second->father = father->father;
	}

	if (father->father) {
		if (father == father->father->right_son) {
			father->father->right_son = element_second;
		}
		else {
			father->father->left_son = element_second;
		}
	}
	else {
		root = element_second;
	}

	element_second->right_son = father;
	if (father != NULL) {
		father->father = element_second;
	}

	return 1;
}

template<class T>
inline int RedBlackTree<T>::left_rotation(Node<T>* father)
{

	Node<T>* element_second = father->right_son;
	father->right_son = element_second->left_son;

	if (element_second->left_son != NULL) {
		element_second->left_son->father = father;
	}

	if (element_second != NULL) {
		element_second->father = father->father;
	}

	if (father->father) {
		if (father == father->father->left_son) {
			father->father->left_son = element_second;
		}
		else {
			father->father->right_son = element_second;
		}
	}
	else {
		root = element_second;
	}

	element_second->left_son = father;
	if (father != NULL) {
		father->father = element_second;
	}

	return 1;
}


template<class T>
inline int RedBlackTree<T>::remove_all_nodes(Node<T>* aNode) {
	if (aNode != NULL)
	{
		remove_all_nodes(aNode->left_son);
		remove_all_nodes(aNode->right_son);

		delete aNode;
		aNode = NULL;
	}
	return 1;
}

template<class T>
inline void RedBlackTree<T>::remove_all_nodes() {
	Node<T>* element = this->root;
	remove_all_nodes(element);
}

template<class T>
inline int RedBlackTree<T>::inorder(Node<T>* aNode) {
	int count = 0;
	if (aNode)
	{
		count += inorder(aNode->left_son);
		std::cout << aNode->data << "  ";
		count++;
		count += inorder(aNode->right_son);
	}
	return count;
}

template<class T>
inline void RedBlackTree<T>::inorder() {
	Node<T>* element = this->root;
	std::cout << "Inorder : " << inorder(element) << std::endl;
}

template<class T>
inline int RedBlackTree<T>::postorder(Node<T>* aNode) {
	int count = 0;
	if (aNode)
	{
		count += postorder(aNode->left_son);
		count += postorder(aNode->right_son);
		std::cout << aNode->data << "  ";
		count++;
	}
	return count;
}

template<class T>
inline void RedBlackTree<T>::postorder() {
	Node<T>* element = this->root;
	std::cout << "Postorder : " << postorder(element) << std::endl;
}


template<class T>
inline int RedBlackTree<T>::preorder(Node<T>* aNode) {
	int count = 0;
	if (aNode)
	{
		std::cout << aNode->data << "  ";
		count++;
		count += preorder(aNode->left_son);
		count += preorder(aNode->right_son);
	}
	return count;
}

template<class T>
inline void RedBlackTree<T>::preorder() {
	Node<T>* element = this->root;
	std::cout << "Preorder : " << preorder(element) << std::endl;
}


template<class T>
inline int RedBlackTree<T>::tree_height(Node<T>* aNode) {
	if (aNode == NULL) return -1;
	return 1 + fmax(tree_height(aNode->left_son), tree_height(aNode->right_son));
}

template<class T>
inline void RedBlackTree<T>::tree_height() {
	Node<T>* element = this->root;
	std::cout << "Tree height : " << tree_height(element) << std::endl;
}

template<class T>
inline int RedBlackTree<T>::display_tree(Node<T>* aNode, int max_number_of_displayed_items) {
	if (aNode != NULL && max_number_of_displayed_items >= 0) {
		display_tree(aNode->left_son, max_number_of_displayed_items - 1);

		std::cout << "   (" << aNode->index;

		if (aNode->color == node_color::B) {
			std::cout << ": [ black,";
		}
		else {
			std::cout << ": [ red,";
		}
		if (aNode->father == NULL) {
			std::cout << " p: NULL";
		}
		else {
			std::cout << " p: " << aNode->father->index;
		}

		if (aNode->left_son == NULL) {
			std::cout << ", l: NULL";
		}
		else {
			std::cout << ", l: " << aNode->left_son->index;
		}

		if (aNode->right_son == NULL) {
			std::cout << ", r: NULL";
		}
		else {
			std::cout << ", r: " << aNode->right_son->index;
		}

		std::cout << "] (" << aNode->data << "));" << std::endl;

		display_tree(aNode->right_son, max_number_of_displayed_items - 1);
	}
	else {
		return 1;
	}
}

template<class T>
inline void RedBlackTree<T>::display_tree() {

	Node<T>* element = this->root;
	display_tree(element);
}

template<class T1>
inline Node<T1>* RedBlackTree<T1>::search_for_item(const T1& data) {

	Node<T1>* element = root;

	while (element != nullptr) {
		if (element->data < data) {
			element = element->right_son;
		}
		else if (data < element->data) {
			element = element->left_son;
		}
		else {
			return element;
		}
	}
	return NULL;
}


template<class T1>
inline void RedBlackTree<T1>::add_item(const T1& data)
{
	Node<T1>* element = root;

	if (this->root == NULL) {
		this->root = element = new Node<T1>(data);
		element->color = node_color::B;

		this->tree_size++;
		element->index = this->tree_size - 1;

		return;
	}

	while (element != nullptr) {
		if (element->data < data) {
			if (element->right_son == nullptr) {

				element->right_son = new Node<T1>(data);
				element->right_son->father = element;
				element->right_son->color = node_color::R;
				element = element->right_son;

				this->tree_size++;
				element->index = this->tree_size - 1;

				break;
			}
			element = element->right_son;
		}
		else if (data < element->data) {
			if (element->left_son == nullptr) {

				element->left_son = new Node<T1>(data);
				element->left_son->father = element;
				element->left_son->color = node_color::R;
				element = element->left_son;
				element->index = this->tree_size - 1;

				this->tree_size++;
				element->index = this->tree_size - 1;

				break;
			}
			element = element->left_son;
		}
		else {
			return;
		}

	}

	while (element != root && element->father->color == node_color::R) {

		if (element->father == element->father->father->left_son) {

			Node<T1>* element_second = element->father->father->right_son;

			if (element_second != NULL && element_second->color == node_color::R) {

				element->father->color = node_color::B;
				element_second->color = node_color::B;
				element->father->father->color = node_color::R;
				element = element->father->father;
			}
			else {

				if (element == element->father->right_son) {

					element = element->father;
					left_rotation(element);
				}

				element->father->color = node_color::B;
				element->father->father->color = node_color::R;
				right_rotation(element->father->father);
			}

		}
		else if (element->father == element->father->father->right_son) {

			Node<T1>* element_second = element->father->father->left_son;

			if (element_second != NULL && element_second->color == node_color::R) {

				element->father->color = node_color::B;
				element_second->color = node_color::B;

				element->father->father->color = node_color::R;
				element = element->father->father;
			}
			else {

				if (element == element->father->left_son) {
					element = element->father;
					right_rotation(element);
				}
				element->father->color = node_color::B;
				element->father->father->color = node_color::R;
				left_rotation(element->father->father);
			}
		}
	}
	root->color = node_color::B;

}
#endif