#ifndef QUEUE_H
#define QUEUE_H

template<class T>
class Queue
{
    public:
        bool empty();
        bool is_full();
        T front();
        T rear();
        void push(T element);
        void pop();
        void clear();
    private:
        T _queue[1000];
        int _capacity = 1000;
        int _size = 0;
        int _front = 0;
        int _rear = _capacity - 1;
};

template<class T>
void Queue<T>::clear()
{
    _size = _front = 0;
    _rear = _capacity - 1;
}

template<class T>
bool Queue<T>::empty()
{
    return _size == 0;
}

template<class T>
bool Queue<T>::is_full()
{
    return _capacity == _size;
}

template<class T>
T Queue<T>::front()
{
    return _queue[_front];
}

template<class T>
T Queue<T>::rear()
{
    return _rear;
}

template<class T>
void Queue<T>::push(T element)
{
    if(!is_full())
    {
        _rear = (_rear + 1) % _capacity;
        _queue[_rear] = element;
        _size++;
    }
}

template<class T>
void Queue<T>::pop()
{
    if(!empty())
    {
        _front = (_front + 1) % _capacity;
        _size--;
    }
}


#endif