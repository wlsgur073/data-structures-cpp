#include <iostream>
#include <string> // std::string

using namespace std;

template <typename K, typename V>
class HashTable
{
public:
	struct Item
	{
		K key = K();
		V value = V();
	};

	HashTable(const int &cap = 8)
	{
		capacity_ = cap;
		table_ = new Item[capacity_];
	}

	~HashTable()
	{
		delete[] table_;
	}

	void Insert(const Item &item)
	{
		size_t index = HashFunc(item.key);
		// key가 int 자료형일때는 0이면 비어있는 것으로 가정
		// key가 문자열 자료형일때는 길이가 0 비어있는 것으로 가정

		if (table_[index].key != K())
			cout << "Collision!" << endl;

		// while(table_[index].key != K()) // 빈 곳 찾을 때까지 무한 반복
		// 	index = (index + 1) % capacity_;

		for (int i = 0; i < capacity_; i++)
		{
			index = (index + i) % capacity_;
			if (table_[index].key == K())
			{
				table_[index] = item;
				return;
			}
		}
		cout << "Failed to insert" << endl;
	}

	V Get(const K &key)
	{
		size_t index = HashFunc(key);
		for (int i = 0; i < capacity_; i++)
		{
			// index = (index + i) % capacity;
			size_t temp = (index + i) % capacity_; // index를 덮어쓰는 것이 아니라 임시 변수 만들기
			if (table_[temp].key == key)
				return table_[temp].value;
		}
		return V();
	}

	// 정수 -> 해시값
	size_t HashFunc(const int &key)
	{
		return key % capacity_; // key 값의 범위를 capacity_가 감당할 수 있는 범위로 제한
	}

	// 문자열을 정수 인덱스(해시값)로 변환
	// Horner's method
	size_t HashFunc(const string &s)
	{
		size_t index = 0;
		for (int i = 0; i < s.size(); i++)
			index = index * 31 + int(s.at(i));

		return index % capacity_;
	}

	void Print()
	{
		for (int i = 0; i < capacity_; i++)
			cout << i << " : " << table_[i].key << " " << table_[i].value << endl;
		cout << endl;
	}

private:
	Item *table_ = nullptr;
	int capacity_ = 0;
};

int main()
{
	// 충돌
	// - 개방 주소법: 선형 조사법 // 한 칸씩 이동하면서 빈 곳을 찾는 방법
	// - 체이닝: 멤버 변수 Item* table_ 대신에 LinkedList<Item>* table_사용

	// 키: int, 값: int 인 경우
	// 키의 범위가 아주 크고 아이템의 개수는 적을 경우
	// {
	// 	using Item = HashTable<int, int>::Item;

	// 	HashTable<int, int> h(8);

	// 	h.Insert(Item{123, 456});

	// 	h.Print();

	// 	cout << "Get 123 " << h.Get(123) << endl;

	// 	h.Insert(Item{1000021, 9898});

	// 	h.Print();

	// 	cout << "Get 1000021 " << h.Get(1000021) << endl;

	// 	h.Insert(Item{1211, 999}); // 충돌!

	// 	h.Print();

	// 	cout << "Get 123 " << h.Get(123) << endl;
	// 	cout << "Get 1211 " << h.Get(1211) << endl;
	// }

	// 키: std::string, 값: int
	{
		using Item = HashTable<string, int>::Item;

		HashTable<string, int> h(8);

		h.Insert(Item{"apple", 1});
		h.Insert(Item{"orange", 2});
		h.Insert(Item{"mandarin", 4});

		h.Print();

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << endl;

		h.Print();

		h.Insert(Item{"tomato", 4});

		h.Print();

		cout << "apple " << h.Get("apple") << endl;
		cout << "orange " << h.Get("orange") << endl;
		cout << "pineapple " << h.Get("pineapple") << endl;
		cout << endl;
	}

	return 0;
}