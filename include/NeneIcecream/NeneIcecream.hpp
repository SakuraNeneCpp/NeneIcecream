#pragma once
#include <iostream>
#include <typeinfo>
#include <utility>

namespace dbg_detail {

constexpr const char* basename(const char* path) noexcept {
    const char* last = path;
    for (const char* p = path; *p; ++p) {
        if (*p == '/' || *p == '\\') { last = p + 1; }
    }
    return last;
}


// yes/no テスト用
template<class...> using void_t = void;

// デフォルト false
template<class T, class = void>
struct is_streamable : std::false_type {};

// os << std::declval<const T&>() が有効なら true
template<class T>
struct is_streamable<T, void_t<
    decltype( std::declval<std::ostream&>() << std::declval<const T&>() )
>> : std::true_type {};

template<class T>
inline constexpr bool is_streamable_v = is_streamable<T>::value;

} // namespace dbg_detail

namespace dbg {


inline std::ostream*& out_stream() {
    static std::ostream* s = &std::cout;
    return s;
}
inline void set_stream(std::ostream& os) { out_stream() = &os; }

template<class T>
void print_value(std::ostream& os, T&& v) {
    if (dbg_detail::is_streamable_v<T>) {
        os << v;
    } else {
        os << "<" << typeid(T).name() << ">";
    }
}

template<class T>
T&& ic_impl(const char* expr_str, const char* file, int line, T&& value) {
    std::ostream& os = *out_stream();
    os
    << "ic [" << file << ":" << line << "] "
    << expr_str << " = ";
    print_value(os, value);
    os << '\n';
    return std::forward<T>(value);
}

void ic_section_impl(const char* title){
    std::cout << "# " << title << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

} // namespace dbg

#define ic(expr) ::dbg::ic_impl(#expr, ::dbg_detail::basename(__FILE__), __LINE__, (expr))
#define ic_section(title) ::dbg::ic_section_impl(title)