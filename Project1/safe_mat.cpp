//Project #1

#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

template<class T>
class SA;
template <class T>
ostream& operator<< (ostream& os, SA<T> s);
template<class T>
class SM;
template<class T>
ostream& operator<< (ostream& os, SM<T> s);

template<class T>
class SA
{
	
private:
	int low, high;
	T *p;
	
public:
		
	//default constructor
	//allows for writing things like SA a;
	
	SA()
	{
		low = 0;
		high = -1;
		p = NULL;
	}
	
	//single paramter constructor lets us
	//create a SA almost like a "standard" one by writing
	//SA x(10); and getting an array x indexed from 0 to 9
	
	SA(int i)
	{
		low = 0;
		high = i-1;
		p = new T[i];
	}
	
	//2 parameter constructor lets us write
	//SA x(10,20);
	
	SA(int l, int h)
	{
		if((h-l+1) <= 0)	//lower bound is greater than higher bound
		{
			cout << "constructor error in bounds definition" << endl;
			exit(1);
		}
		low = l;
		high = h;
		p = new T[h-l+1];	//create size of array within bounds
	}
	
	//copy constructor for pass by value and initialization
	SA(const SA &s)
	{
		int size = s.high-s.low+1;
		p= new T[size];
		for(int i=0; i<size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
	}
	
	//destructor
	
	~SA()
	{
		delete[] p;
	}
	
	T& operator[](int i)
	{
		if(i<low || i>high)
		{
			cout << "index " << i << " out of range" << endl;	//i not withing bounds
			exit(1);
		}
		return p[i-low];	//returns the element 
	}
	
	//overloaded assignment lets us assign
	//one SA to another
	
	SA& operator=(const SA &s)
	{
		if(this == &s) 
			return *this;
		delete []p;
		int size = s.high-s.low+1;
		p = new T[size];
		for(int i=0; i<size; i++)
			p[i] = s.p[i];
		low = s.low;
		high = s.high;
		return *this;
	}
	
	//overloads << so we can directly print SAs
	
	friend ostream& operator<< <T>(ostream& os, SA<T> s);
	
};


template <class T>
class SM 
{
	
private:
	int r_low, r_high;
	int c_low, c_high;
	SA <SA<T>> p;
	
public:
	
	//default constructor
	SM()
	{
		r_low = 0;
		r_high = -1;
		c_low = 0;
		c_high = -1;
		p = NULL;
	}
	
	//2 parameter constructor
	SM(int r, int c)
	{
		r_low = 0;
		r_high = r-1;
		c_low = 0; 
		c_high = c-1;
		p = SA <SA<T>>(r);
		for(int i=0; i<r; i++)
			p[i] = SA<T>(c);
	}
	
	//4 paramater constructor
	SM(int rl, int rh, int cl, int ch)
	{
		r_low = rl;
		r_high = rh;
		c_low = cl;
		c_high = ch;
		p = SA <SA<T>> (rl, rh);
		for(int i = rl; i <= rh; i++)
			p[i] = SA<T> (cl, ch);
	}
	
	//destructor
	~SM() {}
	
	SA<T> &operator[](int i)
	{
		return p[i];
	}
	
	SM<T> operator* (SM& s)
	
	{
		if((c_high-c_low) != (s.r_high-s.r_low))
		{
			cout << "Unable to multiply dimensions" << endl;
			exit(1);
		}	
		SM<T> t_Mat(r_low, r_high, s.c_low, s.c_high);
		int c = c_high-c_low;
		for(int i=r_low; i<=r_high; i++)
		{
			for(int j=s.c_low; j<=s.c_high; j++)
			{
				for(int k=0; k<=c; k++)
					t_Mat[i][j] = t_Mat[i][j] + ((*this)[i][k+c_low] * s.p[k+s.r_low][j]);
			}
		}
		return t_Mat;
	}
	
	friend ostream& operator<< <T>(ostream& os, SM<T> s);
};

template<class T>
ostream& operator <<(ostream& os, SM<T> s)
{
	for(int i=s.r_low; i<=s.r_high; i++)
	{
		for(int j=s.c_low; j<=s.c_high; j++)
		{
			os << s.p[i][j] << " " ;
		}
	os << endl; 
	}
	return os;
};

int main()
{
	
	SM<int> mat1(3, 5, 8, 11);
	mat1[3][8] = 4;
	mat1[3][9] = 3;
	mat1[3][10] = 8;
	mat1[3][11] = 0;
	mat1[4][8] = 7;
	mat1[4][9] = 5;
	mat1[4][10] = 4;
	mat1[4][11] = 9;
	mat1[5][8] = 1;
	mat1[5][9] = 3;
	mat1[5][10] = 5;
	mat1[5][11] = 7;
	
	cout << "matrix 1" << endl;
	cout << mat1 << endl;
	
	SM<int> mat2(6, 9, 15, 16);
	mat2[6][15] = 1;
	mat2[6][16] = 7;
	mat2[7][15] = 9;
	mat2[7][16] = 0;
	mat2[8][15] = 6;
	mat2[8][16] = 3;
	mat2[9][15] = 9;
	mat2[9][16] = 4;

	cout << "matrix 2" << endl;
	cout << mat2 << endl;
	
	SM<int> mat3(2, 3);
	mat3[0][0] = 0;
	mat3[1][1] = 5;
	mat3[0][2] = 0;
	mat3[1][0] = 3;
	mat3[0][1] = 7;
	mat3[1][2] = 8;
	
	cout << "matrix 3" << endl;
	cout << mat3 << endl;
	
	cout << "matrix 1 * matrix 2" << endl;
	cout << mat1*mat2 << endl;
	
	
	/*
	SA a(10), b(3,5);
	b[3] = 3; b[4] = 4; b[5] = 5;
	int i;
	for(i = 0; i < 10; i++)
		a[i] = 10-i;
	
	cout << "printing a the first time" << endl;
	cout << a << endl;
	
	cout << "printing using []" << endl;
	for(i = 0; i < 10; i++)
		cout << a[i] << endl;
	
	//write your own sort
	//Sort(a, 10);
	
	//cout << "printing a the second time" << endl;
	//cout << a << endl;
	
	b[4] = 12;
	cout << "printing b" << endl;
	cout << b << endl;
	a[10] = 12; //should print an error message and exit
	return 0;
	*/
	return 0;	
}
