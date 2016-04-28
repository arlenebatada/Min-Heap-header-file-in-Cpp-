#include "minHeap.h"
#include <iostream>

using namespace std;

class some_random_class
{
	public:
	int value;
	char a;
	
	operator int() 
	{
		return value;
	}
	
	operator = (int x)
	{
		value=x;
	}
	/*
	operator int () is for type casting an object of heapNode to int. 
	operator = (int x) is to overload '=' operator. 
	With this operator we can assign object1.value to object2.value of this class.
	These two functions are mandatory for every user defined entities because internally minHeap deals with int only.
	*/
};


int main()
{
	int int_array[10]={10, 8, 11, 2, 1, 0};//capacity=10
	
	some_random_class c1, c2, c3, c4;
	c1.value=10;
	c2.value=9;
	c3.value=1;
	c4.value=0;
	
	some_random_class some_random_class_array[3]={c1, c2, c3};//capacity=3
	
	/* creating 2 Min Heaps */
	minHeap<int> m1(int_array, 6, 10); //6 elements filled out of 10. So size=6 and capacity=10
	minHeap<some_random_class> m2(some_random_class_array, 3, 3); //all 3 places filled out of maximum 3 places
	//put respective data type inside < > brackets
	
	/*All the heap operations below can be applied to any data-types irrespective of them being user defined or built in data type */
	/*In case of user defined classes, appropriate overloading needs to be done */
	
	cout<<m2.get_capacity()<<endl; //gives 3 as o/p
	cout<<m2.extract_min()<<endl; //gives 1 as o/p b'coz 1 is min of {10, 9, 1}. It also decrements size
	cout<<m2.get_size()<<endl; //gives 2 as o/p b'coz extract_min() extracted 1 out of {1, 9, 10} with only {9, 10} remaining
	m2.insert(c4); //it'll insert c4 into {c3, c2, c1} i.e 0 into {1, 9, 10}
	
	cout<<m1.show_element(2)<<endl; //shows 10 b'coz 10 is at 2nd position (starting from 0) in the Min Heap m1
	
	m1.heap_increase_key(2, 11);//It'll increase 10 (at 2nd position starting from 0) to 11 and then perform heapify function
	m1.heap_decrease_key(0, -1); //It'll change 0 (at 0th position) to -1
	cout<<m1.show_element(0);//displays -1
	
	//new arrays to store sorted values rendered by heap sort
	int int_sorted_array[10];
	some_random_class some_random_class_sorted_array[3]; 
	
	int m1_size=m1.get_size();
	int m2_size=m2.get_size();
	
	m1.heap_sort(int_sorted_array);
	m2.heap_sort(some_random_class_sorted_array);
	
	cout<<endl<<"Some random class sorted values by heap sort:"<<endl;
	for(int i=0; i<m2_size; i++)
	{
		cout<<some_random_class_sorted_array[i]<<endl;
	}
	cout<<endl<<"int sorted values by heap sort:"<<endl;
	for(int i=0; i<m1_size; i++)
	{
		cout<<int_sorted_array[i]<<endl;
	}
}


