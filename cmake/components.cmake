#
#自动添加 工程目录/components下的组件
#
if(POLICY CMP0079 )
  cmake_policy(SET CMP0079 NEW)
endif()
function(components_init main_target_name project_root)
set(COMPENENT_MAIN_TARGET ${main_target_name})
set(COMPONENT_PROJECT_ROOT ${project_root})
set(COMPONENT_CMAKE_PATH ${COMPONENT_PROJECT_ROOT}/cmake/components.cmake)
file(GLOB COMPONENTS ${project_root}/components/*)
foreach(COMPONENT ${COMPONENTS})
	if(IS_DIRECTORY ${COMPONENT})
		file(RELATIVE_PATH COMPONENTNAME ${project_root}/components/ ${COMPONENT})
	 	message(STATUS "Add Component ${COMPONENTNAME}")
		add_subdirectory(${COMPONENT})
	endif()
endforeach()
endfunction()


function(components_add_library library)
target_link_libraries(${COMPENENT_MAIN_TARGET} ${library})
endfunction()
