#pragma once

#include "Types.h"
#include "ComponentArray.h"
#include "Component.h"
#include "Helper.h"
#include <memory>

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		// Create a ComponentArray pointer and add it to the component array
		mComponentArrays[T::Id] = std::make_shared<ComponentArray<T>>();
	}

	template<typename T>
	Component GetComponentType()
	{
		// Return this component's type - used for creating signatures
		return T::Id;
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		// Add a component to the array for an entity
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		// Remove a component from the array for an entity
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		// Get a reference to a component from the array for an entity
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& arr : mComponentArrays)
		{
			arr->EntityDestroyed(entity);
		}
	}

private:
	// Array that contains all component arrays
	std::shared_ptr<IComponentArray> mComponentArrays[Component::NumTypes];

	// Convenience function to get the statically casted pointer to the ComponentArray of type T.
	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[T::Id]);
	}
};
