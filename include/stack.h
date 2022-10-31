#ifndef STACK_H
#define STACK_H

template<class T>
class Stack
{
    public:
        void push(T element);
        void pop(T& element);
        bool empty();
        bool is_full();
        void clear();
    private:
        T _stack[1000];
        int _top = -1;
        int capacity = 1000;
};

template<class T>
void Stack<T>::push(T element)
{
    if(!is_full())
    {
        _top++;
        _stack[_top] = element; 
    }
}

template<class T>
void Stack<T>::pop(T& element)
{
    if(!empty())
    {
        element = _stack[_top];
        _top--;
    }
}

template<class T>
bool Stack<T>::empty()
{
    return _top == -1;
}

template<class T>
bool Stack<T>::is_full()
{
    return _top == capacity;
}

template<class T>
void Stack<T>::clear()
{
    _top = -1;
}

#endif