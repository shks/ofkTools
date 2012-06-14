/*
 *  ofkState.cpp
 *  iPhoneEmptyExample
 *
 *  Created by Shunichi Kasahara on 10/10/17.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofkState.h"


ofkState::ofkState():m_currentState(-1)
{
	
}


ofkState::~ofkState()
{

}

void ofkState::addState(int stateNum,ofkStateCallBack *pInCallBack, ofkStateCallBack *pOutCallBack, ofkStateCallBack *pUpdateCallBack, ofkStateCallBack *pDrawCallBack, void* pUserdata)
{
	//first find defined state
	

	std::map<int, ofkStatePropaty>::iterator it = m_stateMap.find(stateNum);
	
	if(it == m_stateMap.end()){
		//no found == state[stateNum] was not defined yet
		ofkStatePropaty statePropaty;
		statePropaty.pInCallBack = pInCallBack;
		statePropaty.pOutCallBack = pOutCallBack;
		statePropaty.pUpdateCallBack = pUpdateCallBack;
		statePropaty.pDrawCallBack = pDrawCallBack;
		statePropaty.pUserdata = pUserdata;
		m_stateMap.insert( std::pair < int , ofkStatePropaty> ( stateNum, statePropaty ) );
		
	}else{
		//foudn state[stateNum] is already defined, so overwrite it
		ofkStatePropaty *pPropaty = &(it->second);
		pPropaty->pInCallBack = pInCallBack;
		pPropaty->pOutCallBack = pOutCallBack;
		pPropaty->pUpdateCallBack = pUpdateCallBack;
		pPropaty->pDrawCallBack = pDrawCallBack;
		pPropaty->pUserdata = pUserdata;
				
	}
}

void ofkState::changeState(int nextIndex)
{
	
	std::map<int, ofkStatePropaty>::iterator it;
	int previous = m_currentState;
	int next = nextIndex;
	
	if(nextIndex != m_currentState){
		//change different state
		it = m_stateMap.find(previous);
		
		//Out from current State
		if (it != m_stateMap.end()) {
			ofkStatePropaty *pPropaty = &(it->second);
			if(NULL != pPropaty){
				if(NULL != pPropaty->pOutCallBack){
					pPropaty->pOutCallBack(*this,next,pPropaty->pUserdata);
				}
			}
			
		}
				
		//In to Next state
		it = m_stateMap.find(next);
		if (it != m_stateMap.end()) {
			ofkStatePropaty *pPropaty = &(it->second);
			if(NULL != pPropaty){
				if(NULL != pPropaty->pInCallBack){
					pPropaty->pInCallBack(*this,previous,pPropaty->pUserdata);
				}
			}
			
		}
		m_currentState = nextIndex;
	}
}

void ofkState::update()
{
	//@TODO think about cost
	std::map<int, ofkStatePropaty>::iterator it = m_stateMap.find(m_currentState);
	
	if(it != m_stateMap.end()){
		ofkStatePropaty *pPropaty = &(it->second);
		if(NULL != pPropaty){
			if(NULL != pPropaty->pUpdateCallBack){
				pPropaty->pUpdateCallBack(*this,m_currentState,pPropaty->pUserdata);
			}
		}		
	}
}

void ofkState::draw()
{
	//@TODO think about cost
	std::map<int, ofkStatePropaty>::iterator it = m_stateMap.find(m_currentState);
	
	if(it != m_stateMap.end()){
		ofkStatePropaty *pPropaty = &(it->second);
		if(NULL != pPropaty){
			if(NULL != pPropaty->pDrawCallBack){
				pPropaty->pDrawCallBack(*this,m_currentState,pPropaty->pUserdata);
			}
		}		
	}
}

int ofkState::getCurrentState()
{
	return m_currentState;
}


bool ofkState::hasStateDefined(int stateNum)
{
	std::map<int, ofkStatePropaty>::iterator it = m_stateMap.find(stateNum);
	bool res = false;

	if(it != m_stateMap.end()){
		res = true;
	}
	
	return res;
}



