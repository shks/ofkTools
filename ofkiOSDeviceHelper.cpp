/*
 *  ofkiOSDeviceHelper.cpp
 *
 *  Created by Shunichi Kasahara on 12/10/23.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofkiOSDeviceHelper.h"
#include <assert.h>

ofkiOSDeviceVersion ofkiOSDeviceHelper::m_deviceVersion = ofkiOSDeviceVersion_Unknown;


int ofkiOSDeviceHelper::getARMversion()
{
	int ARMversion = 7;
	
	ofkiOSDeviceVersion version = getDeviceVersion();
	
	if(ofkiOSDeviceVersion_iPhone1G == version ||
	   ofkiOSDeviceVersion_iPhone3G == version ||
	   ofkiOSDeviceVersion_iPod1G == version ||
	   ofkiOSDeviceVersion_iPod2G == version){
		ARMversion = 6;
	}
	
	return ARMversion;
}

/*
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
*/