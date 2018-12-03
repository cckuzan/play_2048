#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef unsigned int uint32_t;

vector<vector<uint32_t>> origin_data;

void dbg_display_state(vector<vector<uint32_t>> &data)
{
	cout << endl;
	for (auto i = data.begin(); i != data.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			cout << *j << "  ";
		}
		cout << endl;
	}
}

void adapt_value_to_array_index(int value, int &m, int &n)
{
	m = value / 4;
	n = value % 4;
}

void calculate_empty_place(vector<vector<uint32_t>> &data, vector<uint32_t> &empty_place)
{
	empty_place.clear();

	for (auto i = data.begin(); i != data.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			if (*j == 0)
			{
				auto index_i = i - data.begin();
				auto index_j = j - i->begin();
				empty_place.push_back(index_i * 4 + index_j);
			}
		}
	}
}

bool is_empty_place(vector<uint32_t> &empty_place, int place)
{
	bool result = false;

	for (auto i = empty_place.begin(); i != empty_place.end(); ++i)
	{
		if (*i == place)
		{
			result = true;
			break;
		}
			
	}

	return result;
}

void find_empty_place(vector<uint32_t> &empty_place, int &init_value)
{
	if (empty_place.empty())
		return;

	while (!is_empty_place(empty_place, init_value))
	{
		init_value = rand() % 16;
	}
}

void get_next_step(vector<vector<uint32_t>> &data, uint32_t &score)
{
	int m = 0;
	int n = 0;
	int init_value = rand() % 15;
	vector<uint32_t> empty_place;
	calculate_empty_place(data, empty_place);

	find_empty_place(empty_place, init_value);
	
	adapt_value_to_array_index(init_value, m, n);
	auto add_score = rand() % 2;
	if (add_score)
	{
		data[m][n] = 4;
		score += 4;
	} else {
		data[m][n] = 2;
		score += 2;
	}
}

void init_game(vector<vector<uint32_t>> &data, uint32_t &score, uint32_t &step)
{
	srand(time(0));
	data.clear();
	vector<uint32_t> temp;
	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(0);

	origin_data.push_back(temp);
	origin_data.push_back(temp);
	origin_data.push_back(temp);
	origin_data.push_back(temp);
	
	//vector<uint32_t> empty_place;

	get_next_step(data, score);
	get_next_step(data, score);

	step = 0;
}

void move_left(vector<vector<uint32_t>> &data, int i, uint32_t &score)
{
	auto k = 0;
	for (auto j = 0; j < 4; ++j)
	{
		if (data[i][j] != 0)
		{
			data[i][k] = data[i][j];
			++k;
		}
	}

	if (data[i][0] == data[i][1])
	{
		score += data[i][0];
		data[i][0] += data[i][0];
		
		if (data[i][2] == data[i][3])
		{
			score += data[i][2];
			data[i][1] = data[i][2] + data[i][2];
			data[i][2] = 0;
			data[i][3] = 0;
		} else {
			data[i][1] = data[i][2];
			data[i][2] = data[i][3];
			data[i][3] = 0;
		}
	} else if (data[i][2] == data[i][3])
	{
		score += data[i][2];
		data[i][2] += data[i][2];
		data[i][3] = 0;
	}
}

void move_right(vector<vector<uint32_t>> &data, int i, uint32_t &score)
{
	auto k = 3;
	for (auto j = 3; j > -1; --j)
	{
		if (data[i][j] != 0)
		{
			data[i][k] = data[i][j];
			--k;
		}
	}

	if (data[i][3] == data[i][2])
	{
		score += data[i][3];
		data[i][3] += data[i][3];
		
		if (data[i][1] == data[i][0])
		{
			score += data[i][1];
			data[i][2] = data[i][1] + data[i][1];
			data[i][1] = 0;
			data[i][0] = 0;
		} else {
			data[i][2] = data[i][1];
			data[i][1] = data[i][0];
			data[i][0] = 0;
		}
	} else if (data[i][1] == data[i][0])
	{
		score += data[i][1];
		data[i][1] += data[i][1];
		data[i][0] = 0;
	}
}

