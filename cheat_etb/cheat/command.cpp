#include "command.h"

#include "gvalue.h"

#include <unordered_map>
#include <sstream>

#include "keybind.h"

struct s_value
{
public:
	s_value() = default;
	s_value(void* _value, const std::string& _type)
	{
		value = _value;
		type = _type;
	}
	std::string to_string()
	{
		if (type == "bool")
		{
			bool* ptr = (bool*)(value);
			return *ptr ? "true" : "false";
		}
		if (type == "float")
		{
			float* ptr = (float*)(value);
			return std::to_string(*ptr);
		}
		if (type == "int")
		{
			int* ptr = (int*)(value);
			return std::to_string(*ptr);
		}
		return "";
	}
public:
	void* value = nullptr;
	std::string type = "";
};

std::unordered_map<std::string, s_value> value_map;

command* command::get()
{
	static command inst;
	return &inst;
}

void command::init()
{
#define VALUE_INIT(_name_,_type_) value_map[#_name_] = s_value((void*)&gvalue::_name_, #_type_);

	VALUE_INIT(color_index, int);
	VALUE_INIT(draw_lable, bool);
	VALUE_INIT(new_year_color, bool);
	VALUE_INIT(menu_scale, float);
	VALUE_INIT(menu_scale_buffer, float);

	VALUE_INIT(esp_player.enable, bool);
	VALUE_INIT(esp_player.box, bool);
	VALUE_INIT(esp_player.name, bool);
	VALUE_INIT(esp_player.distance, bool);
	VALUE_INIT(esp_player.line, bool);
	VALUE_INIT(esp_player.extent, bool);

	VALUE_INIT(esp_entity.enable, bool);
	VALUE_INIT(esp_entity.box, bool);
	VALUE_INIT(esp_entity.name, bool);
	VALUE_INIT(esp_entity.distance, bool);
	VALUE_INIT(esp_entity.line, bool);
	VALUE_INIT(esp_entity.extent, bool);

	VALUE_INIT(esp_item.enable, bool);
	VALUE_INIT(esp_item.box, bool);
	VALUE_INIT(esp_item.name, bool);
	VALUE_INIT(esp_item.distance, bool);
	VALUE_INIT(esp_item.line, bool);
	VALUE_INIT(esp_item.extent, bool);

	VALUE_INIT(esp_interact.enable, bool);
	VALUE_INIT(esp_interact.box, bool);
	VALUE_INIT(esp_interact.name, bool);
	VALUE_INIT(esp_interact.distance, bool);
	VALUE_INIT(esp_interact.line, bool);
	VALUE_INIT(esp_interact.extent, bool);

	VALUE_INIT(esp_distance, float);
	VALUE_INIT(draw_mesh, bool);
	VALUE_INIT(fov, float);
	VALUE_INIT(disable_post, bool);
	VALUE_INIT(third_person, bool);
	VALUE_INIT(cam_x, float);
	VALUE_INIT(cam_y, float);
	VALUE_INIT(cam_distance, float);

	VALUE_INIT(inf_energy, bool);
	VALUE_INIT(inf_san, bool);
	VALUE_INIT(inf_health, bool);
	VALUE_INIT(ghost_mode, bool);
	VALUE_INIT(auto_balance, bool);
	VALUE_INIT(inf_jump, bool);
	VALUE_INIT(fly_mode, bool);
	VALUE_INIT(fly_speed, float);
	VALUE_INIT(x_delete, bool);
	VALUE_INIT(walk_speed, float);
	VALUE_INIT(run_speed, float);
	VALUE_INIT(global_speed, float);
	VALUE_INIT(jump_speed, float);
	VALUE_INIT(air_control, float);
	VALUE_INIT(spin, bool);
	VALUE_INIT(spin_speed, float);
	VALUE_INIT(t_pos, bool);
	VALUE_INIT(rb_move, bool);

	VALUE_INIT(entity_speed, float);

#undef VALUE_INIT
}

void command::run(const std::string& cmd)
{
	std::vector<std::string> cmd_list = split(cmd);
	if (cmd_list.size() <= 0)
	{
		return;
	}

	if (cmd_list[0] == "set" && cmd_list.size() == 3)
	{
		auto it = value_map.find(cmd_list[1]);
		if (it == value_map.end())
		{
			printf("[system] find var failed\n");
			return;
		}

#define VAR_CHANGE(_type_,_trans_) \
if (it->second.type == #_type_) \
{ \
	printf("[system] change %s\n",#_type_); \
	_type_* res = reinterpret_cast<_type_*>(it->second.value); \
	(*res) = _trans_; \
	return; \
}

		VAR_CHANGE(bool, cmd_list[2] == "true");
		VAR_CHANGE(float, std::stof(cmd_list[2]));
		VAR_CHANGE(int, std::stoi(cmd_list[2]));

#undef VAR_CHANGE

		printf("[system] find type failed\n");
		return;
	}

	if (cmd_list[0] == "bind")
	{
		const std::string key = cmd_list[1];
		std::vector<std::string> bind_cmd;
		std::string left_string = cmd;
		while (true)
		{
			const size_t left = left_string.find('(');
			const size_t right = left_string.find(')');
			if (left == std::string::npos ||
				right == std::string::npos)
			{
				break;
			}
			const std::string cur_cmd = left_string.substr(left + 1, right - left - 1);
			bind_cmd.emplace_back(cur_cmd);
			left_string = left_string.substr(right + 1);
		}
		printf("bind key : [%s]\n", key.c_str());
		for (const std::string& cur_cmd : bind_cmd)
		{
			printf("bind command : [%s]\n", cur_cmd.c_str());
		}
		keybind::get()->add_bind(key, bind_cmd);
	}
}

std::vector<std::string> command::value_to_cmd()
{
	std::vector<std::string> result;

	for (auto& [key, value] : value_map)
	{
		const std::string& cmd = "set " + key + " " + value.to_string();
		result.push_back(cmd);
		printf("[system] %s\n", cmd.c_str());
	}
	return result;
}

std::vector<std::string> command::split(const std::string& str)
{
	std::vector<std::string> result;
	std::string left_str = str;
	while (true)
	{
		const size_t pos = left_str.find(' ');
		if (pos == std::string::npos)
		{
			result.emplace_back(left_str);
			break;
		}
		result.emplace_back(left_str.substr(0, pos));
		left_str = left_str.substr(pos + 1);
	}
	return result;
}
