/*************************************************************************/
/*	File : XClassArray.h												 */
/*	Author :  Aymeric Bard												 */	
/*																		 */	
/*	Virtools SDK 															 */	 
/*	Copyright (c) Virtools 2000, All Rights Reserved.						 */	
/*************************************************************************/
#ifndef _XCLASSARRAY_H_
#define _XCLASSARRAY_H_  "$Id:$"

#include "XUtil.h"

#ifdef _WIN32
#pragma warning(disable : 4786)
#endif

/************************************************
{filename:XClassArray}
Name: XClassArray

Summary: Class representation of an array.

Remarks:
	This array is designed to hold structure or class
which have something specific to do on the construction,
deletion or recopy, like allocating/destroying pointers.



See Also : XArray, XSArray
************************************************/
template <class T>
class XClassArray
{
public:
	typedef T* Iterator;

	/************************************************
	Summary: Constructors.

	Input Arguments: 
		ss: Default number of reserved elements.
		a: An array to copy from.

	************************************************/
	XClassArray(int ss=0)
	{
		// Allocated
		if(ss>0) {
			m_Begin = Allocate(ss);
			m_End = m_Begin;
			m_AllocatedEnd = m_Begin+ss;
		} else {
			m_AllocatedEnd = 0;
			m_Begin = m_End = 0;
		}
	}

	XClassArray(const XClassArray<T>& a)
	{
		// the resize
		int size = a.Size();
		m_Begin = Allocate(size);
		m_End = m_Begin+size;
		m_AllocatedEnd = m_End;
		// The copy
		XCopy(m_Begin,a.m_Begin,a.m_End);
	}

	/************************************************
	Summary: Destructor.

	Remarks:
		Release the elements contained in the array. If
	you were storing pointers, you need first to iterate 
	on the array and call delete on each pointer.
	************************************************/
	~XClassArray()
	{
		Clear();
	}

	/************************************************
	Summary: Affectation operator.

	Remarks:
		The content of the array is enterely overwritten
	by the given array.
	************************************************/
	XClassArray<T>& operator = (const XClassArray<T>& a)
	{
		if(this != &a) {
			if (Allocated() >= a.Size()) { // No need to allocate
				// The copy
				XCopy(m_Begin,a.m_Begin,a.m_End);
				m_End = m_Begin + a.Size();
			} else {
				Free();
				// the resize
				int size		= a.Size();
				m_Begin			= Allocate(size);
				m_End			= m_Begin+size;
				m_AllocatedEnd	= m_End;
				// The copy
				XCopy(m_Begin,a.m_Begin,a.m_End);
			}
		}

		return *this;
	}

	/************************************************
	Summary: Removes all the elements from an array.

	Remarks:
		There is no more space reserved after this call.
	************************************************/
	void Clear()
	{
		Free();
		m_Begin = 0;
		m_End = 0;
		m_AllocatedEnd = 0;
	}

	/************************************************
	Summary: Reserves n elements fot an array.

	Remarks:
		The elements beyond the reserved limit are 
	discarded.
	************************************************/
	void Reserve(int size)
	{
		// allocation of new size
		T* newdata = Allocate(size);
		
		// Recopy of old elements
		T* last = XMin(m_Begin+size,m_End);
		XCopy(newdata,m_Begin,last);

		// new Pointers
		Free();
		m_End = newdata+(last-m_Begin);
		m_Begin = newdata;
		m_AllocatedEnd = newdata+size;
	}

	/************************************************
	Summary: Resizes th elements numbers of an array.

	Remarks:
		If the size is greater than the reserved size,
	the array is reallocated at the exact needed size.
	If not, threr is no reallocation at all. Resize(0) 
	is faster than Clear() if you know you will probably
	push some more elements after.
	************************************************/
	void Resize(int size)
	{
		// we check if the array has enough capacity
		int oldsize = (m_AllocatedEnd-m_Begin);
		// If not, we allocate extra data
		if(size > oldsize) Reserve(size);
		// We set the end cursor
		m_End = m_Begin+size;
	}

	/************************************************
	Summary: Inserts an element at the end of an array.

	Input Arguments: 
		o: object to insert.
	************************************************/
	void PushBack(const T& o)
	{
		XInsert(m_End,o);
	}

