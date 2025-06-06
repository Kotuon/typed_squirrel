
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "core.hpp"
#include "mesh.hpp"
#include "model.hpp"

namespace SquirrelEngine {

Model::Model( Entity* t_parent )
    : Component( t_parent ), m_mesh( nullptr ), m_renderMethod( GL_TRIANGLES ) {
}

Model::~Model() {}

void Model::initMesh( const std::string& filename ) {
    m_mesh = std::make_unique< Mesh >( this );
    m_mesh->load( filename );
}

void Model::initShader( const std::string& vertName,
                        const std::string& fragName ) {
    if ( !m_mesh ) {
        Trace::message( "Failed to make shader: No mesh" );
        return;
    }

    m_mesh->loadShader( vertName, fragName );
}

void Model::draw() { m_mesh->draw(); }

void Model::setMesh( Mesh* t_mesh ) {
    m_mesh = std::make_unique< Mesh >( t_mesh );
}

Mesh* Model::getMesh() const { return m_mesh.get(); }

void Model::setRenderMethod( unsigned t_renderMethod ) {
    m_renderMethod = t_renderMethod;
}

unsigned Model::getRenderMethod() const { return m_renderMethod; }

} // namespace SquirrelEngine
