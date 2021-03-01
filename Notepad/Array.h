// Array.h
#ifndef _ARRAY_H
#define _ARRAY_H

typedef signed long int Long;

template <typename T>
class Array {
public:
	Array(Long capacity = 256);
	Array(const Array& source);
	~Array();
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void *key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Long *(*indexse), Long *count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void *key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*));
	void BubbleSort(int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void Merge(const Array& one, const Array& other, int(*compare)(void*, void*));
	T& GetAt(Long index);
	Array& operator =(const Array& source);
	T& operator [](Long index);
	T* operator +(Long index);
	Long GetCapacity() const;
	Long GetLength() const;

private:
	T(*front);
	Long capacity;
	Long length;
};

/*
명칭 : Array
기능 : 배열을 생성한다.(생성자)
입력 : 할당량
출력 : X
*/
template <typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}

/*
명칭 : Array
기능 : 복사 생성자를 만든다.
입력 : 배열의 주소에 의한 참조
출력 : X
*/
template <typename T>
Array<T>::Array(const Array& source) {
	Long i = 0;
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

/*
명칭 :  ~Array
기능 : 배열을 소멸시킨다.
입력 : X
출력 : X
*/
template <typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[] this->front;
	}
}

/*
명칭 : Store
기능 : 배열에서 저장한다.
입력 : 위치, 오브젝트
출력 : 위치
*/
template <typename T>
Long Array<T>::Store(Long index, T object) {
	this->front[index] = object;
	this->length++;
	
	return index;
}

