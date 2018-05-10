template <
        typename ValueT,
        ValueT default_value>
void list<ValueT, default_value>::push_front(ValueT value) {
        list_node * node = new list_node();
        node->next = &_head;
        node->value = value;
        _head = *node;
}

template <
        typename ValueT,
        ValueT default_value>
ValueT list<ValueT, default_value>::pop_front() {
        list_node * update = _head.next;
        ValueT ret = _head.value;
        _head = *update;
        return ret;
}

template <
        typename ValueT,
        ValueT default_value>
void list<ValueT, default_value>::insert(iterator & position, ValueT value) {
        list_node * node = new list_node();
        node->next = position._list_node->next;
        node->value = value;
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
bool list<ValueT, default_value>::operator==(self_t & rhs) {
        // printf("\n !! DEBUG const list==\n");
        return (this == &rhs || // identity
                (this->_begin == rhs._begin)
                );
}
