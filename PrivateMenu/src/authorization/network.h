#pragma once

enum eDownloadFileResponses {
	eDownloadFileResponsesCouldntSendRequest,
	eDownloadFileResponsesFileDoesntExist,
	eDownloadFileResponsesSuccess
};

struct NetworkingURLs {
	string m_validate = "https://auth.impulse.one/v2/validate.php";
	string m_event = "https://auth.impulse.one/v2/event.php";
}; extern NetworkingURLs g_networkingURLs;

class Network {
private:
	string m_url;

	wstring Convert(string in);
	string Convert(wstring in);

public:
	Network(string s) {
		m_url = s;
	}

	string Post(string data, string contentType = "\r\nContent-Type: application/x-www-form-urlencoded\r\n", string useragent = "nigger");
	string AdvancedPost(string data, vector<pair<string, string>> additionalHeaders, string contentType = "application/text");

	eDownloadFileResponses Download(string theurl, string saveTo);
};

Network* GetNetwork(string url);