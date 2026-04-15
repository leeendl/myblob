struct myblob
{
    myblob(const char *_data) 
    {
        int len = 0;
        while (_data[len] != '\0')
        {
            ++len;
        }

        mSize = len;
        mData = new char[mSize];

        _memcpy(mData, _data, mSize);
    }
    myblob(int _x)
    {
        mSize = sizeof(int);
        mData = new char[mSize];

        _memcpy(mData, &_x, mSize);
    }

    void copy_to(void* _dest, int _size) const
    {
        _memcpy(_dest, mData, _size);
    }

    const char* data() const { return this->mData; }
    int         size() const { return this->mSize; }

    ~myblob() { delete[] this->mData; }

private:
    char* mData = nullptr;
    int   mSize = 0;

    static void _memcpy(void* _dest, const void* _data, int _size)
    {
#if defined(_STRING_H) || defined(_INC_STRING) || defined(_GLIBCXX_STRING_H)
        std::memcpy(_dest, _data, _size); // for memory overwrite like mimalloc
#else
        char*       dest = (char*)_dest;
        const char* data = (const char*)_data;
        
        for (int i = 0; i < _size; ++i)
        {
            dest[i] = data[i];
        }
#endif
    }
};