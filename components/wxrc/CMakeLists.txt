include(${COMPONENT_CMAKE_PATH})

#RC资源文件（非Windows专用），可存储少量数据
add_subdirectory(rc EXCLUDE_FROM_ALL)

#wxrc库
file(GLOB WXRC_CXX_C_FILES *.cpp *.h *.hpp *.c)
add_library(wxrc ${WXRC_CXX_C_FILES})
target_link_libraries(wxrc RC)
if(WIN32)
	find_package(wxWidgets 3.0.0 REQUIRED core base adv aui webview html gl richtext )
else()
	find_package(wxWidgets 3.0.0 REQUIRED all)
endif()
include(${wxWidgets_USE_FILE})
target_link_libraries(wxrc ${wxWidgets_LIBRARIES})

target_include_directories(wxrc
PUBLIC ./
)

#添加到组件库
components_add_library(wxrc)
