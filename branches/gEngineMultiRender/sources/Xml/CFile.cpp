#include "CFile.h"

file::file()
{
        m_opened = false;
        m_size = -1;
        m_writable = false;
        m_cursor = 0;
        m_file = INVALID_HANDLE_VALUE;
}

file::file(const char* _name,bool _write)
{
        file();
        open(_name,_write);
}

file::~file()
{
        close();
}

unsigned int  file::open(const char* _name,bool _write)
{
        m_writable = _write;

        m_file = CreateFile(_name,_write?GENERIC_ALL:GENERIC_READ,
                                                          _write?FILE_SHARE_WRITE|FILE_SHARE_READ:FILE_SHARE_READ,NULL,
                                                          _write?CREATE_ALWAYS:OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

        if(m_file!=INVALID_HANDLE_VALUE)
        {
                m_opened = true;
                m_size = GetFileSize(m_file,NULL);
        }
        
        return m_size;
}

unsigned int  file::read(void* _buf,unsigned int _size)
{
        DWORD tmp_rb = 0;
        ReadFile(m_file,_buf,_size,&tmp_rb,NULL);
        m_cursor += tmp_rb;
        return tmp_rb;
}

unsigned int  file::write(void* _buf,unsigned int _size)
{
        DWORD tmp_rb = 0;
        WriteFile(m_file,_buf,_size,&tmp_rb,NULL);
        m_size += tmp_rb;
        return tmp_rb;
}

unsigned int  file::size()
{
        return m_size;
}

void file::seek(unsigned int _offset)
{
        SetFilePointer(m_file,_offset,NULL,FILE_BEGIN);
}

void file::close()
{
        if(m_opened)
        {
                CloseHandle(m_file);
                m_opened = false;
                m_cursor = 0;
                m_size = -1;
                m_writable = false;
                m_file = INVALID_HANDLE_VALUE;
        }
}

file& file::operator<<(int _val)
{
        write(&_val,4);
        return *this;
}

file& file::operator<<(float _val)
{
        write(&_val,4);
        return *this;
}

file& file::operator<<(const char* _val)
{
        write((void*)_val,(unsigned int)(strlen(_val)+1));
        return *this;
}

file& file::operator>>(int& _val)
{
        read(&_val,4);
        return *this;
}

file& file::operator>>(float& _val)
{
        read(&_val,4);
        return *this;
}

file& file::operator>>(char* _val)
{
        unsigned char  ch = 0;
        int cntr = 0;
        read(&ch,1);
        while(ch!=0)
        {
                _val[cntr]=ch;
                read(&ch,1);
                cntr++;
        }
        _val[cntr]=0;
        return *this;
}
