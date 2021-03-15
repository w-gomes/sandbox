cmake_minimum_required(VERSION 3.16)

############################ project setup ############################

project(test_bed LANGUAGES CXX)
include(cmake/standard_project_settings.cmake)
include(cmake/prevent_in_source_builds.cmake)


############################ Options ############################

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

set_target_properties(project_options PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)


############################ warnings, sanitizers ############################

# Link this 'library' to use the warnings specified in compiler_warnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/compiler_warnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/sanitizers.cmake)
enable_sanitizers(project_options)

# static analyzers
include(cmake/static_analyzers.cmake)


############################ external libraries ############################

# add installed libraries
find_package(fmt REQUIRED)
find_package(range-v3 CONFIG REQUIRED)


############################ project files ############################

# add sources files
# set(sources path/to/sources)

### especific configs for library ###
# add_library(${PROJECT_NAME} STATIC/SHARED sources)
# add_library(some-alias::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

### end especific configs for library ###

# add_subdirectory(path/to/directory)

# add_executable(${PROJECT_NAME} ${sources})

### if needs to include ###
# target_include_directories(
#  ${PROJECT_NAME} 
#  PUBLIC/PRIVATE/INTERFACE ${PROJECT_SOURCE_DIR}/includes
#)

function(test target path)
  add_executable(${target} ${path})
  target_link_libraries(
    ${target} 
    PRIVATE project_warnings
            project_options
            fmt::fmt-header-only
            range-v3
            range-v3-meta
            range-v3::meta
            range-v3-concepts
  )
endfunction()

test(number_theory src/number_theory.cpp)
test(fmt_test src/fmt_test.cpp)
test(black_hole src/black_hole.cpp)
test(temp src/temp.cpp)


############################ test ############################

### Test configs ###
### make sure to have a CMakeLists.txt in test folder ###
# if(ENABLE_TEST)
#  enable_testing()
#  message("Building tests...")
#  add_subdirectory(${PROJECT_SOURCE_DIR}/test)
#endif()
