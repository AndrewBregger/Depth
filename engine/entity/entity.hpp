#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "common.hpp"
#include "component.hpp"

#include <vector>
#include <type_traits>
#include <glm/glm.hpp>

namespace gfx {
	class Renderer;
}

namespace entity {
    
	struct Transform {
		/// game world position
		glm::vec2 position;
		/// game world rotation
		f32 rotation;
		/// entity scale.
		glm::vec2 scale;
	};
    
	class Entity {
		public:
        /// Entity constructor, a game object. used to represent 
        /// object behaivor.
        /// 
        /// name: name of the entity
        explicit Entity(Entity* entity = nullptr, const std::string& name = "");
		
        virtual ~Entity();
		
        /// update this entity for the next frame.
        /// delta: the change in time for this update. 
        virtual void update(f32 delta);
        
        /// how this entity should be shown.
        virtual void on_render(gfx::Renderer* renderer);
        
        /// gets the entity transform;
        inline const Transform& transform();
		
        /// sets position of entity in world space.
        inline void set_position(const glm::vec2& position);
		
        /// sets rotation of the entity relative to center (maybe give anchor)
        inline void set_rotation(f32 theta);
		
        /// set size of entity.
        inline void set_size(glm::vec2 size);
        
        /// add a component to this entity
        /// component: component to be added.
        void add_component(Component* component);
        
        /// remove a component of type Comp from this entity.
        template <typename Comp>
			void remove_component();
        
        /// find a component of type Comp from this entity.
        template <typename Comp>
			Comp* find_component();
        
        /// add an entity as child to this entity
        void add_child(Entity* child);
        
        /// remove child entity of type Ent from this entity
        template <typename Ent>
			void remove_child();
        
        /// find entity of type Ent from entity, returns null if not found.
        template <typename Ent>
			Ent* find_child();
        
        /// returns the name of this entity.
        inline const std::string& get_name();
        
        /// sets the state
        /// state: true for enabled, false for disabled.
        inline void set_state(bool state);
		
        /// returns the current state.
        inline bool get_state();
        
        template <typename Ent>
			std::vector<Entity*>::iterator find_child_helper();
        
        template <typename Comp>
			std::vector<Component*>::iterator find_component_helper();
        
		private:
        /// parent entity
        Entity* parent;
        /// entity name
        std::string name;
        /// entity world transformation
        Transform world_transform;
        /// components of the entity
        std::vector<Component*> components;
        /// the children entity of this entity.
        std::vector<Entity*> children;
        /// the current state
        /// Currently state is only can be enable and disabled.
        bool enabled;
	};
    
	inline const std::string& Entity::get_name() { return name; }
    
	inline void  Entity::set_state(bool state) {
		enabled = state;
	}
    
	inline bool Entity::get_state() {
		return enabled;
	}
    
	template <typename Comp>
        void Entity::remove_component() {
		auto comp = find_component_helper<Comp>();
		// optimize. Since the order of components doesn't matter.
		// we swap the elemnt with the end and pop off the end
		if(comp != components.end())
			components.erase(comp);
	}
	
	template <typename Comp>
        Comp* Entity::find_component() {
		auto comp = find_component_helper<Comp>();
		if(comp == components.end())
			return nullptr;
		return static_cast<Comp*>(*comp);
	}
    
	template <typename Ent>
        void Entity::remove_child() {
		auto iter = find_child_helper<Ent>();
        
		// optimize. Since the order of entity doesn't matter.
		// we swap the elemnt with the end and pop off the end
		if(iter != children.end())
			children.erase(iter);
	}
	
	template <typename Ent>
        Ent* Entity::find_child() {
		auto iter = find_child_helper<Ent>();
		if (iter == children.end())
			return nullptr;
		return static_cast<Ent*>(*iter);
	}
    
	template <typename Ent>
        std::vector<Entity*>::iterator Entity::find_child_helper() {
        static_assert(std::is_base_of<Entity, Ent>::value, "Type parameter must be a subtype of Entity");
		return std::find_if(children.begin(), children.end(), [](auto entity) {
                            return dynamic_cast<Ent*>(entity) != nullptr;
                            });
	}
    
	template <typename Comp>
        std::vector<Component*>::iterator Entity::find_component_helper() {
		static_assert(std::is_base_of<Component, Comp>::value, "Type parameter must be a subtype of Component");
        return std::find_if(components.begin(), components.end(), [](auto comp) {
                            return dynamic_cast<Comp*>(comp) != nullptr;
                            });
	}
    
	inline const Transform& Entity::transform() {
		return world_transform;
	}
    
	inline void Entity::set_position(const glm::vec2& position) {
		world_transform.position = position;
	}
    
	inline void Entity::set_rotation(f32 theta) {
		world_transform.rotation = theta;
	}
    
	inline void Entity::set_size(glm::vec2 size) {
		world_transform.scale = size;
	}
}

#endif
