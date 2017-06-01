#include "Progbase.h"
#include "PhysicsCubes.h"
#include "Helper.h"

#include "BulletDebugRender.h"

/* Bullet Physics Library */
#include <btBulletDynamicsCommon.h>

int PhysicsCubes::start() {
	std::cout << "Physics Cubes Demo" << std::endl;

	/* OpenGL */
	rendering_program = Helper::compileShaders("camera.vert", "depthvisualization.frag");

	/* Uniforms */
	m_modelViewLocation = glGetUniformLocation(rendering_program, "u_mv_matrix");
	m_projectionLocation = glGetUniformLocation(rendering_program, "u_proj_matrix");
	m_viewLocation = glGetUniformLocation(rendering_program, "u_view_matrix");

	/* Vertex Arrays */
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	/* Cube Vertex */
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Helper::cube_vp), Helper::cube_vp, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	/* Physics */
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;

	dynamicWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicWorld->setGravity(btVector3(0, -10, 0));

	// Set debugger 
	m_BulletDebug = new BulletDebugRender();
	dynamicWorld->setDebugDrawer(m_BulletDebug);

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

	// Debug Render Test
	m_BulletDebug->Test_init();

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

	// Cleanup bullet debug renderer
	delete m_BulletDebug;

	/* Cleanup rendering stuff */
	glUseProgram(0);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteProgram(rendering_program);

	return EXIT_SUCCESS;
}

int PhysicsCubes::render() {
	// Clear
	glClearBufferfv(GL_COLOR, 0, clear_color);
	glClearBufferfv(GL_DEPTH, 0, &one);


	/* Render */
	glUseProgram(rendering_program);
	glBindVertexArray(m_vao);

	// Projection
	glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(proj));

	float r = 10.0f;
	// view
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(
		glm::vec3(r, 5.0f,r),
		glm::vec3(0.0f),
		glm::vec3(0.0, 1.0, 0.0));
	glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	// Model View
	glm::mat4 mv = glm::mat4(1.0f);
	mv = glm::translate(mv, glm::vec3(0, y_pos, 0));
	glUniformMatrix4fv(m_modelViewLocation, 1, GL_FALSE, glm::value_ptr(mv));

	// Wireframe
	glLineWidth(1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawArrays(GL_TRIANGLES, 0, (sizeof(Helper::cube_vp) / sizeof(float)) / 3);
	

	// Drawing line
	m_BulletDebug->Test_rend();
	
	dynamicWorld->debugDrawWorld();

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
		//std::cout << "Sphere Height: " << trans.getOrigin().getY() << std::endl;
		y_pos = trans.getOrigin().getY();
	//}



	return EXIT_SUCCESS;
}