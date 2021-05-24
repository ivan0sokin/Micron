#include "Filesystem.h"
#include "Logger.hpp"

namespace Micron
{
	namespace Filesystem
	{
		Path GetWorkingDirectory() noexcept
		{
			return std::filesystem::current_path();
		}

		Void CreateDirectoryByPath(Path const &directoryPath) noexcept
		{
			std::error_code errorCode;
			Bool directoryCreated = std::filesystem::create_directory(directoryPath, errorCode);

			if (!directoryCreated)
				CoreLogger::Error("Failed to create directory \"{0}\", error code: {1}, message: {2}", directoryPath.string(), errorCode.value(), errorCode.message());
		}

		Void CreateDirectoriesByPath(Path const &directoriesPath) noexcept
		{
			std::error_code errorCode;
			Bool directoryCreated = std::filesystem::create_directories(directoriesPath, errorCode);

			if (!directoryCreated)
				CoreLogger::Error("Failed to create directory \"{0}\", error code: {1}, message: {2}", directoriesPath.string(), errorCode.value(), errorCode.message());
		}

		Void CreateDirectoryByName(MultibyteString const &directoryName) noexcept
		{
			CreateDirectoryByPath(GetWorkingDirectory() / directoryName);
		}

		Void CreateDirectoriesByName(MultibyteString const &directoriesName) noexcept
		{
			CreateDirectoriesByPath(GetWorkingDirectory() / directoriesName);
		}

		Bool IsValidPath(Path const &path) noexcept
		{
			return std::filesystem::exists(path);
		}

		std::ofstream OpenFile(Path const &filePath, std::ios_base::openmode openMode) noexcept
		{
			std::ofstream fileOutputStream = std::ofstream(filePath.native(), openMode);

			if (fileOutputStream.fail())
				CoreLogger::Error("Failed to open file \"{}\"", filePath.string());

			return fileOutputStream;
		}

		Void TruncateFile(Path const &filePath) noexcept
		{
			auto file = OpenFile(filePath, std::ios::trunc);
			file.close();
		}

		Void WriteTextToFile(Path const &filePath, MultibyteString const &text) noexcept
		{
			auto file = OpenFile(filePath, std::ios::ate);
			file << text;
			file.close();
		}
	}
}