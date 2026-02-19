cmake_minimum_required(VERSION 3.15)
project(UU_raytracer LANGUAGES C CXX)

# This adds the cmake modules stored in ./cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(defaults)
include(project_tools)
include(gl_setup)

# The set_up_libraries() macro is a user-defined macro. Look in gl_setup for its definition.
set(PROJECT_LIBRARIES)
set_up_libraries()

# This is for gathering source files. Don't do this in your own projects as this is discouraged by 
# the developers of CMake. This is used for the sake of convenience. If a new source file is added, this 
# will not be detected by CMake. The prefered method is to List the files in your project instead as 
# this will make sure that CMake reconfigures on changing the CMakeList.    
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/source" PROJECT_SOURCES)

# Create build files for the application
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# This instructs the C++ preprocessor to define a macro named "PROJECT_PATH".
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    PROJECT_PATH=\"${PROJECT_SOURCE_DIR}\"
)

# Make the compiler emit warnings for the project source files. 
apply_cxx_compiler_flags(${PROJECT_NAME})
enable_clang_format("${PROJECT_SOURCES}")
enable_clang_tidy("${PROJECT_SOURCES}")

# Link against libraries
target_link_libraries(${PROJECT_NAME} glfw ${PROJECT_LIBRARIES} ${GLFW_LIBRARIES} External_libraries)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Install application
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
