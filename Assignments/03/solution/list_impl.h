template <
        typename ValueT,
        ValueT default_value = ValueT()>
void list<ValueT, default_value>::push_front(ValueT value) {
        list_node * node = new list_node();
        ln->next = &_head;
        ln->value = value;
        _head = *node;
}

template <
        typename ValueT,
        ValueT default_value = ValueT()>
ValueT list<ValueT, default_value>::pop_front(ValueT value) {
        list_node * update = _head.next;
        ValueT ret = _head.value;
        delete _head;
        _head = *update;
        return ret;
}

template <
        typename ValueT,
        ValueT default_value = ValueT()>
void list<ValueT, default_value>::insert(ValueT value) {
        list_node * node = new list_node();
        ln->next = position._list_node->next;
        ln->value = value;
        position._list_node.next = node;
}

template <
        typename ValueT,
        ValueT default_value>
ValueT & list<ValueT, default_value>::operator[](int index){
        if (index < 0 || static_cast<int>(size()) <= index) {
                throw std::invalid_argument("index out of bounds");
        }
        iterator tmp = ListIterator(_begin);
        for (int i=0; tmp != _end; ++tmp) {
                if (i == index) return *tmp;
                i++;
        }
}

template <typename ValueT, ValueT default_value>
bool list<ValueT, default_value>::operator==(const self_t & rhs) const {
        // printf("\n !! DEBUG const list==\n");
        return (this == &rhs || // identity
                (this->_begin == rhs._begin)
                );
}
