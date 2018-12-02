#pragma once

#include <condition_variable>
#include <cstdint>
#include <list>
#include <memory>
#include <mutex>
#include <set>
#include <string>

namespace core {

using ui8 = uint8_t;

using ConditionVariable = ::std::condition_variable;

template <class T>
using List = ::std::list<T>;

using Mutex = ::std::mutex;

template <class U, class V = U>
using Pair = ::std::pair<U, V>;

template <class T>
using Set = ::std::set<T>;

template <class T>
using SharedPtr = ::std::shared_ptr<T>;

using String = ::std::string;

template <class T, class Deleter = ::std::default_delete<T>>
using UniquePtr = ::std::unique_ptr<T, Deleter>;

template <class T>
using WeakPtr = ::std::weak_ptr<T>;

}  // namespace core
