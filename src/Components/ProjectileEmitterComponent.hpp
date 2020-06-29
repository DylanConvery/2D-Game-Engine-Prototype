#ifndef PROJECTILEEMITTERCOMPONENT
#define PROJECTILEEMITTERCOMPONENT

#include "../../lib/glm/glm.hpp"
#include "../EntityManager.hpp"

class ProjectileEmitterComponent : public Component {
   public:
    ProjectileEmitterComponent(int speed, int range, int angle, bool loop);
    ~ProjectileEmitterComponent() override;
    void initialize() override;
    void update(float delta_time) override;
    void render() override;

   private:	
	TransformComponent* _transform;
	glm::vec2 _origin;
	int _speed;
	int _range;
	float _angle_radians;
	bool _loop;
};

#endif  // !PROJECTILEEMITTERCOMPONENT