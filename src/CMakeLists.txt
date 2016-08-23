set(TARGET_NAME hera)

get_filename_component(HERA_INCLUDE_DIR ../ ABSOLUTE)

set(SOURCES
	eei.cpp			eei.h
	hera.cpp		hera.h ${HERA_INCLUDE_DIR}/evm.h
)
source_group("" FILES ${SOURCES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fvisibility=hidden")
	if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--exclude-libs,ALL") # Do not export symbols from dependies, mostly LLVM libs
	endif()
endif()

if(EVMJIT_VERSION_MAJOR EQUAL 0)
	set(HERA_SOVERSION "0.${HERA_VERSION_MINOR}")
else()
	set(HERA_SOVERSION ${HERA_VERSION_MAJOR})
endif()

add_library(${TARGET_NAME} SHARED ${SOURCES})
set_target_properties(${TARGET_NAME} PROPERTIES
						VERSION ${HERA_VERSION} SOVERSION ${HERA_SOVERSION}
						FOLDER "libs")

target_include_directories(${TARGET_NAME} PUBLIC ${HERA_INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../binaryen/src)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen)
target_link_libraries(${TARGET_NAME} PRIVATE binaryen)

install(TARGETS ${TARGET_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
install(DIRECTORY ${HERA_INCLUDE_DIR} DESTINATION include)
