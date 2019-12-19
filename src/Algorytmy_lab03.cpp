//ALGO2 IS1 220A LAB03
//Andrzej Wisznicki
//wa42193@zut.edu.pl

#include <iostream>

#include "Header.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _CLIENT_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <ctime>


struct some_object {
	int liczba;
	char litera;

	bool operator ==(const some_object& value_liczba) const {
		return (liczba == value_liczba.liczba && litera == value_liczba.litera);
	}

	bool operator <(const some_object& value_liczba) const {
		return (this->liczba < value_liczba.liczba || this->liczba == value_liczba.liczba && this->litera < value_liczba.litera);
	}

	bool operator >(const some_object& value_liczba) const {
		return (value_liczba < *this);
	}

};

std::ostream& operator<<(std::ostream& out, const some_object& so) {
	return(out << so.liczba << so.litera);
}


int main() {

	const int MAX_ORDER = 7;

	for (int i = 1; i <= MAX_ORDER; i++) {

		RedBlackTree<some_object>* tree = new RedBlackTree<some_object>();
		some_object* so = new some_object;
		srand(time(NULL));

		const int n = pow(10, i);

		clock_t begin, end;
		double time_spent;
		begin = clock();

		for (int j = 0; j < n; j++) {
			so->liczba = (rand() * 32768 + rand()) % 100000000 + 1;
			so->litera = rand() % ('z' - 'a' + 1) + 'a';

			tree->dodawanie_elementu(*so);
		}
		end = clock();

		tree->wyznacz_wysokosc_drzewa();
		std::cout << "\nRed Black Tree :" << std::endl;
		std::cout << "Tree size : " << tree->tree_size << std::endl;
		std::cout << "{" << std::endl;

		tree->wyswietl_drzewo();

		std::cout << "}" << std::endl;

		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Czas na wstawienie : " << time_spent << " s" << std::endl;

		const int m = pow(10, 4);
		int hits = 0;

		begin = clock();

		for (int j = 0; j < m; j++) {
			so->liczba = rand() % 10000 + 1;
			so->litera = rand() % ('z' - 'a' + 1) + 'a';

			Wezel<some_object>* result = tree->wyszukaj_element(*so);
			if (result != NULL) {
				hits++;
			}
		}
		end = clock();


		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Czas na wyszukiwanie : " << time_spent << " s\n" << std::endl;
		std::cout << "Liczba trafien : " << hits << std::endl;

		//tree->inorder();
		//tree->postorder();
		//tree->preorder();

		tree->usun_wszystkie_wezly();

		delete tree;
		delete so;

	}
	std::cout << "Koniec " << std::endl;

	_CrtDumpMemoryLeaks();

	getchar();

	return 0;
}