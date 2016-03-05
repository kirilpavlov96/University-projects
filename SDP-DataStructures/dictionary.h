#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <utility>
using namespace std;
#include "linked_list.cpp"

template <typename K, typename V>
class Dictionary {
public:
	// ���������� �� ����
	// ht["Ivan"] = "Prodanov";
	// ��� "Ivan" �� ���� � ���������, �� �� �������
	V& operator[](K const& key) {
		V* value = lookup(key);
		if (value != NULL)
			return *value;
		else {
			add(key, V());
			return *lookup(key);
		}
	}

	// �������
	virtual V* lookup(K const&) = 0;

	// ��������
	virtual bool add(K const&, V const&) = 0;

	// ���������
	virtual bool remove(K const&) = 0;

	// ������ �� �������
	virtual LinkedList<K> keys() = 0;

	// ������ �� ���������
	virtual LinkedList<V> values() = 0;

	virtual ~Dictionary() {}
};

template <typename K, typename V>
class KeyValuePair : public pair<K, V> {
public:
	KeyValuePair(K const& key = K(), V const& value = V())
		: pair<K,V>(key, value) {}

	K& key()   { return pair<K,V>::first; }
	V& value() { return pair<K,V>::second; }

	K const& key()   const { return pair<K,V>::first; }
	V const& value() const { return pair<K,V>::second; }

	bool operator==(KeyValuePair const& kvp) const {
		return key() == kvp.key();
	}

	bool operator!=(KeyValuePair const& kvp) const {
		return !(*this == kvp);
	}
};


#endif /* DICTIONARY_H_ */
