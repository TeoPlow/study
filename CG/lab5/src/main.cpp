#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <limits>
#include <random>
#include <algorithm>

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
    Vec3 operator/(float s) const { return Vec3(x / s, y / s, z / s); }

    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 normalize() const {
        float length = std::sqrt(x * x + y * y + z * z);
        return Vec3(x / length, y / length, z / length);
    }
};

struct Sphere {
    Vec3 center;
    float radius;
    Vec3 color;

    Sphere(const Vec3& center, float radius, const Vec3& color) : center(center), radius(radius), color(color) {}

    bool intersect(const Vec3& origin, const Vec3& direction, float& t) const {
        Vec3 oc = origin - center;
        float a = direction.dot(direction);
        float b = 2.0f * oc.dot(direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0) return false;
        t = (-b - std::sqrt(discriminant)) / (2.0f * a);
        return t > 0;
    }
};

struct Plane {
    Vec3 point;
    Vec3 normal;
    Vec3 color;

    Plane(const Vec3& point, const Vec3& normal, const Vec3& color) : point(point), normal(normal), color(color) {}

    bool intersect(const Vec3& origin, const Vec3& direction, float& t) const {
        float denom = normal.dot(direction);
        if (std::abs(denom) < 1e-6) return false;
        t = (point - origin).dot(normal) / denom;
        return t > 0;
    }
};

float randomFloat() {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(generator);
}

Vec3 traceRay(const Vec3& origin, const Vec3& direction, const Sphere& sphere, const Plane& plane, const Vec3& lightPos, float lightRadius, int numSamples) {
    float tSphere = std::numeric_limits<float>::max();
    float tPlane = std::numeric_limits<float>::max();

    if (!sphere.intersect(origin, direction, tSphere)) tSphere = std::numeric_limits<float>::max();

    if (!plane.intersect(origin, direction, tPlane)) tPlane = std::numeric_limits<float>::max();

    Vec3 hitColor;
    Vec3 hitPoint;
    Vec3 hitNormal;

    if (tSphere < tPlane) {
        hitPoint = origin + direction * tSphere;
        hitNormal = (hitPoint - sphere.center).normalize();
        hitColor = sphere.color;
    } else if (tPlane < std::numeric_limits<float>::max()) {
        hitPoint = origin + direction * tPlane;
        hitNormal = plane.normal;
        hitColor = plane.color;
    } else {
        return Vec3(0, 0, 0); // Background color
    }

    float shadowFactor = 0.0f;
    for (int i = 0; i < numSamples; i++) {
        Vec3 randomOffset(randomFloat() * lightRadius, randomFloat() * lightRadius, randomFloat() * lightRadius);
        Vec3 sampleLightPos = lightPos + randomOffset;
        Vec3 lightDir = (sampleLightPos - hitPoint).normalize();

        float tShadow;
        if (!sphere.intersect(hitPoint + hitNormal * 1e-3, lightDir, tShadow) &&
            !plane.intersect(hitPoint + hitNormal * 1e-3, lightDir, tShadow)) {
            shadowFactor += 1.0f;
        }
    }
    shadowFactor /= numSamples;

    Vec3 lightDir = (lightPos - hitPoint).normalize();
    float diffuse = std::max(hitNormal.dot(lightDir), 0.0f);

    return hitColor * diffuse * shadowFactor;
}

int main() {
    const int width = 800;
    const int height = 600;
    const int numSamples = 1024;
    const float aspectRatio = float(width) / height;

    Vec3 cameraPos(0, 1, 5);
    Vec3 cameraDir(0, -0.2, -1);

    Sphere sphere(Vec3(0, 1, 0), 1.0f, Vec3(1, 0, 0)); // Red sphere
    Plane plane(Vec3(0, 0, 0), Vec3(0, 1, 0), Vec3(0.5, 0.5, 0.5)); // Gray floor
    Vec3 lightPos(2, 5, -2);
    float lightRadius = 20.5f;

    std::vector<Vec3> image(width * height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float u = (2.0f * (x + 0.5f) / width - 1.0f) * aspectRatio;
            float v = 1.0f - 2.0f * (y + 0.5f) / height;
            Vec3 rayDir = Vec3(u, v, -1).normalize();

            image[y * width + x] = traceRay(cameraPos, rayDir, sphere, plane, lightPos, lightRadius, numSamples);
        }
    }

    std::ofstream outFile("image.ppm");

    if (!outFile) {
        std::cerr << "Ошибка при открытии файла!" << std::endl;
        return 1;
    }

    outFile << "P3\n";
    outFile << width << " " << height << "\n255\n";

    for (const Vec3& pixel : image) {
        int r = static_cast<int>(std::clamp(pixel.x, 0.0f, 1.0f) * 255);
        int g = static_cast<int>(std::clamp(pixel.y, 0.0f, 1.0f) * 255);
        int b = static_cast<int>(std::clamp(pixel.z, 0.0f, 1.0f) * 255);
        outFile << r << " " << g << " " << b << " ";
    }

    outFile.close();
    std::cout << "Изображение сохранено в файл image.ppm" << std::endl;

    return 0;
}
