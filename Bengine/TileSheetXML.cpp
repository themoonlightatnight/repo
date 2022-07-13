#include "TileSheetXML.h"
#include <rapidXML/rapidxml.hpp>
#include <rapidXML/rapidxml_print.hpp>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace rapidxml;
namespace Bengine
{
	const glm::vec2& TileSheetXML::getSpriteDimension(const std::string& spriteSheetPath)
	{
		auto mit = spriteDimsMap.find(spriteSheetPath);
		if (mit == spriteDimsMap.end())
		{
			xml_document<> doc;
			xml_node<>* root_node;
			// Read the xml file into a vector
			std::ifstream theFile(spriteSheetPath);
			std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
			buffer.push_back('\0');
			// Parse the buffer using the xml file parsing library into doc 
			doc.parse<0>(&buffer[0]);
			// Find our root node
			root_node = doc.first_node("TextureAtlas");
			// Iterate over the brewerys
			m_spriteDimension.x = std::stof(root_node->first_attribute("width")->value());
			m_spriteDimension.y = std::stof(root_node->first_attribute("height")->value());
			spriteDimsMap.insert(std::make_pair(spriteSheetPath, m_spriteDimension));
			return m_spriteDimension;
		}
		return mit->second;
	}
	const glm::vec4& TileSheetXML::getPosDesXML(const std::string& spriteSheetPath,const std::string& subName) 
	{
		std::pair<std::string, std::string> newPair(spriteSheetPath, subName);
		auto mit = map.find(newPair);
		if (mit == map.end())
		{
			texture.name = subName;
			xml_document<> doc;
			xml_node<>* root_node;
			// Read the xml file into a vector
			std::ifstream theFile(spriteSheetPath);
			std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
			buffer.push_back('\0');
			// Parse the buffer using the xml file parsing library into doc 
			doc.parse<0>(&buffer[0]);
			// Find our root node
			root_node = doc.first_node("TextureAtlas");
			// Iterate over the brewerys
			glm::vec4 originalPosDes;
			for (xml_node<>* brewery_node = root_node->first_node("sprite"); brewery_node; brewery_node = brewery_node->next_sibling())
			{
				std::string string = brewery_node->first_attribute("n")->value();
				if (string == subName)
				{
					m_uv.x = std::stof(brewery_node->first_attribute("x")->value());
					m_uv.y = std::stof(brewery_node->first_attribute("y")->value());
					m_uv.z = std::stof(brewery_node->first_attribute("w")->value());
					m_uv.w = std::stof(brewery_node->first_attribute("h")->value());
				}
			}
			map.insert(std::make_pair(newPair, m_uv));
			return m_uv;
		}
		return mit->second;
	}
}