/*
명칭 : Insert
기능 : 배열에서 삽입한다.
입력 : 위치, 오브젝트
출력 : 위치
*/
template <typename T>
Long Array<T>::Insert(Long index, T object) {
	T(*front);
	Long i = 0;
	Long j = 0;

	front = new T[this->capacity + 1];
	while (i < index) {
		front[j] = this->front[i];
		j++;
		i++;
	}
	j++;
	while (i < this->length) {
		front[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = front;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

/*
명칭 : AppendFromFront
기능 : 배열에서 앞에 끼운다.
입력 : 오브젝트
출력 : 위치
*/
template <typename T>
Long Array<T>::AppendFromFront(T object) {
	T(*front);
	Long index;
	Long i = 0;
	Long j = 1;

	front = new T[this->capacity + 1];
	while (i < this->length) {
		front[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = front;
	this->capacity++;
	index = 0;
	this->front[index] = object;
	this->length++;

	return index;
}

/*
명칭 : AppendFromRear
기능 : 배열에서 뒤에 끼운다.
입력 : 오브젝트
출력 : 위치
*/
template <typename T>
Long Array<T>::AppendFromRear(T object) {
	T(*front);
	Long index;
	Long i = 0;
	
	front = new T[this->capacity + 1];
	while (i < this->length) {
		front[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = front;
	this->capacity++;
	index = this->length;
	this->front[index] = object;
	this->length++;

	return index;
}

/*
명칭 : Delete
기능 : 배열에서 지운다.
입력 : 위치
출력 : 위치(0)
*/
template <typename T>
Long Array<T>::Delete(Long index) {
	T(*front) = 0;
	Long i = 0;
	Long j = 0;

	if (this->capacity > 0) {
		front = new T[this->capacity - 1];
	}
	while (i < index) {
		front[i] = this->front[j];
		j++;
		i++;
	}
	j++;
	while (i < this->length - 1) {
		front[i] = this->front[j];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 0) {
		this->front = front;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

/*
명칭 : DeleteFromFront
기능 : 배열에서 맨 앞을 지운다.
입력 : X
출력 : 위치
*/
template <typename T>
Long Array<T>::DeleteFromFront() {
	T(*front);
	Long index;
	Long i = 1;
	Long j = 0;

	if (this->capacity > 0) {
		front = new T[this->capacity - 1];
	}
	while (i < this->length - 1) {
		front[j] = this->front[i];
		j++;
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 0) {
		this->front = front;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

/*
명칭 : DeleteFromRear
기능 : 배열에서 맨 뒤를 지운다.
입력 : X
출력 : 위치
*/
template <typename T>
Long Array<T>::DeleteFromRear() {
	T(*front);
	Long index;
	Long i = 0;

	if (this->capacity > 0) {
		front = new T[this->capacity - 1];
	}
	while (i < this->length - 1) {
		front[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 0) {
		this->front = front;
	}
	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

/*
명칭 : Clear
기능 : 배열에서 원위치한다.
입력 : X
출력 : X
*/
template <typename T>
void Array<T>::Clear() {
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	this->capacity = 0;
	this->length = 0;
}

/*
명칭 : Modify
기능 : 배열에서 변경한다.
입력 : 위치, 오브젝트
출력 : 위치
*/
template <typename T>
Long Array<T>::Modify(Long index, T object) {
	this->front[index] = object;

	return index;
}

/*
명칭 : LinearSearchUnique
기능 : 배열에서 선형검색을 한다.
입력 : 키
출력 : 위치
*/
template <typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;

	while (i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}
	if (i < this->length) {
		index = i;
	}

	return index;
}

/*
명칭 : LinearSearchDuplicate
기능 : 배열에서 중복 선형검색을 한다.
입력 : 키
출력 : 위치들, 개수
*/
template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	*count = 0;

	*indexes = new Long[this->length];

	while (i < this->length) {
		if (compare(this->front + i, key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}

/*
명칭 : BinarySearchUnique
기능 : 배열에서 이진검색한다.
입력 : 키
출력 : 위치
*/
template <typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long front = 0;
	Long rear;
	Long middle;

	rear = this->length - 1;
	middle = (front + rear) / 2;
	while (front <= rear && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			front = middle + 1;
		}
		else {
			rear = middle - 1;
		}
		middle = (front + rear) / 2;
	}
	if (front <= rear) {
		index = middle;
	}

	return index;
}

/*
명칭 : BinarySearchDuplicate
기능 : 배열에서 중복 이진검색한다.
입력 : 키
출력 : 위치들, 개수
*/
template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long front = 0;
	Long rear;
	Long middle;
	Long i = 0;
	Long j = 0;
	*count = 0;

	rear = this->length - 1;
	middle = (front + rear) / 2;
	while (front <= rear && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			front = middle + 1;
		}
		else {
			rear = middle - 1;
		}
		middle = (front + rear) / 2;
	}

	front = middle - 1;
	while (front >= 0 && compare(this->front + front, key) == 0) {
		front--;
	}
	*indexes = new Long[this->length];

	i = front + 1;
	while (i <= rear && compare(this->front + i, key) == 0) {
		(*indexes)[j] = i;
		j++;
		(*count)++;
		i++;
	}
}

/*
명칭 : BubbleSort
기능 : 배열에서 버블정렬한다.
입력 : X
출력 : X
*/
template <typename T>
void Array<T>::BubbleSort(int (*compare)(void*, void*)) {
	T temp;
	Long i;
	Long j;
	
	i = this->length - 1;
	while (i >= 0) {
		j = 0;
		while (j < i) {
			if (compare(this->front + j, this->front + (j + 1)) > 0) {
				temp = this->front[j];
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = temp;
			}
			j++;
		}
		i--;
	}
}

/*
명칭 : SelectionSort
기능 : 배열에서 선택정렬한다.
입력 : X
출력 : X
*/
template <typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 0;
	Long j;
	while (i < this->length - 1) {
		j = i + 1;
		while (j < this->length) {
			if (compare(this->front + i, this->front + j) > 0) {
				temp = this->front[i];
				this->front[i] = this->front[j];
				this->front[j] = temp;
			}
			j++;
		}
		i++;
	}
}

/*
명칭 : InsertionSort
기능 : 배열에서 삽입정렬한다.
입력 : X
출력 : X
*/
template <typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 1;
	Long j;
	while (i < this->length) {
		temp = this->front[i];
		j = i - 1;
		while (j >= 0 && compare(this->front + j, &temp) > 0) {
			this->front[j + 1] = this->front[j];
			j--;
		}
		this->front[j + 1] = temp;
		i++;
	}
}

/*
명칭 : Merge
기능 : 배열에서 병합한다.
입력 : one, other
출력 : X
*/
template <typename T>
void Array<T>::Merge(const Array& one, const Array& other, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;
	
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[one.length + other.length];
	this->capacity = one.length + other.length;

	while (i < one.length && j < other.length) {
		if (compare(one.front + i, other.front + j) < 0) {
			this->front[k] = one.front[i];
			i++;
		}
		else {
			this->front[k] = other.front[j];
			j++;
		}
		k++;
	}

	while (i < one.length) {
		this->front[k] = one.front[i];
		k++;
		i++;
	}

	while (j < other.length) {
		this->front[k] = other.front[j];
		k++;
		j++;
	}

	this->length = one.length + other.length;
}

/*
명칭 : GetAt
기능 : 배열에서 읽는다.
입력 : 위치
출력 : 오브젝트
*/
template <typename T>
T& Array<T>::GetAt(Long index){
	return this->front[index];
}

/*
명칭 : operator =
기능 : = 연산자를 정의한다.
입력 : 소스
출력 : 배열
*/
template <typename T>
Array<T>& Array<T>::operator =(const Array& source) {
	Long i = 0;
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

/*
명칭 : operator []
기능 : [] 연산자를 정의한다.
입력 : 위치
출력 : 오브젝트
*/
template <typename T>
T& Array<T>::operator [](Long index) {
	return this->front[index];
}

/*
명칭 : operator +
기능 : + 연산자를 정의한다.
입력 : 위치
출력 : 오브젝트 주소
*/
template <typename T>
T* Array<T>::operator +(Long index) {
	return this->front + index;
}

/*
명칭 : GetCapacity
기능 : 할당량을 읽는다.
입력 : X
출력 : 할당량
*/
template <typename T>
Long Array<T>::GetCapacity() const {
	return this->capacity;
}

/*
명칭 : GetLength
기능 : 사용량을 읽는다.
입력 : X
출력 : 사용량
*/
template <typename T>
Long Array<T>::GetLength() const {
	return this->length;
}

#endif // _ARRAY_H