cmake_minimum_required(VERSION 3.15)  # FetchContent使うなら3.14+くらい
project(NeneIcecream VERSION 0.1.0 LANGUAGES CXX)

# ヘッダオンリーターゲット
add_library(NeneIcecream INTERFACE)

# ヘッダ検索パス（ビルド時）
target_include_directories(NeneIcecream
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>  # インストール後の相対パス
)

# C++標準（利用側に要求）
target_compile_features(NeneIcecream INTERFACE cxx_std_17)  # 17でOK

# 名前空間エイリアス（推奨）※ 便利にするための IMPORTED エイリアス
add_library(NeneIcecream::NeneIcecream ALIAS NeneIcecream)

# ===== インストール設定 =====
include(GNUInstallDirs)

install(
    TARGETS NeneIcecream
    EXPORT NeneIcecreamTargets
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# パッケージ構成ファイル生成 (Config + Version)
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/NeneIcecreamConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/NeneIcecreamConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/NeneIcecreamConfig.cmake"
    @ONLY
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/NeneIcecreamConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/NeneIcecreamConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NeneIcecream
)

install(
    EXPORT NeneIcecreamTargets
    NAMESPACE NeneIcecream::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NeneIcecream
)
