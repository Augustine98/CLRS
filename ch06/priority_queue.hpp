#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <vector>
#include <functional>
#include <stdexcept>
#include "heap.hpp"

namespace clrs { namespace ch6 {

/**
 * @brief The PriorityQueue class template
 */
template<typename T>
class PriorityQueue
{
public:
    using ValueType     =   T;
    using Vector        =   std::vector<T>;
    using SizeType      =   typename Vector::size_type;
    using Iter          =   typename Vector::iterator;
    using Compare       =   std::function<bool(ValueType,ValueType)>;

    /**
     * @brief default Ctor
     */
    explicit PriorityQueue(Compare&& c = std::greater<ValueType>()):
        vec{}, compare{c}
    {}

    /**
     * @brief Ctor
     * @param list
     * @param c
     */
    explicit PriorityQueue(std::initializer_list<ValueType>&& list,
                           Compare&& c = std::greater<ValueType>()) noexcept:
        vec{std::move(list)}, compare{c}
    {
        clrs::ch6::build_heap(begin(), end(), compare);
    }

    /**
     * @brief Ctor
     * @param first
     * @param last
     * @param c
     */
    template<typename Iterator>
    PriorityQueue(Iterator first,
                  Iterator last,
                  Compare&& c = std::greater<ValueType>()):
        vec{first, last}, compare{c}
    {
        clrs::ch6::build_heap(begin(), end(), compare);
    }

    /**
     * @brief top
     */
    const ValueType& top()const
    {
        return vec.front();
    }

    /**
     * @brief size
     */
    SizeType size()const
    {
        return vec.size();
    }

    /**
     * @brief empty
     */
    bool empty()const
    {
        return vec.empty();
    }

    /**
     * @brief pop
     */
    void pop()
    {
        extract_max();
    }

    /**
     * @brief push
     * @param added
     */
    void push(const ValueType& added)
    {
        insert(added);
    }

private:
    Vector vec;
    Compare compare;

    /**
     * @brief begin
     */
    Iter begin()
    {
        return vec.begin();
    }

    /**
     * @brief end
     */
    Iter end()
    {
        return vec.end();
    }

    /**
     * @brief parent
     */
    Iter parent(Iter it)
    {
        return clrs::ch6::parent(begin(), it);
    }

    /**
     * @brief extract_max
     *
     * @pseudocode HEAP-EXTRACT-MAX, Page 163
     * @complx  O(lg n)
     */
    ValueType extract_max()
    {
        if(empty())
            throw std::underflow_error{"heap underflow."};

        auto max = vec.front();
        vec.front()   =   vec.back();
        vec.resize(size() - 1);

        heapify(begin(), end(), begin());
        return max;
    }

    /**
     * @brief insert
     * @param added
     *
     * @pseudocode  MAX-HEAP-INSERT,    page 164
     *              HEAP-INCREASE-KEY,  page 164
     * @complx  O(lg n)
     *
     * modified for ex6.5-6 that requires using use
     * the idea of the inner loop of INSERTION-SORT .
     */
    void insert(const ValueType& added)
    {
        //! find the right place for added
        vec.resize(size() + 1);
        auto curr = end() - 1;
        while(curr > begin()    &&  added > *parent(curr))
        {
            *curr = *parent(curr);
            curr = parent(curr);
        }

        //! insert added.
        (curr < begin()?    vec.front() :   *curr)  =   added;

    }
};

}}//namespace
#endif // PRIORITY_QUEUE_HPP


//! @test   class PriorityQueue and it's member functions
//!
//#include <vector>
//#include <iostream>
//#include "../misc/alan.hpp"
//#include "priority_queue.hpp"

//int main()
//{
//    clrs::ch6::PriorityQueue<int> queue {1,2,3,4,5,6};
//    queue.push(43);
//    queue.push(42);
//    queue.pop();
//    for(auto elem : {11,13,15,16,19})
//        queue.push(elem);

//    std::cout << queue.top();

//    alan::end();
//    return 0;
//}
//! @output
//!
//42
//exit normally
