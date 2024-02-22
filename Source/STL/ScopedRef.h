//#include <>

namespace AXSTL {

template <class T>
class ScopedRef final
{
public:
    ScopedRef() noexcept : ScopedRef{nullptr} {}
    explicit ScopedRef(T* InPointer) noexcept : mPointer{InPointer} {}

    ScopedRef(const ScopedRef&) = delete;
    ScopedRef& operator=(const ScopedRef&) = delete;

    ScopedRef(ScopedRef&& Other) noexcept : mPointer{Other.Release()} {}
    ScopedRef& operator=(ScopedRef&& Other) noexcept
    {
        if (this != &Other)
        {
            Reset(Other.Release());
        }

        return *this;
    }

    ~ScopedRef() noexcept
    {
        if (mPointer)
        {
            delete mPointer;
        }
    }

    T* Release() noexcept
    {
        return std::exchange(mPointer, nullptr);
    }

    void Reset(T* InPointer = nullptr) noexcept
    {
        T* Old = std::exchange(mPointer, InPointer);

        if (Old)
        {
            delete Old;
        }
    }

    T* GetRaw() const noexcept { return mPointer; }

    explicit operator bool() const noexcept
    {
        return static_cast<bool>(mPointer);
    }

    T* operator->() const noexcept { return mPointer; }

    T& operator*() const noexcept { return *mPointer; }

private:
    T* mPointer = nullptr;
};

template<class T, class... Args>
ScopedRef<T> CreateScopedRef(Args&& ...InArgs)
{
    return ScopedRef<T>(new T(std::forward<Args>(InArgs)...));
}

}