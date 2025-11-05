#include "Line.hpp"
#include "Mesh.hpp"

#include <cmath>

Engine::Graphics::Line::Line(Engine::Vec3f (&lineFunction)(float), float start, float end, float interval, float thickness)
  : Engine::Graphics::Mesh() {

  // Using the following mathematical concepts to create a line:
  // 1. Parametric equations
  // 2. Arc length ||r'(t)||
  float current = start;

  Engine::Vec3f previous = lineFunction(current - interval);
  Engine::Vec3f currentPoint = lineFunction(current);
  Engine::Vec3f nextPoint = lineFunction(current + interval);
  Engine::Vec3f nextNextPoint = lineFunction(current + 2*interval);

  while (current <= end) {
    Engine::Vec3f deltaStart = nextPoint - previous;
    Engine::Vec3f deltaEnd = nextNextPoint - currentPoint;

    // Calculate the direction of each point
    // Approximate f(t)' = f(t+i) - f(t-i)/2i
    // We wont need the 2i here because it's cancelled out in the angle calculation
    float thetaStart = atanf(deltaStart.y/deltaStart.x);
    float thetaEnd = atanf(deltaEnd.y/deltaEnd.x);

    float phiStart = acosf(deltaStart.z/sqrt(deltaStart.lengthSquared()));
    float phiEnd = acosf(deltaEnd.z/sqrt(deltaEnd.lengthSquared()));

    // Angles created and stored in rotStart (for ring1) and rotEnd (for ring2)
    // 0: cos(theta)
    // 1: sin(theta)
    // 2 cos(phi)
    // 3: sin(phi)
    float rotStart[4] = {
      cosf(thetaStart),
      sinf(thetaStart),
      cosf(phiStart),
      sinf(phiStart)
    };

    float rotEnd[4] = {
      cosf(thetaEnd),
      sinf(thetaEnd),
      cosf(phiEnd),
      sinf(phiEnd)
    };

    // Create 2 rings and attach the vertices using the polygons
    // Math has been abstracted. Please look at docs/appA._math.md for more
    // Details
    Engine::Vec3f ring1[4]{
      {rotStart[2]*thickness, rotStart[3]*thickness, 0},
      {rotStart[3]*rotStart[1]*thickness, -rotStart[2]*rotStart[1]*thickness, rotStart[0]*thickness},
      {-rotStart[2]*thickness, -rotStart[3]*thickness, 0},
      {-rotStart[3]*rotStart[1]*thickness, rotStart[2]*rotStart[1]*thickness, -rotStart[0]*thickness}
    };

    Engine::Vec3f ring2[4]{
      {rotEnd[2]*thickness, rotEnd[3]*thickness, 0},
      {rotEnd[3]*rotEnd[1]*thickness, -rotEnd[2]*rotEnd[1]*thickness, rotEnd[0]*thickness},
      {-rotEnd[2]*thickness, -rotEnd[3]*thickness, 0},
      {-rotEnd[3]*rotEnd[1]*thickness, rotEnd[2]*rotEnd[1]*thickness, -rotEnd[0]*thickness}
    };

    AddQuad(
      {ring1[0].x + currentPoint.x, ring1[0].y + currentPoint.y, ring1[0].z + currentPoint.z, 0.0f, 0.0f}, 
      {ring2[0].x + nextPoint.x, ring2[0].y + nextPoint.y, ring2[0].z + nextPoint.z, 0.0f, 0.0f},
      {ring2[1].x + nextPoint.x, ring2[1].y + nextPoint.y, ring2[1].z + nextPoint.z, 0.0f, 0.0f}, 
      {ring1[1].x + currentPoint.x, ring1[1].y + currentPoint.y, ring1[1].z + currentPoint.z, 0.0f, 0.0f}
    );

    AddQuad(
      {ring1[1].x + currentPoint.x, ring1[1].y + currentPoint.y, ring1[1].z + currentPoint.z, 0.0f, 0.0f}, 
      {ring2[1].x + nextPoint.x, ring2[1].y + nextPoint.y, ring2[1].z + nextPoint.z, 0.0f, 0.0f},
      {ring2[2].x + nextPoint.x, ring2[2].y + nextPoint.y, ring2[2].z + nextPoint.z, 0.0f, 0.0f}, 
      {ring1[2].x + currentPoint.x, ring1[2].y + currentPoint.y, ring1[2].z + currentPoint.z, 0.0f, 0.0f}
    );

    AddQuad(
      {ring1[2].x + currentPoint.x, ring1[2].y + currentPoint.y, ring1[2].z + currentPoint.z, 0.0f, 0.0f}, 
      {ring2[2].x + nextPoint.x, ring2[2].y + nextPoint.y, ring2[2].z + nextPoint.z, 0.0f, 0.0f},
      {ring2[3].x + nextPoint.x, ring2[3].y + nextPoint.y, ring2[3].z + nextPoint.z, 0.0f, 0.0f}, 
      {ring1[3].x + currentPoint.x, ring1[3].y + currentPoint.y, ring1[3].z + currentPoint.z, 0.0f, 0.0f}
    );

    AddQuad(
      {ring1[3].x + currentPoint.x, ring1[3].y + currentPoint.y, ring1[3].z + currentPoint.z, 0.0f, 0.0f}, 
      {ring2[3].x + nextPoint.x, ring2[3].y + nextPoint.y, ring2[3].z + nextPoint.z, 0.0f, 0.0f},
      {ring2[0].x + nextPoint.x, ring2[0].y + nextPoint.y, ring2[0].z + nextPoint.z, 0.0f, 0.0f}, 
      {ring1[0].x + currentPoint.x, ring1[0].y + currentPoint.y, ring1[0].z + currentPoint.z, 0.0f, 0.0f}
    );
    current += interval;

    previous = currentPoint;
    currentPoint = nextPoint;
    nextPoint = nextNextPoint;
    nextNextPoint = lineFunction(current + 2*interval);
  }
}
