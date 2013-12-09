//
// AObject.hh for gdl in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon May  6 17:46:09 2013 martin lequeux-gruninger
// Last update Wed Nov 13 10:30:46 2013 martin lequeux-gruninger
//

#ifndef			VECTOR3_HPP_
# define		VECTOR3_HPP_

# include		<math.h>

namespace	My
{
  template <typename T>
  class Vector3
  {
  public:
    T				x;
    T				y;
    T				z;

    Vector3(void)
      : x(0), y(0), z(0) {}

    Vector3(T x, T y, T z)
      : x(x), y(y), z(z) {}

    Vector3(const Vector3 &v)
      : x(v.x), y(v.y), z(v.z) {}

    Vector3(const Vector3 &from, const Vector3 &to)
      : x(to.x - from.x), y(to.y - from.y), z(to.z - from.z) {}

    void				setValues(T x, T y, T z)
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    Vector3&			operator=(const Vector3 &v)
    {
      if (this != &v)
	{
	  this->x = v.x;
	  this->y = v.y;
	  this->z = v.z;
	}
      return (*this);
    }

    bool		       	operator==(const Vector3&v) const
    {
      return (this->x == v.x && this->y == v.y && this->z == v.z);
    }

    bool		       	operator!=(const Vector3 &v) const
    {
      return (this->x != v.x || this->y != v.y || this->z != v.z);
    }

    bool		       	operator<(const Vector3 &v) const
    {
      float me = 1.0/2.0 * (this->x + this->y) * (this->x + this->y + 1) + this->y;
      float other= 1.0/2.0 * (v.x + v.y) * (v.x + v.y + 1) + v.y;

      return (me < other);
    }

    bool		       	operator>(const Vector3 &v) const
    {
      float me = 1.0/2.0 * (this->x + this->y) * (this->x + this->y + 1) + this->y;
      float other= 1.0/2.0 * (v.x + v.y) * (v.x + v.y + 1) + v.y;

      return (me > other);
    }

    Vector3&			operator+=(const Vector3 &v)
    {
      if (this != &v)
	{
	  this->x += v.x;
	  this->y += v.y;
	  this->z += v.z;
	}
      return (*this);
    }

    Vector3			operator+(const Vector3 &v) const
    {
      Vector3	t(*this);

      t += v;
      return (t);
    }

    Vector3&			operator-=(const Vector3 &v)
    {
      if (this != &v)
	{
	  this->x -= v.x;
	  this->y -= v.y;
	  this->z -= v.z;
	}
      return (*this);
    }

    Vector3			operator-(const Vector3 &v) const
    {
      Vector3	t(*this);

      t -= v;
      return (t);
    }

    Vector3			operator-(T v) const
    {
      Vector3	t;

      t.x = (this->x - v);
      t.y = (this->y - v);
      t.z = (this->z - v);

      return (t);
    }

    Vector3&			operator*=(const T v)
    {
      this->x *= v;
      this->y *= v;
      this->z *= v;
      return (*this);
    }

    Vector3			operator*(const T v) const
    {
      Vector3	t(*this);

      t *= v;
      return (t);
    }

    Vector3&			operator/=(const T v)
    {
      if (v != 0.0)
	{
	  this->x /= v;
	  this->y /= v;
	  this->z /= v;
	}
      return (*this);
    }

    Vector3			operator/(const T v) const
    {
      Vector3	t(*this);

      t /= v;
      return (t);
    }

    Vector3			crossProduct(const Vector3 &v) const
    {
      Vector3	t;

      t.x = (this->y * v.z) - (this->z * v.y);
      t.y = (this->z * v.x) - (this->x * v.z);
      t.z = (this->x * v.y) - (this->y * v.x);
      return (t);
    }

    double			dotProduct(const Vector3 &v) const
    {
      return ((this->x * v.x) + (this->y * v.y) + (this->z * v.z));
    }

    double			length() const
    {
      return (sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z)));
    }

    int				distance(const Vector3 &v) const
    {
      return (sqrt(((int)((int)v.x - (int)this->x) * ((int)v.x - (int)this->x)) +
		   ((int)((int)v.z - (int)this->z) * ((int)v.z - (int)this->z))));
    }

    Vector3&			normalize()
    {
      double	lenght_tmp = this->length();

      if (lenght_tmp != 0.0)
	(*this) /= lenght_tmp;
      return (*this);
    }
  };

  typedef Vector3<unsigned int>		Vector3u;
  typedef Vector3<int>			Vector3i;
  typedef Vector3<float>		Vector3f;
  typedef Vector3<double>		Vector3d;
}

#endif			/* !VECTOR_HH_ */
