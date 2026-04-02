#pragma once

// ----------------------------------------------------------------------------------

enum appErrs {
	appErr_AllOk = 0,				// Successful result
	appErr_NotEnoughArgs,			// Не хватает входных данных
	appErr_SourceFileMissed,		// Source failed / wrong path ?
	appErr_ReadSourceFileIO,		// I/O Error
	appErr_ConfigFileMissed,		// Invalid configuration file
	appErr_YAMLParserError,			// Parser error
	appErr_InvalidDestination,		// Destination failed ( fname )
	appErr_TransformationFailed		// Bounds Check failed
};
