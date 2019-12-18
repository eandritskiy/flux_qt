#ifndef FLUX_QT_ACTION_H
#define FLUX_QT_ACTION_H
#include <type_traits>
#include <utility>
#include <QVariant>
namespace flux_qt
{
template<typename E>
using is_scoped_enum = std::integral_constant<bool, std::is_enum<E>::value && !std::is_convertible<E, int>::value>;
class Action final
{
public:
    template <class ScopedEnum, typename std::enable_if<is_scoped_enum<ScopedEnum>::value>::type* = nullptr>
    Action(ScopedEnum type, QVariant& payload, bool error = false)
        : type_(static_cast<int>(type)), payload_(payload), error_(error)
    {
    }
    template <class ScopedEnum, typename std::enable_if<is_scoped_enum<ScopedEnum>::value>::type* = nullptr>
    Action(ScopedEnum type, QVariant&& payload = QVariant(), bool error = false)
        : type_(static_cast<int>(type)), payload_(std::move(payload)), error_(error)
    {
    }
    Action(const Action&) = default;
    Action(Action&&) = default;
    Action& operator=(const Action&) = default;
    Action& operator=(Action&&) = default;
    ~Action() = default;
    template <class ScopedEnum, typename std::enable_if<is_scoped_enum<ScopedEnum>::value>::type* = nullptr>
    ScopedEnum getType() const
    {
        return static_cast<ScopedEnum>(type_);
    }
    template<class T>
    T getPayload() const
    {
        return qvariant_cast<T>(payload_);
    }
    bool getError() const
    {
        return error_;
    }
private:
    int type_;
    QVariant payload_;
    bool error_;
};
}
#endif
