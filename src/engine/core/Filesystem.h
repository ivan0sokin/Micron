#ifndef _MICRON_ENGINE_CORE_FILESYSTEM_H
#define _MICRON_ENGINE_CORE_FILESYSTEM_H

#include "types/BasicTypes.h"
#include "types/ContainerTypes.h"

#include <filesystem>
#include <fstream>

namespace Micron
{
	namespace Filesystem
	{
		using Path = std::filesystem::path;

		Path GetWorkingDirectory() noexcept;

		Void CreateDirectoryByPath(Path const &directoryPath) noexcept;
		Void CreateDirectoriesByPath(Path const &directoriesPath) noexcept;
		Void CreateDirectoryByName(MultibyteString const &directoryName) noexcept;
		Void CreateDirectoriesByName(MultibyteString const &directoriesName) noexcept;

		Bool IsValidPath(Path const &path) noexcept;

		Void TruncateFile(Path const &filePath) noexcept;
		Void WriteTextToFile(Path const &filePath, MultibyteString const &text) noexcept;
	}
}

#endif