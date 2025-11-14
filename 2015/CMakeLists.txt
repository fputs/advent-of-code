cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(advent C)

add_subdirectory(lib/libflint)

file(GLOB SRC src/*.c)

file(COPY input DESTINATION ${CMAKE_BINARY_DIR})

add_executable(advent ${SRC})

set(INCLUDES
	include
	lib/libflint/include
)

if ((${CMAKE_SYSTEM_NAME} STREQUAL "OpenBSD"))
	find_package(PCRE2 REQUIRED)
	find_package(OpenSSL REQUIRED)
	target_include_directories(advent PRIVATE ${INCLUDES} ${PCRE2_INCLUDE_DIR})
	target_link_libraries(advent PRIVATE flint ${PCRE2_LIBRARIES})
elseif ((${CMAKE_SYSTEM_NAME} STREQUAL "Linux"))
	find_package(OpenSSL REQUIRED)
	target_include_directories(advent PRIVATE ${INCLUDES} ${OpenSSL_INCLUDE_DIR})
	target_link_libraries(advent PRIVATE bsd flint pcre2-8 ${OPENSSL_LIBRARIES})
elseif ((${CMAKE_SYSTEM_NAME} STREQUAL "Darwin"))
	# OpenSSL
	set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)
	set(OpenSSL_INCLUDE_DIR /opt/homebrew/opt/openssl@3/include)
	find_package(OpenSSL REQUIRED)

	# PCRE2
	set(PCRE2_INCLUDE_DIR /opt/homebrew/opt/pcre2/include)
	set(PCRE2_LIBRARIES /opt/homebrew/opt/pcre2/lib/libpcre2-8.dylib)

	target_include_directories(advent PRIVATE ${INCLUDES} ${OpenSSL_INCLUDE_DIR} ${PCRE2_INCLUDE_DIR})
	target_link_libraries(advent PRIVATE flint ${OPENSSL_LIBRARIES} ${PCRE2_LIBRARIES})
else()
  message(FATAL_ERROR "OS ${CMAKE_SYSTEM_NAME} is not supported" )
endif()
