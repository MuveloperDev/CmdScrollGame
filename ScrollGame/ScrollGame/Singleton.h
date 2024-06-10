#include <iostream>
#include <mutex>

#pragma once
template<typename T>
class Singleton
{
public:
    // 싱글턴 인스턴스를 얻기 위한 정적 메서드
    static T& GetInstance();
    static void DestroyInstance();
    // 복사 생성자와 대입 연산자를 삭제하여 복사와 대입을 방지
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;

private:
    static T* _instance;
    static std::mutex _mutex;
};

// 정적 멤버 변수 초기화
template <typename T> T* Singleton<T>::_instance = nullptr;
template <typename T> std::mutex Singleton<T>::_mutex;

template<typename T>
inline T& Singleton<T>::GetInstance()
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_instance == nullptr) {
        _instance = new T();
    }
    return *_instance;
}

template<typename T>
inline void Singleton<T>::DestroyInstance()
{
    std::lock_guard<std::mutex> lock(_mutex);
    delete _instance;
    _instance = nullptr;
}
