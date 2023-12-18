#ifndef LIST_H
#define LIST_H
#include <stdexcept>

namespace golchanskiy
{
    namespace detail
    {
        template<typename T>
        struct Node
        {
            T data_;
            Node *next_;
        };
        template < typename T, typename NodeType = Node< T > >
        class List
        {
        public:
            List();
            List(const List &);
            List(List &&) noexcept;
            ~List();
            List &operator=(const List &);
            List &operator=(List &&) noexcept;
            void swap(List &) noexcept;
            bool isEmpty() const;
            size_t getSize() const;
            const T& front() const;
            const T& back() const;
            void clear();
            void pushBack(const T &);
            void pushFront(const T &);
            void popFront();
        protected:
            NodeType* head_;
            NodeType* tail_;
            size_t size_;
        };
        template < typename T, typename NodeType >
        List< T, NodeType >::List():
        head_(nullptr),
                tail_(nullptr),
                size_(0) {}
        template < typename T, typename NodeType >
        List< T, NodeType >::List(const List& src):
        head_(nullptr),
                tail_(nullptr),
                size_(0) {
            if (!src.isEmpty())
            {
                try
                {
                    NodeType* srcPtr = src.head_;
                    do
                    {
                        pushBack(srcPtr->data_);
                        srcPtr = srcPtr->next_;
                    } while (srcPtr);
                }
                catch (...)
                {
                    clear();
                    throw;
                }
            }
        }
        template < typename T, typename NodeType >
        List< T, NodeType >::List(List&& src) noexcept:
        head_(src.head_),
                tail_(src.tail_),
                size_(src.size_)
                {
                    src.head_ = nullptr;
                    src.tail_ = nullptr;
                }
        template < typename T, typename NodeType >
        List< T, NodeType >::~List()
        {
            clear();
        }
        template < typename T, typename NodeType >
        List< T, NodeType >& List< T, NodeType >::operator=(const List& src)
        {
            List< T, NodeType > temp(src);
            swap(temp);
            return *this;
        }
        template < typename T, typename NodeType >
        List< T, NodeType >& List< T, NodeType >::operator=(List&& src) noexcept
        {
            swap(src);
            src.clear();
            return *this;
        }
        template < typename T, typename NodeType >
        void List< T, NodeType >::clear()
        {
            while (head_)
            {
                auto temp = head_;
                head_ = head_->next_;
                delete temp;
                --size_;
            }
        }
        template < typename T, typename NodeType >
        void List< T, NodeType >::swap(List& other) noexcept
        {
            std::swap(head_, other.head_);
            std::swap(tail_, other.tail_);
            std::swap(size_, other.size_);
        }
        template < typename T, typename NodeType >
        bool List< T, NodeType >::isEmpty() const
        {
            return !size_;
        }
        template < typename T, typename NodeType >
        size_t List< T, NodeType >::getSize() const
        {
            return size_;
        }
        template < typename T, typename NodeType >
        const T& List< T, NodeType >::front() const
        {
            if (!size_)
            {
                throw std::logic_error("List is empty");
            }
            return head_->data_;
        }
        template < typename T, typename NodeType >
        const T& List< T, NodeType >::back() const
        {
            if (!size_)
            {
                throw std::logic_error("List is empty");
            }
            return tail_->data_;
        }
        template < typename T, typename NodeType >
        void List< T, NodeType >::pushBack(const T& data)
        {
            if (!size_)
            {
                head_ = new NodeType{data, nullptr};
                tail_ = head_;
            }
            else
            {
                tail_->next_ = new NodeType{data, nullptr};
                tail_ = tail_->next_;
            }
            ++size_;
        }
        template < typename T, typename NodeType >
        void List< T, NodeType >::pushFront(const T& data)
        {
            if (!size_)
            {
                head_ = new NodeType{data, nullptr};
                tail_ = head_;
            }
            else
            {
                auto newHead = new NodeType{data, head_};
                head_ = newHead;
            }
            ++size_;
        }
        template < typename T, typename NodeType >
        void List< T, NodeType >::popFront()
        {
            if (!size_)
            {
                throw std::logic_error("Pop from the empty list");
            }
            auto temp(head_);
            head_ = head_->next_;
            delete temp;
            --size_;
        }
    }
}

#endif

