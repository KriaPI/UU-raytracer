#pragma once

#include <random>
#include <memory>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/component_wise.hpp>



namespace rt {

class Material;
using Color = glm::vec3;


inline double random_float() {
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_float(float min, float max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_float();
}

glm::vec3 sample_square() {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return glm::vec3(random_float() - 0.5f, random_float() - 0.5f, 0.0f);
}

glm::vec3 random_vector() {
    return glm::vec3(random_float(), random_float(), random_float());
}

glm::vec3 random_vector(float min, float max) {
    return glm::vec3(random_float(min, max), random_float(min, max), random_float(min, max));
}

float length_squared(const glm::vec3& vector) {
    return glm::dot(vector, vector);
}

inline glm::vec3 random_unit_vector() {
    while (true) {
        auto p = random_vector(-1.0f, 1.0f);
        auto lensq = length_squared(p);
        if (1e-37 < lensq && lensq <= 1.0f)
            return p / sqrt(lensq);
    }
}

inline glm::vec3 random_on_hemisphere(const glm::vec3& normal) {
    glm::vec3 on_unit_sphere = random_unit_vector();
    if (glm::dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

bool near_zero(glm::vec3& element) {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (std::fabs(element[0]) < s) && (std::fabs(element[1]) < s) && (std::fabs(element[2]) < s);
}

glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
    return v - 2 * glm::dot(v,n) * n;
}

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

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
        return false;
    }
};

class Lambertian : public Material {
  public:
    Lambertian(const Color& albedo) : albedo(albedo) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (near_zero(scatter_direction))
            scatter_direction = rec.normal;

        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

  private:
    Color albedo;
};

class Metal : public Material {
  public:
    Metal(const Color& albedo, float fuzz) : albedo(albedo), fuzziness(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        glm::vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = glm::normalize(reflected) + (fuzziness * random_unit_vector());
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return (glm::dot(scattered.direction(), rec.normal) > 0.0f);
    }

  private:
    Color albedo;
    float fuzziness;
};


class Hitable {
public:
    virtual bool hit(const Ray &r, float t_min, float t_max, HitRecord &rec) const = 0;
};

} // namespace rt
