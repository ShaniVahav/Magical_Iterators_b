//
// Created by shani on 03/06/2023.
//

#ifndef MAGICAL_ITERATORS_A_MAGICALCONTAINER_HPP
#define MAGICAL_ITERATORS_A_MAGICALCONTAINER_HPP
#include <list>
using namespace std;
namespace ariel{};

class MagicalContainer {
public:
    explicit MagicalContainer(list<int> magic_list = {}) : _magic_list(magic_list) {};

    void addElement(int num);  // add element to the container

    void removeElement (int num);  // remove all occurrences of 'num'

    int getElement(int index) const;  // return the element in in index position

    int size();


private:
    list<int> _magic_list;

public:
    class AscendingIterator {
    public:

        explicit AscendingIterator(MagicalContainer& con);

        AscendingIterator(const AscendingIterator& other) : _con(other._con), _acsIt_index(other._acsIt_index) {};

        AscendingIterator& operator= (const AscendingIterator& other);

        bool operator== (const AscendingIterator& other) const;

        bool operator!= (const AscendingIterator& other) const;

        bool operator> (const AscendingIterator& other) const;

        bool operator< (const AscendingIterator& other) const;

        int operator* () const;

        AscendingIterator & operator++ ();

        AscendingIterator begin();

        AscendingIterator end();

    private:
        MagicalContainer& _con;
        int _acsIt_index;
    };

public:
    class PrimeIterator {
    public:

        explicit PrimeIterator(MagicalContainer& con);

        PrimeIterator(const PrimeIterator& other) :
        _con(other._con), _prime_numbers_list(other._prime_numbers_list), _primeIt_index(other._primeIt_index) {};

        PrimeIterator& operator= (const PrimeIterator& other);

        bool operator== (const PrimeIterator& other) const;

        bool operator!= (const PrimeIterator& other) const;

        bool operator> (const PrimeIterator& other) const;

        bool operator< (const PrimeIterator& other) const;

        int operator* () const;

        PrimeIterator& operator++ ();

        int getElement(int index) const;

        PrimeIterator begin();

        PrimeIterator end();

    private:
        MagicalContainer& _con;
        list<int> _prime_numbers_list;
        int _primeIt_index;
    };

public:
    class SideCrossIterator {
    public:

        explicit SideCrossIterator(MagicalContainer& con) :
        _con(con), _forward_index(0), _backwards_index(_con.size()-1), _isForward(true) {};

        SideCrossIterator(const SideCrossIterator& other) :
        _con(other._con), _forward_index(other._forward_index), _backwards_index(other._backwards_index), _isForward(other._isForward) {};

        SideCrossIterator& operator= (const SideCrossIterator& other);

        bool operator== (const SideCrossIterator& other) const;

        bool operator!= (const SideCrossIterator& other) const;

        bool operator> (const SideCrossIterator& other) const;

        bool operator< (const SideCrossIterator& other) const;

        int operator* () const;

        SideCrossIterator& operator++ ();

        SideCrossIterator& begin();

        SideCrossIterator end();

    private:
        MagicalContainer& _con;
        int _forward_index;
        int _backwards_index;
        bool _isForward;
    };

};


#endif //MAGICAL_ITERATORS_A_MAGICALCONTAINER_HPP
