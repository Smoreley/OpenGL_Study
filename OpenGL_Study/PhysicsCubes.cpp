#include "Progbase.h"
#include "PhysicsCubes.h"
#include "Helper.h"

/* Bullet Physics Library */
#include <btBulletDynamicsCommon.h>

int PhysicsCubes::start() {
	std::cout << "Physics Cubes Demo" << std::endl;

	/* OpenGL */
	rendering_program = Helper::compileShaders("camera.vert", "simplecolor.frag");




	/* Physics */
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;

	dynamicWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicWorld->setGravity(btVector3(0, -10, 0));

	/* Physics Objects */
	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	ballShape = new btSphereShape(1);

	// Ground
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicWorld->addRigidBody(groundRigidBody);	// Add the ground rigidbody to the world

	// Ball
	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
	btScalar mass = 1;
	btVector3 ballInertia(0, 0, 0);
	btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(mass, ballMotionState, ballShape, ballInertia);
	ballRigidBody = new btRigidBody(ballRigidBodyCI);
	dynamicWorld->addRigidBody(ballRigidBody);


	return EXIT_SUCCESS;
}

int PhysicsCubes::end() {


	// Cleanup
	dynamicWorld->removeRigidBody(ballRigidBody);		// Remove Ball
	delete ballRigidBody->getMotionState();
	delete ballRigidBody;

	dynamicWorld->removeRigidBody(groundRigidBody);		// Remove Ground
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;

	delete groundShape;									// Delete Shapes
	delete ballShape;

	/* Clean up the Physics */
	delete dynamicWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;

	return EXIT_SUCCESS;
}

int PhysicsCubes::render() {
	// Clear
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);

	return EXIT_SUCCESS;
}

int PhysicsCubes::update(const double dtime) {
	deltaTime = dtime;
	time += deltaTime;


	// Stepping through the simulation
	//for (int i = 0; i < 100; i++) {
		dynamicWorld->stepSimulation(1 / 60.0f, 10);

		btTransform trans;
		ballRigidBody->getMotionState()->getWorldTransform(trans);
		std::cout << "Sphere Height: " << trans.getOrigin().getY() << std::endl;
	//}



	return EXIT_SUCCESS;
}