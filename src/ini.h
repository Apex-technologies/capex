//--------------------------------------------------------------------------
//                                INIPARSER.H
//--------------------------------------------------------------------------
//!
//! \file INIParser.h
//! \brief Header file for parsing INI file
//! \author Maxime Fontaine
//! \version 0.1
//! \date 2015-02-08
//!
//--------------------------------------------------------------------------


#ifndef _CAPEX_INI_H
#define _CAPEX_INI_H

#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "./tools.h"

namespace capex
{

	//--------------------------------------------------------------------------
	//                              STRUCTURES DECLARATIONS
	//--------------------------------------------------------------------------

	//! \brief structure for parameter
	struct parameter
	{
		//! \brief the name of the parameter
		std::string name;
		//! \brief the value of the parameter
		std::string value;
		//! \brief the comment of the parameter
		std::string comment;
		//! \brief the line of the parameter in the ini file
		int line;
	};

	//! \brief structure for section
	struct section
	{
		//! \brief the name of the section
		std::string key;
		//! \brief the comment of the section
		std::string comment;
		//! \brief a vector of structures parameter with the parameters of this section
		std::vector<parameter> parameters;
		//! \brief the line of the section in the ini file
		int line;
	};

	//! \brief structure for dictionary
	struct dictionary
	{
		//! \brief a vector of structures section with the sections of the INI file
		std::vector<section> sections;
		//! \brief a vector of string with the section names
		std::vector<std::string> Keys;
	};

	//! \brief structure for comment
	struct comment
	{
		//!  \brief the text of the comment
		std::string text;
		//! \brief the line of the comment in the ini file
		int line;
	};

	//--------------------------------------------------------------------------
	//                              INI PARSER CLASS
	//--------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	//!
	//! \class ini
	//! \brief INI File Parser class.
	//!
	//! This class allows to deal with INI file (read and write).
	//!
	//--------------------------------------------------------------------------
	class ini
	{
		private:

			std::vector<std::string> *Keys;
			std::vector<unsigned int> *KeysLines;
			std::vector<comment> *Comments;
			std::vector<int> *LinesType;
			dictionary *dico;
			unsigned int FileEndLine;
			unsigned int EndLine;
			
			std::vector<unsigned int> KLines;
			
			
			//-------------------------------------------------------------------------
			//!
			//! \brief    Returns the lines in the INI File
			//! \return   a \e vector of \e strings representing lines
			//! 
			//! This function returns a vector of strings for lines in the INI file.
			//!
			//--------------------------------------------------------------------------
			std::vector<std::string> CAPEX_CALL GetLines();
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get the type of lines in the INI file
			//! 
			//! This function is for local using only. Types are follow :
			//!    0 : comment line
			//!    1 : key or parameter
			//!    2 : key or parameter with comment
			//!
			//--------------------------------------------------------------------------
			void CAPEX_CALL GetLinesType();
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Converts a dictionary into a string
			//! \param    d    the dictionary pointer to convert
			//! \return   a \e string representing the converted dictionary
			//! 
			//! This function returns a string value for the specified dictionary.
			//! Today, the dictionary is linked to the INI file (this will change)
			//!
			//--------------------------------------------------------------------------
			std::string CAPEX_CALL DicoToString(const dictionary *d);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Set a converted string value
			//! \param    section    a char pointer to the section name
			//! \param    key        a char pointer to the parameter name
			//! \param    value      the value to set for the specified key
			//! \return   a \e boolean indicating if the writing operation is a success
			//! 
			//! This function needs a pointer to the specified dictionary and a pointer 
			//! to the specified key. if the section doesn't exists, it will be created.
			//! If the key doesn't exist (but the section does), a new key is added to 
			//! the specified section.
			//! Then, the modified dictionary is written to the INI file if it exists
			//! 
			//! This function returns a boolean to indicate the success of the writing operation
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL WriteValue(const char *section, const char *parameter, std::string value);
			
			// --------------------------------------------------------------------------
			//!
			//! \brief Add a line in the dictionary when a new parameter is added
			//! \param	  NewLine     Number of the line to insert
			//!
			//! Change the lines of sections, parameters and comments when a new parameter
			//! has been added to a dictionary. Only line greater than the 'NewLine' are
			//! modified
			//!
			//--------------------------------------------------------------------------
			void CAPEX_CALL ChangeLine(unsigned int NewLine);

		public:
			
			//! \brief Path of the INI file to read / write
			const char *FileName;
			
			//! \brief Raw text read in the INI file
			std::string TextFile;

			//-------------------------------------------------------------------------
			//!
			//! \brief    Constructor of the ini class
			//! \param    File   INI File to open (optional)
			//! \return   an instance of the class
			//! 
			//! This function creates an instance of the ini class
			//! If a file name is given in parameter, this method open the file
			//! 
			//!
			//--------------------------------------------------------------------------
			CAPEX_CALL ini(const char* File = NULL);
			
			//-------------------------------------------------------------------------
			//!
			//! \brief    Destructor of the ini class
			//! 
			//! This function destroys an instance of the ini class
			//! 
			//!
			//--------------------------------------------------------------------------
			CAPEX_CALL ~ini();
			
			//-------------------------------------------------------------------------
			//!
			//! \brief    Open an INI File
			//! \param    File   INI File to open
			//! \return   a \e boolean. \b true if file is opened, \b false otherwise
			//! 
			//! This function opens an INI file and reads it
			//! 
			//! This function returns \b true in case of success.
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL Open(const char* File);

