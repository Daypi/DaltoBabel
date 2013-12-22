//
// Util.hpp for Util in /home/taiebi_e//workdir/abstractVM
//
// Made by eddy taiebi
// Login   <taiebi_e@epitech.net>
//
// Started on  Tue Feb 12 15:24:52 2013 eddy taiebi
// Last update Mon Jun  3 21:07:43 2013 eddy taiebi
//

#ifndef						UTIL_HPP_
# define					UTIL_HPP_

# include					<string>
# include					<sstream>
# include					<iomanip>

namespace					Util
{
  template<typename T>
  std::string				toString(T a)
  {
    std::ostringstream		oss;

    oss << a;
    return (oss.str());
  }

  template<typename T>
  T							fromString(const std::string& str)
  {
    std::istringstream		iss(str);
    T						val;

    iss >> val;
    return (val);
  }

  template<typename T>
  std::string				toHex(T a)
  {
	  std::ostringstream	oss;

	  oss << std::hex << std::uppercase << a;
	  return (oss.str());
  }

  template<typename T>
  T							fromHex(const std::string& str)
  {
	  std::istringstream	iss(str);
	  T						val;

	  iss >> std::hex >> val;
	  return (val);
  }

  template<typename T>
  std::string				toOct(T a)
  {
	  std::ostringstream	oss;

	  oss << std::oct << a;
	  return (oss.str());
  }

  template<typename T>
  T							fromOct(const std::string& str)
  {
	  std::istringstream	iss(str);
	  T						val;

	  iss >> std::oct >> val;
	  return (val);
  }

  template<typename T>
  std::string				format(char c, unsigned int nb, T a)
  {
	  std::ostringstream	oss;

	  oss << std::setfill(c) << std::setw(nb) << a;
	  return (oss.str());
  }

  std::string&				replace(std::string&, const std::string&, const std::string&);
  bool						isEqual(const std::string&, const std::string&);
  std::string				getBetween(const std::string&, const std::string&, const std::string&);
  std::string				getNext(std::string&, const std::string&);
}

#endif
