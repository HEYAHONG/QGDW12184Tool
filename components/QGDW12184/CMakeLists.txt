include(${COMPONENT_CMAKE_PATH})

#库
file(GLOB QGDW12184_CXX_C_FILES *.cpp *.h *.hpp *.c)
add_library(QGDW12184 ${QGDW12184_CXX_C_FILES})

target_include_directories(QGDW12184
PUBLIC ./
)

#添加到组件库
components_add_library(QGDW12184)
