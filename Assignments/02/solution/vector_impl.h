template <typename VectorType> Vector<VectorType>::Vector(
        const std::string & name,
        size_type size,
        VectorType base_val)
        : _name(name), _size(size)
{
        if (_size > 0) {
                _data = new VectorType[_size];
                for (size_type i = 0; i < _size; i++) {
                        _data[i] = base_val + (i + 1);
                }
        }
}
template <typename VectorType>
Vector<VectorType>::~Vector()
{
        if (nullptr != _data) {
                delete[] _data;
        }
}
template <typename VectorType>
bool Vector<VectorType>::operator==(const Vector & other) {
        if (
                _size == other._size &&
                _data == other._data
                ) {
                return true;
        }
        else if (
                _size == other._size
                ) {
                int f=0;
                for (int i; i<other._size; i++) {
                        if (other._data[i] != _data[i]) f=1;
                }
                if (f==0) { return true;}
                else {return false;}
        }
        return false;
}


template <typename VectorType>
Vector<VectorType>::Vector(const Vector & rhs)
        : _name(rhs._name), _size(rhs._size)
{
        _data = new VectorType[_size];
        for (size_type i = 0; i < _size; i++) {
                _data[i] = rhs._data[i];
        }
}

template <typename VectorType>
Vector<VectorType> & Vector<VectorType>::operator=(const Vector & other)
{
        if (this != &other) {
                _size = other._size;
                _name = other._name;
                if (nullptr != _data) {
                        delete[] _data;
                }
                if (_size > 0) {
                        _data = new VectorType[_size];
                        for (size_type i = 0; i < _size; i++) {
                                _data[i] = other._data[i];
                        }
                }
                else {
                        _data = nullptr;
                }
        }
        return *this;
}

template <typename VectorType>
void Vector<VectorType>::push_back(VectorType val){
        _size = _size+1;
        VectorType * datanew = static_cast<VectorType*>(malloc((sizeof(VectorType)*_size)+1));
        for (size_type i=0; i<_size-1; i++) {
                datanew[i] =_data[i];
        }
        datanew[_size-1] = val;
        _data = datanew;

}

template <typename VectorType>
VectorType Vector<VectorType>::pop_back(){
        if (_size > 0) {
                VectorType ret =  _data[_size-1];
                _size = _size-1;
                VectorType * datanew = static_cast<VectorType*>(malloc((sizeof(VectorType)*_size)+1));
                for (int i=0; i<_size; i++) {
                        datanew[i] =_data[i];
                }
                _data = datanew;
                return ret;
        }
        return 0;
}

template <typename VectorType>
inline void Vector<VectorType>::reverse() {
        VectorType * datanew = static_cast<VectorType*>(malloc((sizeof(VectorType)*_size)+1));
        int o=0;
        for (int i=_size-1; i>=0; i--) {
                datanew[o] = _data[i];
                o++;
        }
        _data = datanew;
}
// }// namespace cpppc
