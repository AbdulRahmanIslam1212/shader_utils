#pragma once
#include <string>
#include <glad/gl.h>

namespace shader_utils {
  struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
  };
  enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

  ShaderProgramSource ParseShader(const std::string &filepath);
  unsigned int CompileShader(unsigned int type, const std::string &source);
  unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
}
