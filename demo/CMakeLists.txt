# # CMakeLists.txt in demo/demo1

# # Add the executable for demo1 with a different name to avoid conflicts
# add_executable(demo1 
#     ./base/base.cpp
# )

# # Link raylib library to demo1
# target_link_libraries(demo1 PRIVATE raylib RayGui++)

# # Specify the directories where CMake should look for the raylib library
# target_link_directories(demo1 PRIVATE ${LIBRARY_INSTALL_DIR}/lib)
