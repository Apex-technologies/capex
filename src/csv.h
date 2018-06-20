//--------------------------------------------------------------------------
//                                CSVPARSER.H
//--------------------------------------------------------------------------
//!
//! \file csv.h
//! \brief Header file for parsing CSV file
//! \author Maxime Fontaine
//! \version 0.1
//! \date 2018-06-12
//!
//--------------------------------------------------------------------------


#ifndef _CAPEX_CSV_H
#define _CAPEX_CSV_H

#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "./tools.h"

namespace capex
{
	//--------------------------------------------------------------------------
	//                              CSV PARSER CLASS
	//--------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	//!
	//! \class csv
	//! \brief CSV File Parser class.
	//!
	//! This class allows to deal with CSV file (read and write).
	//!
	//--------------------------------------------------------------------------
	class csv
	{
		public:

		//----------------------------------------------------------------------
		//                       STRUCTURES DECLARATIONS
		//----------------------------------------------------------------------

		//! \brief Type of line
		enum LineType
		{
			ltValue = 0,
			ltComment = 1
		};

		//! \brief structure for value
		struct value
		{
			//! \brief the string value
			std::string value;
			//! \brief the line of the value in the CSV file
			int line;
			//! \brief the position of the value in the line
			int position;
		};

		//! \brief structure for line
		struct line
		{
			//! \brief type of this line
			LineType type;
			//! \brief the comment of the line
			std::string comment;
			//! \brief a vector of structures value with the values of this line
			std::vector<value> values;
			//! \brief the number of this line in the CSV file
			int line;
		};

		//! \brief structure for comment
		struct comment
		{
			//!  \brief the text of the comment
			std::string text;
			//! \brief the line of the comment in the CSV file
			int line;
		};

		//! \brief structure for table
		struct table
		{
			//! \brief a vector of structures line with the lines of the CSV file
			std::vector<line> lines;

			//! \brief a vector of structures comment with the comments of the CSV file
			std::vector<comment> comments;
		};

		private:
			
			std::vector<comment> *Comments;
			std::vector<int> *LinesType;
			table *tab;
			unsigned int FileEndLine;
			unsigned int EndLine;

			//! \brief Path of the CSV file to read / write
			std::string FileName;

			std::string separator;
			
			//-------------------------------------------------------------------------
			//!
			//! \brief    Returns the lines in the CSV File
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
			//!    1 : values line
			//!    2 : values line with comment
			//!
			//--------------------------------------------------------------------------
			void CAPEX_CALL GetLinesType();
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Converts a table into a string
			//! \param    t    the table pointer to convert
			//! \return   a \e string representing the converted table
			//! 
			//! This function returns a string value for the specified table.
			//! Today, the table is linked to the CSV file (this will change)
			//!
			//--------------------------------------------------------------------------
			std::string CAPEX_CALL TableToString(const table *t);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Set a converted string value
			//! \param    line       the line in which insert the value
			//! \param    position   the position where insert the value in the line
			//! \param    value      the value to insert
			//! \return   a \e boolean indicating if the writing operation is a success
			//! 
			//! This function write the value at the given position in the given line.
			//! Then, the modified dictionary is written to the CSV file if it exists
			//! 
			//! This function returns a boolean to indicate the success of the writing operation
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL WriteValue(unsigned int line, unsigned int position, std::string value);

			// --------------------------------------------------------------------------
			//!
			//! \brief Add a line in the table when a new line is added
			//! \param	  NewLine     Number of the line to insert
			//!
			//! Change the lines of sections, parameters and comments when a new parameter
			//! has been added to a dictionary. Only line greater than the 'NewLine' are
			//! modified
			//!
			//--------------------------------------------------------------------------
			void CAPEX_CALL ChangeLine(unsigned int NewLine);

		public:
			
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
			CAPEX_CALL csv(const char* File = NULL);
			
			//-------------------------------------------------------------------------
			//!
			//! \brief    Destructor of the ini class
			//! 
			//! This function destroys an instance of the ini class
			//! 
			//!
			//--------------------------------------------------------------------------
			CAPEX_CALL ~csv();
			
			//-------------------------------------------------------------------------
			//!
			//! \brief    Open a CSV File
			//! \param    File   CSV File to open
			//! \return   a \e boolean. \b true if file is opened, \b false otherwise
			//! 
			//! This function opens a CSV file and reads it
			//! 
			//! This function returns \b true in case of success.
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL Open(const char* File);

			//-------------------------------------------------------------------------
			//!
			//! \brief    Set the separator character between values
			//! \param    Sep   pointer of character defining the separators
			//!
			//! This function defines the separator(s) of the CSV file.
			//! If different separator are used in the file, a string containing
			//! all chazracters can be given. For exemple, if ',' and ';' are
			//! used as separators in the CSV file, send ",;" as separator.
			//!
			//! By default, the class uses ',' ';' and '\t' as separators
			//!
			//--------------------------------------------------------------------------
			void CAPEX_CALL SetSeparator(const char *Sep);

