#pragma once
#include <iostream>
using namespace std;



class Komp
{
private:
	int r_;
	int i_;
public:
	friend Komp  operator + (Komp & a, Komp & b);
	friend Komp  operator - (Komp & a, Komp & b);
	friend Komp  operator * (Komp & a, Komp & b);
	Komp() : r_(0) , i_(0)
	{
		
	}
	Komp(int r, int nr) : r_(r), i_(nr)
	{
	
	}
	Komp & operator = (Komp & A) = default; 
	
	int   Real() const
	{
		return r_;

	}
	void print() const 
	{
		cout << "(" << r_ << "+" << i_ << "i" << ")";
	}
	int UnReal() const 
	{
		return i_;
	}
	~Komp()
	{

	}
};


Komp  operator + (Komp & a, Komp & b)
{
	Komp c;
	c.r_ = a.r_ + b.r_;
	c.i_ = a.i_ + b.i_;
	return c;
}
Komp  operator - (Komp & a, Komp & b)
{
	Komp c;
	c.r_ = a.r_ - b.r_;
	c.i_ = b.i_ - b.i_;
	return c;
}
Komp  operator * (Komp & a, Komp & b)
{
	Komp c;
	c.r_ = a.r_*b.r_ - a.i_*b.i_;
	c.i_ = a.r_*b.i_ + b.r_*a.i_;
	return c;
}

class Matrix
{
private:
	Komp ** Matr_;
	int n_;
public:
	friend Matrix  operator + (Matrix & a, Matrix & b);
	friend Matrix  operator - (Matrix & a, Matrix & b);
	friend Matrix  operator * (Matrix & a, Matrix & b);
	Matrix() :n_(0) , Matr_(nullptr)
	{

	}
	Matrix(Komp ** Matr, int n) : n_(n)
	{
		Matr_ = new Komp*[n_];
		for (int i = 0; i < n_; i++)
		{
			Matr_[i] = new Komp[n_];
		}
		for (int i = 0; i < n_; i++)
		{
			for (int j = 0; j < n_; j++)
			{
				Matr_[i][j] = Matr[i][j];
			}
		}
	}
	Matrix(Matrix & A): n_(A.n_)
	{
		
		Matr_ = new Komp*[n_];
		for (int i = 0; i < n_; i++)
		{
			Matr_[i] = new Komp[n_];
		}
		for (int i = 0; i < n_; i++)
		{
			for (int j = 0; j < n_; j++)
			{
				Matr_[i][j] = A.Matr_[i][j];
			}
		}
	}
	void print2() const 
	{
		for (int i = 0; i < n_; i++)
		{
			for (int j = 0; j < n_; j++)
			{
				Matr_[i][j].print();
			}
			cout << "\n";
		}
	}
	Matrix & operator= (const Matrix & A)
	{
		if (this != &A)
		{
			std::cout << "Перегруженный оператор присваивания" << std::endl;
			for (size_t i = 0; i < n_; i++)
			{
				delete[] Matr_[i];
			}
			delete[]Matr_;
			n_ = A.n_;
			Matr_ = new Komp *[n_];
			for (int i = 0; i < n_; i++)
			{
				Matr_[i] = A.Matr_[i];
			}
		}
		else
		{
			std::cout << "Самоприсваивание" << std::endl;
		}
		return *this;
	}
	int Size() const 
	{
		return n_;
	}
	Komp ** Mat()
	{
		return Matr_;
	}
	Komp OPR2(Matrix &A)
	{
		Komp k;
		k = A.Matr_[0][0] * A.Matr_[1][1] - A.Matr_[0][1] * A.Matr_[1][0];
		return k;
	}
	Matrix  & TRAN()
	{
		Komp buff;
		for (int i = 0; i < n_; i++)
		{
			for (int j = 0; j < i; j++)
			{
				buff = Matr_[i][j];
				Matr_[i][j] = Matr_[j][i];
				Matr_[j][i] = buff;
			}
		}
		return *this;
	}
	~Matrix()
	{
		if (!n_)
		{
			for (int i = 0; i < n_; ++i)
			{
				delete[] (Matr_[i]);
			}
			
			delete[] Matr_;
			
		}
	}

};

Matrix  operator + (Matrix & a, Matrix & b)
{
	if (a.Size() == b.Size())
	{
		Matrix c(a.Matr_, a.Size());
		for (int i = 0; i < a.Size(); i++)
		{
			for (int j = 0; j < a.Size(); j++)
			{
				c.Matr_[i][j] = a.Matr_[i][j] + b.Matr_[i][j];
			}
		}
		return c;
	}
	else
	{
		cout << "Разные размеры\n";
		return Matrix();
	}
}
Matrix  operator - (Matrix & a, Matrix & b)
{
	if (a.Size() == b.Size())
	{
		Matrix c(a.Matr_, a.Size());
		for (int i = 0; i < a.Size(); i++)
		{
			for (int j = 0; j < a.Size(); j++)
			{
				c.Matr_[i][j] = a.Matr_[i][j] - b.Matr_[i][j];
			}
		}
		return c;
	}
	else
	{
		cout << "Разные размеры \n";
		return Matrix();
	}
}
Matrix  operator * (Matrix & a, Matrix & b)
{
	if (a.Size() == b.Size())
	{
		Matrix c(a.Matr_, a.Size());
		int n = a.Size();
		int x1, x2, x3, x4;
		x1 = x2 = x3 = x4 = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				c.Matr_[i][j] = Komp();
				for (x2 = 0; x2 < n; x2++)
				{
					Komp x3;
					x3 = a.Matr_[i][x2] * b.Matr_[x2][j];
					c.Matr_[i][j] = c.Matr_[i][j] + x3;
				}
			}
		}
		return c;
	}
	else
	{
		cout << "Разные размеры \n";
		return Matrix();
	}
}