#include "Line.hpp"
#include "Mesh.hpp"

#include <cmath>

Engine::Graphics::Line::Line(Engine::Vec3f (&lineFunction)(float), float start, float end, float interval, float thickness)
  : Engine::Graphics::Mesh() {

  // Using the following mathematical concepts to create a line:
  // 1. Parametric equations
  // 2. Arc length ||r'(t)||
  float current = start;

  while (current <= end) {
    Engine::Vec3f previous = lineFunction(current - interval);
    Engine::Vec3f currentPoint = lineFunction(current);
    Engine::Vec3f nextPoint = lineFunction(current + interval);
    Engine::Vec3f nextNextPoint = lineFunction(current + 2*interval);

    float thetaStart = atanf((nextPoint.y - previous.y)/(nextPoint.x - previous.x));
    float thetaEnd = atanf((nextNextPoint.y - currentPoint.y)/(nextNextPoint.x - currentPoint.x));

    float phiStart = atanf((nextPoint.z - previous.z)/(nextPoint.x - previous.x));
    float phiEnd = atanf((nextNextPoint.z - currentPoint.z)/(nextNextPoint.x - currentPoint.x));

    Engine::Vec3f offsetStart = {
      cosf(thetaStart),
      sinf(thetaStart),
      cosf(phiStart),
    };

    Engine::Vec3f offsetEnd = {
      cosf(thetaEnd),
      sinf(thetaEnd),
      cosf(phiEnd),
    };

    // Compute points A, B, C, D as Vec3 and then insert the values into the
    // vertices
    //
    // Structure:
    //
    // B-D
    // | |
    // A-C
    Engine::Vec3f a = currentPoint;
    Engine::Vec3f b = currentPoint - (offsetStart*thickness);
    Engine::Vec3f d = nextPoint - (offsetEnd*thickness);
    Engine::Vec3f c = nextPoint;

    AddQuad({a.x, a.y, a.z, 0.0f, 0.0f}, {c.x, c.y-thickness, c.z, 0.0f, 0.0f},
      {a.x, a.y-thickness, a.z, 0.0f, 0.0f}, {c.x, c.y, c.z, 0.0f, 0.0f});
    current += interval;
  }
}
