#include	<cstring>
#include	"Packet.h"

Packet::Packet()
{
	this->_magicNumber = Packet::MAGIC_NUMBER;
	this->_requestUID = 0;
	this->_group = 0;
	this->_instruction = 0;
	this->_dataSize = 0;
	this->_data = 0;
	this->_serialization = 0;
	this->_actualDataSize = 0;

	this->_formatServer[0][0] = "s";	//login
	this->_formatServer[0][1] = "s";	//chat
	this->_formatServer[0][2] = "";		//update
	this->_formatServer[0][3] = "";		//rooms
	this->_formatServer[0][4] = "";		//server
	this->_formatServer[1][0] = "11sss"; //create
	this->_formatServer[1][1] = "12s";	//join
	this->_formatServer[1][2] = "";		//start
	this->_formatServer[1][3] = "";		//
	this->_formatServer[1][4] = "";		//quit
	this->_formatServer[1][5] = "s";	//chat
	this->_formatServer[1][6] = "";		//logins
	this->_formatServer[2][0] = "";		//score
	this->_formatServer[2][1] = "";		//life
	this->_formatServer[2][2] = "";		//map
	this->_formatServer[3][0] = "11";	//move
	this->_formatServer[3][1] = "1";	//fire
	this->_formatServer[3][2] = "";		//
	this->_formatServer[3][3] = "";		//

	this->_formatClient[0][0] = "1s";	//login
	this->_formatClient[0][1] = "ss";	//chat
	this->_formatClient[0][2] = "";		//update
	this->_formatClient[0][3] = "112sss"; //rooms
	this->_formatClient[0][4] = "s";	//server
	this->_formatClient[1][0] = "1s";	//create
	this->_formatClient[1][1] = "12s";	//join
	this->_formatClient[1][2] = "1s";	//start
	this->_formatClient[1][3] = "";		//end
	this->_formatClient[1][4] = "";		//
	this->_formatClient[1][5] = "ss";	//chat
	this->_formatClient[1][6] = "1s";	//logins
	this->_formatClient[2][0] = "12";	//score
	this->_formatClient[2][1] = "12";	//life
	this->_formatClient[2][2] = "22s";	//map
	this->_formatClient[3][0] = "";		//
	this->_formatClient[3][1] = "1s";	//fire
	this->_formatClient[3][2] = "22p";	//update entities
	this->_formatClient[3][3] = "11";	//update map
}

