#include "Matrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

Matrix::Matrix(int num_rows, int num_cols)
{
	this->num_rows_ = num_rows;
	this->num_cols_ = num_cols;
	this->values_ = new float[num_rows * num_cols];

	for (int i = 0; i < num_rows * num_cols; i++)
		values_[i] = 0.0f; // 초기화 안하면 쓰레기 값 들어감
	
}

// 복사 생성자 (b를 복사)
Matrix::Matrix(const Matrix& b)
{
	if (this != &b)
	{
		num_rows_ = b.num_rows_;
		num_cols_ = b.num_cols_;
		values_ = new float[num_rows_ * num_cols_];
		copy(b.values_, b.values_ + num_rows_ * num_cols_, values_); // 포인터 주소값 이동
	}
}

Matrix::~Matrix()
{
	if(values_) delete[] values_;
}

void Matrix::SetValue(int row, int col, float value)
{
	this->values_[row * num_cols_ + col] = value;
}

float Matrix::GetValue(int row, int col) const // 맨 뒤의 const는 함수 안에서 멤버 변수의 값을 바꾸지 않겠다는 의미
{
	return values_[row * num_cols_ + col];
}

Matrix Matrix::Transpose()
{
	Matrix temp(num_cols_, num_rows_); // num_cols_, num_rows_ 순서 주의
	// Matrix temp(4, 3); 결국 1차원 배열

	for (int i = 0; i < num_cols_; i++)
		for (int j = 0; j < num_rows_; j++)
			temp.SetValue(i, j, GetValue(j, i));

	return temp;
}

Matrix Matrix::Add(const Matrix& b)
{
	assert(b.num_cols_ == num_cols_);
	assert(b.num_rows_ == num_rows_);

	Matrix temp(num_rows_, num_cols_);
	
	for (int i = 0; i < num_rows_ * num_cols_; i++)
		temp.values_[i] = this->values_[i] + b.values_[i];

	return temp;
}

void Matrix::Print()
{
	for (int r = 0; r < num_rows_; r++)
	{
		for (int c = 0; c < num_cols_; c++)
			cout << GetValue(r, c) << " ";

		cout << endl;
	}
}
