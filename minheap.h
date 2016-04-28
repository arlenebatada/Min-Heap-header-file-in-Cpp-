#ifndef MINHEAP_H
#define MINHEAP_H

#include <limits.h>

#define ERROR_SIZE_LESS_THAN_1 INT_MIN
#define ERROR_SIZE_INCREASED INT_MAX
#define ERROR_POSITION_GREATER_THAN_HEAP_SIZE size
#define ERROR_SIZE_DECREASED INT_MIN
#define ERROR_POSITION_LESS_THAN_0 -1
#define ERROR_HEAP_FULL capacity


template<class U>
void swap(U& u1, U& u2)
{
	U temp=u1;
	u1=u2;
	u2=temp;
}

template<class T>

class minHeap 
{
	

	int size;
	int capacity;
	T* array;
	
	int heapify(int element_position);
	
	public:
	
	minHeap(T* array, int size, int capacity)
	{
		this->array= array;
		this->size=size;
		this->capacity=capacity;
		
		if(size>=capacity) 
		{
			return;
		}
	
		for(int i=(size-1)>>1; i>=0; i--)
		{
			heapify(i);
		}
		
	}
	
	int insert(T element);
	int get_capacity();
	int get_size();
	int extract_min();
	int heap_decrease_key(int element_position, int new_value);
	int heap_increase_key(int element_position, int new_value);
	int heap_sort(T *output_array);
	int show_element(int element_position);
};

template<class T>

int minHeap<T>::insert(T element)
{
	if(size==capacity) //if heap is full
	{
		return ERROR_HEAP_FULL;
	}
		
	array[size++]=element;
	
	for(int i=(size-1)>>1; i>=0; i--)
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
int minHeap<T>::extract_min()
{
	if(size < 1)
	{
		return ERROR_SIZE_LESS_THAN_1;
	}
	
	int min= array[0];
	swap(array[0], array[size-1]);
	size--;
	heapify(0);
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
	
	if(new_value > array[element_position])
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
	
	if(new_value < array[element_position])
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
