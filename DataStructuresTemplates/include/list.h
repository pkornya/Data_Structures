#pragma once

#ifndef  LIST_H
#define  LIST_H

#include <initializer_list>
#include <exception>

namespace pkl {

    ///////////// Node /////////////
    // 

    template <typename T>
    struct ListNode
    {
        
        ListNode<T>* pPrev;
        T		     data;
        ListNode<T>* pNext;
        
        ListNode(ListNode<T>* pPrev = nullptr, T data = T(), ListNode<T>* pNext = nullptr);
    };




    ///////////// Iterator /////////////
    // 

    template <typename T, typename Pointer, typename Reference>
    struct ListIterator
    {
        typedef ListIterator<T, Pointer, Reference>         this_type;
        typedef ListIterator<T, T*, T&>                     iterator;
        typedef ListIterator<T, const T*, const T&>         const_iterator;
        typedef T                                           value_type;
        typedef ListNode<T>                                 node_type;
        typedef Pointer                                     pointer;
        typedef Reference                                   reference;

    public:

        //ListIterator();
        ListIterator(const node_type* pElement);
        ListIterator(const iterator& x);

        bool		operator==(const this_type& another) const;
        bool		operator!=(const this_type& another) const;

        reference	operator*() const;
        pointer		operator->() const;

        this_type&	operator++();
        this_type	operator++(int);

        this_type&	operator--();
        this_type	operator--(int);

    public:
        node_type* pNode;
    };




    ///////////// list /////////////
    // 

    template <typename T>
    class list
    {
        typedef list<T>	                                this_type;

    public:
        typedef T                                       value_type;
        typedef T*                                      pointer;
        typedef const T*                                const_pointer;
        typedef T&                                      reference;
        typedef const T&                                const_reference;
        typedef ListNode<T>                             node_type;
        typedef ListIterator<T, T*, T&>                 iterator;
        typedef ListIterator<T, const T*, const T&>     const_iterator;

    public:
        list(); 
        list(std::initializer_list<value_type> il);
        explicit list(size_t n, const value_type& val);

        list(const this_type& another);
        list(this_type&& another);

        this_type& operator=(const this_type& another);
        this_type& operator=(this_type&& another);
        this_type& operator=(std::initializer_list<value_type> il);

        void swap(this_type& another);

        ~list();

        void assign(size_t n, const value_type& val);
        void assign(std::initializer_list<value_type> il);

        iterator        begin();
        const_iterator  begin()  const;
        const_iterator  cbegin() const;

        iterator        end();
        const_iterator  end()  const;
        const_iterator  cend() const;

        bool        empty() const;
        size_t      size()  const;

        void        clear();

        void      resize(size_t n);
        void      resize(size_t n, const value_type& val);

        reference       front();
        const_reference front() const;

        reference       back();
        const_reference back() const;

        void push_front(const value_type& val);
        void push_back(const value_type& val);

        void pop_front();
        void pop_back();

        iterator insert(const_iterator position, const value_type& val);
        iterator insert(const_iterator position, size_t n, const value_type& val);
        iterator insert(const_iterator position, std::initializer_list<value_type> il);

        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);

