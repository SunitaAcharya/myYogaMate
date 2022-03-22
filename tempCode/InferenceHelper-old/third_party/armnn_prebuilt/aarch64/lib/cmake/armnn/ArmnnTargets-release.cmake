#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Armnn::fmt" for configuration "Release"
set_property(TARGET Armnn::fmt APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Armnn::fmt PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libfmt.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Armnn::fmt )
list(APPEND _IMPORT_CHECK_FILES_FOR_Armnn::fmt "${_IMPORT_PREFIX}/lib/libfmt.a" )

# Import target "Armnn::pipeCommon" for configuration "Release"
set_property(TARGET Armnn::pipeCommon APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Armnn::pipeCommon PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libpipeCommon.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Armnn::pipeCommon )
list(APPEND _IMPORT_CHECK_FILES_FOR_Armnn::pipeCommon "${_IMPORT_PREFIX}/lib/libpipeCommon.a" )

# Import target "Armnn::Armnn" for configuration "Release"
set_property(TARGET Armnn::Armnn APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Armnn::Armnn PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libarmnn.so.25.0"
  IMPORTED_SONAME_RELEASE "libarmnn.so.25"
  )

list(APPEND _IMPORT_CHECK_TARGETS Armnn::Armnn )
list(APPEND _IMPORT_CHECK_FILES_FOR_Armnn::Armnn "${_IMPORT_PREFIX}/lib/libarmnn.so.25.0" )

# Import target "Armnn::armnnUtils" for configuration "Release"
set_property(TARGET Armnn::armnnUtils APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Armnn::armnnUtils PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libarmnnUtils.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Armnn::armnnUtils )
list(APPEND _IMPORT_CHECK_FILES_FOR_Armnn::armnnUtils "${_IMPORT_PREFIX}/lib/libarmnnUtils.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
