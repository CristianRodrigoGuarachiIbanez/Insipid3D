#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include "EntityTraits.h"
#include "Serializer.h"
#include <nlohmann/json.hpp>

struct Engine;

struct Entity
{
	Entity();
	Entity(Engine* engine);
	virtual void tick() = 0;
	virtual void render() = 0;
	virtual void init() = 0;
	virtual void remove() = 0;
	virtual nlohmann::json serialize();
	int active;
	int id;
	EntityTraits entityTraits;
	std::string entityType;
	EntityVars vars;
	bool initialised;
	Engine* engine;
};