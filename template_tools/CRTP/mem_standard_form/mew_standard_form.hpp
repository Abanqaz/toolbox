#ifndef _TOOLBOX_CRTP_MEM_STANDARD_FORM_
#define _TOOLBOX_CRTP_MEM_STANDARD_FORM_
#include <new>
class MemStandardForm {
 public:
    // normal form
    static void* operator new(std::size_t size) throw(std::bad_alloc) { return ::operator new(size); }
    static void operator delete(void* pMemory) throw() { return ::operator delete(pMemory); }
    // placement form (void*)
    static void* operator new(std::size_t size, void* ptr) throw() { return ::operator new(size, ptr); }
    static void operator delete(void* pMemory, void* ptr) throw() { return ::operator delete(pMemory, ptr); }
    // no throw
    static void* operator new(std::size_t size, std::nothrow_t& nt) throw() { return ::operator new(size, nt); }
    static void operator delete(void* pMemory, std::nothrow_t&) throw() { return ::operator delete(pMemory); }
};

//example:
class User : public MemStandardForm {
    using MemStandardForm::operator new;
    using MemStandardForm::operator delete;
    // ... customized new delete:
    static void* operator new(std::size_t size, int not_useful) throw(std::bad_alloc);
    static void operator delete(void* pMemory, int not_useful) throw();
    // ...
};

//follow up
//using template to able traits
#endif //_TOOLBOX_CRTP_MEM_STANDARD_FORM_