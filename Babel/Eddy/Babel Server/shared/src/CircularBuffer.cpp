#include	"CircularBuffer.hpp"
#include	"LibC.h"

CircularBuffer::CircularBuffer(int size)
: _size(size), _start(0), _end(0), _buff(new char[size])
{}

CircularBuffer::CircularBuffer(const CircularBuffer& other)
: _size(other._size), _start(other._start), _end(other._end),
_buff(new char[_size])
{
	LibC::memcpy(_buff, other._buff, sizeof(char)* _size);
}

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& other)
{
	if (this != &other)
	{
		delete _buff;
		_size = other._size;
		_start = other._start;
		_end = other._end;
		_buff = new char[_size];
		LibC::memcpy(_buff, other._buff, sizeof(char)* _size);
	}
	return (*this);
}

CircularBuffer::~CircularBuffer()
{
	delete _buff;
}

int	CircularBuffer::getReadable() const
{
	int	ret(_end - _start);

	if (ret < 0)
		ret += _size;
	return (ret);
}

int	CircularBuffer::getSize() const
{
	return (_size);
}

bool	CircularBuffer::getLine(std::string& line)
{
	bool	sent(false);
	int	i;

	if (((_start <= _end
		&& memchr(&_buff[_start], '\n', _end - _start))
		|| (_start > _end
		&& (memchr(&_buff[_start], '\n', _size - _start)
		|| memchr(_buff, '\n', _end)))))
	{
		sent = true;
		line.clear();
		i = _start;
		while (_buff[i] != '\n')
		{
			line += _buff[i];
			if (++i >= _size)
				i = 0;
		}
		_start = (i + 1) % _size;
	}
	return (sent);
}