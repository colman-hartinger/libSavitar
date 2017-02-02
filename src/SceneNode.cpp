#include "SceneNode.h"
#include "../pugixml/src/pugixml.hpp"
#include <iostream>
using namespace Savitar;

SceneNode::SceneNode()
{

}

SceneNode::~SceneNode()
{

}

std::string SceneNode::getTransformation()
{
    return this->transformation;
}

void SceneNode::setStransformation(std::string transformation)
{
    this->transformation = transformation;
}


std::vector<SceneNode> SceneNode::getChildren()
{
    return this->children;
}

SceneNode* SceneNode::getChildByIndex(int index)
{
    if(index < 0 || index >= children.size())
    {
        return NULL;
    }

    return &this->children.at(index);
}

int SceneNode::getNumChildren()
{
    return children.size();
}


void SceneNode::addChild(SceneNode node)
{
    this->children.push_back(node);
}

MeshData* SceneNode::getMeshData()
{
    return &mesh_data;
}

void SceneNode::setMeshData(MeshData mesh_data)
{
    this->mesh_data = mesh_data;
}

void SceneNode::fillByXMLNode(pugi::xml_node xml_node)
{
    settings.clear();
    id = xml_node.attribute("id").as_string();

    if(xml_node.child("mesh"))
    {
        mesh_data.clear();
        mesh_data.fillByXMLNode(xml_node.child("mesh"));
    }

    for(pugi::xml_node setting = xml_node.child("setting"); setting; setting = setting.next_sibling("setting"))
    {
        std::string key = setting.attribute("key").as_string();
        std::string value = setting.text().as_string();
        settings[key] = value;
    }
}

std::string SceneNode::getId()
{
    return this->id;
}

std::map< std::string, std::string > SceneNode::getSettings()
{
    return settings;
}


