#include		<iostream>
#include		<stdexcept>
#include		"Packet.h"
#include		"Util.hpp"

Packet::Packet(unsigned short requestUID, unsigned char instruction)
{
	this->_magicNumber = Packet::MAGIC_NUMBER;
	this->_requestUID = requestUID;
	this->_instruction = instruction;
	this->_dataSize = 0;
	this->_format = "";
	this->_data = 0;
	this->_serialization = 0;
	this->_actualDataSize = 0;
}

Packet::~Packet()
{
	if (this->_serialization != 0)
		delete[] this->_serialization;
}

void		Packet::setMagicNumber(unsigned int magicNumber)
{
	this->_magicNumber = magicNumber;
}

void		Packet::setRequestUID(unsigned short requestUID)
{
	this->_requestUID = requestUID;
}

void		Packet::setInstruction(unsigned char instruction)
{
	this->_instruction = instruction;
}

void		Packet::setDataSize(unsigned int dataSize)
{
	this->_dataSize = dataSize;
}

void		Packet::setFormat(const std::string& format)
{
	this->_format = format;
}

void		Packet::setData(char *data)
{
	this->_data = data;
}

unsigned int		Packet::getMagicNumber() const
{
	return (this->_magicNumber);
}

unsigned short		Packet::getRequestUID() const
{
	return (this->_requestUID);
}

unsigned char		Packet::getInstruction() const
{
	return (this->_instruction);
}

unsigned int			Packet::getDataSize() const
{
	return (this->_dataSize);
}

const std::string&		Packet::getFormat() const
{
	return (this->_format);
}

char		*Packet::getData() const
{
	return (this->_data);
}

void		Packet::updateData(unsigned int size)
{
	char	*tmp;

	if (this->_data == 0)
	{
		this->_data = size == 0 ? 0 : new char[size];
		size += this->_format.size() + 2;
		this->_dataSize = size;
		return;
	}
	tmp = size == 0 ? 0 : new char[size];
	if (size != 0)
	{
		LibC::memcpy(tmp, this->_data, this->_dataSize - this->_format.size() - 2);
		delete[] this->_data;
		size += this->_format.size() + 2;
	}
	this->_data = tmp;
	this->_dataSize = size;
}

void			Packet::deserialize(char *packet)
{
	this->header(packet);
	this->format(packet);
	if (this->_dataSize > 0)
	{
		if (this->_data != 0)
			delete[] this->_data;
		this->_data = new char[this->_dataSize - this->_format.size() - 2];
		LibC::memcpy(this->_data, packet + Packet::HEADER_SIZE + 2 + this->_format.size(), this->_dataSize - this->_format.size() - 2);
	}
}

char				*Packet::serialize()
{
	char			*tmp;
	unsigned int	formatSize;

	if (this->_serialization != 0)
		delete[] this->_serialization;
	this->_serialization = new char[this->size()];
	tmp = reinterpret_cast<char *>(&this->_magicNumber);
	this->_serialization[0] = tmp[0];
	this->_serialization[1] = tmp[1];
	this->_serialization[2] = tmp[2];
	tmp = reinterpret_cast<char *>(&this->_requestUID);
	this->_serialization[3] = tmp[0];
	this->_serialization[4] = tmp[1];
	tmp = reinterpret_cast<char *>(&this->_instruction);
	this->_serialization[5] = tmp[0];
	tmp = reinterpret_cast<char *>(&this->_dataSize);
	this->_serialization[6] = tmp[0];
	this->_serialization[7] = tmp[1];
	this->_serialization[8] = tmp[2];
	if (this->_dataSize > 0)
	{
		formatSize = this->_format.size();
		tmp = reinterpret_cast<char *>(&formatSize);
		this->_serialization[9] = tmp[0];
		this->_serialization[10] = tmp[1];
		LibC::memcpy(this->_serialization + Packet::HEADER_SIZE + 2, this->_format.c_str(), this->_format.size());
		if (this->_data != 0)
			LibC::memcpy(this->_serialization + Packet::HEADER_SIZE + 2 + this->_format.size(), this->_data, this->_dataSize - this->_format.size() - 2);
	}
	return (this->_serialization);
}

