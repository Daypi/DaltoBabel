#pragma once

#include	<sstream>
#include	<map>
#include	<stdexcept>
#include	<cstring>
#include	<iostream>

struct				Position
{
    unsigned char	x;
    unsigned char	_x;
    unsigned char	y;
    unsigned char	_y;
    unsigned char	z;
    unsigned char	_z;
    unsigned char	Tx;
    unsigned char	Ty;
    unsigned char	Vx;
    unsigned char	Vy;
    unsigned short	velocity;
};

class																Packet
{
        unsigned short													_magicNumber;
        unsigned short													_requestUID;
        unsigned char													_group;
        unsigned short													_instruction;
        unsigned int													_dataSize;
        char															*_data;
        char															*_serialization;
        std::map<unsigned char, std::map<unsigned char, std::string> >	_formatServer;
        std::map<unsigned char, std::map<unsigned char, std::string> >	_formatClient;
        std::map<unsigned int, std::pair<const char *, int> >			_received;
        unsigned int													_actualDataSize;

    //	std::string			getStringInData(int *) const;
    //	Position			*getPositionInData(int *) const;
    //	void				consumeFormatServ(int *, int *);
    //	void				consumeFormatCli(int *, int *);

public:
    //	enum				eHeaderIndex
    //	{
    //		MAGIC_NUMBER_INDEX = 0,
    //		REQUEST_UID_INDEX = 2,
    //		GROUP_INDEX = 4,
    //		INSTRUCTION_INDEX = 5,
    //        DATA_SIZE_INDEX = 7
    //	};

    //	static const int	POSITION_SIZE = 10;
    //	static const int	HEADER_SIZE = 10;
    //	static const short	MAGIC_NUMBER = 11235;

    Packet();
    Packet(const Packet&);
    virtual				~Packet();

    //	void				setMagicNumber(unsigned short);
    //	void				setRequestUID(unsigned short);
    //	void				setGroup(unsigned char);
    //	void				setInstruction(unsigned short);
    //	void				setDataSize(unsigned int);
    //	void				setData(char *);

    //	unsigned short		getMagicNumber() const;
    //	unsigned short		getRequestUID() const;
    //	unsigned char		getGroup() const;
    //	unsigned short		getInstruction() const;
    //	unsigned int		getDataSize() const;
    //	char				*getData() const;

    //	void				show();

    //	void				updateData(unsigned int);
    unsigned int		size() const;
    char				*serialize();
    //	void				deserialize(char *);
    //	void				header(char *);
    //	std::string			getStringInDataServ(int);
    //	Position			*getPositionInDataServ(int);
    //	std::string			getStringInDataCli(int);
    //	Position			*getPositionInDataCli(int);

    //	template<typename T, int byteSize = sizeof(T)>
    //	void					appendToData(short id, T data)
    //	{
    //		union				uConvert
    //		{
    //			T				data;
    //			char			tab[byteSize];
    //		}					convert;

    //		convert.data = data;
    //		memcpy(this->_data + this->_actualDataSize, &id, 2);
    //		memcpy(this->_data + this->_actualDataSize + 2, convert.tab, byteSize);
    //		this->_actualDataSize += 2 + byteSize;
    //	}

    //	template<typename T, int byteSize = sizeof(T)>
    //	T						getIntTypeInDataServ(int index)
    //	{
    //		int					curSize = 0;
    //		int					curIdx = 0;
    //		const unsigned char	instruction = (const unsigned char)this->_instruction;
    //		union				uConvert
    //		{
    //			T				data;
    //			char			tab[byteSize];
    //		}					convert;

    //		convert.data = 0;
    //		while (curIdx < index)
    //		{
    //			try
    //			{
    //				this->consumeFormatServ(&curIdx, &curSize);
    //			}
    //			catch (std::exception &e)
    //			{
    //				throw e;
    //				return (convert.data);
    //			}
    //		}
    //		if (curIdx == index)
    //		{
    //			if (this->_formatServer[this->_group][instruction].size() > 0 &&
    //				this->_formatServer[this->_group][instruction][curIdx % this->_formatServer[this->_group][instruction].size()] == '1')
    //			{
    //				convert.tab[0] = this->_data[curSize + 2];
    //			}
    //			else if (this->_formatServer[this->_group][instruction].size() > 0 &&
    //				this->_formatServer[this->_group][instruction][curIdx % this->_formatServer[this->_group][instruction].size()] == '2')
    //			{
    //				convert.tab[0] = this->_data[curSize + 2];
    //				convert.tab[1] = this->_data[curSize + 2 + 1];
    //			}
    //		}
    //		return (convert.data);
    //	}

    //	template<typename T, int byteSize = sizeof(T)>
    //	T						getIntTypeInDataCli(int index)
    //	{
    //		int					curSize = 0;
    //		int					curIdx = 0;
    //		const unsigned char	instruction = (const unsigned char)this->_instruction;
    //		union				uConvert
    //		{
    //			T				data;
    //			char			tab[byteSize];
    //		}					convert;

    //		convert.data = 0;
    //		while (curIdx < index)
    //		{
    //			try
    //			{
    //				this->consumeFormatCli(&curIdx, &curSize);
    //			}
    //			catch (std::exception &e)
    //			{
    //				throw e;
    //				return (convert.data);
    //			}
    //		}
    //		if (curIdx == index)
    //		{
    //			if (this->_formatClient[this->_group][instruction].size() > 0 &&
    //				this->_formatClient[this->_group][instruction][curIdx % this->_formatClient[this->_group][instruction].size()] == '1')
    //			{
    //				convert.tab[0] = this->_data[curSize + 2];
    //			}
    //			else if (this->_formatClient[this->_group][instruction].size() > 0 &&
    //				this->_formatClient[this->_group][instruction][curIdx % this->_formatClient[this->_group][instruction].size()] == '2')
    //			{
    //				convert.tab[0] = this->_data[curSize + 2];
    //				convert.tab[1] = this->_data[curSize + 2 + 1];
    //			}
    //		}
    //		return (convert.data);
    //	}
};

//template<>
//void					Packet::appendToData(short id, const std::string& data);

//template<>
//void					Packet::appendToData(short id, const char *data);

//template<>
//void					Packet::appendToData(short id, const Position& pos);
