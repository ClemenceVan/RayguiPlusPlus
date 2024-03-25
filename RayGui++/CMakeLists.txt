# CMakeLists.txt in RayGui++ directory

# Define the library name and sources
add_library(RayGuiLib
    src/RayGui++.cpp
    # Add more source files if needed
)

# Set include directories for the library
target_include_directories(RayGuiLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/includes # Include RayGui++ headers
    ${RAYLIB_INCLUDE_DIRS} # Include raylib headers (assuming this variable is defined elsewhere)
)

# Link raylib library
target_link_libraries(RayGuiLib PUBLIC raylib)

# Set the installation directory for the library
install(TARGETS RayGuiLib
    ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}/lib
    LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}/lib
    RUNTIME DESTINATION ${LIBRARY_INSTALL_DIR}/bin # Install library binaries to ./bin
)

# Optionally, you might want to install header files
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/includes/RayGui++.hpp DESTINATION ${LIBRARY_INSTALL_DIR}/include)
