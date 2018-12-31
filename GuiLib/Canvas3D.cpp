
#include "Canvas3D.h"

using namespace std;


void Canvas3D::initialize( sf::RenderWindow &window )
{
    Component::initialize( window );

    window.setActive( true );

    glEnable( GL_DEPTH_TEST );
    glDepthMask( GL_TRUE );
    glClearDepth( 1.f );
    glDisable( GL_LIGHTING );

    // Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
    static const GLfloat cube[] =
    {
        -20, -20, -20,
        -20,  20, -20,
        -20, -20,  20,
        -20, -20,  20,
        -20,  20, -20,
        -20,  20,  20,

         20, -20, -20,
         20,  20, -20,
         20, -20,  20,
         20, -20,  20,
         20,  20, -20,
         20,  20,  20,

        -20, -20, -20,
         20, -20, -20,
        -20, -20,  20,
        -20, -20,  20,
         20, -20, -20,
         20, -20,  20,

        -20,  20, -20,
         20,  20, -20,
        -20,  20,  20,
        -20,  20,  20,
         20,  20, -20,
         20,  20,  20,

        -20, -20, -20,
         20, -20, -20,
        -20,  20, -20,
        -20,  20, -20,
         20, -20, -20,
         20,  20, -20,

        -20, -20,  20,
         20, -20,  20,
        -20,  20,  20,
        -20,  20,  20,
         20, -20,  20,
         20,  20,  20
    };

    // Enable position and texture coordinates vertex components
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 3 * sizeof( GLfloat ), cube );

    // Disable normal and color vertex components
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    window.setActive( false );

    window.pushGLStates();
}

void Canvas3D::updateSizeAndPostion( sf::RenderWindow &window )
{
    Component::updateSizeAndPostion( window );

    window.popGLStates();

    window.setActive( true );

    GLfloat viewportWidth = static_cast<GLfloat>( m_actualWidth );
    GLfloat viewportHeight = static_cast<GLfloat>( m_actualHeight );
    GLfloat viewportX = static_cast<GLfloat>( m_actualX );
    GLfloat viewportY = static_cast<GLfloat>( window.getSize().y - m_actualY - m_actualHeight );
    GLfloat ratio = viewportWidth / viewportHeight;

    // Set the viewport
    glViewport( static_cast<GLint>( viewportX ),
                static_cast<GLint>( viewportY ),
                static_cast<GLsizei>( viewportWidth ),
                static_cast<GLsizei>( viewportHeight ) );

    // Setup a perspective projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum( -ratio, ratio, -1.f, 1.f, 1.f, 500.f );

    window.setActive( false );

    window.pushGLStates();
}

void Canvas3D::draw( sf::RenderWindow &window )
{
    Component::draw( window );

    window.popGLStates();

    window.setActive( true );

    // Clear the screen.
    glClear( GL_DEPTH_BUFFER_BIT );

    // Calculate the position of the mouse.
    float x = sf::Mouse::getPosition( window ).x * 200.f / window.getSize().x - 100.f;
    float y = -sf::Mouse::getPosition( window ).y * 200.f / window.getSize().y + 100.f;

    // Setup the model-view matrix.
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Move the cube to the mouse's x and y and away from the camara.
    glTranslatef( x, y, -100.f );

    // Rotate the cube as time passes.
    glRotatef( m_clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f );
    glRotatef( m_clock.getElapsedTime().asSeconds() * 30.f, 0.f, 1.f, 0.f );
    glRotatef( m_clock.getElapsedTime().asSeconds() * 90.f, 0.f, 0.f, 1.f );

    // Draw the cube.
    glDrawArrays( GL_TRIANGLES, 0, 36 );

    window.setActive( false );

    window.pushGLStates();
}