#pragma once

// Precompiled header file. We include this in every C++ file.
// It exists to improve compilation time.

#pragma warning(push, 0)

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define GLM_FORCE_AVX2
#define GLM_FORCE_INLINE
#define GLM_FORCE_NO_CTOR_INIT
#define GLM_ENABLE_EXPERIMENTAL

#include "glm/fwd.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/norm.hpp"

#include "entt/entity/registry.hpp"

#pragma warning(pop)

using ivec2 = glm::ivec2;
using ivec3 = glm::ivec3;
using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using ivec4 = glm::ivec4;
using u8vec2 = glm::u8vec2;
using u8vec3 = glm::u8vec3;
using u8vec4 = glm::u8vec4;
using i16vec2 = glm::i16vec2;
using mat4 = glm::mat4;
