cmake_minimum_required(VERSION 3.10)
project(beatTree)

# Configuración del estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar la librería de hilos
find_package(Threads REQUIRED)

# Buscar archivos fuente y templates
file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/BTree/*.tpp"
)

# Crear el ejecutable
add_executable(beatTree ${SOURCES})

# Enlazar con la librería de hilos
target_link_libraries(beatTree PRIVATE Threads::Threads)

if(MINGW)
    target_link_options(beatTree PRIVATE -static-libgcc -static-libstdc++)
endif()
