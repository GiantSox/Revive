#pragma once

#include <OVR_CAPI.h>
#include <openvr.h>
#include <memory>
#include <atomic>
#include <list>
#include <thread>

// Forward declarations
class CompositorBase;
class InputManager;
class SessionDetails;
class SettingsManager;

struct SessionStatusBits {
	bool IsVisible : 1;
	bool HmdPresent : 1;
	bool HmdMounted : 1;
	bool DisplayLost : 1;
	bool ShouldQuit : 1;
	bool ShouldRecenter : 1;
	bool Internal1 : 1;
	bool Internal2 : 1;
};

struct ovrHmdStruct
{
	std::thread SessionThread;
	std::atomic_bool Running;

	// Session status
	std::atomic<SessionStatusBits> SessionStatus;
	char StringBuffer[vr::k_unMaxPropertyStringSize];
	vr::ETrackingUniverseOrigin TrackingOrigin;

	// Compositor statistics
	std::atomic_llong FrameIndex;
	long long StatsIndex;
	ovrPerfStatsPerCompositorFrame ResetStats;
	vr::Compositor_CumulativeStats Stats[ovrMaxProvidedFrameStats];

	// Revive interfaces
	std::unique_ptr<CompositorBase> Compositor;
	std::unique_ptr<InputManager> Input;
	std::unique_ptr<SessionDetails> Details;
	std::unique_ptr<SettingsManager> Settings;

	ovrHmdStruct();
	~ovrHmdStruct();
};
