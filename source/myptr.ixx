export module myptr;

export template <typename T>
class MyPtr
{
public:
    ~MyPtr() throw()
    {
        InternalRelease();
    }

    operator bool() const throw()
    {
        return Get() != nullptr;
    }

    unsigned long InternalRelease() throw()
    {
        unsigned long ref = 0;
        T* temp = ptr;

        if (temp != nullptr)
        {
            ptr = nullptr;
            ref = temp->Release();
        }

        return ref;
    }

    T* Get() const throw()
    {
        return ptr;
    }

    template<typename U>
    void* As(MyPtr<U>* p) const throw()
    {
        return ptr->QueryInterface(__uuidof(U), reinterpret_cast<void**>(p->ReleaseAndGetAddressOf()));
    }

    T* Detach() throw()
    {
        T* ptr = this->ptr;
        this->ptr = nullptr;
        return ptr;
    }

    T* operator->() const throw()
    {
        return ptr;
    }

    T** operator&() throw()
    {
        return reinterpret_cast<T**>(this);
    }

private:
    T* ptr;
};