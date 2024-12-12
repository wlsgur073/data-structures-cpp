#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

SparseMatrix::SparseMatrix(int num_rows, int num_cols, int capacity)
{
	this->num_rows_ = num_rows;
	this->num_cols_ = num_cols;
	this->capacity_ = capacity;
	this->num_terms_ = 0;

	// MatrixTerm이 일차원 배열이라고 생각하셈
	this->terms_ = new MatrixTerm[capacity];

	// term에 초기화가 필요함? -> GetValue()에서 0.0f 리턴하도록 설정돼 있음
	// for (int r = 0; r < num_rows_; r++)
	// {
	// 	for (int c = 0; c < num_cols_; c++)
	// 	{
	// 		terms_[r * num_cols_ + c].row = r;
	// 		terms_[r * num_cols_ + c].col = c;
	// 		terms_[r * num_cols_ + c].value = 0.0f;
	// 	}
	// }
}

// 복사 생성자 (b를 복사)
SparseMatrix::SparseMatrix(const SparseMatrix &b)
{
	if (b.capacity_ > 0)
	{
		num_rows_ = b.num_rows_;
		num_cols_ = b.num_cols_;
		num_terms_ = b.num_terms_;
		capacity_ = b.capacity_;
		terms_ = new MatrixTerm[capacity_];
		copy(b.terms_, b.terms_ + num_rows_ * num_cols_, terms_);
	}
}

SparseMatrix::~SparseMatrix()
{
	if (terms_) delete[] terms_;
}

void SparseMatrix::SetValue(int row, int col, float value)
{
	if (value == 0.0f) return; // value가 0이 아닌 term만 저장
	if (num_terms_ >= capacity_) return; // capacity_를 넘어가면 저장하지 않음

	// 정렬하지 않는 경우
	// terms_[num_terms_].row = row;
	// terms_[num_terms_].col = col;
	// terms_[num_terms_].value = value;
	// num_terms_++;

	// 선택 정렬
	// for (int i = 1; i < num_terms_; i++)
	// {
	// 	MatrixTerm temp = terms_[i];
	// 	int j = i;
	// 	while (j > 0 && terms_[j - 1].row > temp.row)
	// 	{
	// 		terms_[j] = terms_[j - 1];
	// 		j--;
	// 	}
	// 	terms_[j] = temp;
	// }

	// 정렬할 경우
	int key = row * num_cols_ + col;
	int i = 0;
	while(i < num_terms_)
	{
		int term_key = terms_[i].row * num_cols_ + terms_[i].col;
		if (term_key == key)
		{
			terms_[i].value = value;
			return;
		}
		else if (term_key > key)
			break;
		i++;
	}

	// 끝까지 하나씩 밀어주고 마지막에 교체
	assert(num_terms_ < capacity_); // 자리가 아직 있다면
	num_terms_++;
	for (int j = num_terms_ - 1; j > i; j--)
		terms_[j] = terms_[j - 1];

	terms_[i].row = row;
	terms_[i].col = col;
	terms_[i].value = value;	
}

float SparseMatrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	// for (int i = 0; i < num_terms_; i++)
	// 	if (terms_[i].row == row && terms_[i].col == col)
	// 		return terms_[i].value;

	// terms가 row와 col에 대해 정렬된 상태라면 검색을 더 빠르게 할 수 있음
	int key = row * num_cols_ + col;
	for (int i = 0; i < num_terms_; i++)
	{
		int term_key = terms_[i].row * num_cols_ + terms_[i].col;
		if (term_key == key)
			return terms_[i].value;
		else if (term_key > key)
			break;
	}
	
	return 0.0f;
}

SparseMatrix SparseMatrix::Transpose()
{
	SparseMatrix temp(num_cols_, num_rows_, capacity_); // num_cols_, num_rows_ 순서 주의

	// O(num_rows_ * num_cols_ * num_terms_)
	// for (int i = 0; i < num_cols_; i++)
	// 	for (int j = 0; j < num_rows_; j++)
	// 		temp.SetValue(i, j, GetValue(j, i)); 

	// O(num_rows_ * num_terms_)
	for (int r = 0; r < temp.num_rows_; r++)
	{
		for (int i = 0; i < num_terms_; i++)
		{
			if (terms_[i].col == r)
			{
				// SetValue() 함수를 사용하면 정렬이 다시 발생하니 시간복잡도가 높아짐
				temp.terms_[temp.num_terms_].col = terms_[i].row;
				temp.terms_[temp.num_terms_].row = terms_[i].col;
				temp.terms_[temp.num_terms_].value = terms_[i].value;
				temp.num_terms_++;
			}
		}
	}
	
	return temp;
}

void SparseMatrix::PrintTerms()
{
	for (int i = 0; i < num_terms_; i++)
		cout << "(" << terms_[i].row
			 << ", " << terms_[i].col
			 << ", " << terms_[i].value
			 << ")" << endl;
}

void SparseMatrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";
		cout << endl;
	}
}
