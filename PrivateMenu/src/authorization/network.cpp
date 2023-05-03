#include "stdafx.h"
NetworkingURLs g_networkingURLs;

wstring Network::Convert(string in) {
	wstring wsTmp(in.begin(), in.end());
	return wsTmp;
}

string Network::Convert(wstring in) {
	string sTmp(in.begin(), in.end());
	return sTmp;
}

string Network::Post(string data, string contentType, string useragent) {
	wstring _url = Convert(m_url);

	WinHttpClient client(_url);

	client.SetAdditionalDataToSend((BYTE*)data.c_str(), data.size());

	client.SetRequireValidSslCertificates(true);

	wstring headers = Convert("Content-Length: ");
	headers += Convert(va("%zd", data.size()));
	headers += Convert(contentType);

	client.SetUserAgent(Convert(useragent));
	client.SetAdditionalRequestHeaders(headers);

	client.SendHttpRequest(L"POST");

	return Convert(client.GetResponseContent());
}

string Network::AdvancedPost(string data, vector<pair<string, string>> additionalHeaders, string contentType) {
	WinHttpClient client(Convert(m_url));

	client.SetAdditionalDataToSend(reinterpret_cast<BYTE *>(const_cast<char *>(data.c_str())), data.size());
	client.SetRequireValidSslCertificates(true);

	additionalHeaders.emplace_back("Content-Type", contentType);
	additionalHeaders.emplace_back("Content-Length", std::to_string(data.size()));

	auto headers = Convert("");

	for (const auto& header : additionalHeaders) {
		headers += Convert(va("%s: %s\r\n", header.first.c_str(), header.second.c_str()));
	}

	client.SetAdditionalRequestHeaders(headers);

	//LOG_DEVPRINT("sending request...");
	client.SendHttpRequest(L"POST");
	//LOG_DEVPRINT("received response.");

	return Convert(client.GetResponseContent());
}

eDownloadFileResponses Network::Download(string theurl, string saveTo) {
	WinHttpClient client(Convert(theurl));

	if (!client.SendHttpRequest()) {
		return eDownloadFileResponsesCouldntSendRequest;
	}

	client.SaveResponseToFile(Convert(saveTo));

	ifstream f(saveTo.c_str());
	if (f.good()) {
		return eDownloadFileResponsesSuccess;
	}

	return eDownloadFileResponsesFileDoesntExist;
}

Network* GetNetwork(string url) {
	return new Network(url);
}