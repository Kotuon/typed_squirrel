
#ifndef MODEL_HPP
#define MODEL_HPP
#pragma once

#include <memory>

#include "component.hpp"

namespace SquirrelEngine {
class Mesh;

class Model : public Component {
public:
    Model( Entity* t_parent );
    ~Model();

    void initMesh( const std::string& filename );

    void initShader( const std::string& vertName, const std::string& fragName );

    void draw();

    void setMesh( Mesh* t_mesh );
    Mesh* getMesh() const;

    void setRenderMethod( unsigned t_renderMethod );
    unsigned getRenderMethod() const;

private:
    std::unique_ptr< Mesh > m_mesh;
    GLuint m_renderMethod;
};

} // namespace SquirrelEngine

#endif
