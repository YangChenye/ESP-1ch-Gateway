// 1-channel LoRa Gateway for ESP8266 and ESP32
// Copyright (c) 2016-2021 Maarten Westenberg version for ESP8266 and ESP32
//
// based on work done by Thomas Telkamp for Raspberry PI 1ch gateway
// and many other contributors.
//
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the MIT License
// which accompanies this distribution, and is available at
// https://opensource.org/licenses/mit-license.php
//
// NO WARRANTY OF ANY KIND IS PROVIDED
//
// Author: Maarten Westenberg (mw12554@hotmail.com)
//
// This file contains a number of compile-time settings and declarations that are'
// specific to the LoRa rfm95, sx1276, sx1272 radio of the gateway.
//
//
// ------------------------------------------------------------------------------------

// It is possible to use the gateway as a normal sensor node also. In this case,
// substitute the node info below.
#if _GATEWAYNODE==1
	// Valid coding for internal sensors are LCODE and RAW.
	// Make sure to only select one.
#	define _LCODE 1
//#	define _RAW 1
#	define _CHECK_MIC 1
#	define _SENSOR_INTERVAL 300

	// Sensor and app address information
#	define _DEVADDR { 0x26, 0x01, 0x1B, 0x96 }
#	define _APPSKEY { 0x02, 0x02, 0x04, 0x32, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
#	define _NWKSKEY { 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }

	// For ESP32 based T_BEAM/TTGO boards these two are normally included
	// If included make value 1, else if not, make them 0
#	define _GPS 1
#	define _BATTERY 1
#endif //_GATEWAYNODE


#if _TRUSTED_NODES >= 1
struct nodex {
	uint32_t id;				// This is the LoRa ID (coded in 4 bytes uint32_t
	char nm[32];				// Name of the node
};

// Add all your named and trusted nodes to this list
nodex nodes[] = {
	{ 0x26011C6D , "lora-33 Empty node" },						// F=0
	{ 0x260116BD , "lora-34 PIR node" },						// F=0
	{ 0x26011152 , "lora-35 temp+humi node" },					// F=0
	{ 0x2601148C , "lora-36 test node"  },						// F=0
// LoRa 37
	{ 0x26011B90 , "lora-39 temp DS18B20" },					// F=0
	{ 0x260119A6 , "lora-40 airquality" },						// F=0
	{ 0x2601117D , "lora-41 temp+humi SR04T" },
	{ 0x26011593 , "lora-42 temp DS18B20" },					// F=0	
	{ 0x26011514 , "lora-43 temp DS18B20" },					// F=0
	{ 0x2601145C , "lora-44 Distance" },						// F=0
	{ 0x26011D77 , "lora-45 no sensor" },
	{ 0x2601160F , "lora-46 HTU21 metal case" },				// F=0
	{ 0x26011E71 , "lora-47 Dallas temperature" },				// F=0, or on F=1
	{ 0x26011215 , "lora-48 AM2315 temp/Humi" },				// F=0
	{ 0x2601168F , "lora-49 EU433 Sensor" },					// 433, F=0
	{ 0x26011b96 , "lora-50 Internal T-Beam gway" },			// F=0
//	{ 0xAABBCCDD , "lora-51 Heltec OTAA" },						// F=ALL
	{ 0x26011199 , "lora-52 CubeCell sensor" },					// F=ALL
	{ 0x26011E52 , "lora-53 gas sensor" },						// F=ALL
	{ 0x260112A9 , "lora-54 ESP8266 No sensor" },				// F=0
	{ 0x2601152D , "lora-55 ESP8266 No sensor" },				// F=0	
	{ 0x26011F66 , "lora-62 CubeCell Capsule" },				// F=ALL
	{ 0x260110ED , "lora-63 CubeCell Board" },					// F=ALL
	{ 0x26011A2B , "lora-64 Metal temp humi" },					// F=0
	{ 0x260114EA , "lora-65 Waterproof temp humi" },			// F=0
	{ 0x26011D1D , "lora-152 ESP32 No Sensor" },				// F=0
	{ 0x00000000 , "lora-00 well known sensor" }				// F=0
};

