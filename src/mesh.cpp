
#include "core.hpp"

namespace SquirrelEngine {

Mesh::Mesh() {}

Mesh::Mesh( const Mesh& other )
    : m_vertexbuffer( other.m_vertexbuffer ),
      m_normalbuffer( other.m_normalbuffer ), m_uvbuffer( other.m_uvbuffer ) {
    for ( float vert : other.m_vertices ) {
        m_vertices.emplace_back( vert );
    }
    for ( float norm : other.m_normals ) {
        m_normals.emplace_back( norm );
    }
    for ( float uv : other.m_uvs ) {
        m_uvs.emplace_back( uv );
    }
}

Mesh::Mesh( const Mesh* other )
    : m_vertexbuffer( other->m_vertexbuffer ),
      m_normalbuffer( other->m_normalbuffer ), m_uvbuffer( other->m_uvbuffer ) {
    for ( float vert : other->m_vertices ) {
        m_vertices.emplace_back( vert );
    }
    for ( float norm : other->m_normals ) {
        m_normals.emplace_back( norm );
    }
    for ( float uv : other->m_uvs ) {
        m_uvs.emplace_back( uv );
    }
}

Mesh::Mesh( Model* t_model ) : m_model( t_model ) {}

Mesh::~Mesh() {
    glDeleteBuffers( 1, &m_vertexbuffer );
    glDeleteBuffers( 1, &m_uvbuffer );
    glDeleteBuffers( 1, &m_normalbuffer );
}

bool Mesh::load( std::string t_modelName ) { return read( t_modelName ); }

bool Mesh::read( std::string t_modelName ) {
    // Setting the name of the file (used in model_data_manager)
    m_modelName = t_modelName;

    FILE* file;
    errno_t err = fopen_s( &file, m_modelName.c_str(), "r" );
    if ( err != 0 ) {
        Trace::message( fmt::format( "Unable to open {}.", m_modelName ) );
        return false;
    }

    // Creating variables for reading
    std::vector< unsigned > vertexIndices, uvIndices, normalIndices;
    std::vector< vector3 > tempVertices;
    std::vector< vector2 > tempUvs;
    std::vector< vector3 > tempNormals;

    // Until the whole file is read
    char line[64];
    char* temp;
    while ( fgets( line, 64, file ) ) {
        char* words[4];
        words[0] = strtok_s( line, " ", &temp );
        for ( int i = 1; i < 4; ++i ) {
            words[i] = strtok_s( nullptr, " ", &temp );
        }

        if ( strcmp( words[0], "v" ) == 0 ) {
            tempVertices.push_back(
                { atof( words[1] ), atof( words[2] ), atof( words[3] ) } );
        } else if ( strcmp( words[0], "vt" ) == 0 ) {
            tempUvs.push_back( { atof( words[1] ), atof( words[2] ) } );
        } else if ( strcmp( words[0], "vn" ) == 0 ) {
            tempNormals.push_back(
                { atof( words[1] ), atof( words[2] ), atof( words[3] ) } );
        } else if ( strcmp( words[0], "f" ) == 0 ) {
            char* v1[3];
            char* v2[3];
            char* v3[3];

            v1[0] = strtok_s( words[1], "/", &temp );
            v1[1] = strtok_s( nullptr, "/", &temp );
            v1[2] = strtok_s( nullptr, "/", &temp );

            v2[0] = strtok_s( words[2], "/", &temp );
            v2[1] = strtok_s( nullptr, "/", &temp );
            v2[2] = strtok_s( nullptr, "/", &temp );

            v3[0] = strtok_s( words[3], "/", &temp );
            v3[1] = strtok_s( nullptr, "/", &temp );
            v3[2] = strtok_s( nullptr, "/", &temp );

            insertData( v1, tempVertices, tempUvs, tempNormals );
            insertData( v2, tempVertices, tempUvs, tempNormals );
            insertData( v3, tempVertices, tempUvs, tempNormals );
        }
    }

    // Bind vertex data to buffers
    glGenBuffers( 1, &m_vertexbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexbuffer );
    glBufferData( GL_ARRAY_BUFFER, m_vertices.size() * sizeof( float ),
                  &m_vertices[0], GL_STATIC_DRAW );

    // Bind uv data to buffers
    glGenBuffers( 1, &m_uvbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_uvbuffer );
    glBufferData( GL_ARRAY_BUFFER, m_uvs.size() * sizeof( float ), &m_uvs[0],
                  GL_STATIC_DRAW );

    // Bind m_normals data to buffers
    glGenBuffers( 1, &m_normalbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, m_normalbuffer );
    glBufferData( GL_ARRAY_BUFFER, m_normals.size() * sizeof( float ),
                  &m_normals[0], GL_STATIC_DRAW );

    return true;
}

void Mesh::insertData( char* data[3], std::vector< vector3 >& v,
                       std::vector< vector2 >& vt,
                       std::vector< vector3 >& vn ) {
    m_vertices.push_back( v[atoi( data[0] ) - 1].x );
    m_vertices.push_back( v[atoi( data[0] ) - 1].y );
    m_vertices.push_back( v[atoi( data[0] ) - 1].z );

    m_uvs.push_back( vt[atoi( data[1] ) - 1].x );
    m_uvs.push_back( vt[atoi( data[1] ) - 1].y );

    m_normals.push_back( vn[atoi( data[2] ) - 1].x );
    m_normals.push_back( vn[atoi( data[2] ) - 1].y );
}

void Mesh::draw() {
    Transform& transform = m_model->parent->transform;
    World* world = World::instance();

    CameraComponent* camera =
        world->findEntity( "Main camera" )->findComponent< CameraComponent >();

    // Creating the MVP (Model * View * Projection) matrix
    matrix4 model = transform.matrix();

    glUseProgram( m_shader->getHandle() );

    // Sending data to the shaders
    glUniformMatrix4fv( m_shader->getLocation( "projection" ), 1, GL_FALSE,
                        &camera->projectionMatrix()[0][0] );
    glUniformMatrix4fv( m_shader->getLocation( "model" ), 1, GL_FALSE,
                        &model[0][0] );
    glUniformMatrix4fv( m_shader->getLocation( "view" ), 1, GL_FALSE,
                        &camera->viewMatrix()[0][0] );

    // glm::mat4 MVP = projection * view * model;
    // glUniformMatrix4fv( Shader::GetMatrixId(), 1, GL_FALSE, &MVP[0][0] );
    // glUniformMatrix4fv( Shader::GetModelMatrixId(), 1, GL_FALSE, &model[0][0]
    // ); glUniformMatrix4fv( Shader::GetViewMatrixId(), 1, GL_FALSE,
    // &view[0][0] );

    // // Sending light data to the shaders
    // vector3lightPos = Engine::GetLightPos();
    // glUniform3f( Shader::GetLightId(), lightPos.x, lightPos.y, lightPos.z );
    // glUniform1f( Shader::GetLightPowerId(), Engine::GetLightPower() );

    // Setup texture for drawing if it exists
    // if ( parent->GetTexture() ) parent->GetTexture()->Display();

    // Setup the model m_vertices
    glEnableVertexAttribArray( 0 );
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexbuffer );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, ( void* )0 );

    // Setup the model uv
    glEnableVertexAttribArray( 1 );
    glBindBuffer( GL_ARRAY_BUFFER, m_uvbuffer );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, ( void* )0 );

    // Setup the model m_normals
    glEnableVertexAttribArray( 2 );
    glBindBuffer( GL_ARRAY_BUFFER, m_normalbuffer );
    glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, ( void* )0 );

    // Draw the object
    glDrawArrays( GL_TRIANGLES, 0,
                  static_cast< GLsizei >( m_vertices.size() ) );

    // Disable data sent to shaders
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );

    glUseProgram( 0 );
}

void Mesh::setShader( Program* t_shader ) {
    m_shader = std::make_unique< Program >( t_shader );
}

const Program* Mesh::getShader() const { return m_shader.get(); }

void Mesh::loadShader( const std::string& vertName,
                       const std::string& fragName ) {
    m_shader = std::make_unique< Program >( vertName, fragName );
}

std::string Mesh::getModelName() const { return m_modelName; }

} // namespace SquirrelEngine
