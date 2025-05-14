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
if(MSVC)
    message("MSVC link")
	link_directories(${CMAKE_SOURCE_DIR}/freeglut-msvc/lib/x64)
	link_directories(${CMAKE_SOURCE_DIR}/freeglut-msvc/bin/x64)
endif()

if(MINGW)
    message("MINGW link")
	link_directories(${CMAKE_SOURCE_DIR}/freeglut-mingw/lib/x64)
	link_directories(${CMAKE_SOURCE_DIR}/freeglut-mingw/bin/x64)
endif()


# Добавьте источник в исполняемый файл этого проекта.
# add_executable (Easyplot "easy_plot.hpp" "Source.cpp")
#include_directories(utility)
set(CMAKE_BUILD_TYPE "Debug")
add_executable (Easyplot "easy_plot.hpp" "main.cpp")
#target_link_libraries(Easyplot pthread)
#set(CMAKE_CXX_FLAGS "-O0 -g --coverage")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
#set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   
if(MSVC)
    message("MSVC post")
    add_custom_command(
    TARGET Easyplot
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/freeglut-msvc/bin/x64/freeglut.dll"
       $<TARGET_FILE_DIR:Easyplot>
    )
    #set_property(TARGET Easyplot APPEND PROPERTY LINK_FLAGS /DEBUG)
    #target_link_options(Easyplot PUBLIC /DEBUG)
    #set(CMAKE_CXX_FLAGS "-O0 -g --coverage")
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")
    #set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
endif()


if(MINGW)
    target_link_libraries(Easyplot freeglut)
    target_link_libraries(Easyplot opengl32)
    message("MINGW post")
    add_custom_command(
    TARGET Easyplot
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
       "${CMAKE_SOURCE_DIR}/freeglut-mingw/bin/x64/freeglut.dll"
       $<TARGET_FILE_DIR:Easyplot>
    )
endif()

# sudo apt-get install freeglut3 freeglut3-dev libglew-dev
# sudo apt-get install mesa-utils
if(UNIX)
# SET(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE)
# SET(CMAKE_C_COMPILER "/usr/bin/clang" CACHE STRING "C compiler" FORCE)
    target_link_libraries(Easyplot GL glut pthread)
    message("UNIX post")
    # set(CMAKE_CXX_FLAGS "-fpermissive")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Easyplot PROPERTY CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

add_custom_target(
  cppcheck
  COMMAND cppcheck --enable=all --std=c++20 ${CMAKE_SOURCE_DIR}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(test_memcheck
    COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --test-action memcheck
    COMMAND ${CMAKE_COMMAND} -E cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
#target_compile_options(Easyplot PRIVATE -fsanitize=fuzzer,undefined,address)
target_compile_options(Easyplot PRIVATE -coverage)
target_link_options(Easyplot PRIVATE -coverage)


# string(SUBSTRING ${TEST_TOOL} 3 - 1 EASY_PLOT_TEST_TOOL)

if(NOT ${TEST_TOOL} STREQUAL "")
message(STATUS "Enabling ${TEST_TOOL} sanitizer")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Werror -O0 -fsanitize=${TEST_TOOL} -fno-omit-frame-pointer")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -fsanitize=${TEST_TOOL}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Werror -O0 -fsanitize=${TEST_TOOL} -fno-omit-frame-pointer")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -g -Werror -O0 -fsanitize=${TEST_TOOL} -fno-omit-frame-pointer")

endif()

if("${TEST_TOOL}" STREQUAL "memory")
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIE -fsanitize-memory-track-origins")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE -fsanitize-memory-track-origins") 
endif()


#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Debug")
#list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/test)
#include (TestingScript)

add_test(Test_1, Easyplot "1")
add_test(Test_2, Easyplot "2")
add_test(Test_3, Easyplot "3")
add_test(Test_4, Easyplot "4")
add_test(Test_5, Easyplot "5")
add_test(Test_6, Easyplot "6")
add_test(Test_7, Easyplot "7")
add_test(Test_8, Easyplot "8")