    private:
        node_type* pBegin;
        node_type* pEnd;
        size_t     mSize;
    };




    ///////////// Node /////////////
    // 

    template <typename T>
    ListNode<T>::ListNode(ListNode<T>* pPrev = nullptr, T data = T(), ListNode<T>* pNext = nullptr)
    {
        this->pPrev = pPrev;
        this->data  = data;
        this->pNext = pNext;
    }


    

    ///////////// Iterator /////////////
    // 

    /*template<typename T, typename Pointer, typename Reference>
    ListIterator<T, Pointer, Reference>::ListIterator() :
        pNode(nullptr)
    {

    }*/


    template <typename T, typename Pointer, typename Reference>
    ListIterator<T, Pointer, Reference>::ListIterator(const node_type* pElement)
        : pNode(const_cast<node_type*>(pElement))
    {

    }


    template <typename T, typename Pointer, typename Reference>
    ListIterator<T, Pointer, Reference>::ListIterator(const iterator & x)
        : pNode(const_cast<node_type*>(x.pNode))
    {

    }


    template <typename T, typename Pointer, typename Reference>
    typename ListIterator<T, Pointer, Reference>::reference
    ListIterator<T, Pointer, Reference>::operator*() const
    {
        return pNode->data;
    }


    template<typename T, typename Pointer, typename Reference>
    typename ListIterator<T, Pointer, Reference>::pointer
    ListIterator<T, Pointer, Reference>::operator->() const
    {
        return &pNode->data;
    }


    template<typename T, typename Pointer, typename Reference>
    typename ListIterator<T, Pointer, Reference>::this_type&
    ListIterator<T, Pointer, Reference>::operator++()
    {
        pNode = pNode->pNext;
        return *this;
    }


    template<typename T, typename Pointer, typename Reference>
    typename ListIterator<T, Pointer, Reference>::this_type
    ListIterator<T, Pointer, Reference>::operator++(int)
    {
        ListIterator temp(*this);
        ++(*this);
        return temp;
    }


    template<typename T, typename Pointer, typename Reference>
    typename ListIterator<T, Pointer, Reference>::this_type&
    ListIterator<T, Pointer, Reference>::operator--()
    {
        pNode = pNode->pPrev;
        return *this;
    }


    template<typename T, typename Pointer, typename Reference>
    typename ListIterator<T, Pointer, Reference>::this_type
    ListIterator<T, Pointer, Reference>::operator--(int)
    {
        ListIterator temp(*this);
        --(*this);
        return temp;
    }


    template <typename T, typename Pointer, typename Reference>
    bool ListIterator<T, Pointer, Reference>::operator==(const this_type& other) const
    {
        return pNode == other.pNode;
    }


    template <typename T, typename Pointer, typename Reference>
    bool ListIterator<T, Pointer, Reference>::operator!=(const this_type& other) const
    {
        return !(pNode == other.pNode);
    }


    template <typename T, typename PointerA, typename ReferenceA, typename PointerB, typename ReferenceB>
    bool operator==(const ListIterator<T, PointerA, ReferenceA>& a,
                    const ListIterator<T, PointerB, ReferenceB>& b)
    {
        return a.pNode == b.pNode;
    }


    template <typename T, typename PointerA, typename ReferenceA, typename PointerB, typename ReferenceB>
    bool operator!=(const ListIterator<T, PointerA, ReferenceA>& a,
                    const ListIterator<T, PointerB, ReferenceB>& b)
    {
        return a.pNode != b.pNode;
    }




    ///////////// list /////////////
    // 

    template <typename T>
    list<T>::list() :
        pBegin(nullptr), pEnd(nullptr), mSize(0)
    {

    }


    template <typename T>
    list<T>::list(std::initializer_list<value_type> il) : 
        list()
    {
        for (auto it = il.begin(); it != il.end(); ++it) {
            push_back(*it);
        }
    }


    template <typename T>
    list<T>::list(size_t n, const value_type& val) : 
        list()
    {
        while (n) {
            push_front(val);
            n--;
        }
    }


    template <typename T>
    list<T>::list(const this_type& another) : 
        list()
    {
        node_type* pTempAnother = another.pBegin;

        while (pTempAnother != nullptr) {
            push_back(pTempAnother->data);
            pTempAnother = pTempAnother->pNext;
        }
    }


    template <typename T>
    list<T>::list(this_type&& another) : 
        list()
    {
        swap(another);
    }


    template <typename T>
    typename list<T>::this_type& 
    list<T>::operator=(const this_type& another)
    {
        if (this != &another) {
            clear();
            this_type(another).swap(*this);
        }
        return *this;
    }


    template <typename T>
    typename list<T>::this_type&
    list<T>::operator=(this_type&& another)
    {
        if (this != &another) {
            clear();
            swap(another);
        }
        return *this;
    }


    template <typename T>
    typename list<T>::this_type&
    list<T>::operator=(std::initializer_list<value_type> il)
    {
        clear();

        for (auto it = il.begin(); it != il.end(); ++it)
            push_back(*it);

        mSize = il.size();

        return *this;
    }


    template<typename T>
    void list<T>::swap(this_type & another)
    {
        std::swap(pBegin, another.pBegin);
        std::swap(pEnd, another.pEnd);
        std::swap(mSize, another.mSize);
    }


    template<typename T>
    list<T>::~list()
    {
        clear();
    }


    template<typename T>
    void list<T>::assign(size_t n, const value_type& val)
    {
        clear();

        for (int i = n; i > 0; i--)
            push_front(val);
    }


    template<typename T>
    void list<T>::assign(std::initializer_list<value_type> il)
    {
        clear();

        for (auto it = il.begin() ; it != il.end(); ++it)
            push_back(*it);
    }


    template <typename T>
    typename list<T>::reference
    list<T>::front()
    {
        return pBegin->data;
    }


    template <typename T>
    typename list<T>::const_reference
    list<T>::front() const
    {
        return pBegin->data;
    }


    template <typename T>
    typename list<T>::reference
    list<T>::back()
    {
        return pEnd->data;
    }


    template <typename T>
    typename list<T>::const_reference
    list<T>::back() const
    {
        return pEnd->data;
    }


    template <typename T>
    void list<T>::push_front(const value_type & val)
    {
        if (pBegin == nullptr) {
            pBegin = new node_type(nullptr, val, pBegin);
            pEnd   = pBegin;
            mSize++;
        }
        else {
            pBegin = new node_type(nullptr, val, pBegin);
            pBegin->pNext->pPrev = pBegin;
            mSize++;
        }
    }


    template <typename T>
    void list<T>::push_back(const value_type & val)
    {
        if (pBegin == nullptr)
            push_front(val);
        else {
            pEnd = new node_type(pEnd, val, nullptr);
            pEnd->pPrev->pNext = pEnd;
            mSize++;
        }
    }


    template <typename T>
    void list<T>::pop_front()
    {
        if (pBegin == nullptr)
            throw std::logic_error("list::pop_front -- empty container");

        if (mSize == 1) {
            clear();
            return;
        }

        node_type* pTemp = pBegin;
        pBegin = pBegin->pNext;
        pBegin->pPrev = nullptr;
        delete pTemp;
        mSize--;
    }


    template <typename T>
    void list<T>::pop_back()
    {
        if (pBegin == nullptr)
            throw std::logic_error("list::pop_back -- empty container");

        if (mSize == 1) {
            clear();
            return;
        }

        node_type* pTemp = pEnd;
        pEnd = pEnd->pPrev;
        pEnd->pNext = nullptr;
        delete pTemp;
        mSize--;
    }


    template <typename T>
    typename list<T>::iterator 
    list<T>::insert(const_iterator position, const value_type& val)
    {
        if (position == begin()) {
            push_front(val);
            return begin();
        }
        else if (position != nullptr) {
            position.pNode->pPrev->pNext = new node_type(position.pNode->pPrev, val, position.pNode); 
            position.pNode->pPrev        = position.pNode->pPrev->pNext;

            mSize++;

            return iterator(position.pNode->pPrev);
        }
    }
     
    
    template <typename T>
    typename list<T>::iterator 
    list<T>::insert(const_iterator position, size_t n, const value_type& val)
    {
        if (position == begin()) {
            for (int i = n; i > 0; i--)
                push_front(val);
            return begin();
        }
        else if (position != nullptr) {
            for (int i = n; i > 0; i--) {
                position.pNode->pPrev->pNext = new node_type(position.pNode->pPrev, val, position.pNode);
                position.pNode->pPrev        = position.pNode->pPrev->pNext;
                position.pNode               = position.pNode->pPrev;

                mSize++;
            }

            return iterator(position.pNode);
        }
    }


    template <typename T>
    typename list<T>::iterator
    list<T>::insert(const_iterator position, std::initializer_list<value_type> il)
    {
        if (pBegin == nullptr) {
            for (auto it = il.begin(); it != il.end(); ++it)
                push_back(*it);
            return begin();
        }
 
        else if (position != nullptr) {
            auto it          = il.begin();
            iterator superit = insert(position, *it);

            for (auto it = il.begin() + 1; it != il.end(); ++it) {
                position.pNode->pPrev->pNext = new node_type(position.pNode->pPrev, *it, position.pNode);
                position.pNode->pPrev        = position.pNode->pPrev->pNext;

                mSize++;
            }

            return superit;
        }
    }


    template <typename T>
    typename list<T>::iterator
    list<T>::erase(const_iterator position)
    {
        if (position == begin()) {
            pop_front();
            //return begin();
        }
        else if (position == end()) {
            pop_back();
            //return end();
        }
        else { 
            node_type* pTemp    = position.pNode;
            pTemp->pPrev->pNext = pTemp->pNext;
            pTemp->pNext->pPrev = pTemp->pPrev;
            position.pNode      = position.pNode->pNext;

            delete pTemp;
            mSize--;

            //return iterator(position.pNode);
        }

        return iterator(position.pNode);
    }

    template <typename T>
    typename list<T>::iterator
    list<T>::erase(const_iterator first, const_iterator last)
    {
        if (first == begin() && last == end())
        {	
            clear();
            return end();
        }
        else
        {	
            while (first != last)
                first = erase(first);
            return iterator(last.pNode);
        }
    }


    template <typename T>
    typename list<T>::iterator
    list<T>::begin()
    {
        return iterator(pBegin);
    }


    template <typename T>
    typename list<T>::const_iterator
    list<T>::begin() const
    {
        return const_iterator(pBegin);
    }


    template <typename T>
    typename list<T>::const_iterator
    list<T>::cbegin() const
    {
        return const_iterator(pBegin);
    }


    template <typename T>
    typename list<T>::iterator
    list<T>::end()
    {
        //return iterator(pEnd);
        return iterator(nullptr);
    }


    template <typename T>
    typename list<T>::const_iterator
    list<T>::end() const
    {
        //return const_iterator(pEnd);
        return iterator(nullptr);
    }


    template <typename T>
    typename list<T>::const_iterator
    list<T>::cend() const
    {
        //return const_iterator(pEnd);
        return iterator(nullptr);
    }


    template <typename T>
    bool list<T>::empty() const
    {
        return mSize == 0;
    }


    template <typename T>
    size_t list<T>::size()  const
    {
        return mSize;
    }


    template <typename T>
    void list<T>::clear()
    {
        node_type* pTemp;

        while (pBegin != nullptr) {
            pTemp  = pBegin;
            pBegin = pBegin->pNext;
            delete pTemp;
        }

        mSize = 0;
        pEnd  = nullptr;
    }


    template <typename T>
    void list<T>::resize(size_t n)
    {
        if (mSize < n) {
            while (n > mSize)
                push_back(T());
        }
        else {
            while (n < mSize)
                pop_back();
        }
    }


    template <typename T>
    void list<T>::resize(size_t n, const value_type& val)
    {
        if (mSize < n) {
            while (n > mSize)
                push_back(val);
        }
        else {
            while (n < mSize)
                pop_back();
        }
    }


}

#endif // ! LIST_H