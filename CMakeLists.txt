cmake_minimum_required(VERSION 3.10)

# Set the project name
project(HelloWorld)

# Add the executable
file(GLOB SOURCES "Chapter01/*.cpp"  "Chapter02/*.cpp")
add_executable(main ${SOURCES})