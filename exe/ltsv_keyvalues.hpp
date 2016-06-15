//
// Created by Yuta Hinokuma on 2016/01/25.
//

#ifndef CONSOLA2_LTSV_KEYVALUES_HPP
#define CONSOLA2_LTSV_KEYVALUES_HPP

#include <map>
#include <string>
#include <type_traits>
#include "easylogging++.h"



template<class Key, class Value, class... Rest>
struct ltsv_keyvalues : public el::Loggable
{
  ltsv_keyvalues(
          const Key& _key,
          const Value& _value,
          const Rest&... _rest
  ) :
      key(_key),
      value(_value),
      rest(_rest...)
  {
  }

  virtual void log(el::base::type::ostream_t& os) const
  {
    os << key << ":" << value << "\t";
    rest.log(os);
  }

  Key key;
  Value value;
  ltsv_keyvalues<Rest...> rest;
};

template<class Key, class Value>
struct ltsv_keyvalues<Key, Value> : public el::Loggable
{
  ltsv_keyvalues(const Key& _key, const Value& _value) :
      key(_key),
      value(_value)
  {
  }

  virtual void log(el::base::type::ostream_t& os) const
  {
    os << key << ":" << value;
  }

  Key key;
  Value value;
};


template<class... Rest>
ltsv_keyvalues<Rest...> get_ltsv_keyvalues(
    const Rest&... rest
)
{
    return ltsv_keyvalues<Rest...>(rest...);
}

#endif //CONSOLA2_LTSV_KEYVALUES_HPP
