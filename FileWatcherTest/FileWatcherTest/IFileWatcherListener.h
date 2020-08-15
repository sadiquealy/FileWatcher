#pragma once
#include<string>
class IFileWatcherListener
{
public:
	virtual void OnFileChange(const std::wstring& path)  = 0;
	virtual void OnFileAdded(const std::wstring& path)   = 0;
	virtual void OnFileRemoved(const std::wstring& path) = 0;
	virtual void OnFileRenamed(const std::wstring& path) = 0;
};
