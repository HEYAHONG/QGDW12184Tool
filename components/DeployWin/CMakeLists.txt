include(${COMPONENT_CMAKE_PATH})

#enable deploywin
add_subdirectory(DeployWin)
deploywin_enable(${COMPENENT_MAIN_TARGET})
deploywin_install(${COMPENENT_MAIN_TARGET})

