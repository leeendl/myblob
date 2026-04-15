struct myblob
{
    inline myblob(const char *_Str) 
    {
        const char *_end = _Str;
        while (*_end != '\0') { ++_end; }
        mSize = _end - _Str;
        mData = new char[mSize];

        _memcpy(mData, _Str, mSize);
    }
    inline myblob(const wchar_t *_Str) 
    {
        const wchar_t *_end = _Str;
        while (*_end != wchar_t('\0')) { ++_end; }
        mSize = _end - _Str;
        mData = new char[mSize];

        _memcpy(mData, _Str, mSize);
    }
    inline myblob(int _x)
    {
        mSize = (int)sizeof(int);
        mData = new char[mSize];

        _memcpy(mData, &_x, mSize);
    }

    inline void copy_to(void *__restrict__ __dst, int __n) const
    {
        _memcpy(__dst, mData, __n);
    }

    inline char* data() const { return mData; }
    inline int   size() const { return mSize; }

    ~myblob() { delete[] mData; }

private:
    char* mData = nullptr;
    int   mSize = 0;

    static inline void _memcpy(void *__restrict__ __dst, const void *__restrict__ __src, int __n)
    {
#if defined(_STRING_H) || defined(_INC_STRING) || defined(_GLIBCXX_STRING_H)
        std::memcpy(__dst, __src, __n); // for memory overwrite like mimalloc
#else
        char*       dst = (char*)__dst;
        const char* src = (const char*)__src;
        
        for (int i = 0; i < __n; ++i)
        {
            dst[i] = src[i];
        }
#endif
    }
};