## Functions
function(get_macros out_Macros)
    if (WIN32)
        set(EXEC_PREFIX cmd /c)
    else ()
        set(EXEC_PREFIX)
    endif ()

    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/macro.cpp" "#include <cstddef>")

    execute_process(
            COMMAND ${EXEC_PREFIX} ${CMAKE_CXX_COMPILER} -dM -E "${CMAKE_CURRENT_BINARY_DIR}/macro.cpp"
            OUTPUT_VARIABLE DEFINED_MACROS
    )

    file(REMOVE "${CMAKE_CURRENT_BINARY_DIR}/macro.cpp")

    set(${out_Macros} "${DEFINED_MACROS}" PARENT_SCOPE)
endfunction()

function(is_mingw out_IsMingw)
    get_macros(DEFINED_MACROS)
    string(FIND "${DEFINED_MACROS}" "__MING32__" POS)
    set(${out_IsMingw} (NOT (${POS} EQUAL -1)) PARENT_SCOPE)
endfunction()

function(is_libcxx out_IsLibCXX)
    get_macros(DEFINED_MACROS)
    string(FIND "${DEFINED_MACROS}" "_LIBCPP_VERSION" POS)
    set(${out_IsLivCXX} (NOT (${POS} EQUAL -1)) PARENT_SCOPE)
endfunction()

function(is_libstdcxx out_IsLibSTDCXX)
    get_macros(DEFINED_MACROS)
    string(FIND "${DEFINED_MACROS}" "__GLIBCXX__" POS)
    set(${out_IsLibSTDCXX} (NOT (${POS} EQUAL -1)) PARENT_SCOPE)
endfunction()

function(is_msvc_stl out_IsSTL)
    get_macros(DEFINED_MACROS)
    string(FIND "${DEFINED_MACROS}" "_MSC_VER" POS)
    set(${out_IsSTL} (NOT (${POS} EQUAL -1)) PARENT_SCOPE)
endfunction()
