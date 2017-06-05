#pragma once

/* Forward Declarations */
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btCollisionShape;
class btRigidBody;

// Custom bullet debug
class BulletDebugRender;

// Custom Camera
class Camera;

class PhysicsCubes : public Progbase {
public:

	int start();
	int end();
	int render();
	int update(const double);

private:
	double deltaTime;
	double time;

	GLuint m_vao;
	GLuint m_vbo;

	// Uniforms
	GLuint m_modelViewLocation;
	GLuint m_projectionLocation;
	GLuint m_viewLocation;

	/* Physics Variables */
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicWorld;

	btCollisionShape* groundShape;
	btCollisionShape* ballShape;

	btRigidBody* groundRigidBody;
	btRigidBody* ballRigidBody;

	// Tempor object placement with physics hookup
	float y_pos;

	// Debug renderer for bullet
	BulletDebugRender* m_bulletDebug;

	// Camera Class
	Camera* m_camera;
	float angle;

};