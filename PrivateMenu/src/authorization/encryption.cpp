#include "stdafx.h"

string Encryption::XOR(string str, char ch) {
	for (int i = 0; i < str.size(); i++) {
		str[i] ^= ch;
	}
	return str;
}

string Encryption::rot13(string str) {
	for (string::size_type len = str.length(), idx = 0; idx != len; ++idx) {
		if (str[idx] >= 'a' && str[idx] <= 'm') {
			str[idx] = str[idx] + 13;
		} else if (str[idx] >= 'n' && str[idx] <= 'z') {
			str[idx] = str[idx] - 13;
		} else if (str[idx] >= 'A' && str[idx] <= 'M') {
			str[idx] = str[idx] + 13;
		} else if (str[idx] >= 'N' && str[idx] <= 'Z') {
			str[idx] = str[idx] - 13;
		}
	}

	return str;
}

string Encryption::intRot13Reverse(string str) {
	for (int i = 0; i < str.length(); i++) {
		switch (str[i]) {
		case '3':
			str[i] = '0';
			break;
		case '4':
			str[i] = '1';
			break;
		case '5':
			str[i] = '2';
			break;
		case '6':
			str[i] = '3';
			break;
		case '7':
			str[i] = '4';
			break;
		case '8':
			str[i] = '5';
			break;
		case '9':
			str[i] = '6';
			break;
		case '0':
			str[i] = '7';
			break;
		case '1':
			str[i] = '8';
			break;
		case '2':
			str[i] = '9';
			break;
		}
	}

	return str;
}

string Encryption::hex2str(string str) {
	int len = str.length();
	string newString;
	for (int i = 0; i < len; i += 2) {
		string byte = str.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
		newString.push_back(chr);
	}

	return newString;
}

string Encryption::base64encode(string str) {
	int in_len = str.length();
	string ret;
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = str[in_]; in_++;
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';
	}
	//LOG_PRINT("Base64Encode (OUT): %s", ret);
	return ret;
}

string Encryption::base64encode2(byte* data, size_t length) {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (length--) {
		char_array_3[i++] = *(data++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;
}


string Encryption::base64decode(string str) {
	int in_len = str.length();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	string ret;

	while (in_len-- && (str[in_] != '=') && IsBase64(str[in_])) {
		char_array_4[i++] = str[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

string Encryption::aesEncrypt(string encryptionKey, string str) {
	string key = "";
	if (encryptionKey.empty()) {
		key = "___________penis";
	} else {
		key = encryptionKey;
	}

	string result;

	CryptoPP::AES::Encryption aesEncryption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (byte *)"penisenlargement");

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(result), CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING);

	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(str.c_str()), str.length() + 1);
	stfEncryptor.MessageEnd();

	return result;
}

string Encryption::aesDecrypt(string encryptionKey, string str) {
	string key = "";
	if (encryptionKey.empty()) {
		key = "___________penis";
	} else {
		key = encryptionKey;
	}

	string result;

	CryptoPP::AES::Decryption aesDecryption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (byte *)"penisenlargement");

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(result), CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING);

	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(str.c_str()), str.size());
	stfDecryptor.MessageEnd();

	return result;
}

string EncryptionHelper::DecryptAccessToken(string token) {
	string decoded = Encryption::base64decode(token);
	string decrypted = Encryption::aesDecrypt("___________penis", decoded);
	string fromHex = Encryption::hex2str(decrypted);
	string intReverse = Encryption::intRot13Reverse(fromHex);

	decoded.clear();
	decrypted.clear();
	fromHex.clear();

	return intReverse;
}

string EncryptionHelper::DecryptAuthResponse(string response, string key) {
	string decrypted;

	if (response[0] == 'b' && response[1] == 'a' && response[2] == 'd') {
		response = response.substr(4);
		string decoded = Encryption::base64decode(response);
		string decrypted = Encryption::aesDecrypt(key, decoded);
		string fromHex = Encryption::hex2str(decrypted);
		string intReverse = Encryption::intRot13Reverse(fromHex);
		string rot13 = Encryption::rot13(intReverse);

		decoded.clear();
		decrypted.clear();
		fromHex.clear();
		intReverse.clear();

		return rot13;
	}

	if (response[0] == 'g' && response[1] == 'o' && response[2] == 'o' && response[3] == 'd') {
		response = response.substr(5);

		char reversed[20];
		strcpy(reversed, key.c_str());

		int count = (16 - strlen(reversed));

		for (int i = 0; i < count; i++)
			strcat(reversed, "-");

		string decoded = Encryption::base64decode(response);
		string decrypted = Encryption::aesDecrypt(reversed, decoded);
		string fromHex = Encryption::hex2str(decrypted);
		string intReverse = Encryption::intRot13Reverse(fromHex);
		string rot13 = Encryption::rot13(intReverse);

		decoded.clear();
		decrypted.clear();
		fromHex.clear();
		intReverse.clear();

		return rot13;
	}
	
	return "";
}

string EncryptionHelper::ABitLessSimpleEncrypt(string str) {
	string aes = Encryption::aesEncrypt("ABitLessSimpleEncrypt", str);
	string xor1 = Encryption::XOR(aes, 0x69);
	string xor2 = Encryption::XOR(xor1, 0x71);
	string b64 = Encryption::base64encode(xor2);
	return Encryption::XOR(b64, 0x12);
}

string EncryptionHelper::ABitLessSimpleDecrypt(string str) {
	string xor3 = Encryption::XOR(str, 0x12);
	string b64 = Encryption::base64decode(xor3);
	string xor2 = Encryption::XOR(b64, 0x71);
	string xor1 = Encryption::XOR(xor2, 0x69);
	return Encryption::aesDecrypt("ABitLessSimpleEncrypt", xor1);
}

string EncryptionHelper::SimpleEncrypt(string str) {
	string encrypted = Encryption::aesEncrypt("ahdgcbfhfbcgfbcf", str);
	string encoded = Encryption::base64encode(encrypted);
	return encoded;
}

string EncryptionHelper::SimpleDecrypt(string str) {
	string decoded = Encryption::base64decode(str);
	string decrypted = Encryption::aesDecrypt("ahdgcbfhfbcgfbcf", decoded);
	return decrypted;
}

string EncryptionHelper::Base64Encode(string str) {
	//LOG_PRINT("Base64Encode (IN): %s", str.c_str());
	return Encryption::base64encode(str);
}

uint32_t HashAlgorithm::CRC32(string str) {
	uint32_t hash = 0;
	CryptoPP::CRC32().CalculateDigest((byte*)&hash, (byte*)str.data(), str.size());
	return hash;
}

string HashAlgorithm::SHA1(char *bytes, int size) {
	CryptoPP::SHA1 sha1;
	string hash = "";
	CryptoPP::ArraySource((byte*)bytes, size, true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));
	return hash;
}

string HashAlgorithm::SHA256(string str) {
	CryptoPP::Weak::MD5 hash;
	byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];

	hash.CalculateDigest(digest, (byte*)str.c_str(), str.length());

	CryptoPP::HexEncoder encoder;
	string output;
	encoder.Attach(new CryptoPP::StringSink(output));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();

	return output;
}
