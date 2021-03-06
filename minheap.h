#ifndef MINHEAP_H
#define MINHEAP_H

#include <limits.h>

#define ERROR_SIZE_LESS_THAN_1 INT_MIN
#define ERROR_SIZE_INCREASED INT_MAX
#define ERROR_POSITION_GREATER_THAN_HEAP_SIZE size
#define ERROR_SIZE_DECREASED INT_MIN
#define ERROR_POSITION_LESS_THAN_0 -1
#define ERROR_HEAP_FULL capacity



template<class T>
class minHeap //the main min heap class
{
	
	//these 3 are assigned by constructor
	int size; 
	int capacity;
	T* array; 
	//Instead of a new dynamic array, an array already containing the data elements is referenced by minHeap class so that the heap 
	//can be created in O(n) time complexity, rather than O(n log n) time complexity
	
	int heapify(int element_position); //heapify function is private b'coz it'll be used directly only by other member functions 
	void swap(T&, T&); //swaps two nodes of the heap
	public:
	
	minHeap(T* array, int size, int capacity) //constructor which takes an array of the elements, size and capacity as parameters. 
	{										  //See sample program.cpp to get a clear picture
		this->array= array;
		this->size=size;
		this->capacity=capacity;
		
		if(size>=capacity) 
		{
			return;
		}
	
		for(int i=(size-1)>>1; i>=0; i--) //The input array is heapified. 
		{								  //Heap creation takes O(n) Time Complexity (TC) [using aggregate analysis].
			heapify(i);
		}
		
	}
	
	int insert(T element);//to insert an element in the array of this heap. It takes O(log n) TC.
	int get_capacity(); //returns the total number of elements which can be accomodated
	int get_size(); //returns the total number of elements actually accomodated
	int extract_min(); //takes out and returns the root element of the heap. Root is the minimum in a min heap. It takes O(log n) TC.
	int heap_decrease_key(int element_position, int new_value); //It decreases the value of an element at a given position. It takes O(log n) TC.
	int heap_increase_key(int element_position, int new_value);//It increases the value of an element at a given position. It takes O(log n) TC.
	int heap_sort(T *output_array);//It extracts min in each iteration and copies it into the output array. This way output array is sorted with all the heap elements. It takes O(n log n) TC.
	int show_element(int element_position);//returns the element present at the given position
};

template<class T>

int minHeap<T>::insert(T element)
{
	if(size==capacity) //if heap is full
	{
		return ERROR_HEAP_FULL;
	}
		
	array[size++]=element; //initially size=0; It increases after insertion of every element
	
	for(int i=(size-1)>>1; i>=0; i--)//heapify starts from the least non=leaf node. This is b'coz leaves are always heapified.
	{
		heapify(i);
	}
	
	return 0;
}

template<class T>
int minHeap<T>::get_capacity()
{
	return capacity;
}

template<class T>
int minHeap<T>::get_size()
{
	return size;
}

template<class T>
void minHeap<T> :: swap(T& t1, T& t2) //to swap any two data objects
{
	T temp=t1;
	t1=t2;
	t2=temp;
}

template<class T>
int minHeap<T>::heapify(int element_position)
{
	int right_child_position=(element_position+1)<<1; 
	int left_child_position=right_child_position-1;
	/*
		Ideally it should be element_position*2 for left child and element_position*2+1 for right child. 
		But in that implementation instead of array[0] being the root, array[1] will have to be made the root.
		So here we have (element_position+1)*2 for left child and (element_position+1)*2-1 for right child
	*/
	int smallest_element_position=element_position;
	
	if (array[left_child_position] < array[smallest_element_position] && left_child_position<size)
	{
		smallest_element_position = left_child_position;
	}
	
	if (array[right_child_position] < array[smallest_element_position] && right_child_position<size)
	{
		smallest_element_position = right_child_position;
	}
	
	if(smallest_element_position != element_position)
	{
		swap(array[smallest_element_position], array[element_position]);
		heapify(smallest_element_position);
	}
	return 0;
}


template<class T>
int minHeap<T>::extract_min()//root is the min. It is returned back
{
	if(size < 1)
	{
		return ERROR_SIZE_LESS_THAN_1;
	}
	
	int min= array[0];//min=root
	swap(array[0], array[size-1]);//last element is swapped with the root
	size--;//heap size is decreased coz root no longer belongs to the heap
	heapify(0);//the new root is heapified. This way there will be a new min root.
	return min;
}

template<class T>
int minHeap<T> :: heap_decrease_key(int element_position, int new_value)
{
	if(size < 1)
	{
		return ERROR_SIZE_LESS_THAN_1;
	}
	
	if(element_position > size-1)
	{
		return ERROR_POSITION_GREATER_THAN_HEAP_SIZE;
	}
	
	if(element_position < 0)
	{
		return ERROR_POSITION_LESS_THAN_0;		
	}
	
	if(new_value > array[element_position])//if an attempt to increase the value of the element
	{
		return ERROR_SIZE_INCREASED;
	}
	
	array[element_position]=new_value;
	
	int parent_position=(element_position+1>>1)-1;
	/*
		Ideally it should be parent_position=element_position/2. 
		But in that implementation instead of array[0] being the root, array[1] will have to be made the root.
		So here we have ((element_position+1)/2) -1 for parent.
	*/
	while((array[parent_position] > array[element_position]) && (parent_position>=0))
	{
		swap(array[parent_position], array[element_position]);
		element_position = parent_position;
		parent_position=(parent_position-1)>>1;
	} 
	return 0;
}

template<class T>
int minHeap<T> :: heap_increase_key(int element_position, int new_value)
{
	if(size < 1)
	{
		return ERROR_SIZE_LESS_THAN_1;
	}
	
	if(element_position > size-1)
	{
		return ERROR_POSITION_GREATER_THAN_HEAP_SIZE;
	}
	
	if(element_position < 0)
	{
		return ERROR_POSITION_LESS_THAN_0;		
	}
	
	if(new_value < array[element_position]) //if an attempt to decrease the value of the element
	{
		return ERROR_SIZE_DECREASED;
	}
	
	array[element_position]=new_value;
	
	heapify(element_position);
}

template<class T>
int minHeap<T> :: heap_sort(T *output_array)
{
	if(size < 1)
	{
		return ERROR_SIZE_LESS_THAN_1;
	}
	
	
	int max_loop_count=size; //extract_min will decrease 'size' each time
	
	for (int i=0; i<max_loop_count; i++)
	{
		output_array[i]=extract_min();
	}
	
	
}

template<class T>
int minHeap<T>::show_element(int element_position)
{
	if(element_position>size-1)
	{
		return ERROR_POSITION_GREATER_THAN_HEAP_SIZE;
	}
	
	return array[element_position];
}


#endif
