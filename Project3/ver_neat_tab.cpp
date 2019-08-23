//Very Neat TableProject #3
//main class provided by TA

#include<iostream>
#include <cstdlib>
#include<cassert>
#include <cmath>
using namespace std;

// forward declaration
template <class T>
class SA;

template <class T>
ostream& operator<<(ostream& os, SA<T> s);

template<class T>
class SM;

template<class T>
ostream& operator<<(ostream& os, SM<T> m);

template<class T>
class VNT;

template<class T>
ostream& operator<<(ostream& os, VNT<T> vnt);

template <class T>
class SA 
{
private:
    int low, high;
    T* p;
public:
    // default constructor
    // allows for writing things like SA a;
    SA()
	{
		low=0; 
		high=-1;
		p=nullptr;
	}
		
	// 2 parameter constructor lets us write
    // SA x(10,20);
    SA(int l, int h)
	{
        if((h-l+1)<=0) 
		{
            cout << "constructor error in bounds definition" << endl;
            exit(1);
        }
        low = l;
        high = h;
        p=new T[h-l+1];
    }
        
    // single parameter constructor lets us
    // create a SA almost like a "standard" one by writing
    // SA x(10); and getting an array x indexed from 0 to 9
    SA(int i) 
	{
        low = 0; 
		high = i-1;
        p=new T[i];
    }
    // copy constructor for pass by value and
    // initialization
    SA(const SA & s)
	{
        int size = s.high-s.low+1;
        p = new T[size];
        for(int i = 0; i < size; i++)
            p[i]=s.p[i];
        low = s.low;
        high = s.high;
    }
        
    // destructor
    ~SA()
	{
        delete [] p;
    }
        
    //overloaded [] lets us write
    //SA x(10,20); x[15]= 100;
    T& operator[](int i)
	{
        if(i < low || i > high) 
		{
            cout << "index "<< i <<" out of range" << endl;
            exit(1);
        }
        return p[i-low];
    }
    // overloaded assignment lets us assign
    // one SA to another
    SA & operator=(const SA s)
	{
        if(this == &s)
			return *this;
        delete [] p;
        int size = s.high - s.low + 1;
        p = new T[size];
        for(int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
        return *this;
    }
    // overloads << so we can directly print SAs
    //template <class T>
    friend ostream& operator<< <T> (ostream& os, SA<T> s);
};

template <class T>
ostream& operator<<(ostream& os, SA<T> s)
{
    int size = s.high - s.low + 1;

    for(int i=0; i<size; i++) 
	{
        if(i == 0)
            cout << s.p[i];
        else
            cout << ", " << s.p[i];
    }
    return os;
};

template<class T>
class SM 
{
private:    
    int row_low, row_high;
	int col_low, col_high;
	SA<SA<T>> matrix;

public:
	
    SM()
    {
    	row_low = 0;
    	row_high = 0;
    	col_low = 0;
    	col_high = 0;
	}

    SM(int r, int c)
    {
    	row_low  = 0;
    	row_high = r-1;
    	col_low  = 0;
    	col_high = c-1;

    	matrix = SA<SA<T> >(0, r-1);
    	for(int i=0; i<=r-1; i++) 
		{
        	matrix[i] = SA<T>(0, c-1);
        	for(int j=0; j<=c-1; j++)
            	matrix[i][j] = 0;
    	}
	}

    SM(int rl, int rh, int cl, int ch)
    {
    	row_low  = rl;
    	row_high = rh;
    	col_low  = cl;
    	col_high = ch;

    	matrix = SA<SA<T> >(rl, rh);
    	for(int i = rl; i <= rh; i++) 
		{
        	matrix[i] = SA<T>(cl, ch);
        	for(int j = cl; j <= ch; j++)
            	matrix[i][j] = 0;
    	}
	}
	
    SA<T>& operator[](int i)
    {
    	return matrix[i];
	} 
	   
    friend ostream& operator<< <T>(ostream& os, SM<T> m);
};


template<class T>
ostream& operator<<(ostream& os, SM<T> m) 
{
	for(int i = m.row_low; i <= m.row_high; i++)
	{
		for(int j = m.col_low; j <= m.col_high; j++)
		{
			os << m.matrix[i][j] << " ";
		}
		os << endl;
	}
}

template<class T>
class VNT 
{
private:
    int rows, cols;
    SM<T> table;

public:	
	VNT(int r, int c)
    {
		rows = r;
    	cols = c;
    	SM<T> temp(r, c);
    	for(int i = 0; i < r; i++) 
		{
        	for(int j = 0; j < c; j++) 
			{
            	temp[i][j] = INT_MAX;
        	}
    	}
    	table = temp;
	}

	void add(int num) 
	{	
		int row = rows-1;
		int col	= cols-1;
    	if(table[row][col] < INT_MAX) 
			cout << "VNT is full." << endl;
    	table[row][col] = num;   	
   		bubUL(row, col);
	}	
  

	T getMin() 
	{ 
    	if(table[0][0] == INT_MAX) 
			cout << "VNT is empty." << endl;
    	int min = table[0][0];
    	table[0][0] = INT_MAX;
    	bubDR(0, 0);
    	return min; 	
	}
   
