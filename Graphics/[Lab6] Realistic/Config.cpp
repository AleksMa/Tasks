#include "Config.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

Config::Config(std::string path) : sphere_velocity(0,0,0), sphere_pos(0,0,0)
{
	std::ifstream file;
	file.open(path);
	if (!file.is_open()) {
		std::cerr << "can not open file" << std::endl;
		return;
	}

	std::string line;
	std::stringstream stream;
	stream << file.rdbuf();
	file.close();
	boost::property_tree::ptree json_conf;
	boost::property_tree::read_json(stream, json_conf);

	sphere_velocity.x = json_conf.get<GLfloat>("sphere.speed.x");
	sphere_velocity.y = json_conf.get<GLfloat>("sphere.speed.y");
	sphere_velocity.z = json_conf.get<GLfloat>("sphere.speed.z");

	sphere_pos.x = json_conf.get<GLfloat>("sphere.position.x");
	sphere_pos.y = json_conf.get<GLfloat>("sphere.position.y");
	sphere_pos.z = json_conf.get<GLfloat>("sphere.position.z");

	file.close();
}

void Config::save_config(std::string path)
{
	boost::property_tree::ptree json_conf;

	json_conf.put("sphere.speed.x", sphere_velocity.x);
	json_conf.put("sphere.speed.y", sphere_velocity.y);
	json_conf.put("sphere.speed.z", sphere_velocity.z);

	json_conf.put("sphere.position.x", sphere_pos.x);
	json_conf.put("sphere.position.y", sphere_pos.y);
	json_conf.put("sphere.position.z", sphere_pos.z);

	std::ofstream file(path);
	boost::property_tree::write_json(file, json_conf);
	file.close();
}

void Config::load_config(std::string path)
{
	
}


Config::~Config()
{
}
