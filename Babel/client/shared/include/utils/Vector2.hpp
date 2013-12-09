//
// AObject.hh for gdl in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon May  6 17:46:09 2013 martin lequeux-gruninger
// Last update Wed Nov 13 10:29:02 2013 martin lequeux-gruninger
//

#ifndef			VECTOR2_HPP_
# define		VECTOR2_HPP_

# include		<math.h>

namespace	My
{
  template <typename T>
  class Vector2
  {
  public:
    T				x;
    T				y;

    Vector2(void)
      : x(0), y(0) {}

    Vector2(T x, T y)
      : x(x), y(y) {}

    Vector2(const Vector2 &v)
      : x(v.x), y(v.y) {}

    Vector2(const Vector2 &from, const Vector2 &to)
      : x(to.x - from.x), y(to.y - from.y) {}

    void				setValues(T x, T y)
    {
      this->x = x;
      this->y = y;
    }

    Vector2&			operator=(const Vector2 &v)
    {
      if (this != &v)
	{
	  this->x = v.x;
	  this->y = v.y;
	}
      return (*this);
    }

    bool		       	operator==(const Vector2&v) const
    {
      return (this->x == v.x && this->y == v.y);
    }

    bool		       	operator!=(const Vector2 &v) const
    {
      return (this->x != v.x || this->y != v.y);
    }

    bool		       	operator<(const Vector2 &v) const
    {
      float me = 1.0/2.0 * (this->x + this->y) * (this->x + this->y + 1) + this->y;
      float other= 1.0/2.0 * (v.x + v.y) * (v.x + v.y + 1) + v.y;

      return (me < other);
    }

    bool		       	operator>(const Vector2 &v) const
    {
      float me = 1.0/2.0 * (this->x + this->y) * (this->x + this->y + 1) + this->y;
      float other= 1.0/2.0 * (v.x + v.y) * (v.x + v.y + 1) + v.y;

      return (me > other);
    }

    Vector2&			operator+=(const Vector2 &v)
    {
      if (this != &v)
	{
	  this->x += v.x;
	  this->y += v.y;
	}
      return (*this);
    }

    Vector2			operator+(const Vector2 &v) const
    {
      Vector2	t(*this);

      t += v;
      return (t);
    }

    Vector2&			operator-=(const Vector2 &v)
    {
      if (this != &v)
	{
	  this->x -= v.x;
	  this->y -= v.y;
	}
      return (*this);
    }

    Vector2			operator-(const Vector2 &v) const
    {
      Vector2	t(*this);

      t -= v;
      return (t);
    }

    Vector2			operator-(T v) const
    {
      Vector2	t;

      t.x = (this->x - v);
      t.y = (this->y - v);
      return (t);
    }

    Vector2&			operator*=(const T v)
    {
      this->x *= v;
      this->y *= v;
      return (*this);
    }

    Vector2			operator*(const T v) const
    {
      Vector2	t(*this);

      t *= v;
      return (t);
    }

    Vector2&			operator/=(const T v)
    {
      if (v != 0.0)
	{
	  this->x /= v;
	  this->y /= v;
	}
      return (*this);
    }

    Vector2			operator/(const T v) const
    {
      Vector2	t(*this);

      t /= v;
      return (t);
    }

    Vector2			crossProduct(const Vector2 &v) const
    {
      return (v);
    }

    double			dotProduct(const Vector2 &v) const
    {
      return ((this->x * v.x) + (this->y * v.y));
    }

    double			length() const
    {
      return (sqrt((this->x * this->x) + (this->y * this->y)));
    }

    int				distance(const Vector2 &v) const
    {
      return (sqrt(((int)((int)v.x - (int)this->x) * ((int)v.x - (int)this->x)) +
		   ((int)((int)v.y - (int)this->y) * ((int)v.y - (int)this->y))));
    }

    Vector2&			normalize()
    {
      double	lenght_tmp = this->length();

      if (lenght_tmp != 0.0)
	(*this) /= lenght_tmp;
      return (*this);
    }
  };

  typedef Vector2<unsigned int>		Vector2u;
  typedef Vector2<int>			Vector2i;
  typedef Vector2<float>		Vector2f;
  typedef Vector2<double>		Vector2d;
}

#endif			/* !VECTOR_HH_ */
