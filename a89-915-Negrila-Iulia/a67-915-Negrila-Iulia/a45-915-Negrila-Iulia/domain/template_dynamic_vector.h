#pragma once

template<typename T>
class TemplateDynamicVector{
private:
    T *elements;
    int length;
    int capacity;

public:
    //default constructor
    TemplateDynamicVector(int capacity=10);

    //copy constructor
    TemplateDynamicVector(const TemplateDynamicVector &tdv);

    //destructor
    ~TemplateDynamicVector();

    //overloading assignment operator for dynamic vector
    TemplateDynamicVector& operator=(const TemplateDynamicVector& tdv);

    //return the number of elements from the dynamic vector
    int get_length() const;

    //return the capacity of the dynamic vector
    int get_capacity() const;

    //add an element to the dynamic vector
    void add(const T e);

    //delete an element from the dynamic vector
    void remove(const T e);

    //return element on a given position
    T& operator[](int pos);

private:
    //resize the dynamic vector doubling its capacity (when needed)
    void resize();
};

template<typename T>
TemplateDynamicVector<T>::TemplateDynamicVector(int capacity) {
    /*
         Initialise the length and the capacity of the dynamic vector
         Allocates memory for the elements of the dynamic vector
         Input: capacity -integer
         Output: -
     */

    this->length = 0;
    this->capacity = capacity;
    this->elements = new T[capacity];
}

template<typename T>
TemplateDynamicVector<T>::TemplateDynamicVector(const TemplateDynamicVector &dv) {
    /*
        Copies the length, capacity and elements of the vector given as
        parameter to the current dynamic vector
        Input: dv -dynamic vector
        Output: -
     */
    this->length = dv.length;
    this->capacity = dv.capacity;
    this->elements = new T[this->capacity];
    for (int i = 0; i < this->length; i++)
        this->elements[i] = dv.elements[i];
}

template<typename T>
TemplateDynamicVector<T>::~TemplateDynamicVector() {
    /*
         Deallocates the memory used for the dynamic vector
     */
    delete[] this->elements;
}

template<typename T>
TemplateDynamicVector<T> &TemplateDynamicVector<T>::operator=(const TemplateDynamicVector &dv) {
    /*
        Overloads the assignment operator '='
        If the current vector is the same as the one given as parameter, return it
        Otherwise, assign to the current vector, the values of the one given as parameter
        Input: dv -dynamic vector
        Output: -
     */

    if (this == &dv)
        return *this;

    this->length = dv.length;
    this->capacity = dv.capacity;

    delete[] this->elements;
    this->elements = new T[this->capacity];
    for (int i = 0; i < this->length; i++)
        this->elements[i] = dv.elements[i];

    return *this;
}

template<typename T>
void TemplateDynamicVector<T>::add(const T element) {
    /*
        Adds a new element to the dynamic vector
        Increases the length of the vector
        If the dynamic vector is full,
        calls the resize method of the class to increase vector's capacity
        Input: element -type TElement, element which will be added
        Output: -
     */
    if (this->capacity == this->length)
        resize();
    this->elements[this->length] = element;
    this->length++;
}

template<typename T>
void TemplateDynamicVector<T>::remove(const T e) {
    /*
        Removes an element given as parameter from the dynamic vector
        Decreases the length of the vector
        Input: element- type TElement
        Output: -
     */
    for(int i=0; i<this->length; i++)
        if (this->elements[i] == e) {
            for (int j = i; j < this->length - 1; j++)
                this->elements[j] = this->elements[j + 1];
            this->length--;
            break;
        }
}

template<typename T>
T& TemplateDynamicVector<T>::operator[](int pos)
{
    return this->elements[pos];
}

template<typename T>
int TemplateDynamicVector<T>::get_length() const {
    /*
        Returns the number of elements of the dynamic vector
     */
    return this->length;
}

template<typename T>
int TemplateDynamicVector<T>::get_capacity() const {
    /*
        Returns the capacity of the dynamic vector
     */
    return this->capacity;
}

template<typename T>
void TemplateDynamicVector<T>::resize(){
    /*
        Deallocates the memory where dynamic vector was stored
        and saves it to a new memory address having double allocation memory space
     */
    int new_capacity = this->capacity*2;
    T *elements = new T[new_capacity];

    for (int i=0; i<this->length; i++)
        elements[i]=this->elements[i];

    delete[] this->elements;
    this->elements=elements;
    this->capacity=new_capacity;
}