void					Packet::header(char *packet)
{
	union				uConvert
	{
		unsigned int	size;
		char			tab[3];
	}					convert;

	convert.size = 0;
	convert.tab[0] = *reinterpret_cast<const char *>(packet + Packet::MAGIC_NUMBER_INDEX);
	convert.tab[1] = *reinterpret_cast<const char *>(packet + Packet::MAGIC_NUMBER_INDEX + 1);
	convert.tab[2] = *reinterpret_cast<const char *>(packet + Packet::MAGIC_NUMBER_INDEX + 2);
	this->_magicNumber = convert.size;
	this->_requestUID = *reinterpret_cast<const unsigned short *>(packet + Packet::REQUEST_UID_INDEX);
	this->_instruction = *reinterpret_cast<const unsigned char *>(packet + Packet::INSTRUCTION_INDEX);
	convert.size = 0;
	convert.tab[0] = *reinterpret_cast<const char *>(packet + Packet::DATA_SIZE_INDEX);
	convert.tab[1] = *reinterpret_cast<const char *>(packet + Packet::DATA_SIZE_INDEX + 1);
	convert.tab[2] = *reinterpret_cast<const char *>(packet + Packet::DATA_SIZE_INDEX + 2);
	this->_dataSize = convert.size;
}

void				Packet::format(char *packet)
{
	char			tmp;
	unsigned short	size;
	
	if (this->_dataSize == 0)
		return;
	size = *reinterpret_cast<const unsigned short *>(packet + Packet::DATA_SIZE_INDEX + 3);
	tmp = packet[Packet::DATA_SIZE_INDEX + 3 + 2 + size];
	packet[Packet::DATA_SIZE_INDEX + 3 + 2 + size] = '\0';
	this->_format = std::string(packet + Packet::DATA_SIZE_INDEX + 3 + 2);
	packet[Packet::DATA_SIZE_INDEX + 3 + 2 + size] = tmp;
}

unsigned int	Packet::size() const
{
	return (Packet::HEADER_SIZE + this->_dataSize);
}

bool				Packet::consumeFormat(unsigned int *pos, unsigned int index) const
{
	unsigned int	i;
	std::string		listFormat;

	for (i = 0; *pos < this->_format.size() && i < index; ++i)
	{
		if (this->_format[i] == 'c')
			*pos += 3;
		else if (this->_format[i] == 's')
			this->getStringInData(pos);
		else if (this->_format[i] == 'l')
		{
			this->getListInData(pos);
			if (i < index)
			{
				//std::cout << "index = " << index << std::endl;
				listFormat = this->_format.substr(i + 1);
				index -= (listFormat.size() - 1);
				//std::cout << "listFormat = " << listFormat << ", i = " << i << ", index = " << index << std::endl;
				for (i = 0; i < index; ++i)
				{
					if (listFormat[i % listFormat.size()] == 'c')
						*pos += 3;
					else if (listFormat[i % listFormat.size()] == 's')
						this->getStringInData(pos);
					//std::cout << "listFormat[" << i % listFormat.size() << "] = " << listFormat[i % listFormat.size()] << std::endl;
				}
				break;
			}
		}
		//std::cout << "this->_format[" << i << "] = " << this->_format[i] << std::endl;
	}
	return (i == index);
}

std::string			Packet::getStringInData(unsigned int *pos) const
{
	std::string		str;
	unsigned short	size;
	char			tmp;

	if (*pos + 4 <= this->_dataSize)
		size = *reinterpret_cast<unsigned short *>(this->_data + *pos + 2);
	else
		throw std::out_of_range("Error : not found");
	if (*pos + 4 + size <= this->_dataSize)
	{
		tmp = this->_data[*pos + 4 + size];
		this->_data[*pos + 4 + size] = 0;
		str = std::string(this->_data + *pos + 4);
		this->_data[*pos + 4 + size] = tmp;
		*pos += 4 + size;
	}
	return (str);
}

