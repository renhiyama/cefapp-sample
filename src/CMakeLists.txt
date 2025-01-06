cmake_minimum_required(VERSION 3.20)

project(cef_app)

set(CEF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../cef_binary")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")

find_package(CEF REQUIRED)
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

#
# Source files.
#

# cef-app sources.
set(CEF_APP_SRCS
  main.cpp
  main.h
  handler.cpp
  handler.h
  )
set(CEF_APP_SRCS_LINUX
  cef_linux.cpp
  handler_linux.cpp
  )

APPEND_PLATFORM_SOURCES(CEF_APP_SRCS)
source_group(cefsimple FILES ${CEF_APP_SRCS})


set(CEF_APP_SRCS
  ${CEF_APP_SRCS}
  )


APPEND_PLATFORM_SOURCES(CEF_APP_HELPER_SRCS)
source_group(cefsimple FILES ${CEF_APP_HELPER_SRCS})

#
# Shared configuration.
#

# Target executable names.
set(CEF_TARGET "cefapp")
if(OS_MAC)
  set(CEF_HELPER_TARGET "CEF_APP_Helper")
  set(CEF_HELPER_OUTPUT_NAME "cefsimple Helper")
else()
  # Logical target used to link the libcef library.
  ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")
endif()

# Determine the target output directory.
SET_CEF_TARGET_OUT_DIR()


#
# Linux configuration.
#

if(OS_LINUX)
  # Executable target.
  find_package(X11 REQUIRED)
  add_executable(${CEF_TARGET} ${CEF_APP_SRCS})
  SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})
  add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
  target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS})

  # Set rpath so that libraries can be placed next to the executable.
  set_target_properties(${CEF_TARGET} PROPERTIES INSTALL_RPATH "$ORIGIN")
  set_target_properties(${CEF_TARGET} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
  set_target_properties(${CEF_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CEF_TARGET_OUT_DIR})

  # Copy binary and resource files to the target output directory.
  COPY_FILES("${CEF_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
  COPY_FILES("${CEF_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
  if (EXISTS "${CEF_BINARY_DIR}/libminigbm.so")
    COPY_FILES("${CEF_TARGET}" "libminigbm.so" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
  endif()

  # Set SUID permissions on the chrome-sandbox target.
  SET_LINUX_SUID_PERMISSIONS("${CEF_TARGET}" "${CEF_TARGET_OUT_DIR}/chrome-sandbox")
endif()

