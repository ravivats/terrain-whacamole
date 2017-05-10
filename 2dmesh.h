#pragma once

#include <GL/glew.h>
#include <vector>

std::vector<float> Gen2DMesh(int subdiv)
{


	//Calculate positions of triangles
	std::vector<float> posdata;

	//Generate Position data
	float x_offset = -1.0f, y_offset = -1.0f;
	float delta = 2.0f / subdiv;

	float tx_offset = 0.0f;
	float ty_offset = 0.0f;
	float tdelta = 1.0f / subdiv;

	for (int x = 0; x < subdiv; x++)
	{
		for (int y = 0; y < subdiv; y++)
		{
			posdata.push_back(x_offset); posdata.push_back(y_offset); posdata.push_back(0.0f);
			posdata.push_back(tx_offset); posdata.push_back(ty_offset);

			posdata.push_back(x_offset + delta); posdata.push_back(y_offset); posdata.push_back(0.0f);
			posdata.push_back(tx_offset + tdelta); posdata.push_back(ty_offset);

			posdata.push_back(x_offset); posdata.push_back(y_offset + delta); posdata.push_back(0.0f);
			posdata.push_back(tx_offset); posdata.push_back(ty_offset + tdelta);

			posdata.push_back(x_offset); posdata.push_back(y_offset + delta); posdata.push_back(0.0f);
			posdata.push_back(tx_offset); posdata.push_back(ty_offset + tdelta);

			posdata.push_back(x_offset + delta); posdata.push_back(y_offset); posdata.push_back(0.0f);
			posdata.push_back(tx_offset + tdelta); posdata.push_back(ty_offset);

			posdata.push_back(x_offset + delta); posdata.push_back(y_offset + delta); posdata.push_back(0.0f);
			posdata.push_back(tx_offset + tdelta); posdata.push_back(ty_offset + tdelta);

			y_offset += delta;

			ty_offset += tdelta;
		}
		x_offset += delta;
		y_offset = -1.0f;

		tx_offset += tdelta;
		ty_offset = 0.0f;
	}

	return posdata;
}