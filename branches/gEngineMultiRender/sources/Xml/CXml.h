#ifndef _XML_H_
#define _XML_H_

#include <string.h>

enum xml_node_type
{
        node_null,
        node_document,
        node_element,
        node_rootelement,
        node_pcdata,
        node_cdata,
        node_comment,
        node_pi
};

const size_t       c_memory_block_size          = 1048576;
const unsigned int                  c_parse_minimal                      = 0x0000;
const unsigned int                   c_parse_pi                           = 0x0001;
const unsigned int                   c_parse_comments                     = 0x0002;
const unsigned int                   c_parse_cdata                        = 0x0004;
const unsigned int                   c_parse_ws_pcdata            = 0x0008;
const unsigned int                   c_parse_escapes                      = 0x0010;
const unsigned int                   c_parse_eol                          = 0x0020;
const unsigned int                   c_parse_wnorm_attribute      = 0x0040;
const unsigned int                   c_parse_wconv_attribute      = 0x0080;
const unsigned int                   c_parse_default                      = c_parse_cdata|c_parse_escapes|c_parse_wconv_attribute|c_parse_eol;
const unsigned int                   c_format_indent                      = 0x01;
const unsigned int                   c_format_utf8                        = 0x02;
const unsigned int                   c_format_write_bom           = 0x04;
const unsigned int                   c_format_raw                         = 0x08;
const unsigned int                   c_format_default                     = c_format_indent|c_format_utf8;

struct xml_mem_block
{
        xml_mem_block()
        {
                m_next=0;
                m_prev=0;
                m_size=0;
                m_data=0;
        }
        xml_mem_block* m_next;
        xml_mem_block* m_prev;
        unsigned int                        m_size;
        char*             m_data;
};

class xml_allocator
{
public:
        xml_allocator();
        ~xml_allocator();

        void* alloc(unsigned int  size);
        void free();
private:
        xml_mem_block* m_root;
};

class xml_node;
        
class xml_attribute
{
        friend class xml_node;
        friend class xml_document;
public:
        xml_attribute();
        ~xml_attribute();

        void                    destroy();
		xml_attribute*      next() const;
        xml_attribute*  prev() const;
        bool                    empty() const;
        const char*             name() const;
        const char*             value() const;
private:
        xml_attribute* m_next;
        xml_attribute* m_prev;
        char*              m_name;
        char*              m_value;
};

class xml_node
{
        friend class xml_document;
public:
                         xml_node(xml_node_type type=node_element);
        virtual ~xml_node();

        void               destroy();
        bool               empty() const;
        xml_node_type  type() const;
        const char*        name() const;
        const char*    value() const;
        unsigned int                         child_count() const;
        unsigned int                         attr_count() const;
        xml_node&          operator[](const char* name) const;
        xml_node&          operator[](unsigned int  num) const;
        xml_node*          child(const char* name) const;
        bool               check_attr(const char* name) const;
        bool               check_child(const char* name) const;
        char*              attr_str(const char* name,const char* _default="") const;
        int                        attr_int(const char* name,int _default=0) const;
        bool               attr_bool(const char* name,bool _default=false) const;
        float              attr_float(const char* name, float _default=0) const;
        xml_attribute& attr(const char* name) const;
        xml_attribute& attr(unsigned int  num) const;
        xml_node*          next(const char* name) const;
        xml_node*          next() const;
        xml_node*          prev(const char* name) const;
        xml_node*          prev() const;
        xml_node*          parent() const;
        xml_node*          root() const;
        xml_attribute& first_attr() const;
    xml_attribute& last_attr() const;
        xml_node&          first() const;
    xml_node&      last() const;
protected:
        xml_allocator& get_allocator() const;
private:
        xml_node*               append(xml_node_type type = node_element);
        xml_attribute*  append_attr();

        xml_node_type   m_type;
        unsigned int                              m_num_child;
        unsigned int                              m_num_attr;

        char*                   m_name;
        char*                   m_value;

        xml_node*               m_first;
        xml_node*               m_last;
        xml_node*               m_parent;
        xml_node*               m_prev;
        xml_node*               m_next;

        xml_attribute*  m_first_attr;
        xml_attribute*  m_last_attr;
};

class xml_document: public xml_node
{
        friend class xml_node;
public:
        xml_document();
        ~xml_document();

        void destroy();

        bool parse_file(const char* name,unsigned int  options=c_parse_default);
        bool parse(char* s,unsigned int  optmsk=c_parse_default);
private:
        char*             m_buffer;
        xml_allocator m_allocator;
};

#endif
