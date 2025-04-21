# CMakeList.txt: проект CMake для Easyplot; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Easyplot")
include(CTest)
enable_testing()

#include_directories(${CMAKE_SOURCE_DIR}/main)
link_directories(${CMAKE_SOURCE_DIR}/freeglut/lib/x64)
link_directories(${CMAKE_SOURCE_DIR}/freeglut/bin/x64)

# Добавьте источник в исполняемый файл этого проекта.
# add_executable (Easyplot "easy_plot.hpp" "Source.cpp")
#include_directories(utility)
set(CMAKE_BUILD_TYPE "Debug")
add_executable (Easyplot "easy_plot.hpp" "main.cpp")
if(MSVC)
    #set_property(TARGET Easyplot APPEND PROPERTY LINK_FLAGS /DEBUG)
    #target_link_options(Easyplot PUBLIC /DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
endif()
add_custom_command(
    TARGET Easyplot
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/freeglut/bin/x64/freeglut.dll"
       $<TARGET_FILE_DIR:Easyplot>
)

#add_subdirectory(utility)
#target_link_libraries(Easyplot utility)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Easyplot PROPERTY CXX_STANDARD 20)
endif()

add_custom_target(
  cppcheck
  COMMAND cppcheck --enable=all --std=c++20 ${CMAKE_SOURCE_DIR}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
#target_compile_options(Easyplot PRIVATE -fsanitize=fuzzer,undefined,address)
target_compile_options(Easyplot PRIVATE -coverage)
target_link_options(Easyplot PRIVATE -coverage)

#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Debug")

add_test(Test_1, Easyplot "1")
add_test(Test_2, Easyplot "2")
add_test(Test_3, Easyplot "3")
add_test(Test_4, Easyplot "4")
add_test(Test_5, Easyplot "5")
add_test(Test_6, Easyplot "6")
add_test(Test_7, Easyplot "7")
add_test(Test_8, Easyplot "8")
