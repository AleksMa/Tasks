#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include "Base.h"

class Config
{
public:
	Config(std::string path);

	void save_config(std::string path);
	void load_config(std::string path);

	Vector sphere_velocity;
	Vector sphere_pos;

	~Config();
};