	void sort(int k[], int size) 
	{
    	int n = sqrt(size) + 1;
    	VNT a(n, n);
    	
    	for(int i = 0; i < size; i++) 
		{
        	a.add(k[i]);
    	}

    	for(int i = 0; i < size; i++)
    	{
    		k[i] = a.getMin();
		}
	}
	
	bool find(int num) 
	{
    	if(num < table[0][0]) 
			return false;
    	if(num > table[rows-1][cols-1]) 
			return false;			
    	if(table[0][0] == INT_MAX) 
			return false;

    	int row = rows-1;
		int col = 0;
    	while(row >= 0 && col < cols) 
		{
        	int cur = table[row][col];
        	if(num < cur) 
				row--;
        	else if(num > cur) 
				col++;
        	else 
				return true;
		}
    	return false;
	}
	
	void bubUL(int row, int col) 
	{

		int cr = returnElem(row, col);
    	int up = returnElem(row-1, col);
    	int lf = returnElem(row, col-1);
    	if(cr >= lf && cr >= up)
    		return;
    	else if(up > lf) 
		{
    	    table[row][col] = up;
        	table[row-1][col] = cr;
        	row--;
        	bubUL(row, col);
    	} 
		else 
		{
        	table[row][col] = lf;
        	table[row][col-1] = cr;
        	col--;
        	bubUL(row, col);
    	}
    	
	}
	
	void bubDR(int row, int col) 
	{
	
    	int dn = returnElem(row+1, col);
    	int rt = returnElem(row, col+1);
    	if(dn == INT_MAX && rt == INT_MAX)
        	return;
    	if(dn > rt) 
		{
			table[row][col] = rt;
        	table[row][col+1] = INT_MAX;
        	col++;
        	bubDR(row, col);
    	} 
		else 
		{
			table[row][col] = dn;
        	table[row+1][col] = INT_MAX;
        	row++;
        	bubDR(row, col);
    	}
	}
	
	T returnElem(int row, int col) 
	{
    	if(row < 0 || col < 0)
        	return INT_MIN;
    	if(row >= rows || col >= cols)
        	return INT_MAX;
    	return table[row][col];
	}

    friend ostream& operator<< <T>(ostream&, VNT<T>);
};

template<class T>
ostream& operator<<(ostream& os, VNT<T> vnt) 
{
    for(int i = 0; i < vnt.rows; i++) 
	{
        for(int j = 0; j < vnt.cols; j++) 
		{
            int v = vnt.table[i][j];
            if(v == INT_MAX)
                os << " ?";
            else
                os << v << " ";
        }
        os << endl;
    }
    return os;
};

//main class provided by TA
//
//  main.cpp
//  VNT
//
//  Created by Zhenhua Cai on 10/22/18.
//  Copyright © 2018 Zhenhua Cai. All rights reserved.
//

int main() 
{	
    VNT<int> a(5,6);
    
    for(int i=0;i<30;i++){
        a.add(i*i);
    }
    if(a.find(25)){
        cout<<"Found 25 in VNT table\n";
    }
    if(!a.find(26)){
        cout<<"26 is not in the VNT table\n";
    }
    cout<<"The minimum value in VNT table is: "<<a.getMin()<<endl;
    
    int arr[10]= {2,6,9,0,3,1,8,4,7,5};
    cout<<"Unsorted array is:\n";
    for(auto e:arr)
        cout<<e<<" ";
    cout<<endl;
    
    a.sort(arr,10);
    cout<<"Sorted Array is:\n";
    for(auto e:arr)
        cout<<e<<" ";
    cout<<endl;
    
    return 0;
/*
    int r = 3;
	int c = 4;

    int arr1[12] = {4, 21, 3, 1, 65, 54, 3, 2, 22, 8, 56, 23};
    int len1 = sizeof(arr1)/sizeof(*arr1);

	cout << "Array List: ";
	for(int i = 0; i < len1; i++)
	{
		cout << arr1[i] << " ";
	}
	cout << endl;
	cout << "---------------------------------" << endl;

    VNT<int> A(r, c);
    for(int i = 0; i < len1; i++) 
	{
        cout << "Add: " << arr1[i] << endl;
        A.add(arr1[i]);
        cout << A << endl;
    }
    
    cout << "---------------------------------" << endl;

    cout << "Enter a number to find: ";
    int num;
    cin >> num;

    bool check = A.find(num);
    if(check == 1)
    	cout << "Found in array!" << endl;
    if(check == 0)
    	cout << "Number not found in array." << endl;
    
	cout << "---------------------------------" << endl;
    
    cout << "Minimum value: " << A.getMin() << endl;
    cout << A;
    
    cout << "---------------------------------" << endl;
    
    cout << "Unsorted:" << endl;
    for(int i = 0; i < len1; i++) 
	{
        cout << " | " << arr1[i] << " | ";
    }
    cout << endl;
    
    A.sort(arr1, len1); 
	cout << "Sorted:" << endl;
    for(int i = 0; i < len1; i++) 
	{
        cout << " | " << arr1[i] << " | ";
    }
    cout << endl;
    
    return 0;
*/
}