#endif //_TRUSTED_NODES


// In some cases we like to decode the lora message at the single channel gateway.
// In thisase, we need the NkwSKey and the AppsSKey of the node so that we can decode
// its messages.
// Although this is probably overkill in normal gateway situations, it greatly helps
// in debugging the node messages before they reach the TTN severs.
//
#if _LOCALSERVER>=1
struct codex  {
	uint32_t id;				// This is the device ID (coded in 4 bytes uint32_t
	unsigned char nm[32];		// A name string which is free to choose
	uint8_t nwkKey[16];			// The Network Session Key of 16 bytes
	uint8_t appKey[16];			// The Application Session Key of 16 bytes
};

// Sometimes we want to decode the sensor completely as we do in the TTN server
// This means that for all nodes we want to view the data of, we need to provide
// the AppsSKey and the NwkSKey

// Definition of all nodes that we want to decode locally on the gateway.
//
codex decodes[] = {
	{	0x26011152 , "lora-35",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x23, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 } 
	},
	{	0x2601148C , "lora-36",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x24, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 } 
	},
	{	0x26011B90 , "lora-39",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x27, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
	},
	{	0x26011593 , "lora-42",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
	},
	{	0x26011D77 , "lora-43",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x2B, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
	},
	{	0x27000599 , "lora-44",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
	},
	{	0x26011B96 , "lora-50",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x32, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
	},
	{	0x26011B96 , "lora-52",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x34, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
	},
	{	0x26011B96 , "lora-62",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
	},
	{	0x26011B96 , "lora-63",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
	},
	{	0x260114EA , "lora-65",	// F=0
		{ 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 },
		{ 0x02, 0x02, 0x04, 0x41, 0x00, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x34, 0x55 }
	},
	{	0x00000000 , "lora-00",	// F=0
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
	}					
};
#endif //_LOCALSERVER


// Wifi definitions
// WPA is an array with SSID and password records. Set WPA size to number of entries in array
// When using the WiFiManager, we will overwrite the first entry with the 
// accesspoint we last connected to with WifiManager
struct wpas {
	char login[32];							// Maximum Buffer Size (and allocated memory)
	char passw[64];
};


// Please fill in at least ONE valid SSID and password from your own WiFI network
// below. This is needed to get the gateway working
//
wpas wpa[] = {
//	{ "mala_w", "DeWestenbergjesZijn1Bosbes!" },
//	{ "mala_z", "DeWestenbergjesZijn1Bosbes!" },
	// { "mala", "DeWestenbergjesZijn1Bosbes!" },
	// { "mala_a", "DeWestenbergjesZijn1Bosbes!" },
//	{ "Livebox-8AFC", "QMWvLKjMgcYMDrRGQZ" },
	// { "platenspeler", "maanlama@16" }
	{ "ICSL", "Icslicsl" }
};


// If you have a second back-end server defined such as Semtech or loriot.io
// your can define _THINGPORT and _THINGSERVER with your own value.
// If not, make sure that you do not define these, which will save CPU time
// Port is UDP port in this program
//
// Default for testing: Switched off
// #define _THINGSERVER "westenberg.org"		// Server URL of the LoRa-udp.js handler
// #define _THINGPORT 1700						// Port 1700 is old compatibility


// Define the name of the accesspoint if the gateway is in accesspoint mode (is
// getting WiFi SSID and password using WiFiManager). 
// If you do not need them, comment out.
//#define AP_NAME "Gway-Things4U"
//#define AP_PASSWD "ttnAutoPw"


// Gateway Ident definitions. Where is the gateway located?
#define _DESCRIPTION "ESP Gateway"			// Name of the gateway
#define _EMAIL "cy2540@columbia.edu"		// Owner
#define _PLATFORM "Heltec WiFi LoRa 32 v2"
#define _LAT 40.8099856
#define _LON -73.962459
#define _ALT 20								// Altitude


// For asserting and testing the following defines are used.
//
#if !defined(CFG_noassert)
#define ASSERT(cond) if(!(cond)) gway_failed(__FILE__, __LINE__)
#else
#define ASSERT(cond) /**/
#endif