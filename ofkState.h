/*
 *  ofkState.h
 *  iPhoneEmptyExample
 *
 *  Created by Shunichi Kasahara on 10/10/17.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _KS_STATE_H_
#define _KS_STATE_H_

#include <map>

class ofkState{
	
public:
	
	/**
	 * define state update and change callback, type
	 * &state is referemce for this state instance
	 * 
	 */
	typedef void ofkStateCallBack(ofkState &state, int relativeState, void *pUserdata);
	
	//mean of code : we call function such that has input (ofkState &state, int relativeState, void *pUserdata)
	//and return void, "ofkStateCallBack"
	
	
	/**
	 * Constructor
	 */
	ofkState();
	
	/**
	 * Destructor
	 */
	virtual ~ofkState();
	
	/**
	 * Define new State
	 */
	void addState(int stateNum,ofkStateCallBack *pInCallBack,ofkStateCallBack *pOutCallBack,ofkStateCallBack *pUpdateCallBack,ofkStateCallBack *pDrawCallBack, void* pUserdata);
	
	/**
	 * 	change state
	 */
	void changeState(int index);
	
	/**
	 *	call update
	 */
	void update();
	
	/**
	 * call draw
	 */
	void draw();
	
	/**
	 * 
	 */
	int getCurrentState();
	
	
	/**
	 * return 
	 */
	bool hasStateDefined(int stateNum);
	
protected:
	
	typedef struct _ofkStatePropaty{
		ofkStateCallBack *pInCallBack;
		ofkStateCallBack *pOutCallBack;
		ofkStateCallBack *pUpdateCallBack;
		ofkStateCallBack *pDrawCallBack;
		void *pUserdata;
	} ofkStatePropaty;
	
	std::map<int, ofkStatePropaty> m_stateMap;
	int m_currentState;
	
};
#endif //_KS_STATE_H_