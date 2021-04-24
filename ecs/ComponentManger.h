#pragma once

#include "Types.h"
#include "ComponentArray.h"
#include "Component.h"
#include <unordered_map>
#include <memory>

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		//const char* typeName = typeid(T).name();

		//assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once.");

		// Add this component type to the component type map
		mComponentTypes[T::Id] = mNextComponentType;

		// Create a ComponentArray pointer and add it to the component arrays map
		mComponentArrays[T::Id] = new ComponentArray<T>();

		// Increment the value so that the next component registered will be different
		++mNextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		//const char* typeName = typeid(T).name();

		//assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		// Return this component's type - used for creating signatures
		return mComponentTypes[T::Id];
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
	// Map from type string pointer to a component type
	ComponentType mComponentTypes[Component::Num];

	// Vector that contains all component arrays
	IComponentArray* mComponentArrays[Component::Num];

	// The component type to be assigned to the next registered component - starting at 0
	ComponentType mNextComponentType{};

	// Convenience function to get the statically casted pointer to the ComponentArray of type T.
	template<typename T>
	ComponentArray<T>* GetComponentArray()
	{
		//const char* typeName = typeid(T).name();

		//assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

		return static_cast<ComponentArray<T>*>(mComponentArrays[T::Id]);
	}
};
