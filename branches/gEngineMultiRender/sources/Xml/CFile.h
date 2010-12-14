#ifndef _FILE_H_
#define _FILE_H_

#include <windows.h>

class file
{
public:
         file();
         file(const char* _name,bool _write=false);
        ~file();

        unsigned int  open(const char* _name,bool _write=false);
        unsigned int  read(void* _buf,unsigned int _size);
        unsigned int  write(void* _buf,unsigned int _size);
        unsigned int  size();
        void seek(unsigned int _offset);
        void close();

        file& operator<<(int _val);
        file& operator<<(float _val);
        file& operator<<(const char* _val);

        file& operator>>(int& _val);
        file& operator>>(float& _val);
        file& operator>>(char* _val);

private:
        HANDLE          m_file;
        bool            m_opened;
        bool            m_writable;
        unsigned int                     m_size;
        unsigned int                     m_cursor;
};

#endif