Packet::Packet(const Packet& packet)
{
	this->_actualDataSize = packet._actualDataSize;
	this->_dataSize = packet._dataSize;
	if (this->_dataSize > 0)
	{
		this->_data = new char[this->_dataSize];
		memcpy(this->_data, packet._data, packet._dataSize);
	}
	else
		this->_data = 0;
	this->_formatClient = packet._formatClient;
	this->_formatServer = packet._formatServer;
	this->_group = packet._group;
	this->_instruction = packet._instruction;
	this->_received = this->_received;
	if (packet.size() > 0)
	{
		this->_serialization = new char[packet.size()];
		memcpy(this->_serialization, packet._serialization, packet.size());
	}
	else
		this->_serialization = 0;
	this->_magicNumber = packet._magicNumber;
	this->_requestUID = packet._requestUID;
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

void		Packet::setGroup(unsigned char group)
{
	this->_group = group;
}

void		Packet::setInstruction(unsigned short instruction)
{
	this->_instruction = instruction;
}

void		Packet::setDataSize(unsigned int dataSize)
{
	this->_dataSize = dataSize;
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

unsigned char		Packet::getGroup() const
{
	return (this->_group);
}

unsigned short		Packet::getInstruction() const
{
	return (this->_instruction);
}

unsigned int			Packet::getDataSize() const
{
	return (this->_dataSize);
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

unsigned int	Packet::size() const
{
	return (Packet::HEADER_SIZE + this->_dataSize);
}

char		*Packet::serialize()
{
	char	*tmp;

	if (this->_serialization != 0)
		delete[] this->_serialization;
	this->_serialization = new char[Packet::HEADER_SIZE + this->_dataSize];
	tmp = reinterpret_cast<char *>(&this->_magicNumber);
	this->_serialization[0] = tmp[0];
	this->_serialization[1] = tmp[1];
	tmp = reinterpret_cast<char *>(&this->_requestUID);
	this->_serialization[2] = tmp[0];
	this->_serialization[3] = tmp[1];
	tmp = reinterpret_cast<char *>(&this->_group);
	this->_serialization[4] = tmp[0];
	tmp = reinterpret_cast<char *>(&this->_instruction);
	this->_serialization[5] = tmp[0];
	this->_serialization[6] = tmp[1];
	tmp = reinterpret_cast<char *>(&this->_dataSize);
	this->_serialization[7] = tmp[0];
	this->_serialization[8] = tmp[1];
	this->_serialization[9] = tmp[2];
	if (this->_data != 0)
		memcpy(this->_serialization + Packet::HEADER_SIZE, this->_data, this->_dataSize);
	return (this->_serialization);
}

void				Packet::deserialize(char *packet)
{
	this->header(packet);
	this->_data = new char[this->_dataSize];
	memcpy(this->_data, packet + Packet::HEADER_SIZE, this->_dataSize);
}

void				Packet::header(char *packet)
{
	union				uConvert
	{
		unsigned int	size;
		char			tab[3];
	}					convert;

	convert.size = 0;
	this->_magicNumber = *reinterpret_cast<const unsigned short *>(packet + Packet::MAGIC_NUMBER_INDEX);
	this->_requestUID = *reinterpret_cast<const unsigned short *>(packet + Packet::REQUEST_UID_INDEX);
	this->_group = *reinterpret_cast<const unsigned char *>(packet + Packet::GROUP_INDEX);
	this->_instruction = *reinterpret_cast<const unsigned short *>(packet + Packet::INSTRUCTION_INDEX);
	convert.tab[0] = *reinterpret_cast<const char *>(packet + Packet::DATA_SIZE_INDEX);
	convert.tab[1] = *reinterpret_cast<const char *>(packet + Packet::DATA_SIZE_INDEX + 1);
	convert.tab[2] = *reinterpret_cast<const char *>(packet + Packet::DATA_SIZE_INDEX + 2);
	this->_dataSize = convert.size;
}

void				Packet::consumeFormatServ(int *curIdx, int *curSize)
{
	const unsigned char instruction = (const unsigned char)(this->_instruction);

	if (this->_formatServer[this->_group][instruction].size() > 0 &&
		this->_formatServer[this->_group][instruction][*curIdx % this->_formatServer[this->_group][instruction].size()] == '1')
	{
		*curIdx += 1;
		*curSize += 3;
	}
	else if (this->_formatServer[this->_group][instruction].size() > 0 &&
		this->_formatServer[this->_group][instruction][*curIdx % this->_formatServer[this->_group][instruction].size()] == '2')
	{
		*curIdx += 1;
		*curSize += 4;
	}
	else if (this->_formatServer[this->_group][instruction].size() > 0 &&
		this->_formatServer[this->_group][instruction][*curIdx % this->_formatServer[this->_group][instruction].size()] == 'p')
	{
		*curIdx += 1;
		*curSize += Packet::POSITION_SIZE + 2;
	}
	else if (this->_formatServer[this->_group][instruction].size() > 0 &&
		this->_formatServer[this->_group][instruction][*curIdx % this->_formatServer[this->_group][instruction].size()] == 's')
	{
		*curIdx += 1;
		this->getStringInData(curSize);
	}
}

void				Packet::consumeFormatCli(int *curIdx, int *curSize)
{
	const unsigned char instruction = (const unsigned char)(this->_instruction);

	if (this->_formatClient[this->_group][instruction].size() > 0 &&
		this->_formatClient[this->_group][instruction][*curIdx % this->_formatClient[this->_group][instruction].size()] == '1')
	{
		*curIdx += 1;
		*curSize += 3;
	}
	else if (this->_formatClient[this->_group][instruction].size() > 0 &&
		this->_formatClient[this->_group][instruction][*curIdx % this->_formatClient[this->_group][instruction].size()] == '2')
	{
		*curIdx += 1;
		*curSize += 4;
	}
	else if (this->_formatClient[this->_group][instruction].size() > 0 &&
		this->_formatClient[this->_group][instruction][*curIdx % this->_formatClient[this->_group][instruction].size()] == 'p')
	{
		*curIdx += 1;
		*curSize += Packet::POSITION_SIZE + 2;
	}
	else if (this->_formatClient[this->_group][instruction].size() > 0 &&
		this->_formatClient[this->_group][instruction][*curIdx % this->_formatClient[this->_group][instruction].size()] == 's')
	{
		*curIdx += 1;
		this->getStringInData(curSize);
	}
}

std::string			Packet::getStringInData(int *currSize) const
{
	std::string		str;
	union			uConvert
	{
		short		size;
		char		tab[2];
	}				convert;

	if (*currSize + 4 <= (int)this->getDataSize())
	{
		convert.tab[0] = this->_data[*currSize + 2];
		convert.tab[1] = this->_data[*currSize + 3];
	}
	else
		throw std::out_of_range("Error : not found");
	if (*currSize + 4 + convert.size <= (int)this->getDataSize())
	{
		char	*res;

		res = new char[convert.size + 1];
		res[convert.size] = 0;
		memcpy(res, this->_data + *currSize + 4, convert.size);
		str = std::string(res);
		delete[] res;
		*currSize += 4 + convert.size;
	}
	return (str);
}

Position			*Packet::getPositionInData(int *currSize) const
{
	Position		*pos;
	union			uConvert
	{
		short		velocity;
		char		tab[2];
	}				convert;

	convert.velocity = 0;
	pos = new Position;
	if (*currSize + 2 + Packet::POSITION_SIZE <= (int)this->getDataSize())
	{
		pos->x = this->_data[*currSize + 2];
		pos->_x = this->_data[*currSize + 2 + 1];
		pos->y = this->_data[*currSize + 2 + 2];
		pos->_y = this->_data[*currSize + 2 + 3];
		pos->Tx = this->_data[*currSize + 2 + 4];
		pos->Ty = this->_data[*currSize + 2 + 5];
		pos->Vx = this->_data[*currSize + 2 + 6];
		pos->Vy = this->_data[*currSize + 2 + 7];
		convert.tab[0] = this->_data[*currSize + 2 + 8];
		convert.tab[0] = this->_data[*currSize + 2 + 9];
		pos->velocity = convert.velocity;
		*currSize += 2 + Packet::POSITION_SIZE;
	}
	return (pos);
}

std::string				Packet::getStringInDataServ(int index)
{
	int					curSize = 0;
	int					curIdx = 0;
	const unsigned char	instruction = (const unsigned char)this->_instruction;

	while (curIdx < index)
	{
		try
		{
			this->consumeFormatServ(&curIdx, &curSize);
		}
		catch (std::exception &e)
		{
			throw e;
			return ("");
		}
	}
	if (curIdx == index)
	{
		if (this->_formatServer[this->_group][instruction].size() > 0 &&
			this->_formatServer[this->_group][instruction][curIdx % this->_formatServer[this->_group][instruction].size()] == 's')
		{
			return (this->getStringInData(&curSize));
		}
	}
	return ("");
}

Position				*Packet::getPositionInDataServ(int index)
{
	int					curSize = 0;
	int					curIdx = 0;
	const unsigned char	instruction = (const unsigned char)this->_instruction;

	while (curIdx < index)
	{
		try
		{
			this->consumeFormatServ(&curIdx, &curSize);
		}
		catch (std::exception &e)
		{
			throw e;
			return (0);
		}
	}
	if (curIdx == index)
	{
		if (this->_formatServer[this->_group][instruction].size() > 0 &&
			this->_formatServer[this->_group][instruction][curIdx % this->_formatServer[this->_group][instruction].size()] == 'p')
		{
			return (this->getPositionInData(&curSize));
		}
	}
	return (0);
}

std::string				Packet::getStringInDataCli(int index)
{
	int					curSize = 0;
	int					curIdx = 0;
	const unsigned char	instruction = (const unsigned char)this->_instruction;

	while (curIdx < index)
	{
		try
		{
			this->consumeFormatCli(&curIdx, &curSize);
		}
		catch (std::exception &e)
		{
			throw e;
			return ("");
		}
	}
	if (curIdx == index)
	{
		if (this->_formatClient[this->_group][instruction].size() > 0 &&
			this->_formatClient[this->_group][instruction][curIdx % this->_formatClient[this->_group][instruction].size()] == 's')
		{
			return (this->getStringInData(&curSize));
		}
	}
	return ("");
}

Position				*Packet::getPositionInDataCli(int index)
{
	int					curSize = 0;
	int					curIdx = 0;
	const unsigned char	instruction = (const unsigned char)this->_instruction;

	while (curIdx < index)
	{
		try
		{
			this->consumeFormatCli(&curIdx, &curSize);
		}
		catch (std::exception &e)
		{
			throw e;
			return (0);
		}
	}
	if (curIdx == index)
	{
		if (this->_formatClient[this->_group][instruction].size() > 0 &&
			this->_formatClient[this->_group][instruction][curIdx % this->_formatClient[this->_group][instruction].size()] == 'p')
		{
			return (this->getPositionInData(&curSize));
		}
	}
	return (0);
}

void				Packet::show()
{
	unsigned char	*str;
	const unsigned char	instruction = (const unsigned char)this->_instruction;

	printf("\n***PACKET***\n");
	str = (unsigned char *)this->serialize();
	for (int i = 0; i < (int)this->size(); ++i)
	{
		printf("%02X ", str[i]);
	}
	printf("\n");
	printf("Magic Number = %d\n", this->_magicNumber);
	printf("Request UID = %d\n", this->_requestUID);
	printf("Group = %d\n", this->_group);
	printf("Instruction = %d\n", this->_instruction);
	printf("Data Size = %d\n", this->_dataSize);
	printf("Format = %s\n", this->_formatServer[this->_group][instruction].c_str());
	printf("***######***\n\n");
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
	union				uConvert
	{
		short			data;
		char			tab[2];
	}					convert;
	std::string			data;

	data = std::string(str);
	convert.data = data.size();
	memcpy(this->_data + this->_actualDataSize, &id, 2);
	memcpy(this->_data + this->_actualDataSize + 2, convert.tab, 2);
	memcpy(this->_data + this->_actualDataSize + 4, data.c_str(), data.size());
	this->_actualDataSize += 4 + data.size();
}

template<>
void					Packet::appendToData(short id, const Position& pos)
{
  memcpy(this->_data + this->_actualDataSize, &id, 2);
  memcpy(this->_data + this->_actualDataSize + 2, &pos.x, 1);
  memcpy(this->_data + this->_actualDataSize + 3, &pos._x, 1);
  memcpy(this->_data + this->_actualDataSize + 4, &pos.y, 1);
  memcpy(this->_data + this->_actualDataSize + 5, &pos._y, 1);
  memcpy(this->_data + this->_actualDataSize + 6, &pos.Tx, 1);
  memcpy(this->_data + this->_actualDataSize + 7, &pos.Ty, 1);
  memcpy(this->_data + this->_actualDataSize + 8, &pos.Vx, 1);
  memcpy(this->_data + this->_actualDataSize + 9, &pos.Vy, 1);
  memcpy(this->_data + this->_actualDataSize + 10, &pos.velocity, 2);
}
