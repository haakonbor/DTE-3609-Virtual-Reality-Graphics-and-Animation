#include "../include/Skybox.h"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/type_ptr.hpp"

#include "../include/Projection.h"

Skybox::Skybox()
{
    auto scale = 5000.0f;
    auto scaling = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));

    matrix_ = scaling;
}

Skybox::~Skybox()
{
}

void Skybox::privateInit()
{
  /* VERTEX BUFFER */
  // Is set up in initialization of object attribute

  /* LAYOUT */
  // 3 floats for world position
  layout.Push<float>(3);

  /* VERTEX ARRAY */
  vao.AddBuffer(vbo, layout);

  /* INDEX BUFFER */
  // Is set up in initialization of object attribute

  /* SHADER */
  shader.Bind();

  /* TEXTURE */
  texture.BindCubemap(textureSlot);
  shader.SetUniform1i("u_Texture", textureSlot);

  /* UNBINDING */
  texture.UnbindCubemap();
  vao.Unbind();
  vbo.Unbind();
  ibo.Unbind();
  shader.Unbind();
}

void Skybox::privateRender()
{
    shader.Bind();
    vao.Bind();
    ibo.Bind();
    texture.BindCubemap(textureSlot);

    shader.SetUniformMat4f("u_ViewMatrix", viewMatrix_);
    shader.SetUniformMat4f("u_ProjectionMatrix", projMatrix_);
    shader.SetUniformMat4f("u_ModelMatrix", matrix_);

    GLCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));

    texture.UnbindCubemap();
    ibo.Unbind();
    vao.Unbind();
    shader.Unbind();
}

void Skybox::privateUpdate()
{
}