			//-------------------------------------------------------------------------
			//!
			//! \brief    Get the separator characters used for the CSV class
			//! \retunr   a \e string repressenting the separators
			//!
			//! This function gets the separator(s) of the CSV class.
			//!
			//! By default, the class uses ',' ';' and '\t' as separators
			//!
			//--------------------------------------------------------------------------
			std::string CAPEX_CALL GetSeparator();

			//--------------------------------------------------------------------------
			//!
			//! \brief Get the number of values lines in the CSV File
			//! \brief DataOnly  boolean indicating if only data lines have to be taken into account
			//! \return   an \e integer representing the values lines number
			//! 
			//! This function returns an integer with the values lines number.
			//! If 'DataOnly' is set to \b true (default value), the function returns
			//! only the number of data lines (without comments and new lines). If
			//! 'DataOnly' is set to \b false, the function returns the number
			//! of all lines (with comments and new line)
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetLinesNumber(bool DataOnly = true);

			//--------------------------------------------------------------------------
			//!
			//! \brief Get the number of values column in the CSV File
			//! \return   an \e integer representing the values columns number
			//!
			//! This function returns an integer with the values columns number.
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetColumnsNumber();
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get a specified line of the CSV File
			//! \param    line  the line number for the line of the CSV file to get
			//! \return   a \e line structure
			//! 
			//! This function read the lines of the INI file and picks up the specified line.
			//! 
			//! This function returns a line structure with the specified line.
			//! If the specified line cannot be found, this function returns an empty line.
			//!
			//--------------------------------------------------------------------------
			line CAPEX_CALL GetLine(unsigned int Line);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get the table of the CSV File
			//! \brief FromFile      Read the table from the file (default to false)
			//! \return   a \e table structure
			//! 
			//! This function returns a table structure for the entire CSV file
			//!
			//--------------------------------------------------------------------------
			table CAPEX_CALL GetTable(bool FromFile = false);

			//--------------------------------------------------------------------------
			//!
			//! \brief Clear the table of the CSV class
			//!
			//! This function clears the table structure used in the csv class
			//!
			//--------------------------------------------------------------------------
			void CAPEX_CALL ClearTable();
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get a boolean value
			//! \param    line       an integer representing the line of the value to get
			//! \param    position   an integer representing the position in the line
			//! \return   a \e boolean representing the value at the specified position
			//! 
			//! This function returns a boolean value for the specified position and line.
			//! If the value is \b true or \b 1, the returned value is \b true, \b false
			//! otherwise
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL GetBoolean(unsigned int line, unsigned int position);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get a string value
			//! \param    line       an integer representing the line of the value to get
			//! \param    position   an integer representing the position in the line
			//! \return   a \e string representing the value at the specified position
			//! 
			//! This function returns a string value for the specified position and line.
			//!
			//--------------------------------------------------------------------------
			std::string CAPEX_CALL GetString(unsigned int line, unsigned int position);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get an integer value
			//! \param    line       an integer representing the line of the value to get
			//! \param    position   an integer representing the position in the line
			//! \return   an \e integer representing the value at the specified position
			//! 
			//! This function returns an integer value for the specified position and line..
			//! If the value cannot be converted into integer, 0 is returned
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetInteger(unsigned int line, unsigned int position);
			
			//--------------------------------------------------------------------------
			//!
			//! \brief Get a double value
			//! \param    line       an integer representing the line of the value to get
			//! \param    position   an integer representing the position in the line
			//! \return   a \e double representing the value at the specified position
			//! 
			//! This function returns a double value for the specified position and line.
			//! If the value cannot be converted into double, 0.0 is returned
			//!
			//--------------------------------------------------------------------------
			double CAPEX_CALL GetDouble(unsigned int line, unsigned int position);

            //--------------------------------------------------------------------------
			//!
			//! \brief Get a column values of string type
			//! \param    column     an integer representing the column to get
			//! \param    values     a vector of string values
			//! \param    def        default value if no value is found
			//! \return   an \e integer representing the number of get values
			//!
			//! This function returns a vector of string values from the selected
			//! column. If, at a line, no value is found, the default value is used
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetColumn(unsigned int column, std::vector<std::string> *values, std::string def = "");

			//--------------------------------------------------------------------------
			//!
			//! \brief Get a column values of boolean type
			//! \param    column     an integer representing the column to get
			//! \param    values     a vector of boolean values
			//! \param    def        default value if no value is found
			//! \return   an \e integer representing the number of get values
			//!
			//! This function returns a vector of boolean values from the selected
			//! column. If, at a line, no value is found, the default value is used
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetColumn(unsigned int column, std::vector<bool> *values, bool def = false);

			//--------------------------------------------------------------------------
			//!
			//! \brief Get a column values of integer type
			//! \param    column     an integer representing the column to get
			//! \param    values     a vector of integer values
			//! \param    def        default value if no value is found
			//! \return   an \e integer representing the number of get values
			//!
			//! This function returns a vector of integer values from the selected
			//! column. If, at a line, no value is found, the default value is used
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetColumn(unsigned int column, std::vector<int> *values, int def = 0);

