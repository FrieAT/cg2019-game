FIND_PATH(GLFW_INCLUDE_DIR glfw3.h
	HINTS
	$ENV{GLFWDIR}
	PATH_SUFFIXES include/GL include
	PATHS
	/usr/local/include/GLFW
	/usr/include/GLFW
	/opt/local
	/opt
)

MESSAGE("GLFW_INCLUDE_DIR is ${GLFW_INCLUDE_DIR}")

FIND_LIBRARY(GLFW_LIBRARY
	NAMES glfw3 GLFW
	NAMES glfw GLFW
	HINTS
	$ENV{GLFWDIR}
	PATH_SUFFIXES lib64 lib
	PATHS
    /sw
	/usr/lib
    /usr/lib/x86_64-linux-gnu
	/usr/local
	/opt/local
	/opt
)

MESSAGE("GLFW_LIBRARY_DIR is ${GLFW_LIBRARY}")

IF(GLFW_LIBRARY)

    SET(GLFW_LIBRARIES ${GLFW_LIBRARY})

    # For Unix, GLFW should be linked to X11-releated libraries.
    IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    FIND_LIBRARY(X11_LIBRARY X11)
    FIND_LIBRARY(Xrandr_LIBRARY Xrandr)
    FIND_LIBRARY(Xxf86vm_LIBRARY Xxf86vm)
    FIND_LIBRARY(Xi_LIBRARY Xi)
    SET(GLFW_LIBRARIES ${GLFW_LIBRARIES} ${X11_LIBRARY} ${Xrandr_LIBRARY} ${Xxf86vm_LIBRARY} ${Xi_LIBRARY})
    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

    # Set the final string here so the GUI reflects the final state.
    SET(GLFW_LIBRARY ${GLFW_LIBRARY} CACHE STRING "Where the GLFW Library can be found")

    SET(GLFW_FOUND TRUE)

    #MESSAGE("GLFW_LIBRARIES is ${GLFW_LIBRARIES}")

ENDIF(GLFW_LIBRARY)

MESSAGE("-- Found GLFW: ${GLFW_FOUND}")
