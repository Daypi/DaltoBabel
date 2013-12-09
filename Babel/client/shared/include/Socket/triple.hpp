//
// toto.hpp for iMart1n in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Thu Jun  6 21:00:23 2013 martin lequeux-gruninger
// Last update Thu Jun  6 21:01:17 2013 martin lequeux-gruninger
//

#ifndef __TRIPLE
#define __TRIPLE

namespace std
{
  template <class _T1, class _T2, class _T3>

  struct triple {
    _T1 first;
    _T2 second;
    _T3 third;

    triple() : first(_T1()), second(_T2()), third (_T3()) {}
    triple(const _T1& __a, const _T2& __b, const _T3& __c) : first(__a), second(__b), third(__c) {}
    template <class _U1, class _U2, class _U3>
    triple(const triple<_U1, _U2, _U3>& __p) : first(__p.first), second(__p.second), third(__p.third) {}
  };

  template <class _T1, class _T2, class _T3>
  inline bool operator==(const triple<_T1, _T2, _T3>& __x, const triple<_T1, _T2, _T3>& __y)
  {
    return __x.first == __y.first && __x.second == __y.second && __x.third == __y.third;
  }
  template <class _T1, class _T2, class _T3>
  inline bool operator<(const triple<_T1, _T2, _T3>& __x, const triple<_T1, _T2, _T3>& __y)
  {
    return __x.first < __y.first ||
      (!(__y.first < __x.first) && __x.second < __y.second) ||
      ((!(__y.first < __x.first) && !(__y.second < __x.second) && __x.third < __y.third));
  }
  template <class _T1, class _T2, class _T3>
  inline bool operator!=(const triple<_T1, _T2, _T3>& __x, const triple<_T1, _T2, _T3>& __y) {
    return !(__x == __y);
  }
  template <class _T1, class _T2, class _T3>
  inline bool operator>(const triple<_T1, _T2, _T3>& __x, const triple<_T1, _T2, _T3>& __y) {
    return __y < __x;
  }
  template <class _T1, class _T2, class _T3>
  inline bool operator<=(const triple<_T1, _T2, _T3>& __x, const triple<_T1, _T2, _T3>& __y) {
    return !(__y < __x);
  }
  template <class _T1, class _T2, class _T3>
  inline bool operator>=(const triple<_T1, _T2, _T3>& __x, const triple<_T1, _T2, _T3>& __y) {
    return !(__x < __y);
  }
  template <class _T1, class _T2, class _T3>

  inline triple<_T1, _T2, _T3> make_triple(const _T1& __x, const _T2& __y, const _T3& __z)
  {
    return triple<_T1, _T2, _T3>(__x, __y, __z);
  }
}

#endif
