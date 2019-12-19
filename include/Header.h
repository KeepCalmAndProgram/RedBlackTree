#ifndef  RedBlackTree_h
#define  RedBlackTree_h
#include <math.h>


enum class kolor : char
{
	R, B
};

template<class T>
class Wezel {

public:
	T dane;
	Wezel<T>* father;
	Wezel<T>* left_son;
	Wezel<T>* right_son;
	kolor color;

	int indeks;

	Wezel() {

	}
	Wezel(const T& value_dane) {
		this->dane = value_dane;
	}
	~Wezel() {

	}

private:

};



template<class T1>
class RedBlackTree {

public:
	Wezel<T1>* root;
	int tree_size;

	Wezel<T1>* wyszukaj_element(const T1& dane);

	void dodawanie_elementu(const T1& dane);

	int inorder(Wezel<T1>* aWezel);
	void inorder();

	int postorder(Wezel<T1>* aWezel);
	void postorder();

	int preorder(Wezel<T1>* aWezel);
	void preorder();

	int wyznacz_wysokosc_drzewa(Wezel<T1>* aWezel);
	void wyznacz_wysokosc_drzewa();

	int wyswietl_drzewo(Wezel<T1>* aWezel, int p = 3);
	void wyswietl_drzewo();

	int rotacje_w_lewo(Wezel<T1>* father);
	int rotacje_w_prawo(Wezel<T1>* father);

	int usun_wszystkie_wezly(Wezel<T1>* aWezel);
	void usun_wszystkie_wezly();


private:

};

