

template <
        typename ValueT,
        ValueT default_value>
void list<ValueT,default_value>::push_back(ValueT val){
        // create new list_node
        list_node nn = { nullptr, val };
        if(_head.next == nullptr){
                _head = nn;
                _begin = iterator(this, &_head);
        } else if(_tail.next != nullptr)
                _tail.next = &nn;
        _tail = nn;
        // move pointer TODO
}

template <
        typename ValueT,
        ValueT default_value>
ValueT list<ValueT,default_value>::pop_back() {
        // if(_tail == nullptr)
        //         throw std::runtime_error("Invalid Action");
        return default_value; // TODO FIX
}

template <
        typename ValueT,
        ValueT default_value>
ValueT list<ValueT,default_value>::erase_after(iterator it) {
        iterator deleteiterator = ++it;
        it._list_node.next = deleteiterator._list_node.next;
        delete(deleteiterator);
}
