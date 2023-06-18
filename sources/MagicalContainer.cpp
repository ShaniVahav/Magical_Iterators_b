//
// Created by shani on 03/06/2023.
//

#include <algorithm>
#include <stdexcept>
#include "MagicalContainer.hpp"
using namespace std;

bool isPrime(int num){
    if (num <= 1)
        return false;

    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

void MagicalContainer::addElement(const int num) {
    /// Find the position to insert the new element to keep list sorts
    auto it = _magic_list.begin();
    while (it != _magic_list.end() && *it < num) {
        ++it;
    }
    // insert the new element at the right place
    _magic_list.insert(it, num);
}

void MagicalContainer::removeElement(const int num) {
    /// Check if num is in the list
    // iterate on list
    auto it = find(_magic_list.begin(), _magic_list.end(), num);
    if(it == _magic_list.end()){
        // 'num' not in the list
        throw runtime_error("Cannot remove element that not exist in the list");
    }
    /// Remove all occurrences of 'num'
    _magic_list.remove(num);
}

int MagicalContainer::size() {
    return _magic_list.size();
}

int MagicalContainer::getElement(int index) const {
    // move the iterator to the right position
    auto it = _magic_list.begin();
    advance(it, index);

    return *it;
}

/// -------------------------------------------------------- AscendingIterator -------------------------------------------------------- ///

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &con) : _con(con) {
    if(_con.size() > 0){
        _acsIt_index = 0;
    }
    else{
        _acsIt_index = _con.size();
    }
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if(this != &other){  // if it's not a=a
        if(&this->_con != &other._con){
            throw runtime_error("Cannot assignment iterator with different container");
        }
        this->_acsIt_index = other._acsIt_index;
    }
    return *this;
}


bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    /// Check if the iterators has the same container and same position (pointing to the same element)
    if(&(this->_con) != &(other._con)){
        // their container it's not the same one
        return false;
    }
    if(this->_acsIt_index != other._acsIt_index){
        // the iterators not in the same position
        return false;
    }

    return true;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
    if (this->_acsIt_index > other._acsIt_index){
        return true;
    }
    return false;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
    return !(*this > other) && (*this != other);
}

int MagicalContainer::AscendingIterator::operator*() const {
    int num = _con.getElement(_acsIt_index);
    return num;  // return the current element (int) this iterator points to
}

MagicalContainer::AscendingIterator & MagicalContainer::AscendingIterator::operator++() {
    if(*this == (*this).end()){
        throw runtime_error("Invalid increasing after end()");
    }
    _acsIt_index++; // increase the index

    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    // this iterator need to begin from index 0
    _acsIt_index = 0;
    return  *this;
}


MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    AscendingIterator end(*this);  // create a copy
    end._acsIt_index = _con.size();  // end to iterate

    return end;
}

/// -------------------------------------------------------- PrimeIterator -------------------------------------------------------- ///

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &con) : _con(con) {
    for(const int num : con._magic_list){
        if (isPrime(num)){
            _prime_numbers_list.push_back(num);
        }
    }

    // initialize index of prime
    if(!_prime_numbers_list.empty()){
        _primeIt_index = 0;
    } else{
        _primeIt_index = _prime_numbers_list.size();
    }
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if(this != &other){  // if it's not a=a
        if(&this->_con != &other._con){
            throw runtime_error("Cannot assignment iterator with different container");
        }
        this->_primeIt_index = other._primeIt_index;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const{
    /// Check if the iterators have the same container and same position (pointing to the same element)
    if(&(this->_con) != &(other._con)){
        // their container it's not the same one
        return false;
    }
    if(this->_primeIt_index != other._primeIt_index){
        // the iterators not in the same position
        return false;
    }

    return true;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {

    if (this->_primeIt_index > other._primeIt_index){
        return true;
    }

    return false;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
    return !(*this > other) && (*this != other);
}

int MagicalContainer::PrimeIterator::operator*() const {
    return this->getElement(_primeIt_index);
}

MagicalContainer::PrimeIterator & MagicalContainer::PrimeIterator::operator++() {
    if(*this == (*this).end()){
        throw runtime_error("Invalid increasing after end()");
    }

    _primeIt_index++; // increase the index

    return *this;
}

int MagicalContainer::PrimeIterator::getElement(int index) const{
    auto it = _prime_numbers_list.begin();
    advance(it, _primeIt_index);

    return *it;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    _primeIt_index = 0;
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    PrimeIterator end(*this);  // create a copy
    end._primeIt_index = _prime_numbers_list.size();  // end to iterate

    return end;
}



/// -------------------------------------------------------- SideCrossIterator -------------------------------------------------------- ///

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if(this != &other){  // if it's not a=a
        if(&this->_con != &other._con){
            throw runtime_error("Cannot assignment iterator with different containers");
        }
        this->_forward_index = other._forward_index;
        this->_backwards_index = other._backwards_index;
        this->_isForward = other._isForward;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    /// Check if the iterators have the same container and same position (pointing to the same element)

    if(&(this->_con) != &(other._con)) { return false; }
    if(this->_forward_index != other._forward_index){ return false; }
    if(this->_backwards_index != other._backwards_index){ return false; }
    if(this->_isForward != other._isForward){ return false; }

    return true;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
    if(_isForward){
        if (this->_backwards_index > other._backwards_index){
            return true;
        }
        return false;
    }else{
        if(this->_forward_index > other._forward_index){
            return true;
        }
        return false;
    }
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
    return !(*this > other) && (*this != other);
}

int MagicalContainer::SideCrossIterator::operator*() const {
    int num;
    if (_isForward){
        num = _con.getElement(_forward_index);
    }else{
        num = _con.getElement(_backwards_index);
    }

    return num;
}

MagicalContainer::SideCrossIterator & MagicalContainer::SideCrossIterator::operator++() {
    if(*this == (*this).end()){
        throw runtime_error("Invalid increasing after end()");
    }

    if (_isForward){
        _forward_index++;
        _isForward = false;
    }else{
        _backwards_index--;
        _isForward = true;
    }

    return *this;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin() {
    _forward_index = 0;
    _backwards_index = _con.size() - 1;
    _isForward = true;

    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    SideCrossIterator end(*this);
    int con_size = _con.size();

    if(con_size % 2 == 0){
        end._forward_index = con_size/2;
        end._backwards_index = con_size/2 - 1;
        end._isForward = true;
    } else{
        end._forward_index = con_size/2 + 1;
        end._backwards_index = con_size/2;
        end._isForward = false;
    }

    return end;
}