			//--------------------------------------------------------------------------
			//!
			//! \brief Get a column values of double type
			//! \param    column     an integer representing the column to get
			//! \param    values     a vector of double values
			//! \return   an \e integer representing the number of get values
			//!
			//! This function returns a vector of double values from the selected
			//! column. If, at a line, no value is found, the default value is used
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetColumn(unsigned int column, std::vector<double> *values, double def = 0.0);

			//--------------------------------------------------------------------------
			//!
			//! \brief Get a column values of boolean type
			//! \param    column     an integer representing the column to get
			//! \param    values     an array of boolean values
			//! \param    def        default value if no value is found
			//! \return   an \e integer representing the number of get values
			//!
			//! This function returns an array of boolean values from the selected
			//! column. If, at a line, no value is found, the default value is used
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetColumn(unsigned int column, capex::array<bool> *values, bool def = false);

			//--------------------------------------------------------------------------
			//!
			//! \brief Get a column values of integer type
			//! \param    column     an integer representing the column to get
			//! \param    values     an array of integer values
			//! \param    def        default value if no value is found
			//! \return   an \e integer representing the number of get values
			//!
			//! This function returns an array of integer values from the selected
			//! column. If, at a line, no value is found, the default value is used
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetColumn(unsigned int column, capex::array<int> *values, int def = 0);

			//--------------------------------------------------------------------------
			//!
			//! \brief Get a column values of integer type
			//! \param    column     an integer representing the column to get
			//! \param    values     an array of float values
			//! \param    def        default value if no value is found
			//! \return   an \e integer representing the number of get values
			//!
			//! This function returns an array of float values from the selected
			//! column. If, at a line, no value is found, the default value is used
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetColumn(unsigned int column, capex::array<float> *values, float def = 0.0);

			//--------------------------------------------------------------------------
			//!
			//! \brief Get a column values of integer type
			//! \param    column     an integer representing the column to get
			//! \param    values     an array of double values
			//! \param    def        default value if no value is found
			//! \return   an \e integer representing the number of get values
			//!
			//! This function returns an array of double values from the selected
			//! column. If, at a line, no value is found, the default value is used
			//!
			//--------------------------------------------------------------------------
			int CAPEX_CALL GetColumn(unsigned int column, capex::array<double> *values, double def = 0.0);

			bool CAPEX_CALL SetColumn(unsigned int column, std::vector<std::string> values, int start = 0);

			bool CAPEX_CALL SetColumn(unsigned int column, std::vector<bool> values, int start = 0);

			bool CAPEX_CALL SetColumn(unsigned int column, std::vector<int> values, int start = 0);

			bool CAPEX_CALL SetColumn(unsigned int column, std::vector<double> values, int start = 0);

			bool CAPEX_CALL SetColumn(unsigned int column, capex::array<bool> values, int start = 0);

			bool CAPEX_CALL SetColumn(unsigned int column, capex::array<int> values, int start = 0);

			bool CAPEX_CALL SetColumn(unsigned int column, capex::array<float> values, int start = 0);

			bool CAPEX_CALL SetColumn(unsigned int column, capex::array<double> values, int start = 0);

			//--------------------------------------------------------------------------
			//!
			//! \brief Writes a table into an CSV file
			//! \param    t    the table to write
			//! \param    File a char pointer to the CSV file name
			//! \return   a \e boolean indicating if the writing operation is a success
			//!
			//! This function needs a pointer to the specified table and a pointer
			//! to the file name. If the file name pointer is NULL, the table is
			//! written into the previously opened file.
			//!
			//! This function returns a boolean to indicate the success of the writing operation
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL WriteCSV(const table *t, const char *File = NULL);

			//--------------------------------------------------------------------------
			//!
			//! \brief Writes a table into an CSV file
			//! \param    t    the table to write
			//! \param    mode the open mode to use
			//! \param    File a char pointer to the CSV file name
			//! \return   a \e boolean indicating if the writing operation is a success
			//!
			//! This function needs a pointer to the specified table, an open mode
			//! and a pointer to the file name. If the file name pointer is NULL,
			//! the table is written into the previously opened file.
			//!
			//! This function returns a boolean to indicate the success of the writing operation
			//!
			//--------------------------------------------------------------------------
			bool CAPEX_CALL WriteCSV(const table *t, std::ios_base::openmode mode, const char *File = NULL);

			bool CAPEX_CALL SetValue(unsigned int line, unsigned int position, std::string value);

			bool CAPEX_CALL SetValue(unsigned int line, unsigned int position, bool value);

			bool CAPEX_CALL SetValue(unsigned int line, unsigned int position, int value);

			bool CAPEX_CALL SetValue(unsigned int line, unsigned int position, double value, int precision = 6);
	};

}

#include "./csv.cpp"

#endif
