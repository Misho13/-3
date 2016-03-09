#pragma once
#include <iostream>
using namespace std;



class Komp
{
private:
	int r_;
	int i_;
public:
	friend Komp & operator + (Komp & a, Komp & b);
	friend Komp & operator - (Komp & a, Komp & b);
	friend Komp & operator * (Komp & a, Komp & b);
	Komp()
	{
		r_ = 0;
		i_ = 0;
	}
	Komp(int r, int nr)
	{
		r_ = r;
		i_ = nr;
	}
	int   Real()
	{
		return r_;

	}
	void print()
	{
		cout << "(";
		cout << r_ << "+" << i_ << "i" << ")";
	}
	int UnReal()
	{
		return i_;
	}
	~Komp()
	{

	}
};


Komp & operator + (Komp & a, Komp & b)
{
	Komp c;
	c.r_ = a.r_ + b.r_;
	c.i_ = a.i_ + b.i_;
	return c;
}
Komp & operator - (Komp & a, Komp & b)
{
	Komp c;
	c.r_ = a.r_ - b.r_;
	c.i_ = b.i_ - b.i_;
	return c;
}
Komp & operator * (Komp & a, Komp & b)
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
	friend Matrix & operator + (Matrix & a, Matrix & b);
	friend Matrix & operator - (Matrix & a, Matrix & b);
	friend Matrix & operator * (Matrix & a, Matrix & b);
	Matrix()
	{
		Matr_ = new Komp*[0];
		n_ = 0;
	}
	Matrix(Komp ** Matr, int n)
	{
		n_ = n;
		Matr_ = new Komp*[n];
		for (int i = 0; i < n; i++)
		{
			Matr_[i] = new Komp[n];
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Matr_[i][j] = Komp(Matr[i][j].Real(), Matr[i][j].UnReal());
			}
		}
	}
	void print2()
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
	int Size()
	{
		return n_;
	}
	Komp ** Mat()
	{
		return Matr_;
	}
	Matrix  & TRAN( Matrix& A)
	{
		//Matrix X(A.Matr_, A.n_);
		for (int i = 0; i < n_; i++)
		{
			for (int j = 0; j < n_; j++)
			{
				(*this).Matr_[j][i] = A.Matr_[i][j];
			}
		}
		cout << "TRANS\n";
		//X.print2();
		return *this;
	}
	~Matrix()
	{
		/*for (int i = 0; i < n_; i++)
		{
			delete[] Matr_[i];
		}
		delete[] Matr_;*/
	//	cout << "DESTRUCT" << endl;
	}

};

Matrix & operator + (Matrix & a, Matrix & b)
{
	if (a.Size() == b.Size())
	{
		Matrix c(a.Matr_, a.Size());
		//c.Matr_ = new  Komp *[a.Size()];
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
	}
}
Matrix & operator - (Matrix & a, Matrix & b)
{
	if (a.Size() == b.Size())
	{
		Matrix c(a.Matr_, a.Size());
		//c.Matr_ = new  Komp *[a.Size()];
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
	}
}
Matrix & operator * (Matrix & a, Matrix & b)
{

	Matrix c(a.Matr_, a.Size());
	//c.Matr_ = new  Komp *[a.Size()];
	int n = a.Size();
	int x1, x2, x3, x4;
	x1 = x2 = x3 = x4 = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			c.Matr_[i][j]=Komp();
			for (x2 = 0; x2 < n; x2++)
			{
				Komp x3;
				x3 = a.Matr_[i][x2] * b.Matr_[x2][j] ;
				c.Matr_[i][j] = c.Matr_[i][j] + x3;
				/*cout << "x=";
				x3.print();
				cout << "\nc=";
				c.Matr_[i][j].print();*/
			}
		}
	}
	return c;
}