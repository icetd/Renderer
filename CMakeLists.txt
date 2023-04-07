cmake_minimum_required(VERSION 3.10)
project(Renderer)

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)

if (WIN32)
	add_definitions()

elseif (UNIX)

	add_definitions()
endif()

set (CMKAE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (SOURCE_DIR  "${CMAKE_CURRENT_LIST_DIR}/src") 
set (INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")

set (GLFW_INC			"${CMAKE_CURRENT_LIST_DIR}/thirdparty/glfw/include")
set (GLAD_SRC			"${CMAKE_CURRENT_LIST_DIR}/thirdparty/glad/src")
set (GLAD_INC			"${CMAKE_CURRENT_LIST_DIR}/thirdparty/glad/include")
set (STB_IMAGE_INC		"${CMAKE_CURRENT_LIST_DIR}/thirdparty/stb_image")
set (GLM_INC			"${CMAKE_CURRENT_LIST_DIR}/thirdparty/glm")
set (IMGUI_SRC			"${CMAKE_CURRENT_LIST_DIR}/thirdparty/imgui_mini")


message("${SOURCE_DIR}")
message("${INCLUDE_DIR}")

include_directories(
	${INCLUDE_DIR}
	${GLFW_INC}
	${GLAD_INC}
	${STB_IMAGE_INC}
	${GLM_INC}
	${IMGUI_SRC}
) 

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE SRC_FILES
    "${SOURCE_DIR}/*.cpp"
    "${GLAD_SRC}/*.c"
	"${IMGUI_SRC}/*.cpp"
)

file (GLOB_RECURSE INC_FILES
    "${INCLUDE_DIR}/*.h"
	"${IMGUI_SRC}/*.h"
)

file (GLOB_RECURSE RES_FILES
    "${CMAKE_SOURCE_DIR}/res/shaders/*.shader"
)


if (WIN32)
	source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SRC_FILES})
	source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${INC_FILES})
	source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${RES_FILES})

elseif (UNIX)
#nothing to do
endif ()

if (WIN32)
	list(APPEND EXTRA_LIBS
		opengl32 glfw User32 Gdi32 Shell32
 	)
elseif (UNIX)
	list (APPEND EXTRA_LIBS
		GL GLU X11 glfw
	)
endif ()

if (WIN32)
	add_executable(${PROJECT_NAME} ${SRC_FILES} ${INC_FILES} ${RES_FILES})
elseif (UNIX)
	add_executable(${PROJECT_NAME} ${SRC_FILES} )
endif ()

# Add the target includes for MY_PROJECT 
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})


#===================== LINKING LIBRARIES =======================#
if (WIN32)
	target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
else (UNIX)
	target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
endif()


