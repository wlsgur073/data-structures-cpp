#include <iostream>
#include <math.h> // std::powf()
#include "../shared/SinglyLinkedList.h"

using namespace std;

struct Term
{
	float coef;
	int exp;
};

class LinkedPolynomial : public SinglyLinkedList<Term>
{
public:
	typedef SinglyLinkedList<Term>::Node Node;

	void NewTerm(float coef, int exp)
	{
		if (coef == 0.0f) return;

		// 아예 비어 있으면 PushFront로 추가
		if (IsEmpty()) PushFront({ coef, exp });
		else PushBack({ coef, exp });
	}

	float Eval(float x)
	{
		float temp = 0.0f;

		Node* current = first_;
		while(current)
		{
			temp += current->item.coef * powf(x, current->item.exp);
			current = current->next;
		}

		return temp;
	}

	LinkedPolynomial Add(const LinkedPolynomial& poly)
	{
		// this와 poly의 terms_가 exp의 오름차순으로 정렬되어 있다고 가정
		// 하나의 다항식 안에 exp가 중복되는 term이 없다라고 가정 (한 exp는 하나의 term만 존재)
		LinkedPolynomial temp;
		Node* i = this->first_;
		Node* j = poly.first_;

		while(i && j)
		{
			if (i->item.exp == j->item.exp)
			{
				temp.NewTerm(i->item.coef + j->item.coef, i->item.exp);
				i = i->next;
				j = j->next;
			}
			else if (i->item.exp < j->item.exp)
			{
				temp.NewTerm(i->item.coef, i->item.exp);
				i = i->next;
			}
			else
			{
				temp.NewTerm(j->item.coef, j->item.exp);
				j = j->next;
			}
		}
		
		
		// 남은 노드들 추가
		while (i)
		{
			temp.NewTerm(i->item.coef, i->item.exp);
			i = i->next;
		}
		while(j)
		{
			temp.NewTerm(j->item.coef, j->item.exp);
			j = j->next;
		}

		return temp;
	}

	void Print()
	{
		bool is_first = true; // 더하기 출력시 확인용

		Node* current = first_;

		while (current)
		{
			if (!is_first)
				cout << " + ";
			
			cout << current->item.coef;

			if (current->item.exp > 0)
				cout << "*x^" << current->item.exp;
			
			is_first = false;
			current = current->next;
		}

		cout << endl;
	}

private:
};

int main()
{
	using namespace std;

	LinkedPolynomial p1;

	// exp가 작은 항부터 추가한다고 가정
	// p1.NewTerm(1.0f, 0);	// 1 * x^0 = 1
	// p1.NewTerm(1.5f, 1);	// 1.5 * x^1
	// p1.NewTerm(2.0f, 2);	// 2 * x^2

	// p1.Print(); // 1 + 1.5*x^1 + 2*x^2

	// cout << p1.Eval(0.0f) << endl; // 1 + 1.5*0 + 2*0^2 = 1
	// cout << p1.Eval(1.0f) << endl; // 1 + 1.5*1 + 2*1^2 = 4.5
	// cout << p1.Eval(2.0f) << endl; // 1 + 1.5*2 + 2*2^2 = 1 + 3 + 8 = 12

	// cout << endl;

	// Add() Test1
	// cout << "Add() Test" << endl;
	// {
	// 	LinkedPolynomial p1; // max_degree는 기본값으로 설정

	// 	// exp가 작은 항부터 추가한다고 가정
	// 	p1.NewTerm(1.0f, 0);
	// 	p1.NewTerm(1.5f, 1);
	// 	p1.NewTerm(2.0f, 2);

	// 	p1.Print(); // 1 + 1.5*x^1 + 2*x^2

	// 	LinkedPolynomial p2;

	// 	// exp가 작은 항부터 추가한다고 가정
	// 	p2.NewTerm(1.0f, 1);
	// 	p2.NewTerm(3.0f, 2);
	// 	p2.NewTerm(5.0f, 7);
	// 	p2.NewTerm(2.0f, 11);

	// 	p2.Print(); // 1*x^1 + 3*x^2 + 5*x^7 + 2*x^11

	// 	cout << endl;

	// 	LinkedPolynomial psum = p1.Add(p2);
	// 	psum.Print(); // 1 + 2.5*x^1 + 5*x^2 + 5*x^7 + 2*x^11

	// 	cout << endl;
	// }

	// Add() Test2
	cout << "Add() Test2" << endl;
	{
		LinkedPolynomial p1; // max_degree는 기본값으로 설정

		// exp가 작은 항부터 추가한다고 가정
		p1.NewTerm(1.0f, 0);
		p1.NewTerm(1.5f, 1);
		p1.NewTerm(2.0f, 2);
		p1.NewTerm(5.0f, 7);
		p1.NewTerm(3.5f, 10);
		p1.NewTerm(5.5f, 20);
		p1.NewTerm(5.0f, 1000);

		p1.Print(); // 1 + 1.5*x^1 + 2*x^2 + 5*x^7 + 3.5*x^10 + 5.5*x^20 + 5*x^1000

		LinkedPolynomial p2;

		// exp가 작은 항부터 추가한다고 가정
		p2.NewTerm(3.2f, 0);
		p2.NewTerm(1.0f, 1);
		p2.NewTerm(3.0f, 2);
		p2.NewTerm(2.0f, 11);

		p2.Print(); // 3.2 + 1*x^1 + 3*x^2 + 2*x^11

		cout << endl;

		LinkedPolynomial psum = p1.Add(p2);
		psum.Print(); // 4.2 + 2.5*x^1 + 5*x^2 + 5*x^7 + 3.5*x^10 + 2*x^11 + 5.5*x^20 + 5*x^1000

		cout << endl;
	}

	return 0;
}
