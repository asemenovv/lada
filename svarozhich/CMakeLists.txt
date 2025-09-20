cmake_minimum_required(VERSION 3.31)
project(svarozhich)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "~/Qt/6.9.2/macos")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_VERBOSE ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(svarozhich
        resources/main.qrc
        src/main.cpp
        src/MainWindow.h
        src/MainWindow.cpp
        src/mainwindow.ui
        src/scene/SceneTreeModel.h
        src/scene/SceneTreeModel.cpp
        src/scene/SceneHierarchyWidget.h
        src/scene/SceneHierarchyWidget.cpp
        src/scene/scenehierarchywidget.ui
        src/model/Entity.cpp
        src/model/Entity.h
        src/model/Component.h
        src/model/Math.h
        src/inspector/InspectorWidget.cpp
        src/inspector/InspectorWidget.h
        src/inspector/inspectorwidget.ui
        src/utils.h
        src/components/CollapsibleSection.cpp
        src/components/CollapsibleSection.h
        src/inspector/TransformComponentWidget.cpp
        src/inspector/TransformComponentWidget.h
        src/inspector/transformcomponentwidget.ui
        src/components/DisclosureButton.cpp
        src/components/DisclosureButton.h
        src/inspector/cameracomponentwidget.ui
        src/inspector/CameraComponentWidget.cpp
        src/inspector/CameraComponentWidget.h
        src/inspector/MeshComponentWidget.cpp
        src/inspector/MeshComponentWidget.h
        src/inspector/meshcomponentwidget.ui
        src/model/Project.cpp
        src/model/Project.h
        src/model/Shader.cpp
        src/model/Shader.h
        src/materials/NodeEditorWidget.cpp
        src/materials/NodeEditorWidget.h
        src/materials/nodeeditorwidget.ui
        src/materials/ShaderGraphModel.cpp
        src/materials/ShaderGraphModel.h
        src/model/shader/operations.h
        src/model/shader/NodeElement.cpp
        src/model/shader/NodeElement.h
        src/model/shader/NodesFactory.cpp
        src/model/shader/NodesFactory.h
)

target_include_directories(svarozhich
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(svarozhich
        PRIVATE lada_engine
        PRIVATE QtNodes::QtNodes
        PRIVATE Qt6::Core
        PRIVATE Qt6::Gui
        PRIVATE Qt6::Widgets
)
