#ifndef STATICOBJECT_HPP
#define STATICOBJECT_HPP

namespace segment_d1
{
////////////////////////////////////////////////////////////
/// \brief Mother class for static classes
///
////////////////////////////////////////////////////////////
class StaticObject
{
public:
    StaticObject() = delete;
    StaticObject(const StaticObject &rhs) = delete;
    StaticObject(StaticObject &&rhs) = delete;
    StaticObject &operator=(const StaticObject &rhs) = delete;
    StaticObject &operator=(StaticObject &&rhs) = delete;
    ~StaticObject() = delete;
};

} // namespace segment_d1

#endif // STATICOBJECT_HPP
