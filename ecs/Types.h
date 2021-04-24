#pragma once
#include <cstdint>
#include <bitset>

// ECS defines
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 170010U;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = -1;	// -1 to create underflow to get max value
using Signature = std::bitset<MAX_COMPONENTS>;	// Track which components an entity has and which component is important for a system