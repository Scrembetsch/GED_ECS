#pragma once
#include <cstdint>
#include <bitset>
#include "Component.h"

// ECS defines
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 500000U;
using Signature = std::bitset<Component::NumTypes>;	// Track which components an entity has and which component is important for a system