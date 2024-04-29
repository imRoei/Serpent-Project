cmake_minimum_required(VERSION 3.5)
project(MyGTKApp)

# Set the C standard to C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Find GTK3 package
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Include GTK3 directories
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

# Add compiler flags for GTK3
add_definitions(${GTK3_CFLAGS_OTHER})

# ... other CMake configuration ...

add_subdirectory(serpentEnc)
add_subdirectory(graphEnc)

# Include header directories for serpentEnc and graphEnc
include_directories(serpentEnc graphEnc) 

# Add your source files here
add_executable(MyGTKApp
    src/main.c             # Your main C file
    src/gui.c              # Your GTK-based GUI code file
)

# Link GTK3 libraries to your executable
target_link_libraries(MyGTKApp ${GTK3_LIBRARIES} serpentEnc graphEnc) 

