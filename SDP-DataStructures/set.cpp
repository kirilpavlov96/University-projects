#include "linked_list.cpp"
#include "dictionary.h"

template <typename T, template<typename, typename> class D>
class Set {
private:
	using DT = D<T, bool>;
	DT dict;
public:
	// �������� �� ��������
	bool empty() const {
		return dict.keys().empty();
	}

	// ��������� �� �������
	bool insert(T const& x) {
		return dict.add(x, false);
	}

	// ���������� �� �������
	bool remove(T const& x) {
		return dict.remove(x);
	}

	// �������� �� ���������
	bool contains(T const& x) {
		return dict.lookup(x) != NULL;
	}

	// ������ �� ��������
	LinkedList<T> elements() {
		return dict.keys();
	}

	template <typename K>
	using HashFunction = int (*)(K const&, int);

	void setHashFunction(HashFunction<T> hf) {
		dict.setHashFunction(hf);
	}
};

// Set<int, AVLDictionary>
// Set<string, HashTable>
// template <typename T> using HashSet = Set<T, HashTable>
// HashSet<int>
// template <typename T> using AVLSet = Set<T, AVLDictionary>
// AVLSet<string>
