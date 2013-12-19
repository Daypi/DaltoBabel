#include		"Packet.h"
#include		<iostream>

Packet::Packet()
{
	this->_magicNumber = Packet::MAGIC_NUMBER;
	this->_requestUID = 0;
	this->_instruction = 0;
	this->_dataSize = 0;
	this->_format = "";
	this->_data = 0;
	this->_serialization = 0;
	this->_actualDataSize = 0;
}

Packet::Packet(const Packet& packet)
{
}

Packet::~Packet()
{
	if (this->_serialization != 0)
		delete[] this->_serialization;
}

void		Packet::setMagicNumber(unsigned short magicNumber)
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

unsigned short		Packet::getMagicNumber() const
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
		this->_dataSize = size;
		return;
	}
	tmp = size == 0 ? 0 : new char[size];
	if (size != 0)
	{
		memcpy(tmp, this->_data, this->_dataSize);
		delete[] this->_data;
	}
	this->_data = tmp;
	this->_dataSize = size;
}

void			Packet::deserialize(char *packet)
{
	this->header(packet);
	this->format(packet);
	if (this->_data != 0)
		delete[] this->_data;
	this->_data = new char[this->_dataSize];
	memcpy(this->_data, packet + Packet::HEADER_SIZE, this->_dataSize);
}

char			*Packet::serialize()
{
	char	*tmp;

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
	memcpy(this->_serialization + Packet::HEADER_SIZE, this->_format.c_str(), this->_format.size());
	if (this->_data != 0)
		memcpy(this->_serialization + Packet::HEADER_SIZE + this->_format.size(), this->_data, this->_dataSize);
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
	
	size = *reinterpret_cast<const unsigned short *>(packet + Packet::DATA_SIZE_INDEX + 3);
	tmp = packet[Packet::DATA_SIZE_INDEX + 3 + 2 + size];
	packet[Packet::DATA_SIZE_INDEX + 3 + 2 + size] = '\0';
	this->_format = std::string(packet + Packet::DATA_SIZE_INDEX + 3 + 2);
	packet[Packet::DATA_SIZE_INDEX + 3 + 2 + size] = tmp;
}

unsigned int	Packet::size() const
{
	return (Packet::HEADER_SIZE + this->_format.size() + this->_dataSize);
}

bool				Packet::consumeFormat(unsigned int *pos, unsigned int index) const
{
	unsigned int	i;
	unsigned int	listPos;
	std::string		listFormat;

	for (i = 0; i < this->_format.size() && i < index; ++i)
	{
		if (this->_format[i] == 'c')
			*pos += 3;
		else if (this->_format[i] == 's')
			this->getStringInData(pos);
		else if (this->_format[i] == 'l')
			this->getListInData(pos);
		//std::cout << "this->_format[" << i << "] = " << this->_format[i] << std::endl;
	}
	if (i < index)
	{
		listPos = this->_format.find('l');
		if (listPos != std::string::npos)
		{
			listFormat = this->_format.substr(listPos + 1);
			index -= listFormat.size();
			i -= listFormat.size();
			//std::cout << "listFormat = " << listFormat << ", i = " << i << ", index = " << index << std::endl;
			for (; i < index; ++i)
			{
				if (listFormat[i % listFormat.size()] == 'c')
					*pos += 3;
				else if (listFormat[i % listFormat.size()] == 's')
					this->getStringInData(pos);
				//std::cout << "listFormat[" << i % listFormat.size() << "] = " << listFormat[i % listFormat.size()] << std::endl;
			}
		}
	}
	//std::cout << "i = " << i << ", index = " << index << std::endl;
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

char					Packet::getCharInData(unsigned int index) const
{
	unsigned int		pos = 0;

	return (this->consumeFormat(&pos, index) ? this->_data[pos + 2] : 0);
}

std::string				Packet::getStringInData(unsigned int index) const
{
	unsigned int		pos = 0;

	return (this->consumeFormat(&pos, index) ? this->getStringInData(&pos) : "");
}

unsigned short			Packet::getListInData(unsigned int index, std::string& format) const
{
	unsigned int		pos = 0;
	unsigned short		size = 0;

	if (this->consumeFormat(&pos, index))
		size = this->getListInData(&pos);
	format = this->_format.substr(index + 1);
	return (size);
}

template<>
void					Packet::appendToData(short id, const std::string& data)
{
	union				uConvert
	{
		short			data;
		char			tab[2];
	}					convert;

	convert.data = data.size();
	memcpy(this->_data + this->_actualDataSize, &id, 2);
	memcpy(this->_data + this->_actualDataSize + 2, convert.tab, 2);
	memcpy(this->_data + this->_actualDataSize + 4, data.c_str(), data.size());
	this->_actualDataSize += 4 + data.size();
}

template<>
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
	memcpy(this->_data + this->_actualDataSize, &id, 2);
	memcpy(this->_data + this->_actualDataSize + 2, convert.tab, 2);
	memcpy(this->_data + this->_actualDataSize + 4, data.c_str(), data.size());
	this->_actualDataSize += 4 + data.size();
}

void				Packet::show()
{
	unsigned char	*str;
	std::string		format;
	unsigned short	size;

	printf("\n***PACKET***\n");
	str = (unsigned char *)this->serialize();
	for (unsigned int i = 0; i < this->size(); ++i)
	{
		printf("%02X ", str[i]);
	}
	printf("\nMagic Number = 0x%X\n", this->_magicNumber);
	printf("Request UID = %d\n", this->_requestUID);
	printf("Instruction = %d\n", this->_instruction);
	printf("Data Size = %d\n", this->_dataSize);
	printf("Format = %s\n\n", this->_format.c_str());
	for (unsigned int i = 0; i < this->_format.size(); ++i)
	{
		printf("id = %d : [", i);
		if (this->_format[i] == 'c')
			printf("%d]\n", this->getCharInData(i));
		else if (this->_format[i] == 's')
			printf("%s]\n", this->getStringInData(i).c_str());
		else if (this->_format[i] == 'l')
		{
			size = this->getListInData(i, format);
			printf("%d]\nLIST\n", size);
			++i;
			for (unsigned int j = 0; j < size * format.size(); ++j)
			{
				printf("id = %d : [", j + i);
				if (format[j % format.size()] == 'c')
					printf("%d]\n", this->getCharInData(j + i));
				else if (format[j % format.size()] == 's')
					printf("%s]\n", this->getStringInData(j + i).c_str());
			}
			printf("LIST END\n");
			break;
		}
	}
	printf("***######***\n\n");
}