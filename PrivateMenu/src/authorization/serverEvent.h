#pragma once

enum eServerEvents {
	DEBUGGER_ATTACHED,
	THREAD_KILLED,
	THREAD_BEING_DEBUGGED,
	ANTI_TAMPER_TRIGGERED,
	ANTI_TAMPER_REGISTRATION_FAILURE,
	BLACKLISTED_PROCESS,
	TEXT_SECTION_MODIFIED,
	ROCKSTAR_NETWORK_DRIVE
};

enum eServerEventSeverity {
	SEVERITY_GENERIC,
	SEVERITY_FLAGUSER,
	SEVERITY_BANNABLE
};

struct ServerEventData {
	eServerEventSeverity m_severity;
	string m_additionalInformation;

	ServerEventData() {
		m_severity = eServerEventSeverity::SEVERITY_GENERIC;
	}

	ServerEventData(eServerEventSeverity severity, string additional = "") {
		m_severity = severity;
		m_additionalInformation = additional;
	}
};

class ServerEvent {
private:
	Network* m_network;
public:
	void RegisterServerEvent(eServerEvents id, function<void(ServerEventData)> func);
	void SendEvent(eServerEvents id, ServerEventData structData);
	void RegisterEvents();
};

ServerEvent* GetServerEvent();