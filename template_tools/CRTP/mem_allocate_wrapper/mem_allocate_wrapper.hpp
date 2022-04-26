#ifndef _TOOLBOX_CRTP_MEM_ALLOCATE_WRAPPER_
#define _TOOLBOX_CRTP_MEM_ALLOCATE_WRAPPER_
#include <new>

class NewHandlerHolder {
 public:
    explicit NewHandlerHolder(std::new_handler current_new_handler) : handler(current_new_handler) {}
    ~NewHandlerHolder() { std::set_new_handler(handler); }
 private:
    NewHandlerHolder(const NewHandlerHolder&);
    NewHandlerHolder& operator=(const NewHandlerHolder&);
    std::new_handler handler;
};

template<typename T>
class NewHandlerSupporter {
 public:
    // set customized new handler for operator new to call when mem request can't be fulfilled
    static std::new_handler set_new_handler(std::new_handler p) throw();
    // customized new operator, replace std::new_handler with local version
    static void* operator new(std::size_t size) throw(std::bad_alloc);
    // ...
 private:
    static std::new_handler current_handler;
};

template<typename T>
std::new_handler NewHandlerSupporter<T>::set_new_handler(std::new_handler p) {
    std::new_handler old_handler = current_handler;
    current_handler = p;
    return old_handler;
}

template<typename T>
void* NewHandlerSupporter<T>::operator new(std::size_t size) throw(std::bad_alloc) {
    NewHandlerHolder new_handler_holder(std::set_new_handler(current_handler));
    return ::operator new(size);
}

template<typename T>
std::new_handler NewHandlerSupporter<T>::current_handler = 0;

//example:
class User : public NewHandlerSupporter<User> {
    // ...
};

#endif //#define _TOOLBOX_CRTP_MEM_ALLOCATE_WRAPPER_