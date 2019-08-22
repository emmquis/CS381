//CS381 Project2

#include <iostream>
#include<fstream>
#include <sstream>  
using namespace std;

template<class T>
class LinkedList;

template<class T>
ostream& operator<<(ostream& os, LinkedList<T> list);

template<class T>
class Node 
{
private:
    int coef;
    int exp;
    Node* next;
public:
    Node ()             
	{
		next = 0;
	}
	
    Node (int co, int pow)     
	{
		coef = co; 
		exp = pow; 
		next = nullptr;
	}
	
	~Node()
	{
		delete next;
	}
	
    int &getCoef()      
	{
		return coef;
	}
	
    int &getExp()      
	{
		return exp;
	}
	
    Node* &getNext()
	{
		return next;
	}
};

template <class T>
class LinkedList 
{
private:
    Node<T>* head;
    
public:
    LinkedList() 
	{
        head = new Node <T>(-99999, -99999);
    }

	~LinkedList()
	{

	}

    LinkedList<T> operator+(LinkedList<T> list)
	{
        LinkedList<T> temp;
        Node<T>* firstH = head->getNext();
        Node<T>* secH = list.head->getNext();
        while (firstH != nullptr) 
		{
            temp.insert(new Node<T> (firstH->getCoef(), firstH->getExp()));
            firstH = firstH->getNext();
        }
        while (secH != nullptr) 
		{
            temp.insert(new Node<T> (secH->getCoef(), secH->getExp()));
            secH = secH->getNext();
        }
        return temp;
    }
    
    LinkedList<T> operator-(LinkedList<T> list)
	{
        LinkedList<T> temp;
        Node<T>* firstH = head->getNext();
        Node<T>* secH = list.head->getNext();
        while (firstH != nullptr) 
		{
            temp.insert(new Node<T> (firstH->getCoef(), firstH->getExp()));
            firstH = firstH->getNext();
        }
        while (secH != nullptr) 
		{
            temp.insert(new Node<T> ((-1)*secH->getCoef(), secH->getExp()));
            secH = secH->getNext();
        }
        return temp;
    }
    
    LinkedList<T> operator*(LinkedList<T> list) 
	{
        LinkedList<T> temp;
        Node<T>* firstH = head->getNext();
        Node<T>* secH = list.head->getNext();
        while (firstH != nullptr) 
		{
            while (secH != nullptr ) 
			{
                Node<T>* pro = new Node<T> (firstH->getCoef() * secH->getCoef(), firstH->getExp() + secH->getExp());
                temp.insert(pro);
                secH = secH->getNext();
            }
            firstH = firstH->getNext();
            secH = list.head->getNext();
        }
        return temp;
    }
    
    void insert(Node<T>* no) 
	{
        Node<T>* t = head;
        while (t->getNext() != nullptr) 
		{

            if ((no->getExp() <= t->getExp()) && (no->getExp() > t->getNext()->getExp())) 
			{
                if (no->getExp() == t->getExp())   
				{
                    t->getCoef() += no->getCoef();
                    return;
                }
                Node<T>* temp = t->getNext();
                t->getNext() = no;
                no->getNext() = temp;
                return;
            }
            t = t->getNext();
        }

        if (no->getExp() == t->getExp())   
		{
            t->getCoef() = t->getCoef() + no->getCoef();
            return;
        }
        t->getNext() = no;
    }
    
    friend ostream& operator<< <T>(ostream& os, LinkedList<T> list);
};

template<class T>
ostream& operator<<(ostream& os, LinkedList<T> list) 
{
    Node<T>* temp = list.head->getNext();
    while (temp)
	{
        if (temp->getCoef() == 0)  
		{

            temp =temp->getNext();
        }
        else    
		{
            os << temp->getCoef() << "x ^" << temp->getExp() << "  ";
            temp = temp->getNext();
        }
    }
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

    while (getline (read, str1)) 
	{
        LinkedList<int> list1;
        istringstream strs1 (str1);
        while (strs1)   
		{
			strs1 >> base >> pow;
            Node<int>* no = new Node<int> (base, pow);
            list1.insert(no);
        }

        getline(read, str2);
        LinkedList<int> list2;
        istringstream strs2 (str2);
        while (strs2)   
		{
			strs2 >> base >> pow;
            Node<int>* no2 = new Node <int> (base, pow);
            list2.insert(no2);
        }
		output << "Original List 1		" << str1 << endl;
        output << "Original List 2		" << str2 << endl;
        output << "Canonical List 1 	" << list1 << endl;
        output << "Canonical List 2 	" << list2 << endl;
        
        
        output << list1 << " +  " << list2 << " =  " << list1+list2 << endl;
        output << list1 << " -  " << list2 << " =  " << list1-list2 << endl;
        output << list1 << " *  " << list2 << " =  " << list1*list2 << endl;
        
        output << endl;
    }
          
    read.close();
    output.close();
    return 0;
}
