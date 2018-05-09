template<typename T>
T Measurements<T>::median() const {
        if (size()==0) {
                return 0;
        }
        else if (size()==1) {
                return _values[0];
        }
        else {
                std::vector<T> tmp(_values);
                std::sort(tmp.begin(), tmp.end());
                if (tmp.size() % 2 == 0) {
                        return (tmp[tmp.size() /2 -1] + tmp[tmp.size() / 2]/2);
                } else {
                        return tmp[tmp.size() /2];
                }
        }
}

template<typename T>
double Measurements<T>::mean() const {
    if (size() == 0 ) return 0;
    else return std::accumulate(_values.begin(), _values.end(), 0.0)/(size());
}

template<typename T>
double Measurements<T>::variance() const {
    if (size() == 0 ) return 0;
    else {
      double _mean = mean();
      double temp = 0;
      for(T a : _values)
          temp += (a-_mean)*(a-_mean);
      return temp/(size());
    }
}

template<typename T>
double Measurements<T>::sigma() const {
        return sqrt(variance());
}
