#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <cassert>
#include <cmath>
#include <memory>
#include "shape.h"

namespace golchanskiy {
  template< typename T >
  class Storage {
    public:
     Storage();
     Storage(const Storage& storage) = delete;
     Storage(Storage&& storage) noexcept;
     Storage& operator=(const Storage& storage) = delete;
     Storage& operator=(Storage&& storage) noexcept;
     T& operator[](size_t index);
     const T& operator[](size_t index) const;
     void swap(golchanskiy::Storage< T >& storage);
     size_t getSize() const;
     std::unique_ptr< T[] >&& getStorage();
     void push(T&& obj);
    private:
     std::unique_ptr< T[] > storage_;
     size_t size_;
     size_t capacity_;
  };

  template< typename T >
  Storage< T >::Storage():
    storage_(),
    size_(0),
    capacity_(0)
  {}

  template< typename T >
  Storage< T >::Storage(Storage&& storage) noexcept:
    storage_(std::move(storage.storage_)),
    size_(storage.size_),
    capacity_(storage.capacity_)
  {}

  template< typename T >
  Storage< T >& Storage< T >::operator=(Storage&& storage) noexcept
  {
    Storage tmp(std::move(storage));
    swap(tmp);
    return *this;
  }

  template< typename T >
  T& Storage< T >::operator[](size_t index)
  {
    return const_cast< T& >(static_cast< const Storage< T >& >(*this)[index]);
  }

  template< typename T >
  const T& Storage< T >::operator[](size_t index) const
  {
    assert(index < size_);
    return storage_[index];
  }

  template< typename T >
  void Storage< T >::swap(Storage< T >& storage)
  {
    std::swap(storage_, storage.storage_);
    std::swap(size_, storage.size_);
    std::swap(capacity_, storage.capacity_);
  }

  template< typename T >
  size_t Storage< T >::getSize() const
  {
    return size_;
  }

  template< typename T >
  void Storage< T >::push(T&& obj)
  {
    if (capacity_ == size_) {
      size_t newCapacity = std::ceil(1.618 * capacity_) + 1;;
      auto newStorage = std::make_unique< T[] >(newCapacity);
      for (size_t i = 0; i < size_; ++i) {
        newStorage[i] = std::move(storage_[i]);
      }
      storage_ = std::move(newStorage);
      capacity_ = newCapacity;
    }
    storage_[size_++] = std::move(obj);
  }

  template< typename T >
  std::unique_ptr< T[] >&& Storage< T >::getStorage()
  {
    return std::move(storage_);
  }
}
#endif


