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

#include_directories(${CMAKE_SOURCE_DIR}/main)
link_directories(${CMAKE_SOURCE_DIR}/freeglut/lib/x64)
link_directories(${CMAKE_SOURCE_DIR}/freeglut/bin/x64)

# Добавьте источник в исполняемый файл этого проекта.
# add_executable (Easyplot "easy_plot.hpp" "Source.cpp")
add_executable (Easyplot "easy_plot.hpp" "Source1.cpp")
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/freeglut/bin/x64/freeglut.dll"
        "${CMAKE_SOURCE_DIR}/out/build/x64-debug" 
)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Easyplot PROPERTY CXX_STANDARD 20)
endif()

add_custom_target(
  cppcheck
  COMMAND cppcheck --enable=all --std=c++20 ${CMAKE_SOURCE_DIR}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

