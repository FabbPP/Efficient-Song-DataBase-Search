cmake_minimum_required(VERSION 3.10)
project(beatTree)

# Configuración básica
set(CMAKE_CXX_STANDARD 17)

# Fuentes (ajusta las rutas según tu estructura real)
file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/BTree/*.tpp"  # Incluye archivos de plantillas si es necesario
)

# Ejecutable de CONSOLA (no GUI)
add_executable(beatTree ${SOURCES})

# Para MinGW en Windows
if(MINGW)
    target_link_libraries(beatTree -static-libgcc -static-libstdc++)
endif()