void move_up(vector<vector<uint32_t>> &data, int i, uint32_t &score)
{
	auto k = 0;
	for (auto j = 0; j < 4; ++j)
	{
		if (data[j][i] != 0)
		{
			data[k][i] = data[j][i];
			++k;
		}
	}

	if (data[0][i] == data[1][i])
	{
		score += data[0][i];
		data[0][i] += data[0][i];
		
		if (data[2][i] == data[3][i])
		{
			score += data[2][i];
			data[1][i] = data[2][i] + data[2][i];
			data[2][i] = 0;
			data[3][i] = 0;
		} else {
			data[1][i] = data[2][i];
			data[2][i] = data[3][i];
			data[3][i] = 0;
		}
	} else if (data[2][i] == data[3][i])
	{
		score += data[2][i];
		data[2][i] += data[2][i];
		data[3][i] = 0;
	}
}

void move_down(vector<vector<uint32_t>> &data, int i, uint32_t &score)
{
	auto k = 3;
	for (auto j = 3; j > -1; --j)
	{
		if (data[j][i] != 0)
		{
			data[k][i] = data[j][i];
			--k;
		}
	}

	if (data[3][i] == data[2][i])
	{
		score += data[3][i];
		data[3][i] += data[3][i];
		
		if (data[1][i] == data[0][i])
		{
			score += data[1][i];
			data[2][i] = data[1][i] + data[1][i];
			data[1][i] = 0;
			data[0][i] = 0;
		} else {
			data[2][i] = data[1][i];
			data[1][i] = data[0][i];
			data[0][i] = 0;
		}
	} else if (data[1][i] == data[0][i])
	{
		score += data[1][i];
		data[1][i] += data[1][i];
		data[0][i] = 0;
	}
}

uint32_t is_game_over(vector<vector<uint32_t>> &data)
{
	uint32_t result = 1;
	for (auto i = data.begin(); i != data.end(); ++i)
	{
		for (auto j = i->begin(); j != i->end(); ++j)
		{
			if (*j == 0)
			{
				result = 0;
				return result;
			}
		}
	}

	if (result)
	{
		for (auto i = 0; i < 4; ++i)
		{
			for (auto j = 0; j < 3; ++j)
			{
				if (data[i][j] == data[i][j + 1])
				{
					result = 0;
					return result;
				}
			}
		}

		for (auto i = 0; i < 4; ++i)
		{
			for (auto j = 0; j < 3; ++j)
			{
				if (data[j][i] == data[j + 1][i])
				{
					result = 0;
					return result;
				}
			}
		}
	}

	return result;
}

uint32_t get_next_oper(char oper, vector<vector<uint32_t>> &data, uint32_t &score, uint32_t &step)
{
	uint32_t result = 0;

	if (oper == 'a')
	{
		for (auto i = 0; i < 4; ++i)
		{
			move_left(data, i, score);
		}
	}

	if (oper == 's')
	{
		for (auto i = 0; i < 4; ++i)
		{
			move_down(data, i, score);
		}
	}

	if (oper == 'd')
	{
		for (auto i = 0; i < 4; ++i)
		{
			move_right(data, i, score);
		}
	}

	if (oper == 'w')
	{
		for (auto i = 0; i < 4; ++i)
		{
			move_up(data, i, score);
		}
	}

	get_next_step(data, score);

	result = is_game_over(data);

	++step;
	return result;
}

int main()
{
	char opers[] = {'a', 's', 'd', 'w'};
	uint32_t score = 0;
	uint32_t step = 0;
	init_game(origin_data, score, step);

	auto i = 0;
	for (; i < 1000; ++i)
	{
        if(get_next_oper(opers[rand() % 4], origin_data, score, step) != 0)
			break;
	}

	dbg_display_state(origin_data);
	cout << score << endl;
	cout << step << endl;

	return 0;
}