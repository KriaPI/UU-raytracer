#pragma once

#include <memory>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/component_wise.hpp>

namespace rt {

class Material;

struct HitRecord {
    float t;
    glm::vec3 p;
    glm::vec3 normal;
    std::shared_ptr<Material> material;
    bool front_face;
};

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r_in, const HitRecord rec, glm::vec3& attenuation, Ray& scattered) const {
        return false;
    }
};

class Hitable {
public:
    virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const = 0;
};

} // namespace rt
