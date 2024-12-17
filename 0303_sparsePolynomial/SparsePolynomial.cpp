﻿#include "SparsePolynomial.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <math.h> // std::powf()

using namespace std;

// 새로운 항을 추가할 때 자기 위치를 찾아서 넣어줘야 함

// exp항이 이미 존재하면 거기에 coef를 더해준다.
// 존재하지 않는다면 exp 오름 차순으로 정렬된 상태로 새로 추가한다.
void SparsePolynomial::NewTerm(float coef, int exp)
{
	if (coef == 0.0f) return; // 0이면 추가하지 않음

	if (num_terms_ >= capacity_)
	{
		// capacity 증가 (num_terms는 일단 고정)
		capacity_ = capacity_ > 0 ? capacity_ * 2 : 1; // 2배씩 증가 O(log n)
		Term* new_term = new Term[capacity_];

		// 원래 가지고 있던 데이터 복사
		memcpy(new_term, terms_, sizeof(Term) * num_terms_);

		// 메모리 교체
		if (terms_) delete[] terms_;
		terms_ = new_term;
	}

	terms_[num_terms_].coef = coef;
	terms_[num_terms_].exp = exp;

	num_terms_++;
}

float SparsePolynomial::Eval(float x)
{
	float temp = 0.0f;

	for (int i = 0; i < this->num_terms_; i++)
		temp += terms_[i].coef * powf(x, terms_[i].exp);

	return temp;
}

SparsePolynomial SparsePolynomial::Add(const SparsePolynomial& poly)
{
	// this와 poly의 terms_가 exp의 오름차순으로 정렬되어 있다고 가정
	// 하나의 다항식 안에 exp가 중복되는 term이 없다라고 가정 (한 exp는 하나의 term만 존재)

	// 간단한 방법 (메모리를 더 사용하는 방법)
	// - 1. 최대 exp를 찾는다.
	// - 2. 필요한 크기의 Polynomial을 만든다. (Sparse 아님)
	// - 3. 더하면서 Polynomial에 업데이트 한다. 구조가 고정되어 있어서 쉽다.
	// - 4. Polynomial을 SparsePolynomial로 변환한다.

	SparsePolynomial temp;
	int i, j = 0;

	while(i < this->num_terms_ && j < poly.num_terms_)
	{
		if (this->terms_[i].exp == poly.terms_[j].exp)
		{
			temp.NewTerm(this->terms_[i].coef + poly.terms_[j].coef, terms_[i].exp);
			i++;
			j++;
		}
		else if (this->terms_[i].exp < poly.terms_[j].exp)
		{
			temp.NewTerm(this->terms_[i].coef, this->terms_[i].exp);
			i++;
		}
		else
		{
			temp.NewTerm(poly.terms_[j].coef, poly.terms_[j].exp);
			j++;
		}
	}

	// 남은 항들 추가
	for (; i < this->num_terms_; i++)
		temp.NewTerm(this->terms_[i].coef, this->terms_[i].exp);
	for (; j < poly.num_terms_; j++)
		temp.NewTerm(poly.terms_[j].coef, poly.terms_[j].exp);
	
	// 시간 복잡도: O(n + m) (n: this의 항의 개수, m: poly의 항의 개수)
	// 높은 차수가 굉장히 높고 항의 개수가 적다면 이 방법이 더 효율적일 수 있다.
	return temp;
}

void SparsePolynomial::Print()
{
	bool is_first = true; // 더하기 출력시 확인용

	for (int i = 0; i < num_terms_; i++)
	{
		// 0이 아닌 항들만 골라서 출력할 필요가 없음

		if (!is_first)
			cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

		cout << terms_[i].coef;

		if (terms_[i].exp != 0) cout << "*" << "x^" << terms_[i].exp;

		is_first = false;
	}

	cout << endl;
}

void SparsePolynomial::getCapacity()
{
	cout << "capacity_: " << this->capacity_ << endl;
}