template<class T>
inline int RedBlackTree<T>::rotacje_w_prawo(Wezel<T>* father)
{
	Wezel<T>* element_second = father->left_son;
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
inline int RedBlackTree<T>::rotacje_w_lewo(Wezel<T>* father)
{

	Wezel<T>* element_second = father->right_son;
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
inline int RedBlackTree<T>::usun_wszystkie_wezly(Wezel<T>* aWezel) {
	if (aWezel != NULL)
	{
		usun_wszystkie_wezly(aWezel->left_son);
		usun_wszystkie_wezly(aWezel->right_son);
		delete aWezel;
		aWezel = NULL;
	}
	return 1;
}

template<class T>
inline void RedBlackTree<T>::usun_wszystkie_wezly() {
	Wezel<T>* element = this->root;
	usun_wszystkie_wezly(element);
}

template<class T>
inline int RedBlackTree<T>::inorder(Wezel<T>* aWezel) {
	int count = 0;
	if (aWezel)
	{
		count += inorder(aWezel->left_son);
		std::cout << aWezel->dane << "  ";
		count++;
		count += inorder(aWezel->right_son);
	}
	return count;
}

template<class T>
inline void RedBlackTree<T>::inorder() {
	Wezel<T>* element = this->root;
	std::cout << "Inorder : " << inorder(element) << std::endl;
}

template<class T>
inline int RedBlackTree<T>::postorder(Wezel<T>* aWezel) {
	int count = 0;
	if (aWezel)
	{
		count += postorder(aWezel->left_son);
		count += postorder(aWezel->right_son);
		std::cout << aWezel->dane << "  ";
		count++;
	}
	return count;
}

template<class T>
inline void RedBlackTree<T>::postorder() {
	Wezel<T>* element = this->root;
	std::cout << "Postorder : " << postorder(element) << std::endl;
}


template<class T>
inline int RedBlackTree<T>::preorder(Wezel<T>* aWezel) {
	int count = 0;
	if (aWezel)
	{
		std::cout << aWezel->dane << "  ";
		count++;
		count += preorder(aWezel->left_son);
		count += preorder(aWezel->right_son);
	}
	return count;
}

template<class T>
inline void RedBlackTree<T>::preorder() {
	Wezel<T>* element = this->root;
	std::cout << "Preorder : " << preorder(element) << std::endl;
}


template<class T>
inline int RedBlackTree<T>::wyznacz_wysokosc_drzewa(Wezel<T>* aWezel) {
	if (aWezel == NULL) return -1;
	return 1 + fmax(wyznacz_wysokosc_drzewa(aWezel->left_son), wyznacz_wysokosc_drzewa(aWezel->right_son));
}

template<class T>
inline void RedBlackTree<T>::wyznacz_wysokosc_drzewa() {
	Wezel<T>* element = this->root;
	std::cout << "Wysokosc dzrewa : " << wyznacz_wysokosc_drzewa(element) << std::endl;
}

template<class T>
inline int RedBlackTree<T>::wyswietl_drzewo(Wezel<T>* aWezel, int p) {
	if (aWezel != NULL && p >= 0) {
		wyswietl_drzewo(aWezel->left_son, p - 1);

		std::cout << "   (" << aWezel->indeks;

		if (aWezel->color == kolor::B) {
			std::cout << ": [ black,";
		}
		else {
			std::cout << ": [ red,";
		}
		if (aWezel->father == NULL) {
			std::cout << " p: NULL";
		}
		else {
			std::cout << " p: " << aWezel->father->indeks;
		}

		if (aWezel->left_son == NULL) {
			std::cout << ", l: NULL";
		}
		else {
			std::cout << ", l: " << aWezel->left_son->indeks;
		}

		if (aWezel->right_son == NULL) {
			std::cout << ", r: NULL";
		}
		else {
			std::cout << ", r: " << aWezel->right_son->indeks;
		}

		std::cout << "] (" << aWezel->dane << "));" << std::endl;

		wyswietl_drzewo(aWezel->right_son, p - 1);
	}
	else {
		return 1;
	}
}

template<class T>
inline void RedBlackTree<T>::wyswietl_drzewo() {

	Wezel<T>* element = this->root;
	wyswietl_drzewo(element);
}

template<class T1>
inline Wezel<T1>* RedBlackTree<T1>::wyszukaj_element(const T1& dane) {

	Wezel<T1>* element = root;

	while (element != nullptr) {
		if (element->dane < dane) {
			element = element->right_son;
		}
		else if (dane < element->dane) {
			element = element->left_son;
		}
		else {
			//std::cout << "\nElement : " << element->dane << ";\nIndex : " << element->indeks << ";" << std::endl;
			return element;
		}
	}
	return NULL;
}


template<class T1>
inline void RedBlackTree<T1>::dodawanie_elementu(const T1& dane)
{
	Wezel<T1>* element = root;

	if (this->root == NULL) {
		this->root = element = new Wezel<T1>(dane);
		element->color = kolor::B;

		this->tree_size++;
		element->indeks = this->tree_size - 1;

		return;
	}

	while (element != nullptr) {
		if (element->dane < dane) {
			if (element->right_son == nullptr) {

				element->right_son = new Wezel<T1>(dane);
				element->right_son->father = element;
				element->right_son->color = kolor::R;
				element = element->right_son;

				this->tree_size++;
				element->indeks = this->tree_size - 1;


				break;
			}
			element = element->right_son;
		}
		else if (dane < element->dane) {
			if (element->left_son == nullptr) {

				element->left_son = new Wezel<T1>(dane);
				element->left_son->father = element;
				element->left_son->color = kolor::R;
				element = element->left_son;
				element->indeks = this->tree_size - 1;

				this->tree_size++;
				element->indeks = this->tree_size - 1;


				break;
			}
			element = element->left_son;
		}
		else {
			return;
		}

	}

	while (element != root && element->father->color == kolor::R) {

		if (element->father == element->father->father->left_son) {

			Wezel<T1>* element_second = element->father->father->right_son;

			if (element_second != NULL && element_second->color == kolor::R) {

				element->father->color = kolor::B;
				element_second->color = kolor::B;
				element->father->father->color = kolor::R;
				element = element->father->father;
			}
			else {

				if (element == element->father->right_son) {

					element = element->father;
					rotacje_w_lewo(element);
				}

				element->father->color = kolor::B;
				element->father->father->color = kolor::R;
				rotacje_w_prawo(element->father->father);
			}

		}
		else if (element->father == element->father->father->right_son) {

			Wezel<T1>* element_second = element->father->father->left_son;

			if (element_second != NULL && element_second->color == kolor::R) {

				element->father->color = kolor::B;
				element_second->color = kolor::B;

				element->father->father->color = kolor::R;
				element = element->father->father;
			}
			else {

				if (element == element->father->left_son) {
					element = element->father;
					rotacje_w_prawo(element);
				}
				element->father->color = kolor::B;
				element->father->father->color = kolor::R;
				rotacje_w_lewo(element->father->father);
			}
		}
	}
	root->color = kolor::B;

}
#endif