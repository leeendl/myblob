#include <cstring>
#include <type_traits>

struct myblob
{
    myblob(const void* _data, int _size) : mSize(_size), mData(new char[_size])
    {
        std::memcpy(mData, _data, (size_t)mSize);
    }
    inline myblob(const char *_Str)    : myblob(_Str, (int)std::strlen(_Str)) {}
    inline myblob(const wchar_t *_Str) : myblob(_Str, (int)((wcslen(_Str)+1) * sizeof(wchar_t))) {}
  /**
   * @tparam _Tp   A trivially-copyable type.
   */
  template <typename _Tp>
#ifdef __cpp_concepts
    requires std::is_trivially_copyable_v<_Tp>
#endif
    inline myblob(_Tp _x) : myblob(&_x, sizeof(_Tp)) {}

    inline void *copy_to(void *__restrict__ __dst, int __n)
    {
        if ((!mData || mSize <= 0) || !__dst) return nullptr;

        return std::memcpy(__dst, mData, __n);
    }

    inline const char* data() const { return mData; }
    inline int         size() const { return mSize; }

    inline ~myblob() { delete[] mData; }

private:
    char* mData = nullptr;
    int   mSize = 0;
};