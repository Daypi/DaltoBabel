#pragma		once

# include	<algorithm>
# include	<cstring>
# include	<cstdio>
# include	<string>

class		CircularBuffer
{
public:
  CircularBuffer(int size = 255 * 255);
  CircularBuffer(const CircularBuffer&);
  CircularBuffer&	operator=(const CircularBuffer&);
  ~CircularBuffer();

  template<typename T>
  CircularBuffer&	operator<<(const T&);

  template<typename T>
  bool	operator>>(T&);

  template<typename T>
  void		write(const T* area, int size);

  template<typename T>
  bool		read(T* area, int size);

  template<typename T>
  bool		readNoModify(T* area, int size);

  int		getReadable() const;
  int		getSize() const;
  bool		isEmpty() const;
  bool		isFull() const;

  bool		getLine(std::string& line);

private:
  int		_size;
  int		_start;
  int		_end;
  char*		_buff;
};

template<typename T>
CircularBuffer&	CircularBuffer::operator<<(const T& item)
{
  this->write(&item, sizeof(T));
  return (*this);
}

template<typename T>
bool	CircularBuffer::operator>>(T& item)
{
  return (this->read(&item, sizeof(T)));
}

template<typename T>
void		CircularBuffer::write(const T* area, int size)
{
  int		i(-1);
  const char*	tmp(reinterpret_cast<const char*>(area));

  while (++i < size)
    {
      _buff[_end] = tmp[i];
      _end = (_end + 1) % _size;
      if (_end == _start)
	_start = (_start + 1) % _size;
    }
}

template<typename T>
bool		CircularBuffer::read(T* area, int size)
{
  int		i(-1);
  char*		tmp(reinterpret_cast<char*>(area));

  if (getReadable() >= size)
    while (++i < size)
      {
	tmp[i] = _buff[_start];
	_start = (_start + 1) % _size;
      }
  return (i == -1);
}


template<typename T>
bool		CircularBuffer::readNoModify(T* area, int size)
{
  int		i(-1);
  int		n(_start);
  char*		tmp(reinterpret_cast<char*>(area));

  if (getReadable() >= size)
    while (++i < size)
      {
	tmp[i] = _buff[n];
	n = (n + 1) % _size;
      }
  return (i == -1);
}
