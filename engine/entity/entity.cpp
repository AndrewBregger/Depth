#include "entity.hpp"

namespace entity {
	Entity::Entity(Entity* parent, const std::string& name) :
		parent(parent), name(name) {
	}

	Entity::~Entity() = default;

	void Entity::update() {}
	
	void Entity::on_render(gfx::Renderer* renderer) {}

	void Entity::add_component(Component* component) {
		components.push_back(component);
	}

	void Entity::add_child(Entity* child) {
		children.push_back(child);
	}
}