	/************************************************
	Summary: Expands an array of e elements.
	
	Input Arguments: 
		e: size to expand.
	************************************************/
	void Expand(int e = 1)
	{
		// we check if the array has enough capacity
		
		// If not, we allocate extra data
		while (Size()+e > Allocated()) {
			Reserve(Allocated()?Allocated()*2:2);
		}
		// We set the end cursor
		m_End += e;
	}

	/************************************************
	Summary: Inserts an element at the start of an array.

	Input Arguments: 
		o: object to insert.
	************************************************/
	void PushFront(const T& o)
	{
		XInsert(m_Begin,o);
	}

	/************************************************
	Summary: Inserts an element before another one.

	Input Arguments: 
		i: iterator on the element to insert before.
		pos: position to insert the object
		o: object to insert.

	Remarks:
		The element to insert before is given as 
	an iterator on it, i.e. a pointer on it in 
	this case.
	************************************************/
	void Insert(T* i, const T& o)
	{
		// TODO : s'assurer que i est dans les limites...
		if(i<m_Begin || i>m_End) return;

		// The Call
		XInsert(i,o);
	}
	void Insert(int pos, const T& o)
	{
		Insert(m_Begin+pos,o);
	}

	/************************************************
	Summary: Removes the last element of an array.
	************************************************/
	void PopBack()
	{
		// we remove the last element only if it exists
		if(m_End > m_Begin)	XRemove(m_End-1);
	}

	/************************************************
	Summary: Removes the first element of an array.
	************************************************/
	void PopFront()
	{
		// we remove the first element only if it exists
		if(m_Begin != m_End) XRemove(m_Begin);
	}

	/************************************************
	Summary: Removes an element.

	Input Arguments: 
		i: iterator on the element to remove.
		pos: position of the object to remove.

	Return Value: an iterator on the next 
	element after the element removed (to go on with 
	an iteration).

	Remarks:
		The elements are given by iterators on them, 
	i.e. pointer on them in this case.
	************************************************/
	T* Remove(T* i)
	{
		// we ensure i is in boundary...
		if(i<m_Begin || i>=m_End) return 0;

		// the Call
		return XRemove(i);
	}

	
	T* RemoveAt(int pos)
	{
		// we ensure i is in boundary...
		if (pos >= Size()) return NULL;

		// the Call
		return XRemove(m_Begin+pos);
	}

	void FastRemove(const T& o)
	{
		FastRemove(Find(o));
	}

	void FastRemove(const Iterator& iT)
	{
		// we ensure i is in boundary...
		if(iT<m_Begin || iT>=m_End) 
			return;

		m_End--;
		if (iT < m_End)
			*iT = *m_End;
	}
	
	/************************************************
	Summary: Access to an array element.

	Input Arguments: 
		i: index of the element to access.

	Return Value: a reference on the object accessed.

	Remarks:
		No test are provided on i.
	************************************************/
	T& operator [](int i)  const
	{
		XASSERT(i>=0 && i<Size());		
		return *(m_Begin+i);
	}

	/************************************************
	Summary: Access to an array element.

	Input Arguments: 
		i: index of the element to access.

	Return Value: a pointer on the object accessed.

	Remarks:
		End() is returned if i is outside the array 
	limits.
	************************************************/
	T* At(unsigned int i)  const
	{
		if (i >= (unsigned int)Size()) return m_End;
		return m_Begin+i;
	}

	/************************************************
	Summary: Swaps two items in array.

	Input Arguments: 
		pos1: position of first item to swap
		pos2: position of second item to swap.
	************************************************/
	void Swap(int pos1,int pos2)
	{
		char buffer[sizeof(T)];
		memcpy(buffer,m_Begin+pos1,sizeof(T));
		memcpy(m_Begin+pos1,m_Begin+pos2,sizeof(T));
		memcpy(m_Begin+pos2,buffer,sizeof(T));
	}

	/************************************************
	Summary: Swaps two arrays.

	Input Arguments: 
		o: second array to swap.
	************************************************/
	void Swap(XClassArray<T>& a)
	{
		XSwap(m_Begin,a.m_Begin);
		XSwap(m_End,a.m_End);
		XSwap(m_AllocatedEnd,a.m_AllocatedEnd);
	}

	/************************************************
	Summary: Returns the last element of an array.

	Remarks:
		No test are provided to see if there is an
	element.
	************************************************/
	T& Back() {return *(End()-1);}