			//--------------------------------------------------------------------------
			//!
			//! \brief Get the sections name of the INI File
			//! \return   a \e vector of \e strings with the sections name
			//! 
			//! This function read the lines of the INI file and picks up sections.
			//! 
			//! This function returns a vector of strings with the sections names.
			//!
			//--------------------------------------------------------------------------
			std::vector<std::string> CAPEX_CALL GetSectionsName();
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get the sections number of the INI File
			//! \return   an \e integer representing the sections number
			//! 
			//! This function returns an integer with the sections number.
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetSectionNumber();
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get a specified section of the INI File
			//! \param    SectionName  a char pointer for the section name of the INI file to get
			//! \return   a \e section structure
			//! 
			//! This function read the lines of the INI file and picks up the specified section.
			//! 
			//! This function returns a section structure with the specified section.
			//! If the specified section cannot be found, this function returns an empty section.
			//!
			//--------------------------------------------------------------------------
			section CAPEX_CALL GetSection(const char *SectionName);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get the dictionary of the INI File
			//! \return   a \e dictionary structure
			//! 
			//! This function returns a dictionary structure for the entire INI file
			//!
			//--------------------------------------------------------------------------
			dictionary CAPEX_CALL GetDictionary();
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get a boolean value
			//! \param    section    a char pointer to the section name
			//! \param    key        a char pointer to the parameter name
			//! \return   a \e boolean representing the value of the specified key
			//! 
			//! This function returns a boolean value for the specified key.
			//! If the value is \b true or \b 1, the returned value is \b true, \b false
			//! otherwise
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL GetBoolean(const char *section, const char *key);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get a string value
			//! \param    section    a char pointer to the section name
			//! \param    key        a char pointer to the parameter name
			//! \return   a \e string representing the value of the specified key
			//! 
			//! This function returns a string value for the specified key.
			//!
			//--------------------------------------------------------------------------
			std::string CAPEX_CALL GetString(const char *section, const char *key);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get an integer value
			//! \param    section    a char pointer to the section name
			//! \param    key        a char pointer to the parameter name
			//! \return   an \e integer representing the value of the specified key
			//! 
			//! This function returns an integer value for the specified key.
			//! If the value cannot be converted into integer, 0 is returned
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetInteger(const char *section, const char *key);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get a double value
			//! \param    section    a char pointer to the section name
			//! \param    key        a char pointer to the parameter name
			//! \return   a \e double representing the value of the specified key
			//! 
			//! This function returns a double value for the specified key.
			//! If the value cannot be converted into double, 0.0 is returned
			//!
			//--------------------------------------------------------------------------
			double CAPEX_CALL GetDouble(const char *section, const char *key);

			//--------------------------------------------------------------------------
			//!
			//! \brief Writes a dictionary into an INI file
			//! \param    d    the dictionary to write
			//! \param    File a char pointer to the INI file name
			//! \return   a \e boolean indicating if the writing operation is a success
			//! 
			//! This function needs a pointer to the specified dictionary and a pointer 
			//! to the file name. If the file name pointer is NULL, the dictionary is
			//! written into the previously opened file.
			//! 
			//! This function returns a boolean to indicate the success of the writing operation
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL WriteINI(const dictionary *d, const char *File = NULL);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Set a boolean value
			//! \param    section    a char pointer to the section name
			//! \param    key        a char pointer to the parameter name
			//! \param    value      the value to set for the specified key
			//! \return   a \e boolean indicating if the writing operation is a success
			//! 
			//! This function needs a pointer to the specified dictionary and a pointer 
			//! to the specified key. if the section doesn't exists, it will be created.
			//! If the key doesn't exist (but the section does), a new key is added to 
			//! the specified section.
			//! Then, the modified dictionary is written to the INI file if it exists
			//! 
			//! This function returns a boolean to indicate the success of the writing operation
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL SetValue(const char *section, const char *key, bool value);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Set an integer value
			//! \param    section    a char pointer to the section name
			//! \param    key        a char pointer to the parameter name
			//! \param    value      the value to set for the specified key
			//! \return   a \e boolean indicating if the writing operation is a success
			//! 
			//! This function needs a pointer to the specified dictionary and a pointer 
			//! to the specified key. if the section doesn't exists, it will be created.
			//! If the key doesn't exist (but the section does), a new key is added to 
			//! the specified section.
			//! Then, the modified dictionary is written to the INI file if it exists
			//! 
			//! This function returns a boolean to indicate the success of the writing operation
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL SetValue(const char *section, const char *key, int value);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Set a double value
			//! \param    section    a char pointer to the section name
			//! \param    key        a char pointer to the parameter name
			//! \param    value      the value to set for the specified key
			//! \param    precision  the number of digits after point (default = 6)
			//! \return   a \e boolean indicating if the writing operation is a success
			//! 
			//! This function needs a pointer to the specified dictionary and a pointer 
			//! to the specified key. if the section doesn't exists, it will be created.
			//! If the key doesn't exist (but the section does), a new key is added to 
			//! the specified section.
			//! Then, the modified dictionary is written to the INI file if it exists
			//! 
			//! This function returns a boolean to indicate the success of the writing operation
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL SetValue(const char *section, const char *key, double value, int precision = 6);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Set a string value
			//! \param    section    a char pointer to the section name
			//! \param    key        a char pointer to the parameter name
			//! \param    value      the value to set for the specified key
			//! \return   a \e boolean indicating if the writing operation is a success
			//! 
			//! This function needs a pointer to the specified dictionary and a pointer 
			//! to the specified key. if the section doesn't exists, it will be created.
			//! If the key doesn't exist (but the section does), a new key is added to 
			//! the specified section.
			//! Then, the modified dictionary is written to the INI file if it exists
			//! 
			//! This function returns a boolean to indicate the success of the writing operation
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL SetValue(const char *section, const char *key, std::string value);
	};

}

#include "./ini.cpp"

#endif
