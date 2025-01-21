cmake_minimum_required(VERSION 3.27)
project(SDL_BASE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build: Debug, Release, RelWithDebInfo, MinSizeRel" FORCE)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D _DEBUG)
endif()

find_package(SDL2 REQUIRED SDL2)

add_executable(SDL_BASE Main/Main.cpp
        System/Process/Processer.cpp
        System/Process/Processer.h
        System/Physics/Rigidbody.cpp
        System/Physics/Rigidbody.h
        System/GameObject/GameObject.h
        System/GameObject/GameObject.cpp
        System/Component/Component.h
        System/Component/Component.cpp
        System/Utility/Math.h
        System/Component/SpriteComponent.h
        System/Component/SpriteComponent.cpp
        System/Component/AnimSpriteComponent.h
        System/Component/AnimSpriteComponent.cpp
        System/TENSHI/Player/Player.cpp
        System/TENSHI/Player/Player.h
        System/Utility/Math.cpp
        System/TENSHI/Player/PlayerMoveState.h
        System/TENSHI/Player/PlayerMoveState.cpp
        System/Process/AssetLoader.h
        System/Process/AssetLoader.cpp
        System/Process/Renderer.h
        System/Process/Renderer.cpp
        System/Process/InputReader.h
        System/Process/InputReader.cpp
        System/Utility/Event.h
        System/Data/AssetPath.h
        System/Data/GameObjectData.h
        System/Scene/Scene.h
        System/Scene/InGameScene.h
        System/Scene/InGameScene.cpp
        System/Data/GameObjectData.cpp
        System/Component/FSM/State.cpp
        System/Component/FSM/State.h
        System/Component/FSM/StateMachine.h
        System/Component/FSM/StateMachine.cpp
        System/TENSHI/Player/PlayerIdleState.h
        System/TENSHI/Player/PlayerIdleState.cpp
        System/Data/AnimSpriteData.h
        System/Data/AnimSpriteData.cpp
        System/Process/PhysicsProcesser.h
        System/Process/PhysicsProcesser.cpp
        System/Physics/BoxCollider.h
        System/Physics/BoxCollider.cpp
        System/Utility/DebugRay.h
        System/Utility/DebugRay.cpp
        System/Physics/Collider.cpp
        System/Physics/Collider.h
        System/Physics/LineCollider.h
        System/Physics/LineCollider.cpp
        System/Data/SpriteData.h
        System/Data/SpriteData.cpp
        System/Data/TileData.h
        System/Data/TileData.cpp
        json.hpp
        System/Utility/Singleton.h
        System/Process/IProcess.h
        System/Process/IProcess.cpp
        System/Process/Sprite.h
        System/Process/Sprite.cpp
        System/Component/Camera/Camera.cpp
        System/TENSHI/Player/PlayerJumpState.cpp
        System/RayCast/RayCastObject.h
        System/RayCast/RayCastObject.cpp
        System/TENSHI/Player/Skill/Skill.h
        System/TENSHI/Player/Skill/Skill.h
        System/TENSHI/Player/Skill/Skill.cpp
        System/TENSHI/Player/PlayerSkillState.h
        System/TENSHI/Player/PlayerSkillState.cpp
        System/TENSHI/Player/PlayerSkillState.cpp
        System/TENSHI/Player/PlayerState.cpp
        System/TENSHI/Player/PlayerState.h
        System/Component/TextComponent.h
        System/Component/TextComponent.cpp
        System/Process/Text.h
        System/Process/Text.cpp
        System/UI/View/Canvas.h
        System/UI/View/Canvas.cpp
        System/UI/Presentor/Presentor.h
        System/UI/Presentor/Presentor.cpp
        System/UI/Presentor/Debug/DebugPresentor.h
        System/UI/Presentor/Debug/DebugPresentor.cpp
        System/UI/View/Debug/DebugCanvas.h
        System/UI/View/Debug/DebugCanvas.cpp
        System/Process/SceneManager.h
        System/Process/SceneManager.cpp
        System/Component/FpsCheckComponent.cpp
        System/Component/FpsCheckComponent.h
        System/Component/MousePositionComponent.h
        System/Component/MousePositionComponent.cpp
        System/Data/LineColliderData.h
        System/Data/LineColliderData.cpp
        System/TENSHI/Enemy/Enemy.h
        System/TENSHI/Enemy/Enemy.cpp
        System/TENSHI/Enemy/EnemyIdleState.h
        System/TENSHI/Enemy/EnemyState.h
        System/TENSHI/Enemy/EnemyIdleState.cpp
        System/TENSHI/Enemy/EnemyState.cpp
        System/Data/EnemyData.h
        System/Data/EnemyData.cpp
        System/Data/MonsterData.h
        System/Data/MonsterData.cpp
        System/UI/View/InGameCanvas.h
        System/UI/View/InGameCanvas.cpp
        System/TENSHI/Damage/DamageHandler.h
        System/TENSHI/Damage/Health.h
        System/TENSHI/Damage/Health.cpp
        System/TENSHI/Damage/DamageHandler.cpp
        System/TENSHI/Damage/Damage.h
        System/TENSHI/Damage/Damage.cpp
        System/TENSHI/Enemy/EnemyHitState.h
        System/TENSHI/Enemy/EnemyHitState.cpp
        System/TENSHI/Player/PlayerDoubleJumpState.h
        System/TENSHI/Player/PlayerDoubleJumpState.cpp
        System/TENSHI/Enemy/EnemyDeadState.h
        System/TENSHI/Enemy/EnemyDeadState.cpp
        System/TENSHI/Enemy/EnemyManager.h
        System/TENSHI/Enemy/EnemyManager.cpp
        System/TENSHI/Prob/Portal.h
        System/TENSHI/Prob/Portal.cpp
        System/TENSHI/Prob/Portal.h
        System/GameObject/IinteractableObject.h
        System/GameObject/IinteractableObject.cpp
        System/Scene/TitleScene.h
        System/Scene/TitleScene.cpp
        System/UI/View/TitleCanvas.h
        System/UI/View/TitleCanvas.cpp

)

include_directories(${CMAKE_SOURCE_DIR}/)

set(ASSET_DIR "${CMAKE_SOURCE_DIR}/")
add_compile_definitions(ASSET_DIR="${ASSET_DIR}")

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets" DESTINATION ${CMAKE_BINARY_DIR})
target_link_libraries(SDL_BASE PRIVATE SDL2)