unsigned short		Packet::getListInData(unsigned int *pos) const
{
	unsigned short	size;

	if (*pos + 4 <= this->_dataSize)
	{
		size = *reinterpret_cast<unsigned short *>(this->_data + *pos + 2);
		*pos += 4;
	}
	else
		throw std::out_of_range("Error : not found");
	return (size);
}

char					Packet::getChar(unsigned int index) const
{
	unsigned int		pos = 0;

	return (this->consumeFormat(&pos, index) ? this->_data[pos + 2] : 0);
}

std::string				Packet::getString(unsigned int index) const
{
	unsigned int		pos = 0;

	return (this->consumeFormat(&pos, index) ? this->getStringInData(&pos) : "");
}

unsigned short			Packet::getList(unsigned int index, std::string& format) const
{
	unsigned int		pos = 0;
	unsigned short		size = 0;

	if (this->consumeFormat(&pos, index))
		size = this->getListInData(&pos);
	format = this->_format.substr(index + 1);
	return (size);
}

void					Packet::appendToData(short id, const std::string& data)
{
	union				uConvert
	{
		short			data;
		char			tab[2];
	}					convert;

	convert.data = data.size();
	LibC::memcpy(this->_data + this->_actualDataSize, &id, 2);
	LibC::memcpy(this->_data + this->_actualDataSize + 2, convert.tab, 2);
	LibC::memcpy(this->_data + this->_actualDataSize + 4, data.c_str(), data.size());
	this->_actualDataSize += 4 + data.size();
}

void					Packet::appendToData(short id, const char *str)
{
	std::string			data;
	union				uConvert
	{
		short			data;
		char			tab[2];
	}					convert;

	data = std::string(str);
	convert.data = data.size();
	LibC::memcpy(this->_data + this->_actualDataSize, &id, 2);
	LibC::memcpy(this->_data + this->_actualDataSize + 2, convert.tab, 2);
	LibC::memcpy(this->_data + this->_actualDataSize + 4, data.c_str(), data.size());
	this->_actualDataSize += 4 + data.size();
}

void				Packet::show()
{
	unsigned char	*str;
	std::string		format;
	unsigned short	size;

	std::cout << std::endl << "***PACKET***" << std::endl;
	str = (unsigned char *)this->serialize();
	for (unsigned int i = 0; i < this->size(); ++i)
	{
		std::cout << Util::format<const std::string&>('0', 2, Util::toHex<unsigned int>(str[i])) << " ";
	}
	std::cout << std::endl << "Magic Number = 0x" << Util::toHex(this->_magicNumber) << std::endl;
	std::cout << "Request UID = " << this->_requestUID << std::endl;
	std::cout << "Instruction = " << (unsigned int)this->_instruction << std::endl;
	std::cout << "Data Size = " << this->_dataSize << std::endl;
	std::cout << "Format = " << this->_format.c_str() << std::endl;
	std::cout << "Size = " << this->size() << std::endl << std::endl;
	for (unsigned int i = 0; i < this->_format.size(); ++i)
	{
		std::cout << "id = " << i << " : [";
		if (this->_format[i] == 'c')
			std::cout << (unsigned int)this->getChar(i) << "]" << std::endl;
		else if (this->_format[i] == 's')
			std::cout << this->getString(i).c_str() << "]" << std::endl;
		else if (this->_format[i] == 'l')
		{
			size = this->getList(i, format);
			std::cout << size << "]" << std::endl << "LIST" << std::endl;
			++i;
			for (unsigned int j = 0; j < size * format.size(); ++j)
			{
				std::cout << "id = " << (j + i) << " : [";
				if (format[j % format.size()] == 'c')
					std::cout << (unsigned int)this->getChar(j + i) << "]" << std::endl;
				else if (format[j % format.size()] == 's')
					std::cout << this->getString(j + i).c_str() << "]" << std::endl;
			}
			std::cout << "LIST END" << std::endl;
			break;
		}
	}
	std::cout << "***######***" << std::endl << std::endl;
}
