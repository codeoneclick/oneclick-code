#include "CXml.h"
#include "CFile.h"
#include <stdlib.h>
#include <new>

#define STATIC_ASSERT(cond) {static const char condition_failed[(cond)?1:-1]={0};(void)condition_failed[0];}

const unsigned char UTF8_BYTE_MASK = 0xBF;
const unsigned char UTF8_BYTE_MARK = 0x80;
const unsigned char UTF8_BYTE_MASK_READ = 0x3F;
const unsigned char UTF8_FIRST_BYTE_MARK[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

enum chartype
{
        ct_parse_pcdata = 1,    // \0, &, \r, <
        ct_parse_attr = 2,              // \0, &, \r, ', "
        ct_parse_attr_ws = 4,   // \0, &, \r, ', ", \n, space, tab
        ct_space = 8,                   // \r, \n, space, tab
        ct_parse_cdata = 16,    // \0, ], >, \r
        ct_parse_comment = 32,  // \0, -, >, \r
        ct_symbol = 64,                 // Any symbol > 127, a-z, A-Z, 0-9, _, :, -, .
        ct_start_symbol = 128   // Any symbol > 127, a-z, A-Z, _, :
};

const unsigned char chartype_table[256] =
{
        55,  0,   0,   0,   0,   0,   0,   0,      0,   12,  12,  0,   0,   63,  0,   0,   // 0-15
        0,   0,   0,   0,   0,   0,   0,   0,      0,   0,   0,   0,   0,   0,   0,   0,   // 16-31
        12,  0,   6,   0,   0,   0,   7,   6,      0,   0,   0,   0,   0,   96,  64,  0,   // 32-47
        64,  64,  64,  64,  64,  64,  64,  64,     64,  64,  192, 0,   1,   0,   48,  0,   // 48-63
        0,   192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192, // 64-79
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 0,   0,   16,  0,   192, // 80-95
        0,   192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192, // 96-111
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 0, 0, 0, 0, 0,           // 112-127
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192, // 128+
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192,
        192, 192, 192, 192, 192, 192, 192, 192,    192, 192, 192, 192, 192, 192, 192, 192
};
        
bool is_chartype(char c, chartype ct)
{
        return !!(chartype_table[static_cast<unsigned char>(c)] & ct);
}

char* strutf16_utf8(char* s, unsigned int ch)
{
        unsigned int length;
        if(ch<0x80) 
                length=1;
        else
        if(ch<0x800)
                length=2;
        else 
        if(ch<0x10000) 
                length=3;
        else 
        if(ch<0x200000) 
                length=4;
        else 
                return s;
        
        s+=length;

        switch (length)
        {
                case 4:
                        *--s = (char)((ch | UTF8_BYTE_MARK) & UTF8_BYTE_MASK); 
                        ch >>= 6;
                case 3:
                        *--s = (char)((ch | UTF8_BYTE_MARK) & UTF8_BYTE_MASK); 
                        ch >>= 6;
                case 2:
                        *--s = (char)((ch | UTF8_BYTE_MARK) & UTF8_BYTE_MASK); 
                        ch >>= 6;
                case 1:
                        *--s = (char)(ch | UTF8_FIRST_BYTE_MARK[length]);
        }               
        return s + length;
}

template <bool _1, bool _2> struct opt2_to_type
{
        static const bool o1;
        static const bool o2;
};

template <bool _1, bool _2> const bool opt2_to_type<_1, _2>::o1 = _1;
template <bool _1, bool _2> const bool opt2_to_type<_1, _2>::o2 = _2;

template <bool _1, bool _2, bool _3, bool _4> struct opt4_to_type
{
        static const bool o1;
        static const bool o2;
        static const bool o3;
        static const bool o4;
};

template <bool _1, bool _2, bool _3, bool _4> const bool opt4_to_type<_1, _2, _3, _4>::o1 = _1;
template <bool _1, bool _2, bool _3, bool _4> const bool opt4_to_type<_1, _2, _3, _4>::o2 = _2;
template <bool _1, bool _2, bool _3, bool _4> const bool opt4_to_type<_1, _2, _3, _4>::o3 = _3;
template <bool _1, bool _2, bool _3, bool _4> const bool opt4_to_type<_1, _2, _3, _4>::o4 = _4;

struct gap
{
        char* end;
        size_t size;
                        
        gap(): end(0), size(0)
        {
        }
        // #WARNING Èñïîëüçóåòñÿ memmove. Ðåçóëüòàò íå ïðåäñêàçóåì
        void push(char*& s, size_t count)
        {
                if(end)
                        memmove(end - size, end, s - end);
                s += count;
                end = s;
                size += count;
        }
        // #WARNING Èñïîëüçóåòñÿ memmove. Ðåçóëüòàò íå ïðåäñêàçóåì
        char* flush(char* s)
        {
                if (end)
                {
                        memmove(end - size, end, s - end);
                        return s - size;
                }
                else 
                        return s;
        }
};
        
char* strconv_escape(char* s, gap& g)
{
        char* stre = s + 1;
        switch (*stre)
        {
                case '#':       // &#...
                {
                        unsigned int ucsc = 0;
                        ++stre;
                        if (*stre == 'x') // &#x... (hex code)
                        {
                                ++stre;
                                while (*stre)
                                {
                                        if (*stre >= '0' && *stre <= '9')
                                                ucsc = 16 * ucsc + (*stre++ - '0');
                                        else if (*stre >= 'A' && *stre <= 'F')
                                                ucsc = 16 * ucsc + (*stre++ - 'A' + 10);
                                        else if (*stre >= 'a' && *stre <= 'f')
                                                ucsc = 16 * ucsc + (*stre++ - 'a' + 10);
                                        else if (*stre == ';')
                                                break;
                                        else // cancel
                                                return stre;
                                }

                                if (*stre != ';') return stre;
                                                
                                ++stre;
                        }
                        else    // &#... (dec code)
                        {
                                while (*stre >= '0' && *stre <= '9')
                                        ucsc = 10 * ucsc + (*stre++ - '0');

                                if (*stre != ';') return stre;
                                                
                                ++stre;
                        }

                        s = strutf16_utf8(s, ucsc);
                                        
                        g.push(s, stre - s);
                        return stre;
                }
                case 'a':       // &a
                {
                        ++stre;

                        if (*stre == 'm') // &am
                        {
                                if (*++stre == 'p' && *++stre == ';') // &amp;
                                {
                                        *s++ = '&';
                                        ++stre;
                                                        
                                        g.push(s, stre - s);
                                        return stre;
                                }
                        }
                        else if (*stre == 'p') // &ap
                        {
                                if (*++stre == 'o' && *++stre == 's' && *++stre == ';') // &apos;
                                {
                                        *s++ = '\'';
                                        ++stre;

                                        g.push(s, stre - s);
                                        return stre;
                                }
                        }
                        break;
                }
                case 'g': // &g
                {
                        if (*++stre == 't' && *++stre == ';') // &gt;
                        {
                                *s++ = '>';
                                ++stre;
                                        
                                g.push(s, stre - s);
                                return stre;
                        }
                        break;
                }
                case 'l': // &l
                {
                        if (*++stre == 't' && *++stre == ';') // &lt;
                        {
                                *s++ = '<';
                                ++stre;
                                        
                                g.push(s, stre - s);
                                return stre;
                        }
                        break;
                }
                case 'q': // &q
                {
                        if (*++stre == 'u' && *++stre == 'o' && *++stre == 't' && *++stre == ';') // &quot;
                        {
                                *s++ = '"';
                                ++stre;
                                
                                g.push(s, stre - s);
                                return stre;
                        }
                        break;
                }
        }
                
        return stre;
}

char* strconv_comment(char* s)
{
        if (!*s) return 0;
                
        gap g;
                
        while (true)
        {
                while (!is_chartype(*s, ct_parse_comment)) ++s;
        
                if (*s == '\r') // Either a single 0x0d or 0x0d 0x0a pair
                {
                        *s++ = '\n'; // replace first one with 0x0a
                        
                        if (*s == '\n') g.push(s, 1);
                }
                else if (*s == '-' && *(s+1) == '-' && *(s+2) == '>') // comment ends here
                {
                        *g.flush(s) = 0;
                                
                        return s + 3;
                }
                else if (*s == 0)
                {
                        return 0;
                }
                else ++s;
        }
}

char* strconv_cdata(char* s)
{
        if (!*s) return 0;
                
        gap g;
                
        while (true)
        {
                while (!is_chartype(*s, ct_parse_cdata)) ++s;
                        
                if (*s == '\r') // Either a single 0x0d or 0x0d 0x0a pair
                {
                        *s++ = '\n'; // replace first one with 0x0a
                        
                        if (*s == '\n') g.push(s, 1);
                }
                else if (*s == ']' && *(s+1) == ']' && *(s+2) == '>') // CDATA ends here
                {
                        *g.flush(s) = 0;
                                
                        return s + 1;
                }
                else if (*s == 0)
                {
                        return 0;
                }
                else ++s;
        }
}
                
template <typename opt2> char* strconv_pcdata_t(char* s, opt2)
{
        const bool opt_eol = opt2::o1;
        const bool opt_escape = opt2::o2;

        if (!*s) return 0;

        gap g;
                
        while (true)
        {
                while (!is_chartype(*s, ct_parse_pcdata)) ++s;
                        
                if (opt_eol && *s == '\r') // Either a single 0x0d or 0x0d 0x0a pair
                {
                        *s++ = '\n'; // replace first one with 0x0a
                                
                        if (*s == '\n') g.push(s, 1);
                }
                else if (opt_escape && *s == '&')
                {
                        s = strconv_escape(s, g);
                }
                else if (*s == '<') // PCDATA ends here
                {
                        *g.flush(s) = 0;
                        
                        return s + 1;
                }
                else if (*s == 0)
                {
                        return s;
                }
                else ++s;
        }
}

char* strconv_pcdata(char* s, unsigned int optmask)
{
        STATIC_ASSERT(c_parse_escapes == 0x10 && c_parse_eol == 0x20);

        switch ((optmask >> 4) & 3) // get bitmask for flags (eol escapes)
        {
                case 0: return strconv_pcdata_t(s, opt2_to_type<0, 0>());
                case 1: return strconv_pcdata_t(s, opt2_to_type<0, 1>());
                case 2: return strconv_pcdata_t(s, opt2_to_type<1, 0>());
                case 3: return strconv_pcdata_t(s, opt2_to_type<1, 1>());
                default: return 0; // should not get here
        }
}

template <typename opt4> char* strconv_attribute_t(char* s, char end_quote, opt4)
{
        const bool opt_wconv = opt4::o1;
        const bool opt_wnorm = opt4::o2;
        const bool opt_eol = opt4::o3;
        const bool opt_escape = opt4::o4;

        if (!*s) return 0;
                        
        gap g;

                // Trim whitespaces
        if (opt_wnorm)
        {
                char* str = s;
                        
                while (is_chartype(*str, ct_space)) ++str;
                        
                if (str != s)
                        g.push(s, str - s);
        }

        while (true)
        {
                while (!is_chartype(*s, (opt_wnorm || opt_wconv) ? ct_parse_attr_ws : ct_parse_attr)) ++s;
                
                if (opt_wnorm && is_chartype(*s, ct_space))
                {
                        *s++ = ' ';
        
                        if (is_chartype(*s, ct_space))
                        {
                                char* str = s + 1;
                                while (is_chartype(*str, ct_space)) ++str;
                                
                                g.push(s, str - s);
                        }
                }
                else if (opt_wconv && is_chartype(*s, ct_space))
                {
                        if (opt_eol)
                        {
                                if (*s == '\r')
                                {
                                        *s++ = ' ';
                        
                                        if (*s == '\n') g.push(s, 1);
                                }
                                else *s++ = ' ';
                        }
                        else *s++ = ' ';
                }
                else if (opt_eol && *s == '\r')
                {
                        *s++ = '\n';
                        
                        if (*s == '\n') g.push(s, 1);
                }
                else if (*s == end_quote)
                {
                        char* str = g.flush(s);
                        
                        if (opt_wnorm)
                        {
                                do *str-- = 0;
                                while (is_chartype(*str, ct_space));
                        }
                        else *str = 0;
                
                        return s + 1;
                }
                else if (opt_escape && *s == '&')
                {
                        s = strconv_escape(s, g);
                }
                else if (!*s)
                {
                        return 0;
                }
                else ++s;
        }
}
        
char* strconv_attribute(char* s, char end_quote, unsigned int optmask)
{
        STATIC_ASSERT(c_parse_escapes==0x10&&c_parse_eol==0x20&&c_parse_wnorm_attribute==0x40&&c_parse_wconv_attribute==0x80);
                
        switch ((optmask >> 4) & 15) // get bitmask for flags (wconv wnorm eol escapes)
        {
                case 0:  return strconv_attribute_t(s, end_quote, opt4_to_type<0, 0, 0, 0>());
                case 1:  return strconv_attribute_t(s, end_quote, opt4_to_type<0, 0, 0, 1>());
                case 2:  return strconv_attribute_t(s, end_quote, opt4_to_type<0, 0, 1, 0>());
                case 3:  return strconv_attribute_t(s, end_quote, opt4_to_type<0, 0, 1, 1>());
                case 4:  return strconv_attribute_t(s, end_quote, opt4_to_type<0, 1, 0, 0>());
                case 5:  return strconv_attribute_t(s, end_quote, opt4_to_type<0, 1, 0, 1>());
                case 6:  return strconv_attribute_t(s, end_quote, opt4_to_type<0, 1, 1, 0>());
                case 7:  return strconv_attribute_t(s, end_quote, opt4_to_type<0, 1, 1, 1>());
                case 8:  return strconv_attribute_t(s, end_quote, opt4_to_type<1, 0, 0, 0>());
                case 9:  return strconv_attribute_t(s, end_quote, opt4_to_type<1, 0, 0, 1>());
                case 10: return strconv_attribute_t(s, end_quote, opt4_to_type<1, 0, 1, 0>());
                case 11: return strconv_attribute_t(s, end_quote, opt4_to_type<1, 0, 1, 1>());
                case 12: return strconv_attribute_t(s, end_quote, opt4_to_type<1, 1, 0, 0>());
                case 13: return strconv_attribute_t(s, end_quote, opt4_to_type<1, 1, 0, 1>());
                case 14: return strconv_attribute_t(s, end_quote, opt4_to_type<1, 1, 1, 0>());
                case 15: return strconv_attribute_t(s, end_quote, opt4_to_type<1, 1, 1, 1>());
                default: return 0; // should not get here
        }
}

xml_allocator::xml_allocator()
{
        m_root = new xml_mem_block();
        m_root->m_data=new char[c_memory_block_size];
}

xml_allocator::~xml_allocator()
{
        delete m_root->m_data;
        delete m_root;
}

void* xml_allocator::alloc(unsigned int size)
{
        //Âûðàâíèâàíèå ïî 4ì áàéòàì. Òîëüêî äëÿ NDS.
        //size=(size+3)&~3;

        if(size<0||size>c_memory_block_size)
        {
                return 0;
        }
        if(m_root->m_size+size<=c_memory_block_size)
        {
                void* buf=m_root->m_data+m_root->m_size;
                m_root->m_size+=size;
                return buf;
        }
        else
        {
                m_root->m_next = new xml_mem_block();
                m_root->m_next->m_data=new char[c_memory_block_size];
                xml_mem_block* tmp = m_root;
                m_root=m_root->m_next;
                m_root->m_size=size;
                m_root->m_prev = tmp;
                return m_root->m_data;
        }
}

void xml_allocator::free()
{
        while(m_root->m_prev)
        {
                m_root=m_root->m_prev;
        }
        xml_mem_block* current=m_root->m_next;
        while(current)
        {
                xml_mem_block* next=current->m_next;
                delete current->m_data;
                delete current;
                current=next;
        }
        m_root->m_next=0;
        m_root->m_size=0;
}

xml_attribute::xml_attribute()
{
        m_name=0;
        m_value=0;
        m_prev=0;
        m_next=0;
}

xml_attribute::~xml_attribute()
{
        
}

void xml_attribute::destroy()
{
        m_name=0;
        m_value=0;
        m_prev=0;
        m_next=0;
}

xml_attribute* xml_attribute::next() const
{
        return m_next;
}

xml_attribute* xml_attribute::prev() const
{
        return m_prev;
}

bool xml_attribute::empty() const
{
        return (m_value==0||m_name==0);
}

const char* xml_attribute::name() const
{
        return m_name?m_name:"";
}

const char* xml_attribute::value() const
{
        return m_value?m_value:"";
}

xml_node::xml_node(xml_node_type type)
{
        m_type=type;
        m_parent=0;
        m_name=0;
        m_value=0;
        m_first=0;
        m_last=0;
        m_prev=0;
        m_next=0;
        m_first_attr=0;
        m_last_attr=0;
        m_num_child=0;
        m_num_attr=0;
}

xml_node::~xml_node()
{
        
}

void xml_node::destroy()
{
        for(xml_attribute* attr=m_first_attr;attr;attr=attr->m_next)
                attr->destroy();
        for(xml_node* node=m_first;node;node=node->m_next)
                node->destroy();

        m_parent=0;
        m_name=0;
        m_value=0;
        m_first=0;
        m_last=0;
        m_prev=0;
        m_next=0;
        m_first_attr=0;
        m_last_attr=0;
        m_num_child=0;
        m_num_attr=0;
}

xml_node* xml_node::append(xml_node_type type)
{
        xml_node* child = new(get_allocator().alloc(sizeof(xml_node))) xml_node(type);
        
        child->m_parent = this;
        
        if(m_last)
        {
                m_last->m_next = child;
                child->m_prev = m_last;
                m_last = child;
        }
        else 
                m_first = m_last = child;

        m_num_child++;
        return child;
}

xml_attribute* xml_node::append_attr()
{
        xml_attribute* a = new(get_allocator().alloc(sizeof(xml_attribute))) xml_attribute();
        if(m_last_attr)
        {
                m_last_attr->m_next = a;
                a->m_prev = m_last_attr;
                m_last_attr = a;
        }
        else 
                m_first_attr = m_last_attr = a;
        m_num_attr++;
        return a;
}

bool xml_node::empty() const
{
        return (m_name==0);
}

const char* xml_node::name() const
{
        return m_name?m_name:"";
}

xml_node_type xml_node::type() const
{
        return m_type;
}

const char* xml_node::value() const
{
        return m_value?m_value:"";
}

xml_node& xml_node::operator[](const char* name) const
{
        if(m_num_child==0)
                return *((xml_node*)this);
        for(xml_node* i=m_first;i;i=i->m_next)
                if (i->m_name&&!strcmp(name,i->m_name)) 
                        return *i;
        return *((xml_node*)this);
}

xml_node& xml_node::operator[](unsigned int num) const
{
        if(m_num_child==0)
                return *((xml_node*)this);
        unsigned int cntr=0;
        xml_node* i;
        if(num>=0&&num<m_num_child)
        {
                for(i=m_first;cntr!=num;i=i->m_next)
                {
                        if(!i)
                        {
                                return *((xml_node*)this);
                        }
                        cntr++;
                }
                return *i;
        }
        return *((xml_node*)this);
}

bool xml_node::check_attr(const char* name) const
{
        if(m_num_attr==0)
                return false;
        for(xml_attribute* i=m_first_attr;i;i=i->m_next)
                if(i->m_name&&!strcmp(name,i->m_name))
                        return true;
        return false;
}

bool xml_node::check_child(const char* name) const
{
        if(m_num_child==0)
                return false;
        for(xml_node* i=m_first;i;i=i->m_next)
                if(i->m_name&&!strcmp(name,i->m_name)) 
                        return true;
        return false;
}

xml_attribute& xml_node::attr(const char* name) const
{
        if(m_num_attr==0)
        {
                return *((xml_attribute*)m_first_attr);
        }
        for(xml_attribute* i=m_first_attr;i;i=i->m_next)
                if (i->m_name&&!strcmp(name,i->m_name)) 
                        return *i;
        return *((xml_attribute*)m_first_attr);
}

xml_attribute& xml_node::attr(unsigned int num) const
{
        if(m_num_attr==0)
        {
                return *((xml_attribute*)m_first_attr);
        }
        unsigned int cntr=0;
        xml_attribute* i;
        if(num>=0&&num<m_num_attr)
        {
                for(i=m_first_attr;cntr!=num;i=i->m_next)
                {
                        if(!i)
                        {
                                return *((xml_attribute*)m_first_attr);
                        }
                        cntr++;
                }
                return *i;
        }
        return *((xml_attribute*)m_first_attr);
}

char* xml_node::attr_str(const char* name,const char* _default) const
{
        if(m_num_attr==0)
                return (char*)_default;
        for(xml_attribute* i=m_first_attr;i;i=i->m_next)
                if (i->m_name&&!strcmp(name,i->m_name))
                        return i->m_value;
        return (char*)_default;
}

int xml_node::attr_int(const char* name,int _default) const
{
        if(m_num_attr==0)
                return _default;
        for(xml_attribute* i=m_first_attr;i;i=i->m_next)
                if (i->m_name&&!strcmp(name,i->m_name))
                        return atoi(i->m_value);
        return _default;
}

bool xml_node::attr_bool(const char* name,bool _default) const
{
        if(m_num_attr==0)
                return _default;
        for(xml_attribute* i=m_first_attr;i;i=i->m_next)
                if (i->m_name&&!strcmp(name,i->m_name))
                {
                        return // Only look at first char:
                                (*(i->m_value)=='1'||
                                 *(i->m_value)=='t'||
                                 *(i->m_value)=='T'||
                                 *(i->m_value)=='y'||
                                 *(i->m_value)=='Y')?true:false;
                }
        return _default;
}

float xml_node::attr_float(const char* name, float _default) const
{
        if(m_num_attr==0)
                return _default;
        for(xml_attribute* i=m_first_attr;i;i=i->m_next)
                if (i->m_name&&!strcmp(name,i->m_name))
                        return (float)atof(i->m_value);
        return _default;
}

unsigned int xml_node::child_count() const
{
        return m_num_child;
}

unsigned int xml_node::attr_count() const
{
        return m_num_attr;
}

xml_node* xml_node::next(const char* name) const
{
        for(xml_node* i=m_next;i;i=i->m_next)
                if(i->m_name&&!strcmp(name,i->m_name)) 
                        return i;
        return 0;
}

xml_node* xml_node::next() const
{
        return m_next;
}

xml_node* xml_node::prev(const char* name) const
{
        for(xml_node* i=m_prev;i;i=i->m_prev)
                if(i->m_name&&!strcmp(name,i->m_name)) 
                        return i;
        return 0;
}

xml_node* xml_node::prev() const
{
        return m_prev;
}

xml_node* xml_node::parent() const
{
        return m_parent;
}

xml_node* xml_node::root() const
{
        xml_node* r = (xml_node*)this;
        while(r&&r->m_parent) 
                r=r->parent();
        return r;
}

xml_attribute& xml_node::first_attr() const
{
        return *m_first_attr;
}

xml_attribute& xml_node::last_attr() const
{
        return *m_last_attr;
}

xml_node& xml_node::first() const
{
        return *m_first;
}

xml_node& xml_node::last() const
{
        return *m_last;
}

xml_allocator& xml_node::get_allocator() const
{
        xml_node* r = root();
        return static_cast<xml_document*>(r)->m_allocator;
}

xml_document::xml_document():xml_node(node_document)
{

}
xml_document::~xml_document()
{
        m_allocator.free();
}

void xml_document::destroy()
{
        xml_node::destroy();
        m_allocator.free();
}

bool xml_document::parse_file(const char* name,unsigned int options)
{
        destroy();

        unsigned int rd,len=0;
        file _file;
        bool ret;
        
        if(!_file.open(name))
        {
                return false;
        }

        len=_file.size();
        m_buffer=(char*)m_allocator.alloc(len+1);
        rd=_file.read(m_buffer,len);

        if(rd!=len)
        {
                destroy();
                _file.close();
                return false;
        }

        m_buffer[len]=0;

        ret=parse(m_buffer,options);

        _file.close();
        return ret;
}

bool xml_document::parse(char* s,unsigned int optmsk)
{
#define SKIPWS()                        { while (is_chartype(*s, ct_space)) ++s; }
#define OPTSET(OPT)                     ( optmsk & OPT )
#define PUSHNODE(TYPE)          { cursor=cursor->append(TYPE);}
#define POPNODE()                       { cursor = cursor->m_parent; }
#define SCANFOR(X)                      { while (*s != 0 && !(X)) ++s; }
#define SCANWHILE(X)            { while ((X)) ++s; }
#define ENDSEG()                        { ch = *s; *s = 0; ++s; }
#define CHECK_ERROR()           { if (*s == 0){return false;}}
        
        if(!s)
        {
                return false;
        }

        // UTF-8 BOM
        if((unsigned char)*s == 0xEF && (unsigned char)*(s+1) == 0xBB && (unsigned char)*(s+2) == 0xBF)
                s += 3;

        char ch = 0;
        xml_node* cursor = this;
        char* mark = s;

        while (*s != 0)
        {
                if (*s == '<')
                {
                        ++s;
LOC_TAG:
                        if (*s == '?') // '<?...'
                        {
                                ++s;

                                if (!is_chartype(*s, ct_start_symbol)) // bad PI
                                {
                                        return false;
                                }
                                else if (OPTSET(c_parse_pi))
                                {
                                        mark = s;
                                        SCANWHILE(is_chartype(*s, ct_symbol)); // Read PI target
                                        CHECK_ERROR();
                                        if (!is_chartype(*s, ct_space) && *s != '?') // Target has to end with space or ?
                                        {
                                                return false;
                                        }
                                        ENDSEG();
                                        CHECK_ERROR();
                                        if (ch == '?') // nothing except target present
                                        {
                                                if (*s != '>')
                                                {
                                                        return false;
                                                }
                                                ++s;
                                                // stricmp / strcasecmp is not portable
                                                if ((mark[0] == 'x' || mark[0] == 'X') && (mark[1] == 'm' || mark[1] == 'M')
                                                        && (mark[2] == 'l' || mark[2] == 'L') && mark[3] == 0)
                                                {
                                                }
                                                else
                                                {
                                                        PUSHNODE(node_pi); // Append a new node on the tree.
                                                        cursor->m_name = mark;
                                                        POPNODE();
                                                }
                                        }
                                        // stricmp / strcasecmp is not portable
                                        else if ((mark[0] == 'x' || mark[0] == 'X') && (mark[1] == 'm' || mark[1] == 'M')
                                                && (mark[2] == 'l' || mark[2] == 'L') && mark[3] == 0)
                                        {
                                                SCANFOR(*s == '?' && *(s+1) == '>'); // Look for '?>'.
                                                CHECK_ERROR();
                                                s += 2;
                                        }
                                        else
                                        {
                                                PUSHNODE(node_pi); // Append a new node on the tree.
                                                cursor->m_name = mark;
                                                if (is_chartype(ch, ct_space))
                                                {
                                                        SKIPWS();
                                                        CHECK_ERROR();
                                                        mark = s;
                                                }
                                                else mark = 0;
                                                SCANFOR(*s == '?' && *(s+1) == '>'); // Look for '?>'.
                                                CHECK_ERROR();
                                                ENDSEG();
                                                CHECK_ERROR();
                                                ++s; // Step over >
                                                cursor->m_value = mark;
                                                POPNODE();
                                        }
                                }
                                else // not parsing PI
                                {
                                        SCANFOR(*s == '?' && *(s+1) == '>'); // Look for '?>'.
                                        CHECK_ERROR();
                                        s += 2;
                                }
                        }
                        else if (*s == '!') // '<!...'
                        {
                                ++s;
                                if (*s == '-') // '<!-...'
                                {
                                        ++s;
                                        if (*s == '-') // '<!--...'
                                        {
                                                ++s;

                                                if (OPTSET(c_parse_comments))
                                                {
                                                        PUSHNODE(node_comment); // Append a new node on the tree.
                                                        cursor->m_value = s; // Save the offset.
                                                }
                                                if (OPTSET(c_parse_eol) && OPTSET(c_parse_comments))
                                                {
                                                        s = strconv_comment(s);

                                                        if (!s) 
                                                        {
                                                                return false;
                                                        }
                                                }
                                                else
                                                {
                                                        // Scan for terminating '-->'.
                                                        SCANFOR(*s == '-' && *(s+1) == '-' && *(s+2) == '>');
                                                        CHECK_ERROR();

                                                        if (OPTSET(c_parse_comments))
                                                                *s = 0; // Zero-terminate this segment at the first terminating '-'.

                                                        s += 3; // Step over the '\0->'.
                                                }

                                                if (OPTSET(c_parse_comments))
                                                {
                                                        POPNODE(); // Pop since this is a standalone.
                                                }
                                        }
                                        else 
                                        {
                                                return false;
                                        }
                                }
                                else if(*s == '[')
                                {
                                        // '<![CDATA[...'
                                        if(*++s=='C' && *++s=='D' && *++s=='A' && *++s=='T' && *++s=='A' && *++s == '[')
                                        {
                                                ++s;

                                                if (OPTSET(c_parse_cdata))
                                                {
                                                        PUSHNODE(node_cdata); // Append a new node on the tree.
                                                        cursor->m_value = s; // Save the offset.
                                                        if (OPTSET(c_parse_eol))
                                                        {
                                                                s = strconv_cdata(s);

                                                                if (!s) 
                                                                {
                                                                        return false;
                                                                }
                                                        }
                                                        else
                                                        {
                                                                // Scan for terminating ']]>'.
                                                                SCANFOR(*s == ']' && *(s+1) == ']' && *(s+2) == '>');
                                                                CHECK_ERROR();
                                                                ENDSEG(); // Zero-terminate this segment.
                                                                CHECK_ERROR();
                                                        }
                                                        POPNODE(); // Pop since this is a standalone.
                                                }
                                                else // Flagged for discard, but we still have to scan for the terminator.
                                                {
                                                        // Scan for terminating ']]>'.
                                                        SCANFOR(*s == ']' && *(s+1) == ']' && *(s+2) == '>');
                                                        CHECK_ERROR();
                                                        ++s;
                                                }

                                                s += 2; // Step over the last ']>'.
                                        }
                                        else 
                                        {
                                                return false;
                                        }
                                }
                                else if (*s=='D' && *++s=='O' && *++s=='C' && *++s=='T' && *++s=='Y' && *++s=='P' && *++s=='E')
                                {
                                        ++s;
                                        SKIPWS(); // Eat any whitespace.
                                        CHECK_ERROR();
LOC_DOCTYPE:
                                        SCANFOR(*s == '\'' || *s == '"' || *s == '[' || *s == '>');
                                        CHECK_ERROR();
                                        if (*s == '\'' || *s == '"') // '...SYSTEM "..."
                                        {
                                                ch = *s++;
                                                SCANFOR(*s == ch);
                                                CHECK_ERROR();
                                                ++s;
                                                goto LOC_DOCTYPE;
                                        }
                                        if(*s == '[') // '...[...'
                                        {
                                                ++s;
                                                unsigned int bd = 1; // Bracket depth counter.
                                                while (*s!=0) // Loop till we're out of all brackets.
                                                {
                                                        if (*s == ']') --bd;
                                                        else if (*s == '[') ++bd;
                                                        if (bd == 0) break;
                                                        ++s;
                                                }
                                        }

                                        SCANFOR(*s == '>');
                                        CHECK_ERROR();
                                        ++s;
                                }
                                else 
                                {
                                        return false;
                                }
                        }
                        else if (is_chartype(*s, ct_start_symbol)) // '<#...'
                        {
                                PUSHNODE(node_element); // Append a new node to the tree.
                                cursor->m_name = s;
                                SCANWHILE(is_chartype(*s, ct_symbol)); // Scan for a terminator.
                                CHECK_ERROR();
                                ENDSEG(); // Save char in 'ch', terminate & step over.
                                CHECK_ERROR();
                                if (ch == '/') // '<#.../'
                                {
                                        if(*s != '>')
                                        {
                                                return false;
                                        }
                                        POPNODE(); // Pop.
                                        ++s;
                                }
                                else if (ch == '>')
                                {
                                        // end of tag
                                }
                                else if (is_chartype(ch, ct_space))
                                {
                                        while (*s)
                                        {
                                                SKIPWS(); // Eat any whitespace.
                                                CHECK_ERROR();

                                                if (is_chartype(*s, ct_start_symbol)) // <... #...
                                                {
                                                        xml_attribute* a = cursor->append_attr(); // Make space for this attribute.
                                                        a->m_name = s; // Save the offset.
                                                        SCANWHILE(is_chartype(*s, ct_symbol)); // Scan for a terminator.
                                                        CHECK_ERROR();
                                                        ENDSEG(); // Save char in 'ch', terminate & step over.
                                                        CHECK_ERROR();
                                                        if (is_chartype(ch, ct_space))
                                                        {
                                                                SKIPWS(); // Eat any whitespace.
                                                                CHECK_ERROR();
                                                                ch = *s;
                                                                ++s;
                                                        }

                                                        if (ch == '=') // '<... #=...'
                                                        {
                                                                SKIPWS(); // Eat any whitespace.
                                                                CHECK_ERROR();
                                                                if (*s == '\'' || *s == '"') // '<... #="...'
                                                                {
                                                                        ch = *s; // Save quote char to avoid breaking on "''" -or- '""'.
                                                                        ++s; // Step over the quote.
                                                                        a->m_value = s; // Save the offset.
                                                                        s = strconv_attribute(s, ch, optmsk);

                                                                        if(!s)
                                                                        {
                                                                                return false;
                                                                        }
                                                                        // After this line the loop continues from the start;
                                                                        // Whitespaces, / and > are ok, symbols are wrong,
                                                                        // everything else will be detected
                                                                        if(is_chartype(*s,ct_start_symbol)) 
                                                                        {
                                                                                return false;
                                                                        }
                                                                }
                                                                else 
                                                                {
                                                                        return false;
                                                                }
                                                        }
                                                        else 
                                                        {
                                                                return false;
                                                        }
                                                }
                                                else if (*s == '/')
                                                {
                                                        ++s;
                                                        if (*s != '>')
                                                        {
                                                                return false;
                                                        }
                                                        POPNODE(); // Pop.
                                                        ++s;
                                                        break;
                                                }
                                                else if (*s == '>')
                                                {
                                                        ++s;
                                                        break;
                                                }
                                                else 
                                                {
                                                        return false;
                                                }
                                        }
                                }
                                else
                                {
                                        return false;
                                }
                        }
                        else if (*s == '/')
                        {
                                ++s;
                                if (!cursor)
                                {
                                        return false;
                                }
                                char* name=cursor->m_name;
                                if(!name)
                                {
                                        return false;
                                }

                                while(*s&&is_chartype(*s,ct_symbol))
                                {
                                        if(*s++!=*name++)
                                        {
                                                return false;
                                        }
                                }

                                if(*name)
                                {
                                        return false;
                                }

                                POPNODE(); // Pop.
                                SKIPWS();
                                CHECK_ERROR();

                                if (*s != '>')
                                {
                                        return false;
                                }
                                ++s;
                        }
                        else
                        {
                                return false;
                        }
                }
                else
                {
                        mark = s; // Save this offset while searching for a terminator.
                        SKIPWS(); // Eat whitespace if no genuine PCDATA here.
                        if ((mark == s || !OPTSET(c_parse_ws_pcdata)) && (!*s || *s == '<'))
                        {
                                continue;
                        }
                        s = mark;

                        if(cursor->m_type!= node_document)
                        {
                                PUSHNODE(node_pcdata); // Append a new node on the tree.
                                cursor->m_value = s; // Save the offset.
                                s = strconv_pcdata(s, optmsk);

                                if(!s)
                                {
                                        return false;
                                }

                                POPNODE(); // Pop since this is a standalone.

                                if (!*s) break;
                        }
                        else
                        {
                                SCANFOR(*s == '<'); // '...<'
                                if (!*s) break;

                                ++s;
                        }
                        // We're after '<'
                        goto LOC_TAG;
                }
        }
        if(cursor!=this)
        {
                return false;
        }
        return true;
}
