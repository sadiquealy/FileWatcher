#ifndef CFILEWATCHER_H
#define CFILEWATCHER_H

#include <string>
#include <windows.h>
#include <Winbase.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <tchar.h>
#include "IFileWatcherListener.h"
#include <vector>
#define MAX_DIRS 25
#define MAX_FILES 255
#define MAX_BUFFER 4096

/*!
 *  CFileWatcher class.
 *  Watching a directory passed for file change and notifies if there is a change.
 *
 */
class CFileSystemWatcher
{

public:

	/*!
	 *
	 *
	 * \param logDir
	 */
	CFileSystemWatcher(const std::wstring& logDir);

	/*!
	 *
	 *
	 * \return
	 */
	const std::wstring& GetDir() { return m_sDir; }

	/*!
	 *
	 *
	 * \param listener
	 */
	void AddFileChangeListener(IFileWatcherListener* listener);

	/*!
	 * Starts the Watcher
	 *
	 */
	void Start();

	/*!
	 *
	 * Stops the Watcher
	 */
	void Stop();

	/*!
	 * Destructor for File Wacther
	 *
	 */
	~CFileSystemWatcher();
	/*!
	 *
	 *
	 * \return
	 */
	volatile bool Running() const { return m_bRunning; }
	/*!
	 * Sets the Running Status
	 *
	 * \param val
	 */
	void Running(volatile bool val) { m_bRunning = val; }

	/*!
	 * Funtion called when a file is chnaged in watcher directory
	 *
	 * \param fileNmae
	 */
	void OnFileChange(const std::wstring& fileNmae);

	/*!
	 *
	 * Funtion called when a file is added to watch directory
	 *
	 * \param sFile
	 */
	void OnFileAdded(const std::wstring& sFile);
	/*!
	 * Funtion called when a file is removed from watch directory
	 *
	 * \param sFile
	 */
	void OnFileRemoved(const std::wstring& sFile);
	/*!
	 * Funtion called when a file is renamed from watch directory
	 *
	 * \param sFile
	 */
	void OnFileRenamed(const std::wstring& sFile);

private:
	/*!
	 * Running Status
	 *
	 */
	volatile bool m_bRunning;

	/*!
	 *
	 * File Watcher Directory
	 */
	std::wstring m_sDir;

	/**
	 * List of listeners to be notified.
	 */
	std::vector<IFileWatcherListener*> m_Listeners;

	/*!
	 * File Watcher Thread
	 *
	 */
	std::unique_ptr<std::thread> m_pFileWatcherThread;
};

/*!
 * Internal Thread function executing  win32 file watcher API
 *
 */
void fileWatcherThread(CFileSystemWatcher& watcherObj);

#endif

