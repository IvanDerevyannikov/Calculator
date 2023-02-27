# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_AUTOMOC ON)


project ("Calculator")

# Включите подпроекты.
add_subdirectory ("Calculator")
