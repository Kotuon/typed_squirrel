
#include "imgui.h"

#include "fmt/core.h"
#include "utils/trace.hpp"

#include "cameraComponent.hpp"
#include "editor_windows/world_editor.hpp"
#include "editor.hpp"
#include "engine.hpp"
#include "entity.hpp"
#include "world.hpp"

namespace SquirrelEngine {

WorldEditor::WorldEditor() {
    getSystem< Editor >()->addDisplayMenuCallback(
        std::bind( &WorldEditor::update, this ) );
}

StartupErrors WorldEditor::initialize( Engine* ) {
    m_world = World::instance();

    return StartupErrors::SE_Success;
}

void WorldEditor::update() {
    auto& entityList = m_world->getEntityList();

    showObjects( entityList );

    showComponents( ( m_selectedEntity == -1 )
                        ? nullptr
                        : entityList[m_selectedEntity].get() );
}

void WorldEditor::showObjects(
    std::vector< std::unique_ptr< Entity > >& entityList ) {

    ImGui::Begin( "Object Editor##1" );

    for ( size_t i = 0; i < entityList.size(); ++i ) {
        const bool isSelected = m_selectedEntity == static_cast< int >( i );

        if ( ImGui::Selectable( entityList[i]->name.c_str(), isSelected,
                                ImGuiSelectableFlags_AllowDoubleClick ) ) {
            m_selectedEntity = static_cast< int >( i );
        }
    }

    ImGui::End();
}

void WorldEditor::showComponents( Entity* entity ) {
    ImGui::Begin( "Components##1" );
    if ( entity ) {
        ImGui::Text( entity->name.c_str() );

        {
            // Transform
            ImGui::SeparatorText( "Transform" );
            Transform* transform = &( entity->transform );

            //// Position
            const vector3 position = transform->getPosition();

            ImGui::Text( "Position" );
            ImGui::Text( "%f", position.x );
            ImGui::SameLine();
            ImGui::Text( "%f", position.y );
            ImGui::SameLine();
            ImGui::Text( "%f", position.z );

            //// Rotation
            const Quaternion rotation = transform->getRotation();
            const vector3 eulerRotation = transform->getEulerRotation();

            ImGui::Separator();
            ImGui::Text( "Quaternion Rotation" );
            ImGui::Text( "%f", rotation.w );
            ImGui::SameLine();
            ImGui::Text( "%f", rotation.i );
            ImGui::SameLine();
            ImGui::Text( "%f", rotation.j );
            ImGui::SameLine();
            ImGui::Text( "%f", rotation.k );

            ImGui::Text( "Euler Rotation" );
            ImGui::Text( "%f", eulerRotation.x );
            ImGui::SameLine();
            ImGui::Text( "%f", eulerRotation.y );
            ImGui::SameLine();
            ImGui::Text( "%f", eulerRotation.z );

            //// Transform matrix
            const matrix4 matrix = transform->matrix();

            ImGui::Separator();
            ImGui::Text( "Matrix" );
            for ( int i = 0; i < 4; ++i ) {
                for ( int j = 0; j < 4; ++j ) {
                    ImGui::Text( "%f", matrix[i][j] );
                    if ( j < 3 ) ImGui::SameLine();
                }
            }
            
        }

        // Camera Component
        CameraComponent* camera = entity->findComponent< CameraComponent >();
        if ( camera ) {
            ImGui::SeparatorText( "Camera Component" );

            Transform* cTransform = camera->getLocalTransform();

            //// Position
            const vector3 position = cTransform->getPosition();

            ImGui::Text( "Position" );
            ImGui::Text( "%f", position.x );
            ImGui::SameLine();
            ImGui::Text( "%f", position.y );
            ImGui::SameLine();
            ImGui::Text( "%f", position.z );

            //// Rotation
            const Quaternion rotation = cTransform->getRotation();
            const vector3 eulerRotation = camera->getEulerRotation();
            const vector3 convertRotation = rotation.getEulerRotation();

            ImGui::Separator();
            ImGui::Text( "Quaternion Rotation" );
            ImGui::Text( "%f", rotation.w );
            ImGui::SameLine();
            ImGui::Text( "%f", rotation.i );
            ImGui::SameLine();
            ImGui::Text( "%f", rotation.j );
            ImGui::SameLine();
            ImGui::Text( "%f", rotation.k );

            ImGui::Text( "Euler Rotation" );
            ImGui::Text( "%f", eulerRotation.x );
            ImGui::SameLine();
            ImGui::Text( "%f", eulerRotation.y );
            ImGui::SameLine();
            ImGui::Text( "%f", eulerRotation.z );

            ImGui::Text( "Convert Rotation" );
            ImGui::Text( "%f", convertRotation.x );
            ImGui::SameLine();
            ImGui::Text( "%f", convertRotation.y );
            ImGui::SameLine();
            ImGui::Text( "%f", convertRotation.z );

            //// Vectors

            const vector3 fwd = cTransform->forwardVector();
            const vector3 right = cTransform->rightVector();
            const vector3 up = cTransform->upVector();

            ImGui::Separator();
            ImGui::Text( "Forward vector" );
            ImGui::Text( "%f", fwd.x );
            ImGui::SameLine();
            ImGui::Text( "%f", fwd.y );
            ImGui::SameLine();
            ImGui::Text( "%f", fwd.z );

            ImGui::Text( "Right vector" );
            ImGui::Text( "%f", right.x );
            ImGui::SameLine();
            ImGui::Text( "%f", right.y );
            ImGui::SameLine();
            ImGui::Text( "%f", right.z );

            ImGui::Text( "Up vector" );
            ImGui::Text( "%f", up.x );
            ImGui::SameLine();
            ImGui::Text( "%f", up.y );
            ImGui::SameLine();
            ImGui::Text( "%f", up.z );
        }
    }
    ImGui::End();
}

} // namespace SquirrelEngine
