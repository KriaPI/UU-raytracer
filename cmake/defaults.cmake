# This is needed by tools such as clang-tidy.
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

macro(apply_cxx_compiler_flags target_to_apply_to)
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        target_compile_options(${target_to_apply_to} PRIVATE
            /W4 /w14640 /permissive-
        )
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target_to_apply_to} PRIVATE
            -Wall -Wno-deprecated-declarations -Wno-template-body -Wno-unused-but-set-variable -Wno-class-memaccess -Wno-sign-compare
        )
    endif()
endmacro()