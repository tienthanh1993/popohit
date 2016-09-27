//
//  GameManager.cpp
//  Skeleton
//
//  Created by Pham Thanh on 4/16/16.
//
//

#include "GameManager.hpp"

GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager()
{
    Score = 0;
    Stage = 0;
    RequireScore = 2000;
     Timer = 90;
     CurrentTimer= 90;
    ValueMap dic = FileUtils::getInstance()->getValueMapFromFile("text/mouse.xml");
    int total = dic.size();
    for (int i=0;i<MAX_MOUSE;i++)
    {
        ValueMap m =dic.at(String::createWithFormat("%d",i)->getCString()).asValueMap();
        mouseList[i].id = i;
        mouseList[i].speed = m.at("speed").asFloat();
        mouseList[i].point_type = m.at("point_type").asInt();
        mouseList[i].point = m.at("point").asInt();
        mouseList[i].die  = m.at("die").asString();
        mouseList[i].live  = m.at("live").asString();
    }
}

GameManager* GameManager::getInstance()
{
    //If the singleton has no instance yet, create one
    if(NULL == m_mySingleton)
    {
        //Create an instance to the singleton
        m_mySingleton = new GameManager();
    }
    
    //Return the singleton object
    return m_mySingleton;
}