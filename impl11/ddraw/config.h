// Copyright (c) 2014 J�r�my Ansel
// Licensed under the MIT license. See LICENSE.txt

#pragma once

class Config
{
public:
	Config();

	bool AspectRatioPreserved;
	bool MultisamplingAntialiasingEnabled;
	bool AnisotropicFilteringEnabled;
	bool WireframeFillMode;
	int ScalingType;

	bool Fullscreen;
	bool XWAMode;

	float Concourse3DScale;

	int PresentSleepTime;
};

extern Config g_config;
