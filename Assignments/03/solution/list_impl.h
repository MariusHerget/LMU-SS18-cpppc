template <
        typename ValueT,
        ValueT default_value>
void list<ValueT, default_value>::push_front(ValueT value) {
        _head = new list_node {_head, value};
        ++_size;
}

template <
        typename ValueT,
        ValueT default_value>
ValueT list<ValueT, default_value>::pop_front() {
        if (size() == 0)
                return default_value;

        list_node * tmp = _head;
        ValueT val = tmp->value;
        _head = tmp->next;
        delete tmp;

        --_size;
        return val;
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
        iterator tmp = begin();
        for (int i=0; tmp != (*this).end(); ++tmp, i++) {
                if (i == index) return *tmp;
        }
}

template <typename ValueT, ValueT default_value>
bool list<ValueT, default_value>::operator==(self_t & rhs) {
        if (this == &rhs)
                return true;

        else if ((*this).size() != rhs.size())
                return false;

        else if ((*this).size() == 0)
                return true;

        iterator ithis = begin();
        iterator irhs  = rhs.begin();

        while (ithis != (*this).end() && irhs != rhs.end())
        {
                if (*ithis != *irhs)
                        return false;
                ++ithis;
                ++irhs;
        }

        return true;
}
