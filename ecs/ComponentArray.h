#pragma once

#include "Types.h"
#include "Helper.h"
#include <vector>
#include <cassert>

// An interface is needed so that the ComponentManager
// can tell a generic ComponentArray that an entity has been destroyed
// and that it needs to update its array mappings.
class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray
{
public:
    void InsertData(Entity entity, T component)
    {
        assert(!Helper::find(mEntityToIndexMap, entity) && "Component added to same entity more than once.");

        // Put new entry at the end and update the mappings
        size_t newIndex = mSize;
        if (mEntityToIndexMap.size() <= entity)
        {
            mEntityToIndexMap.resize(entity + 1);
        }
        mEntityToIndexMap[entity] = newIndex;
        if (mIndexToEntityMap.size() <= newIndex)
        {
            mIndexToEntityMap.resize(newIndex + 1);
        }
        mIndexToEntityMap[newIndex] = entity;
        if (mComponentArray.size() <= newIndex)
        {
            mComponentArray.resize(newIndex + 1);
        }
        mComponentArray[newIndex] = component;
        ++mSize;
    }

    void RemoveData(Entity entity)
    {
        assert(!Helper::find(mEntityToIndexMap, entity) && "Removing non-existent component.");

        // Copy element at the end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
        size_t indexOfLastElement = mSize - 1;
        mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

        // Update mappings to point to moved spot
        Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
        mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        mEntityToIndexMap.erase(mEntityToIndexMap.begin() + entity);
        mIndexToEntityMap.erase(mIndexToEntityMap.begin() + indexOfLastElement);

        --mSize;
    }

    T& GetData(Entity entity)
    {
        assert(!Helper::find(mEntityToIndexMap, entity) && "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return mComponentArray[mEntityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override
    {
        if (Helper::find(mEntityToIndexMap, entity))
        {
            // Remove the entity's component if it existed
            RemoveData(entity);
        }
    }

private:
    // The packed array of components (of generic type T),
    std::vector<T> mComponentArray;

    std::vector<size_t> mEntityToIndexMap;
    std::vector<Entity> mIndexToEntityMap;

    // Total size of valid entries in the array.
    size_t mSize = 0;

};