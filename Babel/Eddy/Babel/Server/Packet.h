#pragma once

#include						<string>

class							Packet
{
	unsigned int				_magicNumber;
	unsigned short				_requestUID;
	unsigned char				_instruction;
	unsigned int				_dataSize;
	std::string					_format;
	char						*_data;
	char						*_serialization;
	unsigned int				_actualDataSize;

	std::string					getStringInData(unsigned int *) const;
	unsigned short				getListInData(unsigned int *) const;
	bool						consumeFormat(unsigned int *, unsigned int) const;

public:
	enum						eHeaderIndex
	{
		MAGIC_NUMBER_INDEX = 0,
		REQUEST_UID_INDEX = 3,
		INSTRUCTION_INDEX = 5,
		DATA_SIZE_INDEX = 6,
	};

	static const unsigned int	HEADER_SIZE = 9;
	static const unsigned int	MAGIC_NUMBER = 0xDA170;

	Packet();
	Packet(const Packet&);
	virtual ~Packet();

	void						setMagicNumber(unsigned short);
	void						setRequestUID(unsigned short);
	void						setInstruction(unsigned char);
	void						setDataSize(unsigned int);
	void						setFormat(const std::string&);
	void						setData(char *);

	unsigned short				getMagicNumber() const;
	unsigned short				getRequestUID() const;
	unsigned char				getInstruction() const;
	unsigned int				getDataSize() const;
	const std::string&			getFormat() const;
	char						*getData() const;

	void						deserialize(char *);
	char						*serialize();
	void						header(char *);
	void						format(char *);
	unsigned int				size() const;
	void						updateData(unsigned int);

	char						getCharInData(unsigned int) const;
	std::string					getStringInData(unsigned int) const;
	unsigned short				getListInData(unsigned int, std::string&) const;

	void						show();

	template<typename T>
	void						appendToData(short id, T data)
	{
		union					uConvert
		{
			T					data;
			char				tab[sizeof(T)];
		}						convert;

		convert.data = data;
		memcpy(this->_data + this->_actualDataSize, &id, 2);
		memcpy(this->_data + this->_actualDataSize + 2, convert.tab, sizeof(T));
		this->_actualDataSize += 2 + byteSize;
	}
};

template<>
void					Packet::appendToData(short id, const std::string& data);

template<>
void					Packet::appendToData(short id, const char *data);