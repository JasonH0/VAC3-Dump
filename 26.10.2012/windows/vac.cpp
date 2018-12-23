std::string DecryptVACString(std::string pszEncrypted)
{
	char szBuffer[255] = {NULL};
 
	int iLength = pszEncrypted[0] ^ 0x55;
	int iXor = 0x55;
 
	memcpy(szBuffer, pszEncrypted.c_str() + 0x1, iLength);
 
	for (int i = 0; i < iLength; i++)
	{
		szBuffer[i] ^= iXor;
		iXor = pszEncrypted[i+1];
	}
 
	return szBuffer;
}
 
std::string EncryptVACString(std::string pszDecrypted)
{
	char szBuffer[255] = {NULL};
 
	int iLength = pszDecrypted.length();
	int iXor = 0x55;
 
	szBuffer[0] = iLength ^ iXor;
	memcpy(szBuffer + 0x1, pszDecrypted.c_str(), iLength);
 
	for (int i = 0; i < iLength + 0x1; i++)
	{
		szBuffer[i+1] = pszDecrypted[i] ^ iXor;
		iXor = szBuffer[i+1];
	}
 
	return szBuffer;
}