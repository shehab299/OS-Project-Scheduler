#pragma once

template <typename T>
class ArrayList
{
private:
	T* array;
	int size; // Current count of list items
	int capacity;

	void resize();

public:
	ArrayList();
	ArrayList(const ArrayList<T>& toCopy);
	bool insert(int newPosition, const T& newElement);
	bool remove(int position);
	T getElement(int position);
	int getSize() const;
	bool isEmpty() const;
	void clear();
	~ArrayList();
};



template <typename T>
void ArrayList<T>::resize()
{
    capacity *= 2;
    T* new_array = new T[capacity];
    for (int i = 0; i < size; i++) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
}

template <typename T>
ArrayList<T>::ArrayList()
{
    capacity = 10;
    array = new T[capacity];
    size = 0;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& toCopy)
{
    capacity = toCopy.capacity;
    array = new T[capacity];
    size = toCopy.size;
    for (int i = 0; i < size; i++) {
        array[i] = toCopy.array[i];
    }
}

template <typename T>
bool ArrayList<T>::insert(int newPosition, const T& newElement)
{
    if (newPosition < 0 || newPosition > size) {
        return false;
    }
    if (size == capacity) {
        resize();
    }
    for (int i = size; i > newPosition; i--) {
        array[i] = array[i - 1];
    }
    array[newPosition] = newElement;
    size++;
    return true;
}

template <typename T>
bool ArrayList<T>::remove(int position)
{
    if (position < 0 || position >= size) {
        return false;
    }
    for (int i = position; i < size - 1; i++) {
        array[i] = array[i + 1];
    }
    size--;
    return true;
}

template <typename T>
T ArrayList<T>::getElement(int position)
{
    if (position < 0 || position >= size) {
        throw std::out_of_range("Index out of range");
    }
    return array[position];
}

template<typename T>
int ArrayList<T>::getSize() const
{
    return size;
}

template <typename T>
bool ArrayList<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
void ArrayList<T>::clear()
{
    size = 0;
}
    
 template <typename T>
 ArrayList<T>::~ArrayList()
{
    delete[] array;
}