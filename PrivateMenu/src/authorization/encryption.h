#pragma once

enum eValidEncryptionLayers {
	aesEncrypt,
	aesDecrypt,
	base64encode,
	base64decode,
	hex2str,
	rot13,
	intRot13Reverse,
};

inline bool IsBase64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

static const string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

class Encryption {
public:
	static string XOR(string str, char ch);
	static string rot13(string str);
	static string intRot13Reverse(string str);
	static string hex2str(string str);
	static string base64encode(string str);
	static string base64encode2(byte *data, size_t length);
	static string base64decode(string str);
	static string aesEncrypt(string encryptionKey, string str);
	static string aesDecrypt(string encryptionKey, string str);
};

class EncryptionHelper 
{
public:
	static string DecryptAccessToken(string token);
	static string DecryptAuthResponse(string response, string key = "");
	static string SimpleEncrypt(string str);
	static string SimpleDecrypt(string str);
	static string ABitLessSimpleEncrypt(string str);
	static string ABitLessSimpleDecrypt(string str);
	static string Base64Encode(string str);
};

class HashAlgorithm
{
public:
	static uint32_t CRC32(string str);
	static string SHA1(char *bytes, int size);
	static string SHA256(string str);
};