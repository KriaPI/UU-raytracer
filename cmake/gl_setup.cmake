macro(set_up_libraries)
    # OpenGL
    find_package(OpenGL REQUIRED)
    if(OPENGL_FOUND)
      set(PROJECT_LIBRARIES ${PROJECT_LIBRARIES} ${OPENGL_LIBRARIES})
    endif(OPENGL_FOUND)

    # GLFW (used for window handling)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glfw")

    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/external/glew/src" LIBRARY_SOURCES)
    include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include")
    add_definitions(-DGLEW_STATIC -DGLEW_NO_GLU)

    # gl3w (used for OpenGL function loading)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/external/gl3w/src" LIBRARY_SOURCES)

    # Dear ImGui (used for GUI)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/external/imgui" LIBRARY_SOURCES)
    set(LIBRARY_SOURCES ${LIBRARY_SOURCES})
    add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GL3W)

    # lodepng (used for image I/O)
    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/external/lodepng" LIBRARY_SOURCES)
    include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/external/lodepng")

    add_library(External_libraries ${LIBRARY_SOURCES})
    target_include_directories(External_libraries PUBLIC SYSTEM 
        ${OPENGL_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/gl3w/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/examples
        ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
        ${CMAKE_CURRENT_SOURCE_DIR}/external/rapidjson/include
    )
endmacro(set_up_libraries)