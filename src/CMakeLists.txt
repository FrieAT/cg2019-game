set( 2019_cg_phsysics_SRC
#  add additional files as needed
./Exception.cpp
./GameObject.cpp
./Managers/AbstractManager.cpp
./Managers/GameLogicManager/GameLogicManager.cpp
./Managers/PhysicsManager/PhysicsManager.cpp
./Managers/Object/ObjectManager.cpp
./Managers/Window/WindowManager.cpp
./Managers/Rendering/RenderManager.cpp
./Managers/KeyBoard/KeyboardManager.cpp
./Managers/KeyBoard/KeyBoard.cpp
./Components/Animate/SteveArmAnimation/SteveArmAnimation.cpp
./Components/Animate/SteveLegAnimation/SteveLegAnimation.cpp
./Components/Drawing/Sphere/SphereDrawing.cpp
./Components/Drawing/Geometrie/Geometrie.cpp
./Components/Drawing/Line/LineDrawing.cpp
./Components/Drawing/Texture/SteveAbstractTexture/GrassBlock/GrassBlockTexture.cpp
./Components/Drawing/Texture/SteveAbstractTexture/GameOverBlock/GameOverBlock.cpp
./Components/Drawing/Texture/SteveAbstractTexture/GameOverBlock/GameOverBlockTexture.cpp
./Components/Drawing/Texture/SteveAbstractTexture/SteveBody/SteveBodyTexture.cpp
./Components/Drawing/Texture/SteveAbstractTexture/SteveLeg/SteveLegTexture.cpp
./Components/Drawing/Texture/SteveAbstractTexture/SteveHead/SteveHeadTexture.cpp
./Components/Drawing/Texture/SteveAbstractTexture/WoodBlock/WoodBlockTexture.cpp
./Components/Drawing/Texture/SteveAbstractTexture/SteveArm/SteveArmTexture.cpp
./Components/Drawing/Texture/SteveAbstractTexture/SteveAbstractTexture.cpp
./Components/Drawing/Stage/StageDrawing.cpp
./Components/Drawing/CubeDrawing/CubeDrawing.cpp
./Components/Drawing/Probe/Probe.cpp
./Components/Position/PixelTransform/PixelTransform.cpp
./Components/Movement/LinearMovement/LinearMovement.cpp
./Components/View/PrototypeView/PrototypeView.cpp
./Components/Shader/DefaultShader/DefaultShader.cpp
./Components/Shader/SphereShader/SphereShader.cpp
./Components/Player/IPlayer.cpp
./Factory/PrimitiveObjects.cpp
./Game.cpp
	)

set( 2019_cg_phsysics_HEADERS 
./Managers
./Managers/GameLogicManager
./Managers/PhysicsManager
./Managers/Object
./Managers/Window
./Managers/Rendering
./Managers/KeyBoard
./Components
./Components/Animate
./Components/Animate/SteveArmAnimation
./Components/Animate/SteveLegAnimation
./Components/Drawing
./Components/Drawing/Sphere
./Components/Drawing/Geometrie
./Components/Drawing/Line
./Components/Drawing/Texture
./Components/Drawing/Texture/SteveAbstractTexture
./Components/Drawing/Texture/SteveAbstractTexture/GrassBlock
./Components/Drawing/Texture/SteveAbstractTexture/GameOverBlock
./Components/Drawing/Texture/SteveAbstractTexture/SteveBody
./Components/Drawing/Texture/SteveAbstractTexture/SteveLeg
./Components/Drawing/Texture/SteveAbstractTexture/SteveHead
./Components/Drawing/Texture/SteveAbstractTexture/WoodBlock
./Components/Drawing/Texture/SteveAbstractTexture/SteveArm
./Components/Drawing/Stage
./Components/Drawing/CubeDrawing
./Components/Drawing/Probe
./Components/Position
./Components/Position/PixelTransform
./Components/Collider
./Components/Movement
./Components/Movement/LinearMovement
./Components/View
./Components/View/PrototypeView
./Components/Shader
./Components/Shader/DefaultShader
./Components/Shader/SphereShader
./Components/Player
./Assets
./Factory
./
    )

find_package(OpenGL REQUIRED)
if( OPENGL_FOUND )
    set(2019_cg_phsysics_LIBS ${2019_cg_phsysics_LIBS} ${OPENGL_LIBRARY})
else()               
    message(ERROR "OPENGL not found!")
endif()


if( WITH_GLUT )
    find_package(GLUT REQUIRED)
    if( GLUT_FOUND )
        message("Adding OpenGL GLUT support")
        set(2019_cg_phsysics_LIBS ${2019_cg_phsysics_LIBS} ${GLUT_LIBRARY})
    else()               
        message(ERROR "GLUT not found!")
    endif()
endif()      

if( WITH_GLFW )
    find_package(GLFW REQUIRED)
    if( GLFW_FOUND )
        message("Adding OpenGL GLFW support")
        set(2019_cg_phsysics_LIBS ${2019_cg_phsysics_LIBS} ${GLFW_LIBRARY})
        include_directories(${GLFW_INCLUDE_DIR})
    else()               
        message(ERROR "GLFW not found!")
    endif()
endif()

if( WITH_GLEW )
    find_package(GLEW REQUIRED)
    if( GLEW_FOUND )
        message("Adding OpenGL GLEW support")
        set(2019_cg_phsysics_LIBS ${2019_cg_phsysics_LIBS} ${GLEW_LIBRARY})
        include_directories(${GLEW_INCLUDE_DIR})
    else()               
        message(ERROR "GLEW not found!")
    endif()
endif()

include_directories(${2019_cg_phsysics_HEADERS})

# name der datei mit main() des projektes
# executable heisst "2019_cg_physics"
add_executable(2019_cg_physics ${2019_cg_phsysics_SRC} main.cpp) 

target_link_libraries(2019_cg_physics ${2019_cg_phsysics_LIBS})
	
set_target_properties(2019_cg_physics PROPERTIES COMPILE_FLAGS "")
