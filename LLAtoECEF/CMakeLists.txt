cmake_minimum_required (VERSION 2.6)

project(LLAtoECEF)

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

include_directories(${GLIB_INCLUDE_DIRS})
include_directories(${JSONCPP_INCLUDE_DIRS})

link_directories(${GLIB_LIBRARY_DIRS})
link_directories(${JSONCPP_LIBRARY_DIRS})

set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set (CMAKE_CXX_FLAGS "-fPIC")

add_executable(LLAtoECEF LLAtoECEF.cpp WriterMemoryClass.cpp SolrRequestClass.cpp LLASolrClass.cpp LLACSVClass.cpp LLAClass.cpp LLAUtility.cpp)


add_definitions(${GLIB_CFLAGS_OTHER})
add_definitions(${JSONCPP_CFLAGS_OTHER})

target_link_libraries(LLAtoECEF ${CURLPP_LDFLAGS})
target_link_libraries(LLAtoECEF ${JSONCPP_LDFLAGS})



