# CMakeList.txt: проект CMake для Calculator; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Calculator "display.h" 
					"operations.h" "operations.cpp" 
					"parser.h" "parser.cpp"
					"calculator.h" "calculator.cpp"
					"main.cpp")

target_link_libraries(Calculator PRIVATE Qt6::Widgets)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
