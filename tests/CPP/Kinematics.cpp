#include <Testing.hpp>

using namespace Testing;

TestRunner& runner{TestRunner::getInstance("Kinematics Testing")};

#include <Physics/Object.hpp>
#include <Physics/World.hpp>

int main() {
  runner.addTest("Physics Object Creation and fall for 1.0", []() {
    Engine::GameObject obj("PhysicsTestObject");
    Engine::Physics::World world({0, 0, 9.81});
    Engine::Physics::Object object(obj, 1);

    world.AddObject(&object);

    world.Update(1.0);
    runner.DebugLog("Object velocity.z: " + std::to_string(object.velocity.z));
    runner.DebugLog("Object position.z: " + std::to_string(object.position.z));
    runner.Assert((object.position.z == 4.905f), "Object position should be 4.905");
  });

  runner.addTest("Physics Object Creation with gradual fall for 1.0", []() {
    Engine::GameObject obj("PhysicsTestObject");
    Engine::Physics::World world({0, 0, 9.81});
    Engine::Physics::Object object(obj, 1);

    world.AddObject(&object);

    for (int i = 0; i < 10; ++i) {
      world.Update(0.1);
      runner.DebugLog("Object velocity.z: " + std::to_string(object.velocity.z));
      runner.DebugLog("Object position.z: " + std::to_string(object.position.z));
    }

    runner.Assert((object.position.z == 4.905f), "Object position should be 4.905");
  });

  runner.addTest("Test Static Objects", []() {
    Engine::GameObject obj("PhysicsTestObject");
    Engine::Physics::World world({0, 0, 9.81});
    Engine::Physics::Object object(obj, 1, Engine::Physics::PointMesh(), true);

    world.AddObject(&object);

    world.Update(1.0);
    runner.DebugLog("Object velocity.z: " + std::to_string(object.velocity.z));
    runner.DebugLog("Object position.z: " + std::to_string(object.position.z));
    runner.Assert((object.position.z == 0.0f), "Object should not move");
  });

  return 0;
}
