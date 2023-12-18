#ifndef QUEUE_ON_VECTOR__LIST_VECTOR_H
#define QUEUE_ON_VECTOR__LIST_VECTOR_H

#include <cassert>
#include "iostream"

namespace golchanskiy
{
  namespace detail
  {

    template<typename T>
    T* allocate_memory(size_t size)
    {
      return static_cast<T*>(operator new(sizeof (T)*size));
    }

    template<typename T1,typename T2>
    void construct(T1* place,const T2& value)
    {
      new(place) T1(value);
    }

    template<typename T>
    T* newCopy(const T* src, size_t src_size, size_t dest_size)
    {
      assert(dest_size >= src_size);
      T* dest = new T[dest_size];
      try
      {
        std::copy(src, src+src_size, dest);
      }
      catch(...)
      {
        delete [] dest;
        throw;
      }
      return dest;
    }

    template<class T>
    class Vector
    {
      public:
       Vector();
       Vector(const Vector<T>&);
       Vector(Vector<T>&&);
       ~Vector();
       Vector<T>& operator=(const Vector<T>&);
       Vector<T>& operator=(Vector<T>&&) = default;

       void push_back(T& value);
       void pop_back();
       T& back() const;
       T& front() const;
       void pop_front();
       size_t get_size() const;
       bool empty() const;

      private:
       T* v;
       size_t size;
       size_t head;
       size_t tail;
       size_t capacity;
    };

    template<typename T>
    golchanskiy::detail::Vector<T>::Vector() : v(allocate_memory<T>(10)), size(0), head(0), tail(0),
                                               capacity(10) {}

    template<typename T>
    golchanskiy::detail::Vector<T>::Vector(const Vector<T>& vector) : v(newCopy(vector.v, vector.size, vector.capacity)),
                                                                      size(vector.size), head(vector.head), tail(vector.tail), capacity(vector.capacity) {}

    template<typename T>
    golchanskiy::detail::Vector<T>::Vector(Vector<T>&& vector)
      : v(newCopy(vector.v, vector.size, vector.capacity)),
        size(vector.size), head(vector.head), tail(vector.tail), capacity(vector.capacity)
    {
      vector.v = nullptr;
    }

    template<typename T>
    golchanskiy::detail::Vector<T>::~Vector()
    {
      for(size_t head_ = head; head < size; ++head_)
      {
        v[head_].~T();
      }
      operator delete(v);
    }

    template<typename T>
     typename golchanskiy::detail::Vector<T>::Vector& golchanskiy::detail::Vector<T>::operator=(const Vector<T>& vector)
    {
      if ( this != &vector)
      {
        T* v_new = NewCopy( vector.v_,
                            vector.size,
                            vector.capacity );
        delete[] v;
        v = v_new;
        size = vector.size;
        capacity = vector.capacity;
      }
      return *this;
    }

    template<typename T>
    void golchanskiy::detail::Vector<T>::push_back(T& value)
    {
      if(size+1 > capacity)
      {
        T* new_v = newCopy(v,size,capacity+10);
        try
        {
          construct(new_v+size, value);
        }
        catch(...)
        {
          for(size_t i = head; i < size+1; ++i)
          {
            v[i].~T();
          }
          operator delete(v);
          throw;
        }
        v = new_v;
        ++tail;
        ++size;
        capacity += 10;
      }
      else
      {
        size_t new_tail = 0;
        if(tail == 0)
        {
          new_tail = 0;
        }
        else
        {
          new_tail = tail+1;
        }
        try
        {
          construct(v+new_tail, value);
        }
        catch(...)
        {
          v[new_tail].~T();
          throw;
        }
        tail = new_tail;
        ++size;
      }
    }

    template<typename T>
    T& golchanskiy::detail::Vector<T>::front() const
    {
      if(empty())
      {
        throw std::logic_error("Empty vector, impossible get first element");
      }
      return v[head];
    }

    template<typename T>
    void golchanskiy::detail::Vector<T>::pop_front()
    {
      if(empty())
      {
        throw std::logic_error("try to delete an element from empty vector");
      }
      else
      {
        --size;
        v[head].~T();
        if(head != tail)
        {
          ++head;
        }
        else
        {
          head = 0;
          tail = 0;
        }
      }
    }

    template<typename T>
    void golchanskiy::detail::Vector<T>::pop_back()
    {
      if(empty())
      {
        throw std::logic_error("try to delete an element from empty vector");
      }
      else
      {
        --size;
        v[tail].~T();
        if(head != tail)
        {
          --tail;
        }
        else
        {
          head = 0;
          tail = 0;
        }
      }
    }

    template<typename T>
    T& golchanskiy::detail::Vector<T>::back() const
    {
      if(empty())
      {
        throw std::logic_error("Empty vector, impossible get last element");
      }
      return v[tail];
    }

    template<typename T>
    size_t Vector<T>::get_size() const
    {
      return size;
    }

    template<typename T>
    bool Vector<T>::empty() const
    {
      return size == 0;
    }

  }
}

#endif //STACK_ON_VECTOR__LIST_VECTOR_H
