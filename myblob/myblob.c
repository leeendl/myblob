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

        _copy(mData, _data, mSize);
    }
    myblob(int _x)
    {
        mSize = sizeof(int);
        mData = new char[mSize];

        _copy(this->mData, &_x, mSize);
    }

    void copy_to(void* _dest, int destSize) const
    {
        _copy(_dest, this->mData, destSize);
    }

    const char* data() const { return this->mData; }
    int         size() const { return this->mSize; }

    ~myblob() { delete[] this->mData; }

private:
    char* mData = nullptr;
    int   mSize = 0;

    static void _copy(void* _dest, const void* _data, int _size)
    {
        char*       dest = (char*)_dest;
        const char* data = (const char*)_data;
        
        for (int i = 0; i < _size; ++i)
        {
            dest[i] = data[i];
        }
    }
};