#include "../include/Billboard.h"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/type_ptr.hpp"

Billboard::Billboard()
{

}

Billboard::~Billboard()
{
}

void Billboard::privateInit()
{
  /* VERTEX BUFFER */
  // Is set up in initialization of object attribute

  /* LAYOUT */
  // 2 floats for world position
  layout.Push<float>(3);
  // 2 floats for texture position
  layout.Push<float>(2);

  /* VERTEX ARRAY */
  vao.AddBuffer(vbo, layout);

  /* INDEX BUFFER */
  // Is set up in initialization of object attribute

  /* SHADER */
  shader.Bind();

  /* TEXTURE */
  texture.Bind(textureSlot);
  shader.SetUniform1i("u_Texture", textureSlot);

  /* UNBINDING */
  texture.Unbind();
  vao.Unbind();
  vbo.Unbind();
  ibo.Unbind();
  shader.Unbind();
}

void Billboard::privateRender()
{
    if (draw_) {
        shader.Bind();
        vao.Bind();
        ibo.Bind();
        texture.Bind(textureSlot);

        GLCall(glDrawElements(GL_QUADS, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

        texture.Unbind();
        ibo.Unbind();
        vao.Unbind();
        shader.Unbind();
    }
}

void Billboard::privateUpdate()
{

}

