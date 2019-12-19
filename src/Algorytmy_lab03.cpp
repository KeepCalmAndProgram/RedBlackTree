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
	int number;
	char letter;

	bool operator ==(const some_object& value_number) const {
		return (number == value_number.number && letter == value_number.letter);
	}

	bool operator <(const some_object& value_number) const {
		return (this->number < value_number.number || this->number == value_number.number && this->letter < value_number.letter);
	}

	bool operator >(const some_object& value_number) const {
		return (value_number < *this);
	}

};

std::ostream& operator<<(std::ostream& out, const some_object& so) {
	return(out << so.number << so.letter);
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
			so->number = (rand() * 32768 + rand()) % 100000000 + 1;
			so->letter = rand() % ('z' - 'a' + 1) + 'a';

			tree->add_item(*so);
		}
		end = clock();

		tree->tree_height();
		std::cout << "\nRed Black Tree :" << std::endl;
		std::cout << "Tree size : " << tree->tree_size << std::endl;
		std::cout << "{" << std::endl;

		tree->display_tree();

		std::cout << "}" << std::endl;

		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Time to insert : " << time_spent << " s" << std::endl;

		const int m = pow(10, 4);
		int hits = 0;

		begin = clock();

		for (int j = 0; j < m; j++) {
			so->number = rand() % 10000 + 1;
			so->letter = rand() % ('z' - 'a' + 1) + 'a';

			Wezel<some_object>* result = tree->search_for_item(*so);
			if (result != NULL) {
				hits++;
			}
		}
		end = clock();


		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Time to search : " << time_spent << " s\n" << std::endl;
		std::cout << "Number of hits : " << hits << std::endl;

		//tree->inorder();
		//tree->postorder();
		//tree->preorder();

		tree->remove_all_nodes();

		delete tree;
		delete so;

	}
	std::cout << "Koniec " << std::endl;

	_CrtDumpMemoryLeaks();

	getchar();

	return 0;
}