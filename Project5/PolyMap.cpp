/*
Project #5 - Polynomial Arithmetic Redux
*/

#include<iostream>
#include<fstream>
#include <sstream>
#include<map>
using namespace std;

class Poly
{
public:
    map<int, int> poly;
    Poly() {}
    
    Poly operator+(Poly p) 
	{
        map<int,int>:: iterator iter1 = poly.begin();
        Poly temp;
        while (iter1 != poly.end()) 
		{
            temp.append(iter1->second, iter1->first);
            ++iter1;
        }
        
        map<int,int>:: iterator iter2 = p.poly.begin();
        while (iter2 != p.poly.end()) 
		{
            temp.append(iter2->second, iter2->first);
            ++iter2;
        }
        return temp;
    }
    
    Poly operator-(Poly p) 
	{
        map<int,int>:: iterator iter1 = poly.begin();
        Poly temp;
        while (iter1 != poly.end()) 
		{
            temp.append(iter1->second, iter1->first);
            ++iter1;
        }
        
        map<int,int>:: iterator iter2 = p.poly.begin();
        while (iter2 != p.poly.end()) 
		{
            temp.append((-1)*iter2->second, iter2->first);
            ++iter2;
        }
        return temp;
    }
    
    Poly operator*(Poly p) 
	{  
        map<int,int>:: iterator iter1 = poly.begin();
        map<int,int>:: iterator iter2 = p.poly.begin();
        Poly temp;
        while (iter1 != poly.end()) 
		{
            while (iter2 != p.poly.end()) 
			{
                int n = iter1->first + iter2->first;
                temp.append(iter1->second * iter2->second, n);
                ++iter2;
            }
            ++iter1;
            iter2 = p.poly.begin();
        }
        return temp;
    }
    
	void append(int coef, int pow) 
	{
        map<int, int>:: iterator iter = poly.begin();
        
        while (iter != poly.end()) 
		{
            if (iter->first == pow)    
			{
				iter->second += coef;    
				return;
			}
            ++iter;
        }
        poly.insert(pair<int, int>(pow, coef));
    }
    
    friend ostream& operator<< (ostream& os, Poly p);
};

ostream& operator<<(ostream& os, Poly p) 
{	
    map<int, int>:: reverse_iterator iter;
    for(iter = p.poly.rbegin(); iter != p.poly.rend(); iter++)
	{		
		if(iter->second != 0)
			os << iter->second << " " << iter->first  << " ";
	}
    os << endl;
    return os;
};


int main() 
{
	ifstream read;
    ofstream output;
    read.open("input.txt");    
    output.open("output.txt");
    if(!read)
    {
    	cout << "Unable to open input file." << endl;
    	exit(1);
	}
	
	string str1, str2;
    int base, pow; 
    while (getline(read, str1)) 
	{
		Poly poly1;
		istringstream iss1(str1);
        while(iss1 >> base >> pow) 
            poly1.append(base, pow);
			      
        if(getline(read, str2)) 
		{
			Poly poly2;
			istringstream iss2(str2);
            while (iss2 >> base >> pow) 
                poly2.append(base, pow);
                
			output << "First's original " << str1 << endl;
			output << "First's canonical " << poly1;
			output << "Second's original " << str2 << endl;
            output << "Second's canonical  " << poly2;
            
            output << "Their sum " << poly1+poly2;
            output << "Their difference " << poly1-poly2;
            output << "Their product " << poly1*poly2;
        }
		output << endl;        
    }
    read.close();
    output.close();
}
