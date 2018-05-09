
template <
        typename ValueT,
        ValueT default_value>
bool list<ValueT, default_value>::operator==(self_t & rhs){
        return (this == &rhs || // identity
                (this->_begin == rhs._begin)
                );
}
// Why does this not work
    // -> invalid operands to binary expression ('const cpppc::list<int, 0>::ListIterator' and 'const cpppc::list<int, 0>::ListIterator')
//
template <typename ValueT, ValueT default_value>
bool list<ValueT, default_value>::operator==(const self_t & rhs) const {
        return (this == &rhs || // identity
                (this->_begin == rhs._begin)
                );
}




template <
        typename ValueT,
        ValueT default_value>
void list<ValueT, default_value>::push_back(ValueT val){

}

template <
        typename ValueT,
        ValueT default_value>
ValueT list<ValueT, default_value>::pop_back(){
        // necessary?
        return default_value;
}

template <
        typename ValueT,
        ValueT default_value>
ValueT & list<ValueT, default_value>::operator[](int index){
        if (index < 0 || static_cast<int>(size()) <= index) {
                throw std::invalid_argument("index out of bounds");
        }
        iterator tmp = ListIterator(&_head, this);
        for (int i=0; tmp != _end; ++tmp) {
                if (i == index) return *tmp;
                i++;
        }
}
