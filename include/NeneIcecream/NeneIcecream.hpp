#pragma once
#include <iostream>
#include <typeinfo>
#include <utility>

#ifndef NENEICECREAM_ROOT
#define NENEICECREAM_ROOT ""
#endif

namespace dbg_detail {

inline const char* shorten_path(const char* path) {
    constexpr auto root = NENEICECREAM_ROOT;
    constexpr std::size_t root_len = sizeof(root) - 1;
    // コンパイル時定数 root と path を比較（実行時）
    const char* p = path;
    const char* r = root;
    while (*p && *r && *p == *r) {
        ++p; ++r;
    }
    return (*r == '\0') ? p : path; // 途中で違ったら元のフルパス
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
    const char* short_file =
    #ifdef _MSC_VER
        __FILE_NAME__; // ただしここで file は無視なので注意
    #else
        dbg_detail::shorten_path(file);
    #endif
    os << "[" << short_file << ":" << line << "] "
       << expr_str << " = ";
    print_value(os, value);
    os << '\n';
    return std::forward<T>(value);
}

} // namespace dbg

#ifdef _MSC_VER
  #define NENE_IC(expr) ::dbg::ic_impl(#expr, __FILE__, __LINE__, (expr))
#else
  #define NENE_IC(expr) ::dbg::ic_impl(#expr, __FILE__, __LINE__, (expr))
#endif