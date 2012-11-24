/*
 *  ofkiOSDeviceHelper.h
 *
 *  Created by Shunichi Kasahara on 12/10/23.
 *  Copyright 2010 Shunichi Kasahara. All rights reserved.
 *
 */


#pragma once

#include "ofMain.h"

typedef enum{
	ofkiOSDeviceVersion_Unknown = -1,
	ofkiOSDeviceVersion_iPhone1G,
	ofkiOSDeviceVersion_iPhone3G,
	ofkiOSDeviceVersion_iPhone3GS,
	ofkiOSDeviceVersion_iPhone4G,
	ofkiOSDeviceVersion_iPhone4GS,
	ofkiOSDeviceVersion_iPhone5,
	ofkiOSDeviceVersion_iPod1G,
	ofkiOSDeviceVersion_iPod2G,
	ofkiOSDeviceVersion_iPod3G,
	ofkiOSDeviceVersion_iPod4G,
	ofkiOSDeviceVersion_iPod5G,
	ofkiOSDeviceVersion_iPad1G,
	ofkiOSDeviceVersion_iPad2G,
	ofkiOSDeviceVersion_iPad3G
} ofkiOSDeviceVersion;


class ofkiOSDeviceHelper{
	
public:
	
    static ofkiOSDeviceVersion getDeviceVersion(){return m_deviceVersion;}
	static void setDeviceVersion(ofkiOSDeviceVersion deviceVersion){m_deviceVersion = deviceVersion;}
	static int getARMversion();
    
    static ofkiOSDeviceVersion m_deviceVersion;
	
    
};