	const T& Back() const {return *(End()-1);}	

	/************************************************
	Summary: Returns an iterator on the first element.

	Example:
		Typically, an algorithm iterating on an array 
	looks like:

		for(T* t = a.Begin(); t != a.End(); ++t) {
			// do something with *t
		}

	************************************************/
	T* Begin()  const {return m_Begin;}

	/************************************************
	Summary: Returns an iterator after the last element.
	************************************************/
	T* End()  const {return m_End;}

	/************************************************
	Summary: Returns the elements number.
	************************************************/
	int Size() const {return m_End-m_Begin;}

	/************************************************
	Summary: Returns the elements allocated.
	************************************************/
	int Allocated() const {return m_AllocatedEnd-m_Begin;}

	/************************************************
	Summary: Returns the occupied size in memory in bytes
	
	Parameters:
		addstatic: TRUE if you want to add the size occupied
	by the class itself.
	************************************************/
	int GetMemoryOccupation(XBOOL addstatic=FALSE) const {
		return Allocated()*sizeof(T)+(addstatic?sizeof(*this):0);
	}

	/************************************************
	Summary: Finds an element.

	Input Arguments: 
		o: element to find.

	Return Value: a pointer on the first object found 
	or End() if the object is not found.
	************************************************/
	T* Find(const T& o)  const
	{
		// If the array is empty
		if(!(m_End - m_Begin)) return m_End;
		T* t = m_Begin;
		while(t < m_End && *t != o) 
			++t;					

		return t;
	}

	/************************************************
	Summary: Returns the position of an element.

	Input Arguments: 
		o: element to find.

	Return Value: position or -1 if not found.
	************************************************/
	int GetPosition(const T& o)  const
	{
		T* t = Find(o);
		// If the element is not found
		if(t == m_End) return -1;
		// else return the position
		return t-m_Begin;
	}

	
	static
	int XCompare(const void *elem1, const void *elem2 )
	{
		return *(T*)elem1 - *(T*)elem2;
	}

	/************************************************
	Summary: Sorts an array with a quick sort.

	Input Arguments: 
		compare: The function comparing two elements.

	Remarks:
		Two sorts algorithm are available : BubbleSort 
	and (quick)Sort.
	************************************************/
	void Sort(  VxSortFunc Fct = XCompare)
	{
		qsort(m_Begin,Size(),sizeof(T),Fct);
	}

protected:
	///
	// Methods

	
	void XCopy(T* dest, T* start, T* end)
	{
		while(start != end) {
			*dest = *start;
			start++;
			dest++;
		}
	}
	
	
	void XMove(T* dest, T* start, T* end)
	{
		if (dest>start)
		{
			dest += end-start;
			while(start != end) {
				--dest;
				--end;
				*dest = *end;
			}
		} else XCopy(dest,start,end);
	}
	
	void XInsert(T* i, const T& o)
	{
		// Test For Reallocation
		if(m_End+1 > m_AllocatedEnd) {
			int newsize = (m_AllocatedEnd-m_Begin)*2;//+m_AllocationSize;
			if(!newsize) newsize = 1;
			T* newdata = Allocate(newsize);
			
			// copy before insertion point
			XCopy(newdata,m_Begin,i);

			// copy the new element
			T* insertionpoint = newdata+(i-m_Begin);
			*(insertionpoint) = o;
			
			// copy after insertion point
			XCopy(insertionpoint+1,i,m_End);

			// New Pointers
			m_End = newdata+(m_End-m_Begin);
			Free();
			m_Begin = newdata;
			m_AllocatedEnd = newdata+newsize;
		} else {
			// copy after insertion point
			XMove(i+1,i,m_End);
			// copy the new element
			*i = o;
		}
		m_End++;
	}

	
	T* XRemove(T* i)
	{
		// copy after insertion point
		XMove(i,i+1,m_End);
		m_End--;
		return i;
	}

	///
	// Allocation and deallocation methods : to be override for alignement purposes

	
	T* Allocate(int size)
	{
		if(size) return new T[size];
		else return 0;
	}

	
	void Free()
	{
		delete [] m_Begin;
	}

	///
	// Members

	
	T*			m_Begin;
	
	T*			m_End;
	
	T*			m_AllocatedEnd;

};


#endif
