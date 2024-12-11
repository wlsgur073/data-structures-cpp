#pragma once

struct Term
{
	float coef;
	int exp;
};

class SparsePolynomial
{
public:
	SparsePolynomial()
	{
		// 아무것도 하지 않음 (동적할당 메모리 없이 시작)
		// 메모리를 효율적으로 사용하기 위해 처음부터 불필요한 메모리를 설정하지 않는다.
	}

	~SparsePolynomial()
	{
		if (terms_) delete[] terms_;
	}

	// 새로운 항을 추가할 때 자기 위치를 찾아서 넣어줘야 함
	void NewTerm(float coef, int exp);

	float Eval(float x);

	SparsePolynomial Add(const SparsePolynomial& poly);

	void Print();
	void getCapacity();

private:
	Term* terms_ = nullptr;
	int capacity_ = 0;
	int num_terms_ = 0;
};