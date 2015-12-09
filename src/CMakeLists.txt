set(BIN_NAME globe)

set(CPP_FILES
    camera.cpp
    main.cpp
    image.cpp
    mesh.cpp
    stb.cpp
    )

set(CPP_HEADERS
    camera.h
    extra.h
    image.h
    mesh.h
    stb_image.h
    stb_image_write.h
    )

set(LIBS_USED
    vecmath
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${RK4_LIBRARIES}
    )

if (CMAKE_SYSTEM_NAME STREQUAL Linux)                        
    set(LIBS_USED ${LIBS_USED} dl)                           
endif()                                                      

add_executable(${BIN_NAME} ${CPP_FILES} ${CPP_HEADERS})
target_link_libraries(${BIN_NAME} ${LIBS_USED})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
