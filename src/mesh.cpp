/**
 *
 * @file mesh.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief Implements the Mesh class, which represents a renderable mesh and its
 * associated data in SquirrelEngine.
 * @date 2025-06-06
 *
 */

#include "core.hpp"

namespace SquirrelEngine {

/**
 * @brief Default constructor for Mesh.
 */
Mesh::Mesh() {}

/**
 * @brief Copy constructor for Mesh.
 * @param other Mesh to copy from.
 */
Mesh::Mesh( const Mesh& other ) : vao( other.vao ), vbo( other.vbo ) {
    for ( Vertex vert : other.m_vertices ) {
        m_vertices.emplace_back( vert );
    }
}

/**
 * @brief Copy constructor from pointer for Mesh.
 * @param other Pointer to Mesh to copy from.
 */
Mesh::Mesh( const Mesh* other ) : vao( other->vao ), vbo( other->vbo ) {
    for ( Vertex vert : other->m_vertices ) {
        m_vertices.emplace_back( vert );
    }
}

/**
 * @brief Constructs a Mesh with a given Model.
 * @param t_model Pointer to the Model.
 */
Mesh::Mesh( Model* t_model ) : m_model( t_model ) {}

/**
 * @brief Destructor for Mesh.
 */
Mesh::~Mesh() {
    glDeleteBuffers( 1, &vao );
    glDeleteBuffers( 1, &vbo );
}

/**
 * @brief Loads mesh data from a model file.
 * @param t_modelName Name of the model file.
 * @return true if loaded successfully, false otherwise.
 */
bool Mesh::load( std::string t_modelName ) { return read( t_modelName ); }

/**
 * @brief Reads mesh data from a model file.
 * @param t_modelName Name of the model file.
 * @return true if read successfully, false otherwise.
 */
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

    vertCount = static_cast< GLsizei >( m_vertices.size() );

    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    glGenBuffers( 1, &vbo );

    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, sizeof( Vertex ) * vertCount,
                  m_vertices.data(), GL_STATIC_DRAW );

    // Positions
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ),
                           ( void* )0 );

    // Normals
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ),
                           ( void* )offsetof( Vertex, normal ) );

    // Texture coords
    glEnableVertexAttribArray( 2 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ),
                           ( void* )offsetof( Vertex, uv ) );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );

    return true;
}

/**
 * @brief Inserts vertex data from parsed model data.
 * @param data Array of strings containing vertex data.
 * @param v Vector of positions.
 * @param vt Vector of texture coordinates.
 * @param vn Vector of normals.
 */
void Mesh::insertData( char* data[3], std::vector< vector3 >& v,
                       std::vector< vector2 >& vt,
                       std::vector< vector3 >& vn ) {

    m_vertices.emplace_back( v[atoi( data[0] ) - 1], vn[atoi( data[2] ) - 1],
                             vt[atoi( data[1] ) - 1] );
}

/**
 * @brief Draws the mesh.
 */
void Mesh::draw() {
    Transform& transform = m_model->owner->transform;
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

    glBindVertexArray( vao );

    glDrawArrays( m_model->getRenderMethod(), 0, vertCount );

    glUseProgram( 0 );

    glBindVertexArray( 0 );
}

/**
 * @brief Sets the shader program for this mesh.
 * @param t_shader Pointer to the shader Program.
 */
void Mesh::setShader( Program* t_shader ) {
    m_shader = std::make_unique< Program >( t_shader );
}

/**
 * @brief Gets the shader program associated with this mesh.
 * @return Pointer to the shader Program.
 */
const Program* Mesh::getShader() const { return m_shader.get(); }

/**
 * @brief Loads and sets the shader from vertex and fragment shader files.
 * @param vertName Vertex shader filename.
 * @param fragName Fragment shader filename.
 */
void Mesh::loadShader( const std::string& vertName,
                       const std::string& fragName ) {
    m_shader = std::make_unique< Program >( vertName, fragName );
}

/**
 * @brief Gets the model name associated with this mesh.
 * @return The model name as a string.
 */
std::string Mesh::getModelName() const { return m_modelName; }

} // namespace SquirrelEngine
