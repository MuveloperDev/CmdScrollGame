#include <iostream>
#include <mutex>

#pragma once
template<typename T>
class Singleton
{
public:
    // �̱��� �ν��Ͻ��� ��� ���� ���� �޼���
    static T& GetInstance();
    static void DestroyInstance();
    // ���� �����ڿ� ���� �����ڸ� �����Ͽ� ����� ������ ����
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;

private:
    static T* _instance;
    static std::mutex _mutex;
};

// ���� ��� ���� �ʱ�ȭ
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
