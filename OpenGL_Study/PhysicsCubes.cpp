#include "Progbase.h"
#include "PhysicsCubes.h"
#include "Helper.h"
#include "Camera.h"

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

	// Camera setup
	m_camera = new Camera();

	m_camera->SetPosition(glm::vec3(0, 2, 2));
	m_camera->SetUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
	m_camera->SetLookAtTarget(glm::vec3(0.0));

	/* Physics */
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;

	dynamicWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicWorld->setGravity(btVector3(0, -10, 0));

	// Set debugger 
	m_bulletDebug = new BulletDebugRender();
	m_bulletDebug->SetCamera(m_camera);							// Set Camera
	dynamicWorld->setDebugDrawer(m_bulletDebug);
	dynamicWorld->getDebugDrawer()->setDebugMode(1);			// Draw Wireframe

	/* Physics Objects */
	groundShape = new btStaticPlaneShape(btVector3(0, 1.0, 0), 1.0);
	ballShape = new btSphereShape(1.0);

	// Ground Physics/Collision setup
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicWorld->addRigidBody(groundRigidBody);	// Add the ground rigidbody to the world

	// Ball Physics/Collision setup
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

	// Cleanup bullet debug renderer
	delete m_bulletDebug;

	delete m_camera;

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
	//glm::mat4 proj = glm::perspective(1.0472f, 1280.0f / 720.0f, 0.1f, 100.0f);
	//glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(proj));


	//glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjectionMatrix()));
	//glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_camera->GetViewMatrix()));

	glUniformMatrix4fv(m_viewLocation, 1, GL_FALSE, glm::value_ptr(m_camera->GetMatrix()));



	// Model View
	glm::mat4 mv = glm::mat4(1.0f);
	mv = glm::translate(mv, glm::vec3(0, y_pos, 0));
	glUniformMatrix4fv(m_modelViewLocation, 1, GL_FALSE, glm::value_ptr(mv));

	// Wireframe
	//glLineWidth(1.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, (sizeof(Helper::cube_vp) / sizeof(float)) / 3);
	

	// Drawing line
	//m_BulletDebug->Test_rend();
	dynamicWorld->debugDrawWorld();
	m_bulletDebug->RenderMe();


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

	if (bmap.rot_left) {
		ballRigidBody->applyForce(btVector3(0.0, 0.0, 100.0), btVector3(0.0, 0.0, 0.0) );
	}
	
	// Rotation
	if (bmap.rot_left) { angle += deltaTime * 1.0f;	}
	if (bmap.rot_right) { angle -= deltaTime * 1.0f; }

	// Input for moving Camera
	if (bmap.up) { m_camera->SetPosition(glm::vec3(0.0, 0.0, 1.0) + m_camera->GetPosition()); }
	if (bmap.down) { m_camera->SetPosition(glm::vec3(0.0, 0.0, -1.0) + m_camera->GetPosition()); }

	m_camera->SetLookAtTarget(m_camera->GetPosition() + glm::normalize(glm::vec3(sin(angle), 0.0f, cos(angle))));


	return EXIT_SUCCESS;
}